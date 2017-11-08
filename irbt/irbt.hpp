//
//  irbt.hpp
//  irbt
//
//  Created by Colin on 07/11/2017.
//  Copyright © 2017 Colin. All rights reserved.
//

#ifndef irbt_hpp
#define irbt_hpp

#include <iostream>
#include <vector>

/*
 @brief: The node in a red-black tree
 */
struct RBTNode {
    int value;        // value stored
    char color;     // 'R' or 'B'
    RBTNode *left;  // left child
    RBTNode *right; // right child
    RBTNode *parent;     // parent
    RBTNode(int val, char c= 'B') : value(val), left(nullptr), right(nullptr), parent(nullptr), color(c) {  }
};

/*
 @brief: Red Black Tree class
 */
class RBT {
public:
    RBT() : root(nil) {  }
    RBT(std::vector<int> value_list);
    ~RBT();
    bool empty() { return root == nil; }
    RBTNode *search(int target);
    RBTNode *successor(RBTNode *curr);
    RBTNode *predecessor(RBTNode *curr);
    RBTNode *minimum(RBTNode *curr);
    RBTNode *maximum(RBTNode *curr);
    void inorder_tree_walk();
    void insert_node(int value);
    void delete_node(RBTNode *targetNode);
    RBTNode *nil = new RBTNode(-1);     // nil node TODO make const
private:
    void left_rotate(RBTNode *curr);
    void right_rotate(RBTNode *curr);
    void transplant(RBTNode *u, RBTNode *v);
    void insert_fixup(RBTNode *curr);
    
    void inorder_tree_walk_helper(RBTNode *curr);
    void destruct_helper(RBTNode *curr);
    RBTNode *root;      // TODO use inclass initializer make root nil?
};

#endif /* irbt_hpp */
