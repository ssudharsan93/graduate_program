#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

int main() {

    struct ListNode {
        int data;
        ListNode* next;
    };

    ListNode head, second, third, fourth, fifth;

    head.data = 10;
    head.next = &second;
    second.data = 60;
    second.next = &third;
    third.data = 40;
    third.next = &fourth;
    fourth.data = 25;
    fourth.next = &fifth;
    fifth.data = 85;
    fifth.next = nullptr;

    ListNode *current_node = &head;

    while (current_node->next != nullptr) {
        cout << current_node->data << ", ";
        current_node = current_node->next;
    }
    cout << current_node->data << endl;
}
