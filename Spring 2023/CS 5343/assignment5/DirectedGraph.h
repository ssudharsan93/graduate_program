#ifndef DIRECTEDGRAPH_H
#define DIRECTEDGRAPH_H

#include <limits.h>
#include <queue>
#include <algorithm>

#include "DirectedEdge.h"

class DirectedGraph {
private:
    vector<Vertex*> *vertices;
    vector<DirectedEdge*> *directed_edges;

public:
    DirectedGraph();
    ~DirectedGraph();
    void insert_vertex(Vertex *new_vertex);
    void insert_directed_edge(DirectedEdge *new_directed_edge);
    void erase_vertex(Vertex *new_vertex);
    void erase_edge(DirectedEdge *edge_to_be_deleted);
    vector<Vertex*>* get_vertices();
    vector<DirectedEdge*>* get_directed_edges();
    int** get_adjacency_matrix();
    int** get_incidence_matrix();
    void print_vertices();
    void print_directed_edges();
    void print_adjacent_vertices();
    void print_distances(vector<DijkstraDistanceStructure*>* priority_queue);
    void relax_distances(Vertex *current, vector<DijkstraDistanceStructure*>* priority_queue);
    vector<DijkstraDistanceStructure*>* init_priority_queue();
    void run_dijkstras_algorithm_for_shortest_path();

};

#endif DIRECTEDGRAPH_H
