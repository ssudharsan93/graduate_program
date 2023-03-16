#include <iostream>
#include <cmath>

using namespace std;

//HEAP METHODS_START
int Parent(int index) {
    return floor( index / 2.0 );
}

int Left(int index) {
    return 2 * index;
}

int Right(int index) {
    return 2 * index + 1;
}

void swap( int heap[], int first_index, int second_index ) {

    int temp = heap[first_index];
    heap[first_index] = heap[second_index];
    heap[second_index] = temp;

}

void maxPercolateDown(int heap[], int index) {

    int heap_size = heap[0];

    int left_child_index, right_child_index, max_val;

    left_child_index = Left(index);
    right_child_index = Right(index);

    while ( ! ( left_child_index > heap_size ) || 
             ! ( right_child_index > heap_size ) ) {

        // if parent is less than both children heap property not violated.
        if ( ( heap[index] > heap[left_child_index] ) &&
             ( heap[index] > heap[right_child_index] ) ) {
                return;
        }

        // if only left child exists, swap if left child is less than parent.
        // Then return right away. We are at a leaf node.
        if ( right_child_index > heap_size ) {
            if ( heap[index] < heap[left_child_index] ) {
                swap(heap, index, left_child_index);
                return;
            }
        }
        
        // set min initially to left child
        max_val = heap[left_child_index];

        // if left child is greater than right child
        // swap with right child if right child is less than parent.
        if ( max_val < heap[right_child_index] ) {
            if ( heap[index] < heap[right_child_index] ) {
                swap(heap, index, right_child_index);
                index = right_child_index;
            }
        }
        
        // otherwise swap with left child 
        // if left child is less than parent.
        else { 
            if ( heap[index] < max_val ) {
                swap(heap, index, left_child_index);
                index = left_child_index;
            }
        }

        left_child_index = Left(index);
        right_child_index = Right(index);
    }

}

//Floyds algorithm
void maxBuildHeap(int heap[]){
    
    int heap_size = heap[0];
    int left_child_index, right_child_index;

    for ( int bh_cntr = heap_size; bh_cntr > 0; bh_cntr-- ) {
        left_child_index = Left(bh_cntr);
        right_child_index = Right(bh_cntr);

        if ( ( left_child_index > heap_size ) && 
             ( right_child_index > heap_size ) ) {
            continue;
        }

        else { 
            maxPercolateDown(heap, bh_cntr);
        }
    }


}

void minPercolateDown(int heap[], int index) {

    int heap_size = heap[0];

    int left_child_index, right_child_index, min_val;

    left_child_index = Left(index);
    right_child_index = Right(index);

    while ( ! ( left_child_index > heap_size ) || 
             ! ( right_child_index > heap_size ) ) {

        // if parent is less than both children heap property not violated.
        if ( ( heap[index] < heap[left_child_index] ) &&
             ( heap[index] < heap[right_child_index] ) ) {
                return;
        }

        // if only left child exists, swap if left child is less than parent.
        // Then return right away. We are at a leaf node.
        if ( right_child_index > heap_size ) {
            if ( heap[index] > heap[left_child_index] ) {
                swap(heap, index, left_child_index);
                return;
            }
        }
        
        // set min initially to left child
        min_val = heap[left_child_index];

        // if left child is greater than right child
        // swap with right child if right child is less than parent.
        if ( min_val > heap[right_child_index] ) {
            if ( heap[index] > heap[right_child_index] ) {
                swap(heap, index, right_child_index);
                index = right_child_index;
            }
        }
        
        // otherwise swap with left child 
        // if left child is less than parent.
        else { 
            if ( heap[index] > min_val ) {
                swap(heap, index, left_child_index);
                index = left_child_index;
            }
        }

        left_child_index = Left(index);
        right_child_index = Right(index);
    }

}

//Floyds algorithm
void minBuildHeap(int heap[]){
    
    int heap_size = heap[0];
    int left_child_index, right_child_index;

    for ( int bh_cntr = heap_size; bh_cntr > 0; bh_cntr-- ) {
        left_child_index = Left(bh_cntr);
        right_child_index = Right(bh_cntr);

        if ( ( left_child_index > heap_size ) && 
             ( right_child_index > heap_size ) ) {
            continue;
        }

        else { 
            minPercolateDown(heap, bh_cntr);
        }
    }

}

void MinHeapify(int heap[]){
    return;
}

void MaxHeapify(int heap[]){
    return;
}

void PrintHeap(int heap[]) {

    int heap_size = heap[0];

    cout << "[ ";
    
    for ( int heap_cntr = 1; heap_cntr < heap_size + 1; heap_cntr++ ) {
        cout << heap[heap_cntr] << " ";
    }
    
    cout << "]" << endl;
}

//HEAP METHODS_END



int main() {
    int heap_size = 15;
    int heap[heap_size + 1];

    heap[0] = heap_size;

    int input[15] = {
        40, 60, 20, 80, 50, 
        10, 30, 15, 5, 35, 
        25, 45, 55, 70, 90
    };

    for ( int heap_cntr = 1; heap_cntr < heap_size + 1; heap_cntr++ ) {
        heap[heap_cntr] = input[heap_cntr - 1]; 
    }

    cout << endl;
    cout << "Heap is: \t";
    cout << endl;

    PrintHeap(heap);
    //minBuildHeap(heap);
    maxBuildHeap(heap);

    cout << endl;
    cout << "After Max BuildHeap the Heap is: \t";
    cout << endl;
    
    PrintHeap(heap);

    cout << endl;

}



