import pickle
import os

from pprint import pprint

import tensorflow as tf
import sklearn
import pandas as pd
import numpy as np

from tensorflow.keras.layers import Input, Dense, Dropout, LayerNormalization
from tensorflow.keras.layers import MultiHeadAttention, Embedding, GlobalAveragePooling1D
from tensorflow.keras.models import Model, Sequential
from tensorflow.keras.preprocessing.sequence import pad_sequences

from sklearn.preprocessing import LabelEncoder
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.model_selection import train_test_split

def write_pickle_file(filename, data_dict):
    with open(filename, "wb") as pickle_file:
        pickle.dump(data_dict, pickle_file)

def read_pickle_file(filename):
    with open(filename, "rb") as pickle_file:
        ngram_dict = pickle.load(pickle_file)
    return ngram_dict

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

def classification_model(num_features, num_classes):
    model = Sequential()
    model.add(Dense(units=128, activation='relu', input_shape=(num_features,)))
    model.add(Dense(units=64, activation='relu'))
    model.add(Dense(units=num_classes, activation='softmax'))
    model.compile(optimizer='adam', loss='sparse_categorical_crossentropy', metrics=['accuracy'])
    model.summary()

    return model

def main():
    CWD = os.getcwd()
    corpus_dir = os.path.join(CWD, 'corpus')
    chatbot_dir= os.path.join(CWD, 'chatbot')
    model_dir = os.path.join(CWD, 'model')
    
    if not os.path.exists(model_dir):
        os.mkdir(model_dir)

    pickle_corpus_dir = os.path.join(corpus_dir,'pickle')

    knowledge_base = read_pickle_file(os.path.join(pickle_corpus_dir, "knowledge_base.pickle"))

    topics = sorted(list(knowledge_base.keys()))
    topic_df = pd.DataFrame(
        data=[ ( text, idx ) for idx, text in enumerate(topics) ], 
        columns=['topic', 'label'] 
    )

    trainable_df = pd.DataFrame(
        data=[ ( topic, knowledge_base[topic]) for topic in topics ], 
        columns=['topic', 'text']
    ).explode('text').reset_index(drop=True)

    trainable_df = pd.merge(topic_df, trainable_df, on='topic', how='inner').drop(columns=['topic'])
    trainable_df = pd.concat(
        [
            topic_df.rename(columns={'topic': 'text'}),
            trainable_df
        ],
        ignore_index=True
    )

    global tfidf_vectorizer
    global topic_model

    tfidf_vectorizer = TfidfVectorizer()
    vectorized_data = tfidf_vectorizer.fit_transform(trainable_df['text'])
    trainable_df['vectorized'] = vectorized_data.toarray().tolist()

    max_document_length = trainable_df['vectorized'].apply(len).max()
    trainable_df['vectorized'] = trainable_df['vectorized'].apply(
        lambda x: pad_sequences(
            [x], 
            maxlen=max_document_length, 
            padding='post',
            dtype='float32'
        )[0]
    )

    #classification_model_params
    class_mod_num_classes = len(topics)
    class_mod_num_features = max_document_length
    num_epochs = 100
    batch_size = 8
    topic_model = classification_model(class_mod_num_features, class_mod_num_classes)

    X = np.vstack(trainable_df['vectorized'].to_numpy())
    y = trainable_df['label'].to_numpy()

    random_state = np.random.randint(0, 1000)
    #X_train, X_test, y_train, y_test = train_test_split(
    #    X, y, test_size=0.1, stratify=y, random_state=random_state
    #)

    class_model_weights_path = os.path.join(model_dir, "classification_model.weights.h5")

    if not os.path.exists(class_model_weights_path):
        # topic_model.fit(
        #     X_train, 
        #     y_train, 
        #     epochs=num_epochs, 
        #     batch_size=batch_size, 
        #     validation_data=(X_test, y_test),
        #     verbose=1
        # )

        topic_model.fit(
             X, 
             y, 
             epochs=num_epochs, 
             batch_size=batch_size, 
             verbose=1,
             validation_split=0.2
        )

        topic_model.save_weights(class_model_weights_path)
    else: topic_model.load_weights(class_model_weights_path)

    test_data = [
        "Daenerys Targaryen", 
        "Aegon The First",
        "Rhaenyra Targaryen",
        "Maegor I Targaryen The Cruel",
        "Viserys I Targaryen",
    ]

    transformed_test = tfidf_vectorizer.transform(test_data)
    predictions = topic_model.predict(transformed_test)
    for prediction in predictions:
       print(topics[np.argmax(prediction)])



main()
