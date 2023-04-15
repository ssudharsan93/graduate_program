#include "Graph.h"


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
//################# GRAPH METHODS START #################
//-----------------------------------------------------

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

    new_edge->get_first_end_vertex()->add_adjacent_node(new_edge->get_second_end_vertex());
    new_edge->get_second_end_vertex()->add_adjacent_node(new_edge->get_first_end_vertex());
    new_edge->get_first_end_vertex()->add_incident_edge(new_edge);
    new_edge->get_second_end_vertex()->add_incident_edge(new_edge);

    this->edges->push_back(new_edge);
}

void Graph::erase_vertex(Vertex *vertex_to_be_deleted){
    
    int vector_size = this->vertices->size();
    for ( int vector_cntr = 0; vector_cntr < vector_size; vector_cntr++ ){
        if ( this->vertices->at(vector_cntr) == vertex_to_be_deleted ){
            this->vertices->erase(this->vertices->begin() + vector_cntr);
        }
    }

}

void Graph::erase_edge(Edge *edge_to_be_deleted){

    int vector_size = this->edges->size();
    for ( int vector_cntr = 0; vector_cntr < vector_size; vector_cntr++ ){
        if ( this->edges->at(vector_cntr) == edge_to_be_deleted ){
            this->edges->erase(this->edges->begin() + vector_cntr);
        }
    }
}


vector<Vertex*>* Graph::get_vertices(){
    return this->vertices;
}

vector<Edge*>* Graph::get_edges(){
    return this->edges;
}

int** Graph::get_adjacency_matrix(){
    
    int matrix_n_param = this->vertices->size();

    int **adjacency_matrix = new int*[matrix_n_param]();
    Vertex *curr_vertex, *adjacent_node;
    vector<Vertex*> *adjacent_nodes;
    int num_adjacent_nodes;

    for( int matrix_row_cntr = 0; matrix_row_cntr < matrix_n_param; matrix_row_cntr++ ) {
        adjacency_matrix[matrix_row_cntr] = new int[matrix_n_param]();
        curr_vertex = this->vertices->at(matrix_row_cntr);
        adjacent_nodes = curr_vertex->get_adjacent_nodes();
        num_adjacent_nodes = adjacent_nodes->size();

        for( int node_cntr = 0; node_cntr < num_adjacent_nodes; node_cntr++  ) {
            adjacent_node = adjacent_nodes->at(node_cntr);
            adjacency_matrix[matrix_row_cntr][adjacent_node->get_index()] = 1; 
        }
    }

    return adjacency_matrix;

}

void Graph::print_vertices(){
    auto vertices_map_begin = this->vertices->begin();
    auto vertices_map_end = this->vertices->end();

    Vertex *curr_vertex;

    int vector_cntr = 0;

    cout << endl;
    cout << "---------------------------------" << endl;
    cout << "           Vertices" << endl;
    cout << "---------------------------------" << endl;

    for ( auto vertices_it = vertices_map_begin; vertices_it != vertices_map_end; ++vertices_it) {
        curr_vertex = this->vertices->at(vector_cntr);
        curr_vertex->print_vertex();
        vector_cntr = vector_cntr + 1;
    }

    cout << "---------------------------------" << endl;
    cout << endl;
}

void Graph::print_edges(){
    
    auto edges_map_begin = this->edges->begin();
    auto edges_map_end = this->edges->end();

    Edge *curr_edge;

    cout << endl;
    cout << "---------------------------------" << endl;
    cout << "           Edges" << endl;
    cout << "---------------------------------" << endl;

    int vector_cntr = 0;

    for ( auto edges_it = edges_map_begin; edges_it != edges_map_end; ++edges_it ) {
        curr_edge = this->edges->at(vector_cntr);
        curr_edge->print_edge();
        vector_cntr = vector_cntr + 1;
    }

    cout << "---------------------------------" << endl;
    cout << endl;
}

void Graph::print_adjacent_vertices() {

    auto vertices_map_begin = this->vertices->begin();
    auto vertices_map_end = this->vertices->end();

    Vertex *curr_vertex;

    int vector_cntr = 0;

    cout << endl;
    cout << "---------------------------------" << endl;
    cout << "           Adjacent Vertices" << endl;
    cout << "---------------------------------" << endl;

    vector<Vertex*> *adjacent_nodes; 
    int num_adjacent_nodes;

    for ( auto vertices_it = vertices_map_begin; vertices_it != vertices_map_end; ++vertices_it) {
        curr_vertex = this->vertices->at(vector_cntr);

        adjacent_nodes = curr_vertex->get_adjacent_nodes();
        num_adjacent_nodes = adjacent_nodes->size();

        for (int node_cntr = 0; node_cntr < num_adjacent_nodes; node_cntr++ ) {
            if ( node_cntr == 0 ) { 
                cout << "\t" << curr_vertex->get_name() << ":\t" << adjacent_nodes->at(0)->get_name();
            } 
            else { cout << ", " << adjacent_nodes->at(node_cntr)->get_name(); }
        }

        cout << endl;

        vector_cntr = vector_cntr + 1;
    }

    cout << "---------------------------------" << endl;
    cout << endl;
}

struct distance_ordering {
    bool ordering(DijkstraDistanceStructure* first, DijkstraDistanceStructure* second) const {
        if ( first->get_distance() < second->get_distance() ) { return true; }
        else { return false; }
    }
};

void Graph::print_distances(vector<DijkstraDistanceStructure*>* priority_queue) {

    int PQ_size = priority_queue->size();

    cout << endl;
    cout << "-----Vertex Distances------" << endl;
    for ( int PQ_cntr = 0; PQ_cntr < PQ_size; PQ_cntr++ ){
        DijkstraDistanceStructure *current_DDS = priority_queue->at(PQ_cntr);

        cout << "\tVertex: " << current_DDS->get_vertex()->get_name();
        cout << "\tCurrent Distance: " << current_DDS->get_distance() << endl;
    }
    cout << "---------------------------" << endl;

}

vector<DijkstraDistanceStructure*>* Graph::init_priority_queue() {
    
    int num_vertices = this->vertices->size();

    vector<DijkstraDistanceStructure*> *priority_queue = new vector<DijkstraDistanceStructure*>();

    for ( int vertex_cntr = 0; vertex_cntr < num_vertices; vertex_cntr++ ) {
        if ( vertex_cntr == 0 ) {
            priority_queue->push_back( new DijkstraDistanceStructure(this->vertices->at(vertex_cntr), 0) );
        } else { 
            priority_queue->push_back( new DijkstraDistanceStructure(this->vertices->at(vertex_cntr), INT_MAX ) );

        }
    }

    return priority_queue;

}

void Graph::run_dijkstras_algorithm_for_shortest_path() {

    vector<DijkstraDistanceStructure*> *priority_queue = this->init_priority_queue();

    this->print_distances(priority_queue);

    make_heap(priority_queue->begin(), priority_queue->end(), distance_ordering());

    // while ( priority_queue.size() != 0 ) {
    //     priority_queue.front();
    //     priority_queue.erase();
    // }

}

//-----------------------------------------------------
//################# GRAPH METHODS END #################
//-----------------------------------------------------

