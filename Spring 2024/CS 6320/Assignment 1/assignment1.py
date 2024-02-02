import sys
import nltk
import time
import random
import math
nltk.download('stopwords')
nltk.download('averaged_perceptron_tagger')

from nltk import word_tokenize
from nltk import sent_tokenize
from nltk.stem.porter import *
from nltk.stem import WordNetLemmatizer

STOP_WORDS = nltk.corpus.stopwords.words('english')

def read_input_file(FILENAME):
    """
        Preprocess raw tex.
        Arguments: a raw text string
        Output:
            text - raw_text with punctuation and numbers removed, lower cased
            tokens - tokens
            stemmed - stemmed words
            lemmas - lemmas
            content - tokens with stop words removed
    """

    with open(FILENAME, "r+") as open_f:
        input_text = open_f.read()

    return input_text

def desired_token(curr_token):
    """
        Preprocess raw tex.
        Arguments: a raw text string
        Output:
            text - raw_text with punctuation and numbers removed, lower cased
            tokens - tokens
            stemmed - stemmed words
            lemmas - lemmas
            content - tokens with stop words removed
    """

    if ( ( len(curr_token) > 5 ) and 
         ( curr_token not in STOP_WORDS) and
         ( curr_token.isalpha() ) ):
        #print(curr_token, ": True")
        return True

    #if ( curr_token in STOP_WORDS ):
    #    print(curr_token, ": False")

    return False

def is_noun(tagged_lemma):
    """
        Preprocess raw tex.
        Arguments: a raw text string
        Output:
            text - raw_text with punctuation and numbers removed, lower cased
            tokens - tokens
            stemmed - stemmed words
            lemmas - lemmas
            content - tokens with stop words removed
    """

    lemma, part_of_speech = tagged_lemma
    return part_of_speech.lower().startswith("n")

def extract_noun_from_tagged_noun(tagged_noun):
    """
        Preprocess raw tex.
        Arguments: a raw text string
        Output:
            text - raw_text with punctuation and numbers removed, lower cased
            tokens - tokens
            stemmed - stemmed words
            lemmas - lemmas
            content - tokens with stop words removed
    """

    noun, part_of_speech = tagged_noun
    return noun

def extract_noun_from_count_list(tagged_noun):
    """
        Preprocess raw tex.
        Arguments: a raw text string
        Output:
            text - raw_text with punctuation and numbers removed, lower cased
            tokens - tokens
            stemmed - stemmed words
            lemmas - lemmas
            content - tokens with stop words removed
    """

    noun, count = tagged_noun
    return noun

def text_preprocessing(input_filename):    
    """
        Preprocess raw tex.
        Arguments: a raw text string
        Output:
            text - raw_text with punctuation and numbers removed, lower cased
            tokens - tokens
            stemmed - stemmed words
            lemmas - lemmas
            content - tokens with stop words removed
    """

    #read in the text in the input file
    input_text = read_input_file(input_filename)

    # lowercase the text
    input_text = input_text.lower()
    
    anat19_tokens = word_tokenize(input_text)
    unique_anat19_tokens = list(set(anat19_tokens))
    lexical_diversity = ( 1.0 * len(unique_anat19_tokens) ) / ( 1.0 * len(anat19_tokens) )

    print("\n\tLexical Diversity ( # unique tokens / total # of tokens ) : ", lexical_diversity)

    desired_anat19_tokens = list(filter(desired_token, anat19_tokens))

    word_net_lemmatizer = WordNetLemmatizer()
    anat19_lemmas = [ word_net_lemmatizer.lemmatize(wtok) for wtok in desired_anat19_tokens ]
    unique_anat19_lemmas = list(set(anat19_lemmas))
    anat19_lemmas_pos_tagged = nltk.pos_tag(unique_anat19_lemmas)

    print("\n\tFirst 20 POS tagged Lemmas: ")
    print("\n[", end='')
    for itr in range(20):
        curr_lemma, part_of_speech = anat19_lemmas_pos_tagged[itr]
        print(" (", curr_lemma, ",", part_of_speech, ")", end='')
    print(" ]")

    anat19_lemmas_nouns_tagged = list(filter(is_noun, anat19_lemmas_pos_tagged))
    anat19_nouns = list(map(extract_noun_from_tagged_noun, anat19_lemmas_nouns_tagged))

    print("\n\tNumber of tokens from step(a) : ", len(desired_anat19_tokens))
    print("\n\tNumber of nouns from step(d) : ", len(anat19_nouns))
    #print("\n\tNumber of nouns from step(d) : ", len(anat19_lemmas_nouns_tagged))

    return desired_anat19_tokens, anat19_nouns
    
    
