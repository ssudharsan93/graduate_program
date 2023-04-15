#ifndef GRAPH_H
#define GRAPH_H

#include <limits.h>
#include <queue>

#include "Edge.h"

class DijkstraDistanceStructure{
private:
    Vertex *vertex;
    int distance;
    Edge *parent_edge;

public:
    DijkstraDistanceStructure(Vertex *vertex_to_be_assigned, int distance);
    Vertex* get_vertex();
    int get_distance();
    void set_vertex(Vertex* vertex_to_be_assigned);
    void set_distance(int distance);
    Edge* get_parent_edge();
    void set_parent_edge(Edge* parent_edge_to_be_assigned);
};

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
    vector<DijkstraDistanceStructure*>* init_priority_queue();
    void run_dijkstras_algorithm_for_shortest_path();

};

#endif GRAPH_H