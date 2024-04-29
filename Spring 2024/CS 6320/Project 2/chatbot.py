#! python3
import os
import pickle
from pprint import pprint
from datetime import datetime
import functools
import numpy as np

import nltk
nltk.download('punkt')
nltk.download('stopwords')
nltk.download('sentiwordnet')
from nltk.tokenize import sent_tokenize, word_tokenize
from nltk.corpus import stopwords, sentiwordnet as swn

from vaderSentiment.vaderSentiment import SentimentIntensityAnalyzer

import spacy

import tensorflow as tf
import sklearn
import pandas as pd
import numpy as np

from tensorflow.keras.layers import Input, Dense, Dropout, LayerNormalization
from tensorflow.keras.layers import MultiHeadAttention, Embedding, GlobalAveragePooling1D
from tensorflow.keras.models import Model, Sequential
from tensorflow.keras.preprocessing.sequence import pad_sequences

from sklearn.preprocessing import LabelEncoder
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.model_selection import train_test_split

#### MACHINE LEARNING METHODS

def classification_model(num_features, num_classes):
    model = Sequential()
    model.add(Dense(units=128, activation='relu', input_shape=(num_features,)))
    model.add(Dense(units=64, activation='relu'))
    model.add(Dense(units=num_classes, activation='softmax'))
    model.compile(optimizer='adam', loss='sparse_categorical_crossentropy', metrics=['accuracy'])
    model.summary()

    return model

def train_models(knowledge_base):
    global topics
    topics = sorted(list(knowledge_base.keys()))

    topic_df = pd.DataFrame(
        data=[ ( text, idx ) for idx, text in enumerate(topics) ], 
        columns=['topic', 'label'] 
    )

    trainable_df = pd.DataFrame(
        data=[ ( topic, knowledge_base[topic]) for topic in topics ], 
        columns=['topic', 'text']
    ).explode('text').reset_index(drop=True)

    trainable_df = pd.merge(topic_df, trainable_df, on='topic', how='inner').drop(columns=['topic'])
    trainable_df = pd.concat(
        [
            topic_df.rename(columns={'topic': 'text'}),
            trainable_df
        ],
        ignore_index=True
    )

    global topic_tfidf_vectorizer
    global topic_model

    topic_tfidf_vectorizer = TfidfVectorizer()
    vectorized_data = topic_tfidf_vectorizer.fit_transform(trainable_df['text'])
    trainable_df['vectorized'] = vectorized_data.toarray().tolist()

    max_document_length = trainable_df['vectorized'].apply(len).max()
    trainable_df['vectorized'] = trainable_df['vectorized'].apply(
        lambda x: pad_sequences(
            [x], 
            maxlen=max_document_length, 
            padding='post',
            dtype='float32'
        )[0]
    )

    #classification_model_params
    class_mod_num_classes = len(topics)
    class_mod_num_features = max_document_length
    num_epochs = 100
    batch_size = 8
    topic_model = classification_model(class_mod_num_features, class_mod_num_classes)

    X = np.vstack(trainable_df['vectorized'].to_numpy())
    y = trainable_df['label'].to_numpy()

    #
    random_state = np.random.randint(0, 1000)
    #X_train, X_test, y_train, y_test = train_test_split(
    #    X, y, test_size=0.1, stratify=y, random_state=random_state
    #)

    model_dir = os.path.join(os.getcwd(), 'model')
    class_model_weights_path = os.path.join(model_dir, "classification_model.weights.h5")

    if not os.path.exists(class_model_weights_path):
        # topic_model.fit(
        #     X_train, 
        #     y_train, 
        #     epochs=num_epochs, 
        #     batch_size=batch_size, 
        #     validation_data=(X_test, y_test),
        #     verbose=1
        # )

        topic_model.fit(
             X, 
             y, 
             epochs=num_epochs, 
             batch_size=batch_size, 
             verbose=1,
             validation_split=0.2
        )

        topic_model.save_weights(class_model_weights_path)
    else: topic_model.load_weights(class_model_weights_path)

#### MACHINE LEARNING METHODS

