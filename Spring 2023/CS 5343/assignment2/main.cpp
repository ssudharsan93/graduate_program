#include <iostream>
#include "TreeNode.h"

using namespace std;


//40, 60, 20, 80, 50, 10, 30, 15, 5, 35, 25, 45, 55, 70, 90, 32, 33, 48, 46
int main() {
    
    TreeNode *root = NULL;
    TreeNode *node1 = NULL;
    TreeNode *node2 = NULL;
    TreeNode *node3 = NULL;
    TreeNode *node4 = NULL;
    TreeNode *node5 = NULL;
    TreeNode *node6 = NULL;
    TreeNode *node7 = NULL;
    TreeNode *node8 = NULL;
    TreeNode *node9 = NULL;
    TreeNode *node10 = NULL;
    TreeNode *node11 = NULL;
    TreeNode *node12 = NULL;
    TreeNode *node13 = NULL;
    TreeNode *node14 = NULL;
    TreeNode *node15 = NULL;
    TreeNode *node16 = NULL;
    TreeNode *node17 = NULL;
    TreeNode *node18 = NULL;
    
    root = insert_node(root, 40);
    node1 = insert_node(root, 60);
    node2 = insert_node(root, 20);
    node3 = insert_node(root, 80);
    node4 = insert_node(root, 50);
    node5 = insert_node(root, 10);
    node6 = insert_node(root, 30);
    node7 = insert_node(root, 15);
    node8 = insert_node(root, 5);
    node9 = insert_node(root, 35);
    node10 = insert_node(root, 25);
    node11 = insert_node(root, 45);
    node12 = insert_node(root, 55);
    node13 = insert_node(root, 70);
    node14 = insert_node(root, 90);
    node15 = insert_node(root, 32);
    node16 = insert_node(root, 33);
    node17 = insert_node(root, 48);
    node18 = insert_node(root, 46);

    TreeNode *test_pred1 = get_predecessor(node1);
    TreeNode *test_pred2 = get_predecessor(node8);
    TreeNode *test_pred3 = get_predecessor(root);
    TreeNode *test_pred4 = get_predecessor(node9);
    TreeNode *test_succ1 = get_successor(root);
    TreeNode *test_succ2 = get_successor(node11);

    if ( test_pred1 != NULL ) { 
        cout << "Predecessor of " << node1->get_val() << " is " <<  test_pred1->get_val() << endl;
    } else { cout << "Predecessor of " << node1->get_val() << " is NULL. " << endl; }

    if ( test_pred2 != NULL ) { 
        cout << "Predecessor of " << node8->get_val() << " is " <<  test_pred2->get_val() << endl;
    } else { cout << "Predecessor of " << node8->get_val() << " is NULL. " << endl; }

    if ( test_pred3 != NULL ) { 
        cout << "Predecessor of " << root->get_val() << " is " <<  test_pred3->get_val() << endl;
    } else { cout << "Predecessor of " << root->get_val() << " is NULL. " << endl; }

    if ( test_pred4 != NULL ) { 
        cout << "Predecessor of " << node9->get_val() << " is " <<  test_pred4->get_val() << endl;
    } else { cout << "Predecessor of " << node9->get_val() << " is NULL. " << endl; }

    if ( test_succ1 != NULL ) { 
        cout << "Successor of " << root->get_val() << " is " <<  test_succ1->get_val() << endl;
    } else { cout << "Successor of " << root->get_val() << " is NULL. " << endl; }

    if ( test_succ2 != NULL ) { 
        cout << "Successor of " << node11->get_val() << " is " <<  test_succ2->get_val() << endl;
    } else { cout << "Successor of " << node11->get_val() << " is NULL. " << endl; }

    inorder_traversal(root);
    cout << endl;

    root = delete_node(root, 40);

    inorder_traversal(root);
    cout << endl;

    root = delete_node(root, 20);

    inorder_traversal(root);
    cout << endl;

}