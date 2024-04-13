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

def save_user_model(user_key, user_model_log, curr_user_model):
    user_model_log.update({
        user_key : curr_user_model
    })
    #pprint(user_model_log)
    write_pickle_file(user_model_path, user_model_log)

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

def starting_prompt():
    starting_exchange_str = "\nHello There! My name is Sam.\n"
    starting_exchange_str += "I'm studying to become a Maester at the Citadel in Old Town.\n"
    starting_exchange_str += "I specialize in the history of the great Targaryen House and their "
    starting_exchange_str += "time ruling Westeros,\nbut I may be able to offer information about "
    starting_exchange_str += "other things as well.\n"
    starting_exchange_str += "What's your name?\n\n>"

    exchange = list()
    exchange.append(starting_exchange_str)
    name = input(starting_exchange_str)
    exchange.append(name)

    bot_response_str = "\nI'm so glad to meet you, " + name + "."
    print(bot_response_str)
    exchange.append(bot_response_str)

    feeling_prompt_str = "\nAre you feeling well today?\n\n>"
    feeling_response_str = input(feeling_prompt_str)
    exchange.append(feeling_prompt_str)
    exchange.append(feeling_response_str)

    sent_analysis_score = sentiment_analysis(feeling_response_str)
    
    return exchange, name, sent_analysis_score

def initial_prompt(knowledge_base):
    initial_prompt_str = "\nWhat would you like to talk about today?\n\n"
    initial_prompt_str += "You can ask me about the following:\n\t"
    initial_prompt_str += ",\n\t".join(knowledge_base.keys())
    initial_prompt_str += "\n\n>"

    exchange = list()
    exchange.append(initial_prompt_str)
    response = input(initial_prompt_str)
    exchange.append(response)

    return exchange, response

def middle_prompt(knowledge_base):
    initial_prompt_str = "\nWhat else would you like to talk about today?\n\n"
    initial_prompt_str += "You can ask me about the following:\n\t"
    initial_prompt_str += ",\n\t".join(knowledge_base.keys())
    initial_prompt_str += "\n\n>"

    exchange = list()
    exchange.append(initial_prompt_str)
    response = input(initial_prompt_str)
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
        confusion_str = "\nI'm afraid I don't speak in that tongue.\n"
        confusion_str += "What does " + "`" + response + "` mean exactly?\n"
        print(confusion_str)
        exchange.append(confusion_str)

        new_exchange, new_will_continue = continue_prompt()
        exchange += new_exchange
        return exchange, new_will_continue

    return exchange, will_continue

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

def give_information(corpus, knowledge_base, response, exchange):
    key_terms = extract_important_terms(response)
    vocabulary = get_vocabulary(corpus)
    relevant_tokens = get_topic_relevant_tokens(key_terms, vocabulary)

    if ( len(relevant_tokens) > 0 ):
        relevant_info_str = "\nCertainly! I'd be happy to discuss those things. \n"
        print(relevant_info_str)
        exchange.append(relevant_info_str)

        found_info_str = "\nHmm... Here's what I can say about that:"
        found_info_str += "\n\n"

        information = search_for_information(corpus, knowledge_base, key_terms)

        if information: 
            found_info_str += information

        print(found_info_str)
        exchange.append(found_info_str)
        
    else:
        unsure_str = "Hmm... I'm unsure about the following topic(s):"
        unsure_str += ",\n\t".join(key_terms)
        print(unsure_str)
        exchange.append(unsure_str)

    return exchange


def chat(corpus, tf_idf, knowledge_base, user_model):
    curr_user_model = dict()
    exchange = list()
    name = None

    starting_exchange, name, sentiment_score = starting_prompt()
    exchange += starting_exchange

    #positive sentiment: compound score >= 0.05
    #neutral sentiment: (compound score > -0.05) and (compound score < 0.05)
    #negative sentiment: compound score <= -0.05

    still_chatting = True

    if ( sentiment_score >= 0.05 ):
        happiness_str = "\nIt gladdens me to hear that."
        print(happiness_str)
        exchange.append(happiness_str)
        
        initial_exchange, response = initial_prompt(knowledge_base)
        exchange += initial_exchange

        exchange = give_information(corpus, knowledge_base, response, exchange)

        cont_prompt_exchange, still_chatting = continue_prompt()
        exchange += cont_prompt_exchange
        
    elif ( ( sentiment_score > -0.05 ) and ( sentiment_score < 0.05 ) ):
        initial_exchange, response = initial_prompt(knowledge_base)
        exchange += initial_exchange

        exchange = give_information(corpus, knowledge_base, response, exchange)

        cont_prompt_exchange, still_chatting = continue_prompt()
        exchange += cont_prompt_exchange

    else:
        sadness_str = "\nThat's unfortunate. I lament your circumstances."
        print(sadness_str)
        exchange.append(sadness_str)

        cont_prompt_exchange, still_chatting = continue_prompt()
        exchange += cont_prompt_exchange

    while ( still_chatting ):
        middle_exchange, response = middle_prompt(knowledge_base)
        exchange += middle_exchange

        exchange = give_information(corpus, knowledge_base, response, exchange)

        cont_prompt_exchange, still_chatting = continue_prompt()
        exchange += cont_prompt_exchange

    curr_user_model.update({
        'chat' : exchange,
        'name' : name,
        'sentiment' : sentiment_score,
    })
    curr_index = len(user_model.keys())
    save_user_model(
        "user" + str(curr_index) + "_" + get_formatted_current_date_time(), 
        user_model, 
        curr_user_model
    )

def main():

    global STOPWORDS
    STOPWORDS = stopwords.words('english')

    CWD = os.getcwd()
    corpus_dir = os.path.join(CWD, 'corpus')
    pickle_corpus_dir = os.path.join(corpus_dir,'pickle')

    chatbot_dir = os.path.join(CWD, 'chatbot')

    if not os.path.exists(chatbot_dir):
        os.mkdir(chatbot_dir)

    global user_model_path

    user_model_path = os.path.join(chatbot_dir, "user_model.pickle")
    user_model = dict()

    if os.path.exists(user_model_path):
        user_model = read_pickle_file(user_model_path)

    tf_idf = read_pickle_file(os.path.join(pickle_corpus_dir,'tf_idf.pickle'))
    corpus = read_pickle_file(os.path.join(pickle_corpus_dir,'corpus.pickle'))
    knowledge_base = read_pickle_file(os.path.join(pickle_corpus_dir,'knowledge_base.pickle'))

    chat(corpus, tf_idf, knowledge_base, user_model)

if __name__ == "__main__":
    global NER
    global ROMAN_CONSTANTS
    ROMAN_CONSTANTS = [ "i", "ii", "iii", "iv", "v", "vi", "vii", "viii", "ix", "x"]
    nlp_ner = spacy.load('en_core_web_md')
    main()