def get_noun_count_dict(tokens_list, nouns_list):
    """
        Preprocess raw tex.
        Arguments: a raw text string
        Output:
            text - raw_text with punctuation and numbers removed, lower cased
            tokens - tokens
            stemmed - stemmed words
            lemmas - lemmas
            content - tokens with stop words removed
    """

    noun_count = { noun : 0 for noun in nouns_list }  

    for wtok in tokens_list:
        word_net_lemmatizer = WordNetLemmatizer()
        lemmatized_wtok = word_net_lemmatizer.lemmatize(wtok)
        if ( noun_count.get(lemmatized_wtok, None) is not None ):
            val = noun_count.get(lemmatized_wtok)
            noun_count.update({ lemmatized_wtok: (val + 1) })

    return noun_count

def choose_random_word(word_list):
    """
        Preprocess raw tex.
        Arguments: a raw text string
        Output:
            text - raw_text with punctuation and numbers removed, lower cased
            tokens - tokens
            stemmed - stemmed words
            lemmas - lemmas
            content - tokens with stop words removed
    """
    random.seed(time.time())
    random_idx = math.floor(50 * random.random())
    return word_list[random_idx]

def print_curr_guess_str(curr_str):
    """
        Preprocess raw tex.
        Arguments: a raw text string
        Output:
            text - raw_text with punctuation and numbers removed, lower cased
            tokens - tokens
            stemmed - stemmed words
            lemmas - lemmas
            content - tokens with stop words removed
    """

    for itr in range( len(curr_str) - 1 ):
        print(curr_str[itr], " ", end='')
    print(curr_str[-1])

def update_guess_str(guess_str, chosen_word, char_guess):
    """
        Preprocess raw tex.
        Arguments: a raw text string
        Output:
            text - raw_text with punctuation and numbers removed, lower cased
            tokens - tokens
            stemmed - stemmed words
            lemmas - lemmas
            content - tokens with stop words removed
    """

    for itr in range(len(chosen_word)):
        if char_guess == chosen_word[itr]:
            guess_str[itr] = char_guess

    return guess_str

def guessing_game(most_common_nouns):
    """
        Preprocess raw tex.
        Arguments: a raw text string
        Output:
            text - raw_text with punctuation and numbers removed, lower cased
            tokens - tokens
            stemmed - stemmed words
            lemmas - lemmas
            content - tokens with stop words removed
    """
    curr_points = 5
    unknown_char = "_"
    print("\nLet's play a word guessing game!")

    playing = True

    chosen_word = list(choose_random_word(most_common_nouns))
    chosen_word_length = len(chosen_word)
    guess_str = list("_" * chosen_word_length)


    while(playing):
        print_curr_guess_str(guess_str)
        char_guess = input("Guess a letter:")
        
        if ( char_guess == "!" ):
            playing = False
            continue
        
        if char_guess in chosen_word:
            guess_str = update_guess_str(guess_str, chosen_word, char_guess)
            curr_points += 1
            print("Right! ", end='')

        else:
            curr_points -= 1
            
            if ( curr_points < 0 ):
                playing = False
                print("Sorry, you lose. ")
                continue

            print("Sorry, guess again. ", end='') 
        
        print("Score is ", curr_points)

        if ( guess_str == chosen_word ):
            print_curr_guess_str(guess_str)
            print("You solved it!\n")

            print("Current score: ", curr_points)
            print("\nGuess another word")
            chosen_word = list(choose_random_word(most_common_nouns))
            chosen_word_length = len(chosen_word)
            guess_str = list("_" * chosen_word_length)

    return

def main():

    if ( len(sys.argv) <= 1 ):
        print("Error! Input File not provided. Aborting...")
    
    anat19_tokens, anat19_nouns = text_preprocessing(sys.argv[1])
    count_dict = get_noun_count_dict(anat19_tokens, anat19_nouns)
    sorted_noun_list = sorted(list(count_dict.items()), key=lambda item: item[1], reverse=True)

    print("\n\t50 most common nouns and their counts: \n")
    print(sorted_noun_list[:50])

    most_common_nouns = list(map(extract_noun_from_count_list, sorted_noun_list[:50]))

    guessing_game(most_common_nouns)

    return

main()
