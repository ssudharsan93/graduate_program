#include "DirectedGraph.h"

//-----------------------------------------------------
//################# GRAPH METHODS START #################
//-----------------------------------------------------

DirectedGraph::DirectedGraph(){
    this->vertices = new vector<Vertex*>();
    this->directed_edges = new vector<DirectedEdge*>();
}

DirectedGraph::~DirectedGraph() {
    delete this->vertices;
    delete this->directed_edges;
}

void DirectedGraph::insert_vertex(Vertex *new_vertex){
    this->vertices->push_back(new_vertex);
}

void DirectedGraph::insert_directed_edge(DirectedEdge *new_directed_edge){

    new_directed_edge->get_origin()->add_adjacent_node(new_directed_edge->get_destination());
    new_directed_edge->get_destination()->add_adjacent_node(new_directed_edge->get_origin());
    new_directed_edge->get_origin()->add_outgoing_edge(new_directed_edge);
    new_directed_edge->get_destination()->add_incoming_edge(new_directed_edge);

    this->directed_edges->push_back(new_directed_edge);
}

void DirectedGraph::erase_vertex(Vertex *vertex_to_be_deleted){
    
    int vector_size = this->vertices->size();
    for ( int vector_cntr = 0; vector_cntr < vector_size; vector_cntr++ ){
        if ( this->vertices->at(vector_cntr) == vertex_to_be_deleted ){
            this->vertices->erase(this->vertices->begin() + vector_cntr);
        }
    }

}

void DirectedGraph::erase_edge(DirectedEdge *edge_to_be_deleted){

    int vector_size = this->directed_edges->size();
    for ( int vector_cntr = 0; vector_cntr < vector_size; vector_cntr++ ){
        if ( this->directed_edges->at(vector_cntr) == edge_to_be_deleted ){
            this->directed_edges->erase(this->directed_edges->begin() + vector_cntr);
        }
    }
}


vector<Vertex*>* DirectedGraph::get_vertices(){
    return this->vertices;
}

vector<DirectedEdge*>* DirectedGraph::get_directed_edges(){
    return this->directed_edges;
}

int** DirectedGraph::get_adjacency_matrix(){
    
    int matrix_n_param = this->vertices->size();

    int **adjacency_matrix = new int*[matrix_n_param]();
    Vertex *curr_vertex, *adjacent_node;
    vector<DirectedEdge*> *outgoing_edges;
    int num_outgoing_edges;

    DirectedEdge *curr_edge;

    for( int matrix_row_cntr = 0; matrix_row_cntr < matrix_n_param; matrix_row_cntr++ ) {
        adjacency_matrix[matrix_row_cntr] = new int[matrix_n_param]();
        curr_vertex = this->vertices->at(matrix_row_cntr);
        outgoing_edges = curr_vertex->get_outgoing_edges();
        num_outgoing_edges = outgoing_edges->size();
        
        for( int out_edge_cntr = 0; out_edge_cntr < num_outgoing_edges; out_edge_cntr++  ) {
            curr_edge = outgoing_edges->at(out_edge_cntr);
            adjacent_node = curr_edge->opposite_vertex(curr_vertex);
            adjacency_matrix[matrix_row_cntr][adjacent_node->get_index()] = 1; 
        }
    }

    return adjacency_matrix;

}

int** DirectedGraph::get_incidence_matrix(){
    
    int num_vertices = this->vertices->size();
    int num_columns = this->directed_edges->size();

    int **incidence_matrix = new int*[num_vertices]();
    Vertex *curr_vertex, *adjacent_node;

    DirectedEdge *curr_edge;

    for( int matrix_row_cntr = 0; matrix_row_cntr < num_vertices; matrix_row_cntr++ ) {
        incidence_matrix[matrix_row_cntr] = new int[num_columns]();
        curr_vertex = this->vertices->at(matrix_row_cntr);

        for( int matrix_col_cntr = 0; matrix_col_cntr < num_columns; matrix_col_cntr++ ) {
            curr_edge = this->directed_edges->at(matrix_col_cntr);
            if ( curr_vertex == curr_edge->get_origin() ){
                incidence_matrix[matrix_row_cntr][matrix_col_cntr] = 1;
            }

            else if ( curr_vertex == curr_edge->get_destination() ){
                incidence_matrix[matrix_row_cntr][matrix_col_cntr] = -1;
            }

            else { 
                incidence_matrix[matrix_row_cntr][matrix_col_cntr] = 0;
            }
        }

    }

    return incidence_matrix;

}

