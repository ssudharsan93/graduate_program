import sys
import nltk
nltk.download('stopwords')
nltk.download('averaged_perceptron_tagger')

from nltk import word_tokenize
from nltk import sent_tokenize
from nltk.stem.porter import *
from nltk.stem import WordNetLemmatizer

STOP_WORDS = nltk.corpus.stopwords.words('english')

def read_input_file(FILENAME):
    with open(FILENAME, "r+") as open_f:
        input_text = open_f.read()

    return input_text

def desired_token(curr_token):
    if ( ( len(curr_token) > 5 ) and 
         ( curr_token not in STOP_WORDS) and
         ( curr_token.isalpha() ) ):
        #print(curr_token, ": True")
        return True

    #if ( curr_token in STOP_WORDS ):
    #    print(curr_token, ": False")

    return False

def text_preprocessing(input_filename):    
    #read in the text in the input file
    input_text = read_input_file(input_filename)

    # lowercase the text
    input_text = input_text.lower()
    
    anat19_tokens = word_tokenize(input_text)
    unique_anat19_tokens = list(set(anat19_tokens))
    lexical_diversity = ( 1.0 * len(unique_anat19_tokens) ) / ( 1.0 * len(anat19_tokens) )

    print("\n\t Lexical Diversity ( # unique tokens / total # of tokens ) : ", lexical_diversity)

    desired_anat19_tokens = list(filter(desired_token, anat19_tokens))

    word_net_lemmatizer = WordNetLemmatizer()
    anat19_lemmas = [ word_net_lemmatizer.lemmatize(wtok) for wtok in anat19_tokens ]
    unique_anat19_lemmas = list(set(anat19_lemmas))
    anat19_lemmas_pos_tagged = nltk.pos_tag(unique_anat19_lemmas)

    print(anat19_lemmas_pos_tagged)

    print("\n\tFirst 20 POS tagged Lemmas: ")
    for itr in range(20):
        anat19_lemmas_pos_tagged[itr]
        #print("\n\t", )
    

def main():

    if ( len(sys.argv) <= 1 ):
        print("Error! Input File not provided. Aborting...")
    
    text_preprocessing(sys.argv[1])

    return

main()
