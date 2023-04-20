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

Edge* DijkstraDistanceStructure::get_parent_edge(){
    return this->parent_edge;
}

void DijkstraDistanceStructure::set_parent_edge(Edge* parent_edge_to_be_assigned){
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
    this->incident_edges = new vector<Edge*>();
}

Vertex::~Vertex(){
    delete this->adjacent_nodes;
    delete this->incident_edges;
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

void Vertex::set_visited(int distance){
    this->visited = true;
}

void Vertex::clear_visited(int distance){
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

void Vertex::add_incident_edge(Edge* incident_edge) {
    this->incident_edges->push_back(incident_edge);
}

vector<Vertex*>* Vertex::get_adjacent_nodes(){
    return this->adjacent_nodes;
}

vector<Edge*>* Vertex::get_incident_edges(){
    return this->incident_edges;
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