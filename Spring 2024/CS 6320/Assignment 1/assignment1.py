#! python3

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

def read_input_file(file_name):
    """
        Reads the text from an input file.
        Arguments: a filename string
        Output:
            text - raw_text from a particular file
    """

    with open(file_name, "r+") as open_f:
        input_text = open_f.read()

    return input_text

def desired_token(curr_token):
    """
        Checks whether a token matches a set of desired criteria.
        Arguments: a token string
        Output:
            Boolean True or False value indicating whether a token
            meets the desired criteria or not.
    """

    if ( ( len(curr_token) > 5 ) and 
         ( curr_token not in STOP_WORDS) and
         ( curr_token.isalpha() ) ):
        return True

    return False

def is_noun(tagged_lemma):
    """
        Checks whether a word is a noun.
        Arguments: a tuple that contains a lemma and its part of speech
        Output:
            Boolean True or False value indicating whether a lemma
            is a noun or not.
    """

    lemma, part_of_speech = tagged_lemma
    return part_of_speech.lower().startswith("n")

def extract_noun_from_tagged_noun(tagged_noun):
    """
        Takes a noun and part of speech tuple and returns just the noun.
        Arguments: a tuple that contains a noun and its part of speech
        Output:
            a string that represents a noun
    """

    noun, part_of_speech = tagged_noun
    return noun

def extract_noun_from_count_list(tagged_noun):
    """
        Takes a noun and count tuple and returns just the noun.
        Arguments: a tuple that contains a noun and occurrence count
        Output:
            a string that represents a noun
    """

    noun, count = tagged_noun
    return noun

def text_preprocessing(input_filename):    
    """
        Handles all the text preprocessing,
        lemmatization, part of speech tagging, etc.
        Prints out the necessary information for the assignment
        (tokens, lexical diversity, token count, noun count etc.)
        Arguments: a string that represents the input filename.
        Output:
           a tuple that contains a list of tokens that meet the desired
           critera ( they are not unique ) and a list of unique nouns
           from the input file.
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

    return desired_anat19_tokens, anat19_nouns
    
    
def get_noun_count_dict(tokens_list, nouns_list):
    """
        Creates a dictionary, with nouns as keys
        and the count of how many times they appear 
        in the list of tokens as the values.
        Arguments: a list of tokens and a list of nouns
        Output:
            Dictionary, has nouns as keys, and occurence counts as
            values.
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
        Randomly selects a word from the provided word list.
        Arguments: list of words to choose from
        Output:
            A string that represents the randomly selected word.
    """
    random.seed(time.time())
    random_idx = math.floor(50 * random.random())
    return word_list[random_idx]

def print_curr_guess_str(curr_str):
    """
        Prints the guess string with proper formatting.
        Arguments: A string representing the letters still unknown
        and the letters that have been guessed correctly. 
        Output:
            Void. Simply outputs the guess string. 
    """

    for itr in range( len(curr_str) - 1 ):
        print(curr_str[itr], " ", end='')
    print(curr_str[-1])

def update_guess_str(guess_str, chosen_word, char_guess):
    """
        Modifies the guess string with the guessed character
        placed/ showing up in the correct spots based on the
        chosen word.
        Arguments: A list of individual characters representing the guess string that 
        indicates which letters were guessed correctly and which letters are unknown, 
        a list containing the individual characters of the
        chosen word, and the character that was guessed.
        Output:
            A list containing the individual characters of the updated guess string
            corresponding to a correct guessed character being placed in its corresponding
            proper location.
    """

    for itr in range(len(chosen_word)):
        if char_guess == chosen_word[itr]:
            guess_str[itr] = char_guess

    return guess_str

def guessing_game(most_common_nouns):
    """
        Handles the guessing hangman-type minigame.
        Arguments: a list of the most common nouns
        Output:
            Void. Simply allows the user to play the guessing game.
            Prints out statements indicating the success, failure, 
            and general performance of the user playing the game.
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
    """
        Main method that handles passing proper arguments to 
        methods. Calls the pre-processing method, guessing game 
        method. 
        Arguments: Expects just a command line argument for the 
        name of the file that contains the input data.
        Output:
            Void. Simply allows the user to run the pre-processing code,
            and guessing game code.
    """

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

if __name__ == "__main__":
    main()
