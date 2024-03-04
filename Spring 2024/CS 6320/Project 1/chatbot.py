#! python3
import os
import pickle
from pprint import pprint

def read_pickle_file(filename):
    with open(filename, "rb") as pickle_file:
        ngram_dict = pickle.load(pickle_file)
    return ngram_dict

def print_statement(knowledge_base):
    prompt_str = "What would you like to talk about today?\n\n"
    prompt_str += "You can ask about the following:\n\t"
    prompt_str += ",\n\t".join(knowledge_base.keys())
    prompt_str += "\n\n>"
    response = input(prompt_str)

def main():

    CWD = os.getcwd()
    corpus_dir = os.path.join(CWD, 'corpus')
    pickle_corpus_dir = os.path.join(corpus_dir,'pickle')

    tf_idf = read_pickle_file(os.path.join(pickle_corpus_dir,'tf_idf.pickle'))
    corpus = read_pickle_file(os.path.join(pickle_corpus_dir,'corpus.pickle'))
    knowledge_base = read_pickle_file(os.path.join(pickle_corpus_dir,'knowledge_base.pickle'))

    #chatting = True

    #while ( chatting ):
    print_statement(knowledge_base)

if __name__ == "__main__":
    main()