def cosine_similarity(sentence1, sentence2):
    sent1_tokens = word_tokenize(sentence1)
    sent2_tokens = word_tokenize(sentence2)
    sentence_vocab = list(set(sent1_tokens).union(set(sent2_tokens)))

    sent1_vector = np.array([ sent1_tokens.count(word) for word in sentence_vocab ])
    sent2_vector = np.array([ sent2_tokens.count(word) for word in sentence_vocab ])

    num = np.sum(np.multiply(sent1_vector, sent2_vector))
    sent1_vec_norm = np.linalg.norm(sent1_vector)
    sent2_vec_norm = np.linalg.norm(sent2_vector)

    cosine_similarity_score = float(num) / ( float(sent1_vec_norm) * float(sent2_vec_norm) )

    return cosine_similarity_score

def get_formatted_current_date_time():
    curr_date_time = str(datetime.now()).replace(" ", "__")
    curr_date_time = curr_date_time.replace("-", "_")
    curr_date_time = curr_date_time.replace(":", "_")
    curr_date_time = curr_date_time.replace(".", "_")

    return curr_date_time

def write_pickle_file(filename, data_dict):
    with open(filename, "wb") as pickle_file:
        pickle.dump(data_dict, pickle_file)

def read_pickle_file(filename):
    with open(filename, "rb") as pickle_file:
        ngram_dict = pickle.load(pickle_file)
    return ngram_dict

def save_user_model(user_key, curr_user_model):
    user_model.update({
        user_key : curr_user_model
    })
    pprint(user_model)
    write_pickle_file(user_model_path, user_model)

def get_vocabulary(corpus):
    vocabulary = list(map(lambda x: set(corpus[x]['counts'].keys()), corpus.keys()))
    vocabulary = sorted(list(functools.reduce(lambda x, y: x.union(y), vocabulary)))
    return vocabulary

def get_topic_relevant_tokens(response_tokens, vocabulary):
    return ([ 
        response_token
        for response_token in response_tokens
        if response_token in vocabulary
    ])

def is_important_term(term):
    #print(term.text)
    #print(term.pos_)
    #print(( ( term.pos_.lower() == "propn" )  or 
    #         ( term.pos_.lower() == "nn" ) or 
    #         ( term.pos_.lower() == "noun" ) or
    #         ( term.pos_.lower() == "adj" ) ) or
    #         ( term.text in ROMAN_CONSTANTS )
    #    )

    return ( ( term.pos_.lower() == "propn" )  or 
             ( term.pos_.lower() == "nn" ) or 
             ( term.pos_.lower() == "noun" ) or
             ( term.pos_.lower() == "adj" ) or
             ( term.text in ROMAN_CONSTANTS )
           )


def extract_important_terms(response):
    ner_obj = nlp_ner(response)

    key_terms = list(
        map(
            lambda x: str(x.text),
            list(filter(
                lambda x: is_important_term(x),
                ner_obj
            ))
        )
    )

    return key_terms

def sentiment_analysis(sentence):
    analyzer = SentimentIntensityAnalyzer()
    vs = analyzer.polarity_scores(sentence)
    return vs.get('compound')

##### PROMPT METHODS #####

def starting_prompt():
    starting_prompt_str = "\nHello There! My name is Sam.\n"
    starting_prompt_str += "I'm studying to become a Maester at the Citadel in Old Town.\n"
    starting_prompt_str += "I specialize in the history of the great Targaryen House and their "
    starting_prompt_str += "time ruling Westeros,\nbut I may be able to offer information about "
    starting_prompt_str += "other things as well.\n"
    starting_prompt_str += "What's your name?\n\n>"

    exchange = list()
    exchange.append(starting_prompt_str)
    name = input(starting_prompt_str)
    exchange.append(name)

    if not ( user_model.get(name, None) ):
        name_response_str = "\nSeven blessings! It gladdens me to meet you, " + name + ".\n"
        print(name_response_str)
        exchange.append(name_response_str)
    else:
        old_exchange = user_model[name]['chat']
        exchange = old_exchange + exchange
        name_response_str = "\nIndeed, I suspected it was you. My apologies for not immediately recognizing you,\n"
        name_response_str += "but as a maester engrossed in the studies of human afflictions, mystical forces, and\n" 
        name_response_str += "the intricacies of our world, facial recognition often eludes me.\n"
        name_response_str += "Furthermore, I have always struggled with recalling faces, a shortcoming I readily admit.\n"
        name_response_str += "But I digress, let us speak no more of that.\n"

        old_wellbeing = user_model[name]['wellbeing_sentiment']

        if ( old_wellbeing >= 0.05 ): 
            name_response_str += "I recall our last encounter, during which you seemed to be blessed by good fortune.\n"
            name_response_str += "I trust that this trend has persisted in your endeavors since then.\n"
        elif ( ( old_wellbeing > -0.05 ) and ( old_wellbeing < 0.05 ) ): 
            name_response_str += "I recall our previous conversation, where your life seemed marked by tranquility and\n"
            name_response_str += "routine amidst the tumultuous world we inhabit.\n"
            name_response_str += "May fortune continue to smile upon you in these trying times."
        else: 
            name_response_str += "I recall our previous discussion, during which your life appeared fraught with hardship\n"
            name_response_str += "and adversity. I hope the seven have smiled upon you since."

        print(name_response_str)
        exchange.append(name_response_str)

    feeling_prompt_str = "\nHow stands your well-being at present?\n\n>"
    feeling_response_str = input(feeling_prompt_str)
    exchange.append(feeling_prompt_str)
    exchange.append(feeling_response_str)

    sent_analysis_score = sentiment_analysis(feeling_response_str)
    
    return exchange, name, sent_analysis_score

