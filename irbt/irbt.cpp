//
//  irbt.cpp
//  irbt
//
//  Created by Colin on 07/11/2017.
//  Copyright © 2017 Colin. All rights reserved.
//

#include "irbt.hpp"
#include <vector>

using std::cout; using std::endl;
using std::vector;

RBT::RBT(vector<int> value_list) : root(nil) {
    // when the value list is empty
    if(value_list.size() == 0) {
        root = nil;
        return;
    }
    for(int value : value_list) {
        insert_node(value);
    }
}
RBT::~RBT() {
    if(!empty()) {
        destruct_helper(root);
    }
    delete nil;
}
void RBT::insert_node(int val) {
    // if empty
    if(empty()) {
        root = new RBTNode(val);
        root->left = root->right = root->parent = nil;
        return;
    }
    // not empty
    RBTNode *dummy = root, *p = nil;
    while(dummy != nil) {
        if(dummy->value > val) {
            p = dummy;
            dummy = dummy->left;
        } else {
            p = dummy;
            dummy = dummy->right;
        }
    }
    RBTNode *newNode = new RBTNode(val, 'R');
    newNode->left = newNode->right = nil;
    newNode->parent = p;
    if(val < p->value)
        p->left = newNode;
    else
        p->right = newNode;
    insert_fixup(newNode);
}
void RBT::insert_fixup(RBTNode *curr) {
    // curr->color is Red, loop only if its parent is also red
    // if the while loop is entered, curr's grandparent must be exist and is black
    while(curr->parent->color == 'R') {
        RBTNode *p = curr->parent, *gp = curr->parent->parent;
        if(p == gp->left) {
            RBTNode *uncle = gp->right;
            // case one, recolor parent, grandparent and uncle. Move curr two levels up
            if(uncle->color == 'R') {
                p->color = uncle->color = 'B';
                gp->color = 'R';
                curr = gp;
            } else {
                // case two, curr is right of parent, do a rotate
                if(curr == p->right)
                    left_rotate(p);
                // case three, terminating step, rotate and recolor
                right_rotate(gp);
                curr->color = 'B';
                gp->color = 'R';
                break;
            }
        } else {
            RBTNode *uncle = gp->left;
            // case one, recolor parent, grandparent and uncle, Move curr two level up
            if(uncle->color == 'R') {
                p->color = uncle->color = 'B';
                gp->color = 'R';
                curr = gp;
            } else {
                // case two, curr is left of parent, rotate
                if(curr == p->left)
                    right_rotate(p);
                // case three, terminating step, rotate and recolor
                left_rotate(gp);
                curr->color = 'B';
                gp->color = 'R';
                break;
            }
        }
    }
    // when loop terminates, curr may be root, change to black
    root->color = 'B';
}
void RBT::left_rotate(RBTNode *curr) {
    RBTNode *rightChild = curr->right;
    curr->right = rightChild->left;
    if(rightChild->left != nil) {
        rightChild->left->parent = curr;
    }
    rightChild->parent = curr->parent;
    if(curr->parent != nil) {
        if(curr == curr->parent->left)
            curr->parent->left = rightChild;
        else
            curr->parent->right = rightChild;
    } else {
        root = rightChild;
    }
    curr->parent = rightChild;
    rightChild->left = curr;
}
void RBT::right_rotate(RBTNode *curr) {
    RBTNode *leftChild = curr->left;
    curr->left = leftChild->right;
    if(leftChild->right != nil){
        leftChild->right->parent = curr;
    }
    leftChild->parent = curr->parent;
    if(curr->parent != nil) {
        if(curr == curr->parent->left)
            curr->parent->left = leftChild;
        else {
            curr->parent->right = leftChild;
        }
    } else {
        root = leftChild;
    }
    curr->parent = leftChild;
    leftChild->right = curr;
}
void RBT::destruct_helper(RBTNode *curr) {
    if(curr != nil) {
        destruct_helper(curr->left);
        destruct_helper(curr->right);
        delete curr;
    }
}
void RBT::inorder_tree_walk() {
    inorder_tree_walk_helper(root);
    cout << endl;
}
void RBT::inorder_tree_walk_helper(RBTNode *curr) {
    if(curr != nil) {
        inorder_tree_walk_helper(curr->left);
        cout << curr->value << " ";
        inorder_tree_walk_helper(curr->right);
    }
}
RBTNode *RBT::search(int target) {
    RBTNode *dummy = root;
    while(dummy != nil) {
        if(target == dummy->value)
            return dummy;
        else if(target > dummy->value) {
            if(dummy->right != nil)
                dummy = dummy->right;
            else
                return nil;
        } else {
            if(dummy->left != nil)
                dummy = dummy->left;
            else
                return nil;
        }
    }
    return dummy;
}

RBTNode *RBT::minimum(RBTNode *curr) {
    if(curr == nil)
        return nil;
    while(curr->left != nil)
        curr = curr->left;
    return curr;
}
RBTNode *RBT::maximum(RBTNode *curr) {
    if(curr == nil)
        return nil;
    while(curr->right != nil)
        curr = curr->right;
    return curr;
}
RBTNode *RBT::successor(RBTNode *curr) {
    if(curr == nil)
        return nil;
    if(curr->right != nil)
        return minimum(curr->right);
    RBTNode *p = curr->parent;
    while(p != nil && curr == p->right) {
        curr = p;
        p = p->parent;
    }
    return p;
}
RBTNode *RBT::predecessor(RBTNode *curr) {
    if(curr == nil)
        return nil;
    if(curr->left != nil)
        return maximum(curr->left);
    RBTNode *p = curr->parent;
    while(p != nil && curr == p->left) {
        curr = p;
        p = p->parent;
    }
    return p;
}




