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

/*
 three cases to consider until there is no such a red node whose parent is red
 when it is case 1, the "redness" moves up 2 levels, case 2 and case 3 are terminating cases. Time complexity is O(h) = O(logn)
 */
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

/*
 The originalColor tracks the color of deleted node (when it has fewer than two children) or the color of successor (when the deleted node has two children).
 When this color is red, properties are not violated, otherwise do fixup
 Although the node is deleted, the blackness is preserved with toBeInspected. So toBeInspected could be red-and-black or double-black. fixup just either pushes this extra blackness upwards or resolves the blackness in the subtree when possible.
 */

void RBT::delete_node(RBTNode *targetNode) {
    char originalColor = targetNode->color;
    RBTNode *toBeInspected = root;
    if(targetNode->left == nil) {
        toBeInspected = targetNode->right;
        transplant(targetNode, targetNode->right);
    } else if(targetNode->right == nil) {
        toBeInspected = targetNode->left;
        transplant(targetNode, targetNode->left);
    } else {
        RBTNode *theSuccessor = successor(targetNode);
        originalColor = theSuccessor->color;
        toBeInspected = theSuccessor->right;
        if(theSuccessor->parent == targetNode)
            // is this redundant?
            toBeInspected->parent = theSuccessor;
        else {
            theSuccessor->right = targetNode->right;
            theSuccessor->right->parent = theSuccessor;
            transplant(theSuccessor, toBeInspected);
        }
        transplant(targetNode, theSuccessor);
        theSuccessor->left = targetNode->left;
        theSuccessor->left->parent = theSuccessor;
        theSuccessor->color = targetNode->color;
    }
    delete targetNode;
    // if the color of the deleted or moved node is red, red black properties are preserved
    if(originalColor == 'B') {
        delete_fixup(toBeInspected);
    }
}
/*
 The curr node has extra "blackness" that belongs to the deleted node.
 The idea is first make sure sibling is black, when its children are both black, the extra "blackness" is pass up to the parent; whenever one children of sibling is red, we do rotate and recolor to distribute this extra "blackness" among the subtree denoted by curr->parent without violating red black property
 */
void RBT::delete_fixup(RBTNode *curr) {
    while(curr != root && curr->color == 'B') {
        if(curr == curr->parent->left) {
            RBTNode *sibling = curr->parent->right;
            // case 1, the sibling has color red, recolor and rotate to make sibling color black
            if(sibling->color == 'R') {
                sibling->color = 'B';
                curr->parent->color = 'R';
                left_rotate(curr->parent);
                sibling = curr->parent->right;
            }
            // case 2-4 sibling has color black
            // case 2 two children are black, pass the extra black to the parent
            if(sibling->left->color == 'B' && sibling->right->color == 'B') {
                sibling->color = 'R';
                curr = curr->parent;
            } else {
                // case 3 and 4 are terminating cases
                // case 3 the sibling has a red left child, move the "redness" to the right of sibiling, transfer to case 4
                if(sibling->right->color == 'B') {
                    sibling->color = 'R';
                    sibling->left->color = 'B';
                    right_rotate(sibling);
                    sibling = curr->parent->right;
                }
                // case 4
                sibling->color = curr->parent->color;
                curr->parent->color = 'B';
                sibling->right->color = 'B';
                left_rotate(curr->parent);
                curr = root;
            }
        } else {
            RBTNode *sibling = curr->parent->left;
            // case 1, the sibling has color red, recolor and rotate to make sibling color black
            if(sibling->color == 'R') {
                sibling->color = 'B';
                curr->parent->color = 'R';
                right_rotate(curr->parent);
                sibling = curr->parent->left;
            }
            // case 2-4 sibling has color black
            // case 2 two children are black, pass the extra black to the parent
            if(sibling->left->color == 'B' && sibling->right->color == 'B') {
                sibling->color = 'R';
                curr = curr->parent;
            } else {
                // case 3 and 4 are terminating cases
                // case 3 the sibling has a red right child, move the "redness" to the left of sibiling, transfer to case 4
                if(sibling->left->color == 'B') {
                    sibling->color = 'R';
                    sibling->right->color = 'B';
                    left_rotate(sibling);
                    sibling = curr->parent->left;
                }
                // case 4
                sibling->color = curr->parent->color;
                curr->parent->color = 'B';
                sibling->left->color = 'B';
                right_rotate(curr->parent);
                curr = root;
            }
        }
    }
    // when case 2 (when black is passed to the parent and the parent is red) or case 4 (when curr is set to root to jump out of the loop)
    curr->color = 'B';
}
/*
 set u's parent as v's parent, and v as u's parent's child
 */
void RBT::transplant(RBTNode *u, RBTNode *v) {
    if(u == root)
        root = v;
    else {
        if(u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;
    }
    v->parent = u->parent;
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
        cout << curr->value << " " << curr->color << " ";
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




