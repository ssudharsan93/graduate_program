#! python3

import urllib
from urllib import request, error, parse, robotparser
from bs4 import BeautifulSoup
import sys
import requests
from collections import deque, Counter
import functools
import os
import re
import pickle

import nltk
nltk.download('punkt')
nltk.download('stopwords')
from nltk.tokenize import sent_tokenize, word_tokenize
from nltk.corpus import stopwords

import sklearn
from sklearn.feature_extraction.text import TfidfVectorizer,CountVectorizer

import numpy as np
import math
from pprint import pprint

############ KNOWLEDGE BASE METHODS ##############
def pickle_data_dictionary(filename, data_dict):
    with open(filename, "wb") as pickle_file:
        pickle.dump(data_dict, pickle_file)

def get_best_matching_corpus_file(corpus_dict, tf_idf_dict, keyword):
    tokens = word_tokenize(keyword)
    counts = dict([
        ( corpus_file, 
            functools.reduce(
                lambda x, y: x + y,
                [ 
                    corpus_dict[corpus_file]['counts'].get(token, 0)
                    for token in tokens 
                ] 
            )
        )
        for corpus_file in tf_idf_dict.keys()
    ])

    tf_idf_scores = dict([
        ( corpus_file, 
            functools.reduce(
                lambda x, y: x * y,
                [ 
                    tf_idf_dict[corpus_file].get(token, 1) 
                    for token in tokens 
                ] 
            )
        )
        for corpus_file in tf_idf_dict.keys()
    ])

    best_match_scores = {
        corpus_file : counts[corpus_file] * tf_idf_scores[corpus_file] 
        for corpus_file in tf_idf_dict.keys() 
    }

    #print(keyword)
    #print("\n")
    #print(sorted(list(counts.items()), key=lambda x: x[1], reverse=True))
    #print("\n")
    #print(sorted(list(tf_idf_scores.items()), key=lambda x: x[1], reverse=True))
    best_match = sorted(list(best_match_scores.items()), key=lambda x: x[1], reverse=True)[0][0]

    return best_match

def build_knowledge_base(corpus_dict, tf_idf_dict, keywords):
    knowledge_base_dict = dict()
    
    for keyword in keywords:
        best_match_corpus_file = get_best_matching_corpus_file(corpus_dict, tf_idf_dict, keyword)
        knowledge_base_dict[keyword] = corpus_dict[best_match_corpus_file]['sentences']
        
        #print("\n")
        #print(keyword)
        #print(best_match_corpus_file)
        #
        #print("\n")
        #print(knowledge_base_dict[keyword])
    
    return knowledge_base_dict

############ KNOWLEDGE BASE METHODS ##############

############ COUNTS / IMPORTANT TERMS METHODS ##############
def get_top_twenty_five_terms(tf_idf_dict):
    tf_idf_scores = list( functools.reduce(
            lambda x, y: x + y,
            [ 
                list(tf_idf_dict.get(corpus_file).items())
                for corpus_file in tf_idf_dict.keys() 
            ] 
        )
    )

    sorted_tf_idf_scores = sorted(
        tf_idf_scores, 
        key=lambda x: x[1],
        reverse=True
    )

    top_terms = list(map(lambda x: x[0], sorted_tf_idf_scores))
    top_twenty_five_terms = list()

    index = 0
    while ( len(top_twenty_five_terms) < 25 ):
        if ( top_terms[index] not in top_twenty_five_terms ):
            top_twenty_five_terms.append(top_terms[index])
        index += 1

    return top_twenty_five_terms

def is_valid_sentence(sentence):
    format_matched = re.search(r'[^\r\n\t]+[.!]$', sentence, re.A) is not None
    special_char_found = re.search(r'[\|]', sentence, re.A) is not None

    return ( ( format_matched ) and ( not special_char_found ) )

