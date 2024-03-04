#! python3
import os
import pickle
from pprint import pprint
from datetime import datetime
import functools

import nltk
nltk.download('punkt')
nltk.download('stopwords')
from nltk.tokenize import sent_tokenize, word_tokenize
from nltk.corpus import stopwords

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

def check_topic_relevance(response_tokens, vocabulary):
    return any([ 
        response_token in vocabulary 
        for response_token in response_tokens 
    ])


def chat(corpus, tf_idf, knowledge_base, user_model):
    prompt_str = "What would you like to talk about today?\n\n"
    prompt_str += "You can ask me about the following:\n\t"
    prompt_str += ",\n\t".join(knowledge_base.keys())
    prompt_str += "\n\n>"

    vocabulary = get_vocabulary(corpus)
    curr_user_model = dict()

    exchange = [ prompt_str ]

    response = input(prompt_str)
    response_tokens = filter(
        lambda x: x not in STOPWORDS, 
        word_tokenize(response)
    )
    exchange.append(response)

    print(response_tokens)
    print(check_topic_relevance(response_tokens, vocabulary))
    
    curr_user_model.update({
        'chat' : exchange
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
    main()