def topic_prompt(knowledge_base):
    topic_prompt_str = "\nOn what subject do you desire enlightenment?\n\n"
    topic_prompt_str += "You may inquire about the following:\n\t"
    topic_prompt_str += ",\n\t".join(knowledge_base.keys())
    topic_prompt_str += "\n\n>"

    exchange = list()
    exchange.append(topic_prompt_str)
    response = input(topic_prompt_str)
    exchange.append(response)

    return exchange, response

def continue_prompt():
    exchange = list()
    continue_prompt_str = "\nDid you still want to continue speaking with me?\n"
    continue_prompt_str += "\t\t(You can type Yes to continue or \n"
    continue_prompt_str += "\t\t You can type No to stop speaking with me. ) \n>"
    will_continue = False

    response = input(continue_prompt_str)
    exchange.append(continue_prompt_str)
    exchange.append(response)

    if ( response.lower() == "yes" ):
        will_continue = True
    elif ( response.lower() == "no" ):
        will_continue = False
    else:
        confusion_str = "\nI beg your pardon, but your words are lost on me,\n"
        confusion_str += "and I am unfamiliar with the tongue you speak.\n"
        confusion_str += "What does " + "`" + response + "` mean exactly?\n"
        print(confusion_str)
        exchange.append(confusion_str)

        new_exchange, new_will_continue = continue_prompt()
        exchange += new_exchange
        return exchange, new_will_continue

    return exchange, will_continue

##### PROMPT METHODS #####

def search_corpus_for_information(corpus, response):
    pertinent_sentences = list(map(lambda x: corpus[x]['sentences'], corpus.keys()))
    pertinent_sentences = list(functools.reduce(lambda x,y: x + y, pertinent_sentences))
    pertinent_sentences = list(filter(lambda x : cosine_similarity(x, response) > 0.0, pertinent_sentences))
    
    return "\n".join(pertinent_sentences)

def search_for_information(corpus, knowledge_base, relevant_tokens):
    information = None
    
    if ( len(relevant_tokens) > 1 ):
        for term in knowledge_base.keys():
            term_parts = [ str(term_part.text) for term_part in nlp_ner(term) ]
            #print(term_parts)
            if all([ token in term_parts for token in relevant_tokens ]):
                return "\n".join(knowledge_base[term])
    else:
        information = search_corpus_for_information(corpus, " ".join(relevant_tokens))

    return information

def predict_topic(response):
    transformed_res = topic_tfidf_vectorizer.transform([response])
    predictions = topic_model.predict(transformed_res)
    return topics[np.argmax(predictions[0])]

def give_information(corpus, knowledge_base, response, exchange):
    #key_terms = extract_important_terms(response)
    #vocabulary = get_vocabulary(corpus)
    #relevant_tokens = get_topic_relevant_tokens(key_terms, vocabulary)

    predicted_topic = predict_topic(response)

    relevant_info_str = "\nIt seems as if you'd like to discuss: \n"
    relevant_info_str += "\t" + predicted_topic
    print(relevant_info_str)
    exchange.append(relevant_info_str)

    #found_info_str = "\nHmm... Here's what I can say about that."
    #found_info_str += "\n\n"

    #information = search_for_information(corpus, knowledge_base, key_terms)

    #if information: 
    #    found_info_str += information

    #print(found_info_str)
    #exchange.append(found_info_str)
    
    #unsure_str = "I possess no knowledge concerning that matter or person."
    #print(unsure_str)
    #exchange.append(unsure_str)

    return exchange

