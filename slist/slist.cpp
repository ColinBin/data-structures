//
//  slist.cpp
//  slist
//
//  Created by Colin on 27/09/2017.
//  Copyright © 2017 Colin. All rights reserved.
//

#include "slist.hpp"
using std::cout; using std::endl;

sList::~sList() {
    sListNode *dummy = head->next;
    while(dummy != nullptr) {
        sListNode *toBeDeleted = dummy;
        dummy = dummy->next;
        delete toBeDeleted;
    }
    delete head;
}

void sList::insert_node(int key) {
    sListNode *newNode = new sListNode(key);
    if(head->next == nullptr) {
        head->next = newNode;
    } else {
        newNode->next = head->next;
        head->next = newNode;
    }
}

sListNode *sList::search_prev(int k) {
    sListNode *dummy = head;
    while(dummy->next != nullptr && dummy->next->key != k) {
        dummy = dummy->next;
    }
    // if dummy->next == nullptr, there is not a match
    if(dummy->next == nullptr) {
        return nullptr;
    } else {
        return dummy;
    }
    
}
void sList::delete_node(sListNode *prev) {
    sListNode *toBeDeleted = prev->next;
    prev->next = prev->next->next;
    delete toBeDeleted;
}
void sList::print() {
    sListNode *dummy = head->next;
    while(dummy != nullptr) {
        cout << dummy->key << " ";
        dummy = dummy->next;
    }
    cout << endl;
}
