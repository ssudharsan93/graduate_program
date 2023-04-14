#ifndef GRAPH_H
#define GRAPH_H

#include <vector>


class Graph {
private:
vector<int, Vertex*> vertices;
vector<int, Edge*> edges;
public:
    add_vertex(Vertex *new_vertex);
    add_edge(Edge *new_edge);
    int* get_adjacency_matrix();
    get_vertices();
    get_edges();
    print_vertices();
    print_edges();
    

}

#endif GRAPH_H