def topic_exchange(corpus, knowledge_base, exchange):
    topic_prompt_exchange, response = topic_prompt(knowledge_base)
    exchange += topic_prompt_exchange
    exchange = give_information(corpus, knowledge_base, response, exchange)

    return exchange

def continue_exchange(exchange):
    cont_prompt_exchange, still_chatting = continue_prompt()
    exchange += cont_prompt_exchange

    return exchange, still_chatting

def introductions(corpus, knowledge_base, exchange):
    first_exchange, name, sentiment_score = starting_prompt()
    exchange += first_exchange

    #positive sentiment: compound score >= 0.05
    #neutral sentiment: (compound score > -0.05) and (compound score < 0.05)
    #negative sentiment: compound score <= -0.05

    if ( sentiment_score >= 0.05 ):
        happiness_str = "\nIt gladdens me to hear that."
        print(happiness_str)
        exchange.append(happiness_str)

        exchange = topic_exchange(corpus, knowledge_base, exchange)
        exchange, still_chatting = continue_exchange(exchange)
        
    elif ( ( sentiment_score > -0.05 ) and ( sentiment_score < 0.05 ) ):
        neutral_str = "\nIt appears fortune smiles upon you, for your existence seems\n"
        neutral_str += "remarkably tranquil amidst the chaos of this realm."
        print(neutral_str)
        exchange.append(neutral_str)

        exchange = topic_exchange(corpus, knowledge_base, exchange)
        exchange, still_chatting = continue_exchange(exchange)

    else:
        sadness_str = "\nI offer my sympathies for your plight. May the Seven watch over you."
        print(sadness_str)
        exchange.append(sadness_str)

        exchange, still_chatting = continue_exchange(exchange)

    return exchange, still_chatting, name, sentiment_score

def chat(corpus, tf_idf, knowledge_base):
    curr_user_model = dict()
    exchange = list()
    name = None
    still_chatting = True

    exchange, still_chatting, name, wellbeing_sentiment = introductions(corpus, knowledge_base, exchange)

    while ( still_chatting ):
        exchange = topic_exchange(corpus, knowledge_base, exchange)
        exchange, still_chatting = continue_exchange(exchange)

    curr_user_model.update({
        'chat' : exchange,
        'name' : name,
        'wellbeing_sentiment' : wellbeing_sentiment,
    })
    
    curr_index = len(user_model.keys())
    save_user_model(
        name, 
        curr_user_model
    )

def main():
    global STOPWORDS
    STOPWORDS = stopwords.words('english')

    CWD = os.getcwd()
    corpus_dir = os.path.join(CWD, 'corpus')
    pickle_corpus_dir = os.path.join(corpus_dir,'pickle')
    chatbot_dir = os.path.join(CWD, 'chatbot')
    model_dir = os.path.join(CWD, 'model')


    if not os.path.exists(chatbot_dir):
        os.mkdir(chatbot_dir)
    
    if not os.path.exists(model_dir):
        os.mkdir(model_dir)
    
    global user_model
    global user_model_path

    user_model_path = os.path.join(chatbot_dir, "user_model.pickle")
    user_model = dict()

    if os.path.exists(user_model_path):
        user_model = read_pickle_file(user_model_path)

    tf_idf = read_pickle_file(os.path.join(pickle_corpus_dir,'tf_idf.pickle'))
    corpus = read_pickle_file(os.path.join(pickle_corpus_dir,'corpus.pickle'))
    knowledge_base = read_pickle_file(os.path.join(pickle_corpus_dir,'knowledge_base.pickle'))

    train_models(knowledge_base)
    chat(corpus, tf_idf, knowledge_base)

if __name__ == "__main__":
    global nlp_ner
    global ROMAN_CONSTANTS
    ROMAN_CONSTANTS = [ "i", "ii", "iii", "iv", "v", "vi", "vii", "viii", "ix", "x"]
    nlp_ner = spacy.load('en_core_web_sm')
    main()

