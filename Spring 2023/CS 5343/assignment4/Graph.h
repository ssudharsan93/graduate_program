#ifndef GRAPH_H
#define GRAPH_H

#include "Edge.h"

class Graph {
private:
    vector<Vertex*> *vertices;
    vector<Edge*> *edges;

public:
    Graph();
    ~Graph();
    void insert_vertex(Vertex *new_vertex);
    void insert_edge(Edge *new_edge);
    void erase_vertex(Vertex *new_vertex);
    void erase_edge(Edge *new_edge);
    vector<Vertex*> get_vertices();
    vector<Edge*> get_edges();
    void incident_edges(Vertex *curr_vertex);
    int* get_adjacency_matrix();
    void print_vertices();
    void print_edges();

};

#endif GRAPH_H