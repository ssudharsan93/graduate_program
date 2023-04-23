#include <ctime>
#include <cstdlib>
#include <iostream>
#include <iomanip>

#include "DirectedGraph.h"

void print_matrix(int **matrix, int num_rows, int num_columns) {

    for ( int row_cntr = 0; row_cntr < num_rows; row_cntr++ ) {

        cout << "v" << row_cntr << "\t[ ";
        
        for ( int col_cntr = 0; col_cntr < num_columns; col_cntr++ ) {
            if ( col_cntr == 0 ) { 
                cout << setw(5) << right << matrix[row_cntr][col_cntr]; 
            }
            else { 
                cout << ", " << setw(5) << right << matrix[row_cntr][col_cntr]; 
            
            }
        }

        cout << "     ]" << endl;

    }
}

void print_incidence_matrix(DirectedGraph* dataset, int index){
    cout << endl;
    cout << "---------------------------------" << endl;
    cout << "    Incidence Matrix Dataset " << index << endl;
    cout << "---------------------------------" << endl;

    int **incidence_matrix = dataset->get_incidence_matrix();

    int matrix_row_size = dataset->get_vertices()->size();
    int matrix_col_size = dataset->get_directed_edges()->size();

    cout << "  \t";

    for ( int col_cntr = 0; col_cntr < matrix_col_size; col_cntr++ ){ 
        cout << setw(6) << right << "e" << col_cntr;
    }

    cout << endl;
    cout << endl;

    print_matrix(incidence_matrix, matrix_row_size, matrix_col_size);

    cout << endl;
    cout << "---------------------------------" << endl;
    cout << endl;
}

void print_adjacency_matrix(DirectedGraph* dataset, int index){
    cout << endl;
    cout << "---------------------------------" << endl;
    cout << "    Adjacency Matrix Dataset " << index << endl;
    cout << "---------------------------------" << endl;

    int **adjacency_matrix = dataset->get_adjacency_matrix();

    int matrix_n = dataset->get_vertices()->size();

    cout << "  \t";

    for ( int row_cntr = 0; row_cntr < matrix_n; row_cntr++ ){ 
        cout << setw(6) << right << "v" << row_cntr;
    }

    cout << endl;
    cout << endl;

    print_matrix(adjacency_matrix, matrix_n, matrix_n);

    cout << endl;
    cout << "---------------------------------" << endl;
    cout << endl;
}

void print_dataset(DirectedGraph* dataset, int index){
    cout << endl;
    cout << "#################################" << endl;
    cout << "          Dataset " << index << endl;
    cout << "#################################" << endl;
    
    dataset->print_vertices();
    dataset->print_adjacent_vertices();
    dataset->print_directed_edges();
    
    print_adjacency_matrix(dataset, index);
    print_incidence_matrix(dataset, index);

    cout << endl;
    cout << "################################" << endl;
    cout << endl;
}

DirectedGraph* create_and_insert_vertices_and_edges2(DirectedGraph* dataset) {
    Vertex *one1 = new Vertex("1", 0);
    Vertex *two1 = new Vertex("2", 1);
    Vertex *three1 = new Vertex("3", 2);
    Vertex *four1 = new Vertex("4", 3);
    Vertex *five1 = new Vertex("5", 4);
    Vertex *six1 = new Vertex("6", 5);
    Vertex *seven1 = new Vertex("7", 6);
    Vertex *eight1 = new Vertex("8", 7);

    dataset->insert_vertex(one1);
    dataset->insert_vertex(two1);
    dataset->insert_vertex(three1);
    dataset->insert_vertex(four1);
    dataset->insert_vertex(five1);
    dataset->insert_vertex(six1);
    dataset->insert_vertex(seven1);
    dataset->insert_vertex(eight1);

    DirectedEdge *e0 = new DirectedEdge(one1, two1, 0, 0);
    DirectedEdge *e1 = new DirectedEdge(one1, five1, 1, 0);
    DirectedEdge *e2 = new DirectedEdge(one1, six1, 2, 0);
    DirectedEdge *e3 = new DirectedEdge(two1, three1, 3, 0);
    DirectedEdge *e4 = new DirectedEdge(two1, five1, 4, 0);
    DirectedEdge *e5 = new DirectedEdge(two1, seven1, 5, 0);
    DirectedEdge *e6 = new DirectedEdge(three1, four1, 6, 0);
    DirectedEdge *e7 = new DirectedEdge(four1, five1, 7, 0);
    DirectedEdge *e8 = new DirectedEdge(five1, seven1, 8, 0);
    DirectedEdge *e9 = new DirectedEdge(five1, eight1, 9, 0);
    DirectedEdge *e10 = new DirectedEdge(six1, five1, 10, 0);
    DirectedEdge *e11 = new DirectedEdge(six1, eight1, 11, 0);
    DirectedEdge *e12 = new DirectedEdge(seven1, four1, 12, 0);
    DirectedEdge *e13 = new DirectedEdge(seven1, eight1, 13, 0);

    dataset->insert_directed_edge(e0);
    dataset->insert_directed_edge(e1);
    dataset->insert_directed_edge(e2);
    dataset->insert_directed_edge(e3);
    dataset->insert_directed_edge(e4);
    dataset->insert_directed_edge(e5);
    dataset->insert_directed_edge(e6);
    dataset->insert_directed_edge(e7);
    dataset->insert_directed_edge(e8);
    dataset->insert_directed_edge(e9);
    dataset->insert_directed_edge(e10);
    dataset->insert_directed_edge(e11);
    dataset->insert_directed_edge(e12);
    dataset->insert_directed_edge(e13);

    return dataset;
}

