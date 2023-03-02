#include <iostream>

using namespace std;

class TreeNode {
private:
    TreeNode *left_child;
    TreeNode *right_child;
    TreeNode *parent;

public:
    void get_left_child();
    void get_right_child();
    void get_parent();
    void set_left_child();
    void set_right_child();
    void set_parent();

}

class BinarySearchTree {
private:
    TreeNode *root;
public:
    void get_root();
    void set_root();
    void insert_node();
    void delete_node();
    void inorder_traversal(); // print after left child call
    void preorder_traversal(); // print before left child or right child call
    void postorder_traversal(); // print after left child and right child call return
    void print_tree();
};
