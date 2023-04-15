#ifndef VERTEX_H
#define VERTEX_H

#include <map>
#include <string>
#include <vector>
#include <iostream>

#include "Edge.h"

class Edge;

using namespace std;

class Vertex {
private:
    string name;
    int index;
    vector<Vertex*> *adjacent_nodes;
    vector<Edge*> *incident_edges;

public:
    Vertex(string name, int index);
    ~Vertex();
    string get_name();
    int get_index();
    bool is_adjacent(Vertex *vertex_to_check);
    void add_adjacent_node(Vertex* adjacent_node);
    void add_incident_edge(Edge* incident_edge);
    vector<Vertex*>* get_adjacent_nodes();
    vector<Edge*>* get_incident_edges();
    void print_vertex();
};

#endif VERTEX_H