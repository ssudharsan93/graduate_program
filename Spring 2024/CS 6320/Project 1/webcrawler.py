#! python3

import urllib
from urllib import request, error, parse, robotparser
from bs4 import BeautifulSoup
import sys
import requests
from collections import deque, Counter
import os
import re

import nltk
nltk.download('punkt')
nltk.download('stopwords')
from nltk.tokenize import sent_tokenize, word_tokenize
from nltk.corpus import stopwords

import sklearn
from sklearn.feature_extraction.text import TfidfVectorizer,CountVectorizer

import numpy as np

############ COUNTS / IMPORTANT TERMS METHODS ##############
def is_valid_sentence(sentence):
    format_matched = re.search(r'[^\r\n\t]+[.!?]$', sentence, re.A) is not None
    special_char_found = re.search(r'[\|]', sentence, re.A) is not None

    return ( ( format_matched ) and ( not special_char_found ) )

def is_valid_token(token):
    is_not_stop_word = token not in STOPWORDS
    is_alpha = token.isalpha()
    return ( is_not_stop_word and is_alpha )

def extract_counts(tokens):
    return dict(Counter(tokens))
    #return { tok : tokens.count(tok) for tok in set(tokens) }

def extract_tokens(sentences):
    tokens = list()
    for sentence in sentences:
        tokens = tokens + word_tokenize(sentence.lower())
    tokens = list(filter(is_valid_token, tokens))

    return tokens

def extract_valid_sentences(content):
    sentences = sent_tokenize(content)
    sentences = list(filter(is_valid_sentence, sentences))
    return sentences

def read_clean_corpus_file(clean_corpus_file):
    with open(clean_corpus_file, "r+") as corpus_fd:
        content = corpus_fd.read()
    return content

def make_corpus_dictionaries():
    clean_corpus_dir = os.path.join(CWD, 'corpus','clean')
    clean_corpus_files = os.listdir(clean_corpus_dir)

    for clean_corpus_file in sorted(clean_corpus_files):
        clean_corpus_file_path = os.path.join(clean_corpus_dir, clean_corpus_file)
        content = read_clean_corpus_file(clean_corpus_file_path)
        sentences = extract_valid_sentences(content)
        tokens = extract_tokens(sentences)
        counts = extract_counts(tokens)

############ COUNTS / IMPORTANT TERMS METHODS ##############

############ FILE CLEANING METHODS ##############
def clean_raw_files(content):
    content = content.replace("\xa0", "")
    content = content.replace("\t", "")
    content = content.replace("\n", "")
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

def preprocess_corpus_files():
    raw_corpus_dir = os.path.join(CWD, 'corpus','raw')
    raw_corpus_files = os.listdir(raw_corpus_dir)
    clean_corpus_dir = os.path.join(CWD, 'corpus','clean')

    if not os.path.exists(clean_corpus_dir):
        os.mkdir(clean_corpus_dir)

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


def filter_hrefs_by_relevance(hrefs, keywords, strict=False):
    if strict:
        return list(filter(
            lambda x: all([
                kw in x.lower() for kw in keywords 
            ]),
            hrefs
        ))

    return list(filter(
        lambda x: any([
            kw in x.lower() for kw in keywords 
        ]),
        hrefs
    ))

def get_hrefs_from_a_tags(a_tags):
    return list(map(lambda x: x['href'], a_tags))

def get_a_tags(bs4_soup_inst):
    return bs4_soup_inst.find_all('a', href=True)

def read_keywords(keywords_file):
    with open(keywords_file) as keywords_fd:
        keywords = keywords_fd.readlines()
        keywords = list(map(lambda x: x.strip().lower(), keywords))
    return keywords

def scrape_url(url):
    try:
        with request.urlopen(url) as url_fd:
             html = url_fd.read().decode('utf8')
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
    keywords_file=None, 
    strict=False, 
    min_num_url=15, 
    max_num_url=50
):
    starting_urls = read_starting_urls(url_file)
    keywords = None
    if keywords_file:
        keywords = read_keywords(keywords_file)

    if not os.path.exists(os.path.join(CWD, 'corpus', 'raw')):
        os.mkdir(os.path.join(CWD, 'corpus', 'raw'))

    url_deque = deque(starting_urls, maxlen=max_num_url)
    num_urls_processing = len(starting_urls)
    num_corpus_file_written = 0
    extra_urls = list()

    while ( len(url_deque) != 0 ):
        curr_url = url_deque.pop()
        html = scrape_url(curr_url)

        if html:
            curr_soup_inst = BeautifulSoup(
                html, 
                features="html.parser"
            )
            curr_url_text = scrape_text_from_soup(curr_soup_inst)

            write_raw_corpus_file(curr_url_text, index)
            num_corpus_file_written += 1
            
            a_tags = get_a_tags(curr_soup_inst)
            hrefs = get_hrefs_from_a_tags(a_tags)
            if keywords:
                hrefs = filter_hrefs_by_relevance(
                    hrefs,
                    keywords,
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
            #    if ( num_corpus_file_written < max_num_url ):


############ SCRAPING METHODS ##############

def main():
    if ( len(sys.argv) < 2 ):
        print("Error: No starting URL file provided.")
        exit()

    url_file = sys.argv[1]
    keywords_file = None

    if ( len(sys.argv) == 3 ):
        keywords_file = sys.argv[2]

    if not os.path.exists(os.path.join(CWD, 'corpus')):
        os.mkdir(os.path.join(CWD, 'corpus'))
    scrape_web(url_file, keywords_file, True)

    preprocess_corpus_files()
    make_corpus_dictionaries()

if __name__ == "__main__":
    global CWD
    global stopwords
    CWD = os.getcwd()
    STOPWORDS = stopwords.words('english')
    main()