def is_valid_token(token):
    is_not_stop_word = token not in STOPWORDS
    is_alpha = token.isalpha()
    return ( is_not_stop_word and is_alpha )

def extract_idf(corpus_dict, vocabulary):
    num_documents = len(corpus_dict.keys())
    N = 1 + num_documents
    doc_appearance_freqs = np.array([  
        float( sum(list(map( 
            lambda x: int( ( corpus_dict[x]['counts'].get(word, 0) != 0 ) ), 
            corpus_dict.keys()
        ))) + 1.0 )
        for word in vocabulary 
    ])

    doc_appearance_freqs = np.power(doc_appearance_freqs, -1)
    idf_values = np.log( N * doc_appearance_freqs )

    return idf_values.tolist()

def extract_tf(corpus_file_dict, vocabulary):
    tf_values = ( 1.0 / float(corpus_file_dict['num_tokens']) ) * \
                np.array( [ float(corpus_file_dict['counts'].get(word, 0)) for word in vocabulary ] )
    return tf_values.tolist()

def extract_tfidf_scores(corpus_dict):
    vocabulary = list(map(lambda x: set(corpus_dict[x]['counts'].keys()), corpus_dict.keys()))
    vocabulary = sorted(list(functools.reduce(lambda x, y: x.union(y), vocabulary)))
    idf_array = np.array(extract_idf(corpus_dict, vocabulary))

    tf_idf_dict = dict()

    for corpus_file in corpus_dict.keys():
        tf_array = np.array(extract_tf(corpus_dict[corpus_file], vocabulary))
        tf_idf_array = np.multiply(tf_array, idf_array)
        tf_idf_dict[corpus_file] = dict(zip(vocabulary, tf_idf_array))

    return tf_idf_dict

def extract_counts(tokens):
    return dict(Counter(tokens))

def extract_tokens(sentences):
    tokens = list()
    for sentence in sentences:
        tokens = tokens + word_tokenize(sentence.lower())
    tokens = list(filter(is_valid_token, tokens))

    return tokens

def extract_valid_sentences(content):
    sentences = sent_tokenize(content)
    sentences = list( 
        functools.reduce(
            lambda x, y: x + y,
            [ sentence.split("\n") for sentence in sentences ] 
        )
    )
    sentences = list(filter(is_valid_sentence, sentences))
    
    return sentences

def read_clean_corpus_file(clean_corpus_file):
    with open(clean_corpus_file, "r+") as corpus_fd:
        content = corpus_fd.read()
    return content

def make_corpus_dictionaries():
    clean_corpus_dir = os.path.join(CWD, 'corpus','clean')
    clean_corpus_files = os.listdir(clean_corpus_dir)

    corpus_dict = dict()

    for clean_corpus_file in clean_corpus_files:
        clean_corpus_file_path = os.path.join(clean_corpus_dir, clean_corpus_file)
        content = read_clean_corpus_file(clean_corpus_file_path)

        sentences = extract_valid_sentences(content)
        tokens = extract_tokens(sentences)
        counts = extract_counts(tokens)        

        corpus_dict.update(
            {
                clean_corpus_file : {
                    'sentences' : sentences,
                    'counts' : counts,
                    'num_tokens' : len(tokens)
                }
            }
        )
    
    tf_idf_dict = extract_tfidf_scores(corpus_dict)

    return ( corpus_dict, tf_idf_dict )

############ COUNTS / IMPORTANT TERMS METHODS ##############

############ FILE CLEANING METHODS ##############
def clean_raw_files(content):
    content = content.replace("\xa0", " ")
    content = content.replace("\t", " ")
    content = content.replace("\n\n", "\n")
    content = re.sub(r'[\[\]\{\}\<\>]',' ', content)
    content = re.sub(r'[^\x00-\x7F]+',' ', content)
    return content

def write_clean_corpus_file(corpus_file, content):
    with open(corpus_file, "w+") as corpus_fd:
        corpus_fd.write(content)

