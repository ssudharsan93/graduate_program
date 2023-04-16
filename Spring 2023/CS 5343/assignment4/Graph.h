#ifndef GRAPH_H
#define GRAPH_H

#include <limits.h>
#include <queue>
#include <algorithm>

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
    vector<Vertex*>* get_vertices();
    vector<Edge*>* get_edges();
    int** get_adjacency_matrix();
    void print_vertices();
    void print_edges();
    void print_adjacent_vertices();
    void print_distances(vector<DijkstraDistanceStructure*>* priority_queue);
    void relax_distances(Vertex *current, vector<DijkstraDistanceStructure*>* priority_queue);
    vector<DijkstraDistanceStructure*>* init_priority_queue();
    void run_dijkstras_algorithm_for_shortest_path();

};

#endif GRAPH_H
