#include "Graph.h"

Graph::Graph(){
    this->vertices = new vector<Vertex*>();
    this->edges = new vector<Edge*>();
}

Graph::~Graph() {
    delete vertices;
    delete edges;
}

void Graph::insert_vertex(Vertex *new_vertex){
    this->vertices->push_back(new_vertex);
}

void Graph::insert_edge(Edge *new_edge){
    this->edges->push_back(new_edge);
}

void Graph::erase_vertex(Vertex *vertex_to_be_deleted){
    
    int vector_size = this->vertices->size();
    for ( int vector_cntr = 0; vector_cntr < vector_size; vector_cntr++ ){
        if ( this->vertices[vector_cntr] == vertex_to_be_deleted ){
            this->vertices->erase(vector_cntr);
        }
    }

}

void Graph::erase_edge(Edge *edge_to_be_deleted){

    int vector_size = this->edges->size();
    for ( int vector_cntr = 0; vector_cntr < vector_size; vector_cntr++ ){
        if ( this->vertices[vector_cntr] == edge_to_be_deleted ){
            this->vertices->erase(vector_cntr);
        }
    }


vector<Vertex*>* Graph::get_vertices(){
    return this->vertices();
}

vector<Edge*>* Graph::get_edges(){
    return this->edges();
}

void Graph::incident_edges(Vertex *curr_vertex){
    return;
}

int* Graph::get_adjacency_matrix(){
    return NULL;
}

void Graph::print_vertices(){
    auto vertices_map_begin = this->vertices->begin();
    auto vertices_map_end = this->vertices->end();

    Vertex *curr_vertex;

    for ( auto vertices_it = vertices_map_begin; vertices_it != vertices_map_end; ++vertices_it ) {
        vertices_it->first;
    }

}
void Graph::print_edges(){
    
    auto edges_map_begin = this->edges->begin();
    auto edges_map_end = this->edges->end();

    for ( auto edges_it = edges_map_begin; edges_it != edges_map_end; ++edges_it ) {
    
    }

}