def read_raw_corpus_file(corpus_file):
    with open(corpus_file, "r+") as corpus_fd:
        content = corpus_fd.read()
    return content

def clean_corpus_files():
    raw_corpus_dir = os.path.join(CWD, 'corpus','raw')
    raw_corpus_files = os.listdir(raw_corpus_dir)
    clean_corpus_dir = os.path.join(CWD, 'corpus','clean')

    for corpus_file in raw_corpus_files:
        raw_corpus_file_path = os.path.join(raw_corpus_dir, corpus_file)
        clean_corpus_file_path = os.path.join(clean_corpus_dir, corpus_file.replace("raw", "clean"))

        content = read_raw_corpus_file(raw_corpus_file_path)
        content = clean_raw_files(content)
        write_clean_corpus_file(clean_corpus_file_path, content)
    
    return

############ FILE CLEANING METHODS ##############


############ SCRAPING METHODS ##############

def scrape_text_from_soup(bs4_soup_inst):
    # kill all script and style elements
    for script in bs4_soup_inst(["script", "style"]):
        script.extract()
    # get text
    text = bs4_soup_inst.get_text()

    return text

def write_raw_corpus_file(html, index):
    corpus_dir = os.path.join(CWD, 'corpus','raw')
    with open(
        os.path.join(corpus_dir, "corpus" + str(index) + "_raw.txt"), 
        "w+"
    ) as corp_fd:
        corp_fd.write(html)
    return

def transform_hrefs(starting_url, hrefs):
    protocol = starting_url.split("//")[0]
    address = starting_url.split("//")[1].split("/")[0]
    
    for href_itr, href in enumerate(hrefs):
        if ( href.startswith("https://") or 
           href.startswith("http://") ):
           continue
        elif ( href.startswith("/") ):
            hrefs[href_itr] = protocol + "//" + address + href
    
    return hrefs


def filter_hrefs_by_relevance(hrefs, search_terms = None, ignore_terms=None, strict=False):

    if strict: func = all
    else: func = any

    #hrefs that contained search terms
    if search_terms:
        filtered_hrefs = list(filter(
            lambda x: func([
                kw in x.lower() for kw in search_terms
            ]),
            hrefs
        ))

    #hrefs that didn't contain ignore terms
    if filtered_hrefs and ignore_terms:
        filtered_hrefs = list(filter(
            lambda x: all([
                kw not in x.lower() for kw in ignore_terms
            ]),
            filtered_hrefs
        ))

    return filtered_hrefs


def get_hrefs_from_a_tags(a_tags):
    return list(map(lambda x: x['href'], a_tags))

def get_a_tags(bs4_soup_inst):
    return bs4_soup_inst.find_all('a', href=True)

def read_terms(terms_file):
    with open(terms_file) as terms_fd:
        terms = terms_fd.readlines()
        terms = list(map(lambda x: x.strip().lower(), terms))
    return terms

def scrape_url(url):
    try:
        with request.urlopen(url) as url_fd:
            try: html = url_fd.read().decode('utf8')
            except Exception as e: return None
    except urllib.error.HTTPError as e:
        print(e.reason)
        return None
    return html

def read_starting_urls(url_file):
    with open(url_file) as start_url_fd:
        urls = start_url_fd.readlines()
    return urls