void DirectedGraph::print_vertices(){
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

void DirectedGraph::print_directed_edges(){
    
    auto edges_map_begin = this->directed_edges->begin();
    auto edges_map_end = this->directed_edges->end();

    DirectedEdge *curr_edge;

    cout << endl;
    cout << "---------------------------------" << endl;
    cout << "           Directed Edges" << endl;
    cout << "---------------------------------" << endl;

    int vector_cntr = 0;

    cout << "\tEdge (Index) - ";
    cout << "\t\t(Origin ,Destination)\t\tWeight: (Weight)" << endl;

    for ( auto edges_it = edges_map_begin; edges_it != edges_map_end; ++edges_it ) {
        curr_edge = this->directed_edges->at(vector_cntr);
        curr_edge->print_directed_edge();
        vector_cntr = vector_cntr + 1;
    }

    cout << "---------------------------------" << endl;
    cout << endl;
}

void DirectedGraph::print_adjacent_vertices() {

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

// int dfs_label_vertex(Vertex* curr_vertex, int label){

//     curr_vertex->set_visited();
//     vector<DirectedEdge*> *outgoing_edges = curr_vertex->get_outgoing_edges();
//     int num_outgoing_edges = outgoing_edges->size();

//     DirectedEdge *curr_edge;
//     Vertex *opposite_vertex;

//     for ( int out_edge_cntr = 0; out_edge_cntr < num_outgoing_edges; out_edge_cntr++ ){
//         curr_edge = outgoing_edges->at(out_edge_cntr);
//         opposite_vertex = curr_edge->opposite_vertex(curr_vertex);
//         if ( ! ( opposite_vertex->is_visited() ) ) {
//             label = dfs_label_vertex(opposite_vertex, label);
//         }
//     }

//     //cout << "Label to be assigned: " << label << endl;
//     curr_vertex->set_label(label);

//     return label - 1;
// }

int DirectedGraph::dfs_label_vertex(Vertex* curr_vertex, int label){

    curr_vertex->set_visited();
    vector<DirectedEdge*> *outgoing_edges = curr_vertex->get_outgoing_edges();
    int num_outgoing_edges = outgoing_edges->size();

    DirectedEdge *curr_edge;
    Vertex *opposite_vertex;

    for ( int out_edge_cntr = 0; out_edge_cntr < num_outgoing_edges; out_edge_cntr++ ){
        curr_edge = outgoing_edges->at(out_edge_cntr);
        opposite_vertex = curr_edge->opposite_vertex(curr_vertex);
        if ( ! ( opposite_vertex->is_visited() ) ) {
            label = this->dfs_label_vertex(opposite_vertex, label);
        }
    }

    curr_vertex->set_label(label);

    return label - 1;
}

void DirectedGraph::dfs_topological_sort(){
    int num_vertices = this->vertices->size();
    int label = num_vertices;
    Vertex *curr_vertex;

    for( int clr_vertex_cntr = 0; clr_vertex_cntr < num_vertices; clr_vertex_cntr++ ){
        this->vertices->at(clr_vertex_cntr)->reset_label();
        this->vertices->at(clr_vertex_cntr)->clear_visited();
    }
    
    for( int dfs_vertex_cntr = 0; dfs_vertex_cntr < num_vertices; dfs_vertex_cntr++ ){
        curr_vertex = this->vertices->at(dfs_vertex_cntr);
        if ( ! ( curr_vertex->is_visited() ) ) {
            label = this->dfs_label_vertex(curr_vertex, label);
        }
    }
    
}

void DirectedGraph::bfs_topological_sort(){
    
    int label = 0;
    int num_vertices = this->vertices->size();
    int *pred_count = new int[num_vertices];
    
    int index, num_incoming_edges, num_outgoing_edges;
    Vertex *curr_vertex, *opposite_vertex;
    DirectedEdge *curr_outgoing_edge;
    vector<DirectedEdge*> *outgoing_edges;
    
    queue<Vertex*> *no_predecessors = new queue<Vertex*>();

    for( int pred_set_cntr = 0; pred_set_cntr < num_vertices; pred_set_cntr++ ){
        curr_vertex = this->vertices->at(pred_set_cntr);
        num_incoming_edges = curr_vertex->get_incoming_edges()->size();

        curr_vertex->reset_label();
        pred_count[pred_set_cntr] = num_incoming_edges;

        if ( num_incoming_edges == 0 ){
            no_predecessors->push(curr_vertex);
            //cout << "Adding " << curr_vertex->get_name() << " ..." << endl;
        }
    }

    // cout << "\t [ ";
    // for( int pred_vertex_cntr = 0; pred_vertex_cntr < num_vertices; pred_vertex_cntr++ ){
    //     cout << pred_count[pred_vertex_cntr] << " ";
    // }

    // cout << "]" << endl;

    while ( no_predecessors->size() != 0 ){
        curr_vertex = no_predecessors->front();
        //cout << "Removing " << curr_vertex->get_name() << " ..." << endl;
        curr_vertex->set_label(label);
        label = label + 1;
        no_predecessors->pop();
        outgoing_edges = curr_vertex->get_outgoing_edges();
        num_outgoing_edges = outgoing_edges->size();

        for ( int update_cntr = 0; update_cntr < num_outgoing_edges; update_cntr++ ){
            curr_outgoing_edge = outgoing_edges->at(update_cntr);
            opposite_vertex = curr_outgoing_edge->opposite_vertex(curr_vertex);
            index = opposite_vertex->get_index();

            pred_count[index] = pred_count[index] - 1;
            // cout << "Decreasing count for " << opposite_vertex->get_name() 
            //      << " to " << pred_count[index] << " ..." << endl;

            if ( pred_count[index] == 0 ){
                no_predecessors->push(opposite_vertex);
                //cout << "Adding " << opposite_vertex->get_name() << " ..." << endl;
            }
        }

    }


    // cout << "\t [ ";
    // for( int pred_vertex_cntr = 0; pred_vertex_cntr < num_vertices; pred_vertex_cntr++ ){
    //     cout << pred_count[pred_vertex_cntr] << " ";
    // }
    // cout << "]" << endl;

    delete no_predecessors;


}


//-----------------------------------------------------
//################# GRAPH METHODS END #################
//-----------------------------------------------------

