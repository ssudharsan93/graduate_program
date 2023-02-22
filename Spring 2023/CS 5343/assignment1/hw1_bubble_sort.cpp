#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "ListNode.h"

using namespace std;

int main() {

    int LIST_SIZE = 15;

    ListNode *head = NULL;

    int new_elem;
    ListNode* curr_elem;

    //set a new seed value so rand() produces new values
    srand(time(NULL));

    // we want 15 elements in our linked list.
    for (int populate_ctr = 0; populate_ctr < LIST_SIZE; populate_ctr++ ) {
        // get a random value for the linked list between 1 and 100.
        new_elem = rand() % 100 + 1;

        // if head is NULL we are creating the first element
        // and putting it in the linked list.
        if (head == NULL) {
            head = new ListNode( new_elem );
            curr_elem = head;
        }

        // otherwise we are adding another element
        // and putting it in the linked list; we need to
        // have the last element's next pointer point to the
        // new list node. we also need to set the current
        // element to refer to the new list node.
        else {
            ListNode* new_node = new ListNode( new_elem );
            curr_elem->set_next(new_node);
            curr_elem = new_node;

        }
    }

    cout << endl;
    cout << "################################################" << endl;
    cout << "List Node Bubble Sort:" << endl;
    cout << "################################################" << endl;
    cout << endl;

    cout << "\tOriginal: " << endl;
    cout << "\t\t";
    head->print_values();
    cout << endl;

    head = bubble_sort(head, LIST_SIZE);

    cout << "\tSorted: " << endl;
    cout << "\t\t";
    head->print_values();

    cout << endl;
    cout << endl;

}
