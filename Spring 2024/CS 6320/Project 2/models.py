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

import tensorflow as tf
from tensorflow.keras.layers import Input, Dense, Dropout, LayerNormalization
from tensorflow.keras.layers import MultiHeadAttention, Embedding, GlobalAveragePooling1D
from tensorflow.keras.models import Model

def transformer_model(
    input_vocab_size, 
    output_vocab_size, 
    max_length, 
    num_heads, 
    embedding_dim, 
    dense_dim, 
    num_layers, 
    dropout_rate
):
    # Encoder
    inputs = Input(shape=(max_length,))
    x = Embedding(input_vocab_size, embedding_dim)(inputs)
    for _ in range(num_layers):
        x = encoder_layer(x, num_heads, dense_dim, dropout_rate)
        
    # Decoder
    outputs = Dense(output_vocab_size, activation='softmax')(x)
    
    model = Model(inputs, outputs)
    return model

def encoder_layer(
    x, 
    num_heads, 
    dense_dim, 
    dropout_rate
):
    # Multi-head self-attention
    attn_output = MultiHeadAttention(num_heads=num_heads, key_dim=dense_dim)(x, x)
    attn_output = Dropout(dropout_rate)(attn_output)
    out1 = LayerNormalization(epsilon=1e-6)(x + attn_output)
    
    # Feed forward network
    ffn_output = Dense(dense_dim, activation='relu')(out1)
    ffn_output = Dense(dense_dim)(ffn_output)
    ffn_output = Dropout(dropout_rate)(ffn_output)
    out2 = LayerNormalization(epsilon=1e-6)(out1 + ffn_output)
    
    return out2

# Example usage:
#input_vocab_size = 10000  # Example vocabulary size for input tokens
#output_vocab_size = 10000  # Example vocabulary size for output tokens
#max_length = 100  # Example maximum sequence length
#num_heads = 8  # Number of attention heads
#embedding_dim = 128  # Dimension of token embeddings
#dense_dim = 256  # Dimension of dense layers
#num_layers = 4  # Number of encoder layers
#dropout_rate = 0.1  # Dropout rate

#model = transformer_model(
#    input_vocab_size, 
#    output_vocab_size, 
#    max_length, 
#    num_heads, 
#    embedding_dim, 
#    dense_dim, 
#    num_layers, 
#    dropout_rate
#)
#model.summary()

def classification_model():
    return 

def main():
    CWD = os.getcwd()
    corpus_dir = os.path.join(CWD, 'corpus')
    chatbot_dir= os.path.join(CWD, 'chatbot')

    pickle_corpus_dir = os.path.join(corpus_dir,'pickle')

    knowledge_base = read_pickle_file(os.path.join(pickle_corpus_dir, "knowledge_base.pickle"))
    chats = read_pickle_file(os.path.join(chatbot_dir, "user_model.pickle"))

    for term in knowledge_base.keys():
        print("\n\n")
        print("Term: ", term)
        print("\n\n")
        print("\n".join(knowledge_base[term][:10]))

main()
