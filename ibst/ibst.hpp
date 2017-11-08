//
//  ibst.hpp
//  ibst
//
//  Created by Colin on 05/11/2017.
//  Copyright © 2017 Colin. All rights reserved.
//

#ifndef ibst_hpp
#define ibst_hpp

#include <iostream>
#include <vector>

/*
 @brief: TreeNode for Binary Search Tree
 */
struct BSTNode {
    int val;        // value
    BSTNode *p;     // pointer to parent
    BSTNode *left;  // pointer to left child
    BSTNode *right; // pointer to right child
    BSTNode(int v) : val(v), p(nullptr), left(nullptr), right(nullptr) {  }
};

/*
 @brief: binary search tree
 */
class BST {
public:
    BST() : root(nullptr) {  }
    // parameter random denotes whether to shuffle the input before BST is constructed
    BST(std::vector<int> node_list, bool random = false);
    ~BST();
    bool empty() { return root == nullptr; }
    BSTNode *search(int target);
    BSTNode *successor(BSTNode *curr);
    BSTNode *predecessor(BSTNode *curr);
    BSTNode *minimum(BSTNode *curr);    // TODO make curr default to root
    BSTNode *maximum(BSTNode *curr);    // TODO make curr default to root
    void inorder_tree_walk();
    void preorder_tree_walk();
    void postorder_tree_walk(); 
    void insert_node(int value);
    void delete_node(BSTNode *targetNode);
private:
    void inorder_tree_walk_helper(BSTNode *curr);
    void preorder_tree_walk_helper(BSTNode *curr);
    void postorder_tree_walk_helper(BSTNode *curr);
    void transplant(BSTNode *u, BSTNode *v);
    void destruct_helper(BSTNode *curr);
    BSTNode *root;
};

#endif /* ibst_hpp */
