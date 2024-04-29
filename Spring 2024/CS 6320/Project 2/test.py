#! python3

import pickle
import os

from pprint import pprint

def write_pickle_file(filename, data_dict):
    with open(filename, "wb") as pickle_file:
        pickle.dump(data_dict, pickle_file)

def read_pickle_file(filename):
    with open(filename, "rb") as pickle_file:
        ngram_dict = pickle.load(pickle_file)
    return ngram_dict

def main():
    CWD = os.getcwd()
    corpus_dir = os.path.join(CWD, 'corpus')
    chatbot_dir= os.path.join(CWD, 'chatbot')

    pickle_corpus_dir = os.path.join(corpus_dir,'pickle')

    knowledge_base = read_pickle_file(os.path.join(pickle_corpus_dir, "knowledge_base.pickle"))
    chats = read_pickle_file(os.path.join(chatbot_dir, "user_model.pickle"))

    pprint(knowledge_base)
    
    #for term in knowledge_base.keys():
    #    print("\n\n")
    #    print("Term: ", term)
    #    print("\n\n")
    #    print("\n".join(knowledge_base[term][:10]))"""

    #for user in chats.keys():
    #    pprint({
    #        "key" : user,
    #        "name" : chats[user]['name'],
    #        "sentiment": chats[user]['sentiment'],
    #        "chat" : "truncated for space saving purposes"
    #    })



main()

