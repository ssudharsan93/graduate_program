#ifndef TREENODE_H
#define TREENODE_H
#include <iostream>
#include <queue>
#include <map>

class TreeNode {
private:
    TreeNode *left_child;
    TreeNode *right_child;
    TreeNode *parent;
    int val;

public:
    TreeNode(int val);
    TreeNode* get_left_child();
    TreeNode* get_right_child();
    TreeNode* get_parent();
    void set_left_child(TreeNode *new_left_child);
    void set_right_child(TreeNode *new_right_child);
    void set_parent(TreeNode *new_parent);
    int get_val();
};

using namespace std;

TreeNode* insert_node(TreeNode *root, int val);
TreeNode* delete_node(TreeNode *root, int val);
TreeNode* get_successor(TreeNode *node);
TreeNode* get_predecessor(TreeNode *node);
void inorder_traversal(TreeNode *node); // print after left child call
void preorder_traversal(TreeNode *node); // print before left child or right child call
void postorder_traversal(TreeNode *node); // print after left child and right child call return
void breadth_first_search(TreeNode *node, queue<TreeNode*> *to_be_searched, queue<TreeNode*> *searched);
int get_node_count(TreeNode *node);
void print_tree(TreeNode *root);

#endif TREENODE_H