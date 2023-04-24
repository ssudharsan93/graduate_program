#ifndef VERTEX_H
#define VERTEX_H

#include <map>
#include <string>
#include <vector>
#include <iostream>

#include "DirectedEdge.h"

class Vertex;
class DirectedEdge;

using namespace std;

class DijkstraDistanceStructure{
private:
    Vertex *vertex;
    int distance;
    DirectedEdge *parent_edge = NULL;

public:
    DijkstraDistanceStructure(Vertex *vertex_to_be_assigned, int distance);
    Vertex* get_vertex();
    int get_distance();
    void set_vertex(Vertex* vertex_to_be_assigned);
    void set_distance(int distance);
    DirectedEdge* get_parent_edge();
    void set_parent_edge(DirectedEdge* parent_edge_to_be_assigned);
};

class Vertex {
private:
    string name;
    int index;
    int distance;
    int label = -1;
    bool visited = false;
    DirectedEdge *parent_edge = NULL;
    vector<Vertex*> *adjacent_nodes;
    vector<DirectedEdge*> *incoming_edges;
    vector<DirectedEdge*> *outgoing_edges;
    DijkstraDistanceStructure *distance_structure = NULL;

public:
    Vertex(string name, int index);
    ~Vertex();
    string get_name();
    int get_index();
    int get_distance();
    void set_distance(int distance);
    int get_label();
    void set_label(int label);
    void reset_label();
    bool is_visited();
    void set_visited();
    void clear_visited();
    bool is_adjacent(Vertex *vertex_to_check);
    void add_adjacent_node(Vertex* adjacent_node);
    void add_incoming_edge(DirectedEdge* incoming_edge);
    void add_outgoing_edge(DirectedEdge* outgoing_edge);
    vector<Vertex*>* get_adjacent_nodes();
    vector<DirectedEdge*>* get_incoming_edges();
    vector<DirectedEdge*>* get_outgoing_edges();
    void print_vertex();
    DijkstraDistanceStructure* get_distance_structure();
    void set_distance_structure(DijkstraDistanceStructure *distance_structure);
};

#endif VERTEX_H
