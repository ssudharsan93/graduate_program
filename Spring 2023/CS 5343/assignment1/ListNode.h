#include <iostream>

using namespace std;

class ListNode {

    ListNode *next;
    int val;

public:
    ListNode();
    ListNode(int value);
    ListNode* get_next();
    void set_next(ListNode *next_node);
    int get_val();
    void set_val(int value);
    void print_values();
};

void swap (ListNode *first, ListNode *second);
ListNode* bubble_sort(ListNode *head, int size);