DirectedGraph* create_and_insert_vertices_and_edges(DirectedGraph* dataset) {

    Vertex *m1 = new Vertex("m", 0);
    Vertex *n1 = new Vertex("n", 1);
    Vertex *o1 = new Vertex("o", 2);
    Vertex *p1 = new Vertex("p", 3);
    Vertex *q1 = new Vertex("q", 4);
    Vertex *r1 = new Vertex("r", 5);
    Vertex *s1 = new Vertex("s", 6);
    Vertex *t1 = new Vertex("t", 7);
    Vertex *u1 = new Vertex("u", 8);
    Vertex *v1 = new Vertex("v", 9);
    Vertex *w1 = new Vertex("w", 10);
    Vertex *x1 = new Vertex("x", 11);
    Vertex *y1 = new Vertex("y", 12);
    Vertex *z1 = new Vertex("z", 13);

    dataset->insert_vertex(m1);
    dataset->insert_vertex(n1);
    dataset->insert_vertex(o1);
    dataset->insert_vertex(p1);
    dataset->insert_vertex(q1);
    dataset->insert_vertex(r1);
    dataset->insert_vertex(s1);
    dataset->insert_vertex(t1);
    dataset->insert_vertex(u1);
    dataset->insert_vertex(v1);
    dataset->insert_vertex(w1);
    dataset->insert_vertex(x1);
    dataset->insert_vertex(y1);
    dataset->insert_vertex(z1);

    DirectedEdge *e0 = new DirectedEdge(m1, q1, 0, 0);
    DirectedEdge *e1 = new DirectedEdge(m1, r1, 1, 0);
    DirectedEdge *e2 = new DirectedEdge(m1, x1, 2, 0);
    DirectedEdge *e3 = new DirectedEdge(n1, o1, 3, 0);
    DirectedEdge *e4 = new DirectedEdge(n1, q1, 4, 0);
    DirectedEdge *e5 = new DirectedEdge(n1, u1, 5, 0);
    DirectedEdge *e6 = new DirectedEdge(o1, r1, 6, 0);
    DirectedEdge *e7 = new DirectedEdge(o1, s1, 7, 0);
    DirectedEdge *e8 = new DirectedEdge(o1, v1, 8, 0);
    DirectedEdge *e9 = new DirectedEdge(p1, o1, 9, 0);
    DirectedEdge *e10 = new DirectedEdge(p1, s1, 10, 0);
    DirectedEdge *e11 = new DirectedEdge(p1, z1, 11, 0);
    DirectedEdge *e12 = new DirectedEdge(q1, t1, 12, 0);
    DirectedEdge *e13 = new DirectedEdge(r1, u1, 13, 0);
    DirectedEdge *e14 = new DirectedEdge(r1, y1, 14, 0);
    DirectedEdge *e15 = new DirectedEdge(s1, r1, 15, 0);
    DirectedEdge *e16 = new DirectedEdge(u1, t1, 16, 0);
    DirectedEdge *e17 = new DirectedEdge(v1, w1, 17, 0);
    DirectedEdge *e18 = new DirectedEdge(v1, x1, 18, 0);
    DirectedEdge *e19 = new DirectedEdge(w1, z1, 19, 0);
    DirectedEdge *e20 = new DirectedEdge(y1, v1, 20, 0);

    dataset->insert_directed_edge(e0);
    dataset->insert_directed_edge(e1);
    dataset->insert_directed_edge(e2);
    dataset->insert_directed_edge(e3);
    dataset->insert_directed_edge(e4);
    dataset->insert_directed_edge(e5);
    dataset->insert_directed_edge(e6);
    dataset->insert_directed_edge(e7);
    dataset->insert_directed_edge(e8);
    dataset->insert_directed_edge(e9);
    dataset->insert_directed_edge(e10);
    dataset->insert_directed_edge(e11);
    dataset->insert_directed_edge(e12);
    dataset->insert_directed_edge(e13);
    dataset->insert_directed_edge(e14);
    dataset->insert_directed_edge(e15);
    dataset->insert_directed_edge(e16);
    dataset->insert_directed_edge(e17);
    dataset->insert_directed_edge(e18);
    dataset->insert_directed_edge(e19);
    dataset->insert_directed_edge(e20);
    
    return dataset;
}

void run_test() {
    
    DirectedGraph *dataset = new DirectedGraph();
    DirectedGraph *dataset2 = new DirectedGraph();

    dataset = create_and_insert_vertices_and_edges(dataset);
    dataset2 = create_and_insert_vertices_and_edges2(dataset2);

    print_dataset(dataset, 1);
    print_dataset(dataset2, 2);
    
}

int main() {
    run_test();
}