def scrape_web(
    url_file, 
    search_terms_file=None,
    ignore_terms_file=None,
    strict=False, 
    min_num_url=15, 
    max_num_url=25
):
    starting_urls = read_starting_urls(url_file)

    search_terms = None
    if search_terms_file:
        search_terms = read_terms(search_terms_file)
    
    ignore_terms = None
    if ignore_terms_file:
        ignore_terms = read_terms(ignore_terms_file)

    url_deque = deque(starting_urls, maxlen=max_num_url)
    num_urls_processing = len(starting_urls)
    num_corpus_file_written = 0
    extra_urls = list()
    visited_urls = list()

    while ( len(url_deque) != 0 ):
        curr_url = url_deque.pop()

        if ( curr_url in visited_urls ): continue
        else: visited_urls.append(curr_url)
        html = scrape_url(curr_url)

        #print(curr_url)

        if html:
            curr_soup_inst = BeautifulSoup(
                html, 
                features="html.parser"
            )
            curr_url_text = scrape_text_from_soup(curr_soup_inst)

            #print(num_corpus_file_written)
            write_raw_corpus_file(curr_url_text, num_corpus_file_written)
            num_corpus_file_written += 1
            
            a_tags = get_a_tags(curr_soup_inst)
            hrefs = get_hrefs_from_a_tags(a_tags)
            if search_terms:
                hrefs = filter_hrefs_by_relevance(
                    hrefs,
                    search_terms,
                    ignore_terms,
                    strict
                )

            #print("Href length: ", len(hrefs))
            hrefs = transform_hrefs(curr_url, hrefs)
            hrefs = list(filter(
                lambda x: ( x.startswith("https://") or x.startswith("http://")), 
                hrefs
            ))

            if ( not ( num_urls_processing >= min_num_url ) ):
                url_deque.extendleft(hrefs)
                num_urls_processing += len(hrefs)
            else:
                extra_urls = extra_urls + hrefs
                if ( ( len(url_deque) == 0 ) and 
                     ( num_corpus_file_written <= max_num_url ) ):
                    url_deque.extendleft(extra_urls)


############ SCRAPING METHODS ##############

def main():
    if ( len(sys.argv) < 2 ):
        print("Error: No starting URL file provided.")
        exit()

    if ( len(sys.argv) < 3 ):
        print("Error: No Keywords file provided.")
        exit()
    
    corpus_dir = os.path.join(CWD, 'corpus')

    if not os.path.exists(corpus_dir):
        os.mkdir(corpus_dir)

    raw_corpus_dir = os.path.join(corpus_dir,'raw')

    if not os.path.exists(raw_corpus_dir):
        os.mkdir(raw_corpus_dir)

    clean_corpus_dir = os.path.join(corpus_dir,'clean')

    if not os.path.exists(clean_corpus_dir):
        os.mkdir(clean_corpus_dir)

    pickle_corpus_dir = os.path.join(corpus_dir,'pickle')

    if not os.path.exists(pickle_corpus_dir):
        os.mkdir(pickle_corpus_dir)

    url_file = sys.argv[1]
    search_terms_file = None
    ignore_terms_file = None
    keywords_file = None

    if ( len(sys.argv) >= 3 ):
        keywords_file = sys.argv[2]

    if ( len(sys.argv) >= 4 ):
        search_terms_file = sys.argv[3]

    if ( len(sys.argv) >= 5 ):
        ignore_terms_file = sys.argv[4]
    
    #scrape_web(url_file, search_terms_file, ignore_terms_file, False, 150, 200)
    #clean_corpus_files()
    corpus_dict, tf_idf_dict = make_corpus_dictionaries()
    top_twenty_five_terms = get_top_twenty_five_terms(tf_idf_dict)

    print("The top 25 terms are as follows:\n")
    for term in top_twenty_five_terms: print("\t", term)

    keywords = read_terms(keywords_file)
    knowledge_base = build_knowledge_base(corpus_dict, tf_idf_dict, keywords)
    
    pickle_data_dictionary(os.path.join(pickle_corpus_dir, 'knowledge_base.pickle'), knowledge_base)
    pickle_data_dictionary(os.path.join(pickle_corpus_dir, 'corpus.pickle'), corpus_dict)
    pickle_data_dictionary(os.path.join(pickle_corpus_dir, 'tf_idf.pickle'), tf_idf_dict)


if __name__ == "__main__":
    global stopwords
    global CWD
    CWD = os.getcwd()
    STOPWORDS = stopwords.words('english')

    main()




