#include "Vertex.h"

//-----------------------------------------------------
//##### DIJKSTRA DISTANCE STRUCTURE METHODS START ######
//-----------------------------------------------------

DijkstraDistanceStructure::DijkstraDistanceStructure(Vertex *vertex_to_be_assigned, int distance){
    this->vertex = vertex_to_be_assigned;
    this->distance = distance;
}

Vertex* DijkstraDistanceStructure::get_vertex(){
    return this->vertex;
}

void DijkstraDistanceStructure::set_vertex(Vertex* vertex_to_be_assigned){
    this->vertex = vertex_to_be_assigned;
}

int DijkstraDistanceStructure::get_distance(){
    return this->distance;
}

void DijkstraDistanceStructure::set_distance(int distance){
    this->distance = distance;
}

DirectedEdge* DijkstraDistanceStructure::get_parent_edge(){
    return this->parent_edge;
}

void DijkstraDistanceStructure::set_parent_edge(DirectedEdge* parent_edge_to_be_assigned){
    this->parent_edge = parent_edge_to_be_assigned;
}

//-----------------------------------------------------
//##### DIJKSTRA DISTANCE STRUCTURE METHODS END ######
//-----------------------------------------------------

//-----------------------------------------------------
//################# VERTEX METHODS START #################
//-----------------------------------------------------


Vertex::Vertex(string name, int index){
    this->name = name;
    this->index = index;
    this->adjacent_nodes = new vector<Vertex*>();
    this->incoming_edges = new vector<DirectedEdge*>();
    this->outgoing_edges = new vector<DirectedEdge*>();
}

Vertex::~Vertex(){
    delete this->adjacent_nodes;
    delete this->incoming_edges;
    delete this->outgoing_edges;
}
    
string Vertex::get_name() {
    return this->name;
}

int Vertex::get_index(){
    return this->index;
}

int Vertex::get_distance(){
    return this->distance;
}

void Vertex::set_distance(int distance){
    this->distance = distance;
}

bool Vertex::is_visited(){
    return this->visited;
}

void Vertex::set_visited(){
    this->visited = true;
}

void Vertex::clear_visited(){
    this->visited = false;
}

bool Vertex::is_adjacent(Vertex *vertex_to_check){
    
    int vector_size = this->adjacent_nodes->size();
    
    for ( int vector_cntr = 0; vector_cntr < vector_size; vector_cntr++ ){
        if ( this->adjacent_nodes->at(vector_cntr) == vertex_to_check ){
            return true;
        }
    }

    return false;

}

void Vertex::add_adjacent_node(Vertex* adjacent_node) {
    this->adjacent_nodes->push_back(adjacent_node);
}

void Vertex::add_incoming_edge(DirectedEdge* incoming_edge) {
    this->incoming_edges->push_back(incoming_edge);
}

void Vertex::add_outgoing_edge(DirectedEdge* outgoing_edge) {
    this->outgoing_edges->push_back(outgoing_edge);
}

vector<Vertex*>* Vertex::get_adjacent_nodes(){
    return this->adjacent_nodes;
}

vector<DirectedEdge*>* Vertex::get_incoming_edges(){
    return this->incoming_edges;
}

vector<DirectedEdge*>* Vertex::get_outgoing_edges(){
    return this->outgoing_edges;
}

void Vertex::print_vertex(){
    cout << "\t" << this->index << " : " << this->name << endl; 
}

DijkstraDistanceStructure* Vertex::get_distance_structure() {
    return this->distance_structure;
}

void Vertex::set_distance_structure(DijkstraDistanceStructure *distance_structure) {
    this->distance_structure = distance_structure;
}

//-----------------------------------------------------
//################# VERTEX METHODS END #################
//-----------------------------------------------------