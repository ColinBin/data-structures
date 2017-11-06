//
//  dblist.cpp
//  dblist
//
//  Created by Colin on 27/09/2017.
//  Copyright © 2017 Colin. All rights reserved.
//

#include "dblist.hpp"

using std::cout; using std::endl;

dbList::~dbList() {
    dbListNode *dummy = pivot->next;
    while(dummy != pivot) {
        dbListNode *toBeDeleted = dummy;
        dummy = dummy->next;
        delete toBeDeleted;
    }
    delete pivot;
}
void dbList::print() {
    dbListNode *dummy = pivot->next;
    while(dummy != pivot) {
        cout << dummy->key << " ";
        dummy = dummy->next;
    }
    cout << endl;
}
void dbList::print_reverse() {
    dbListNode *dummy = pivot->prev;
    while(dummy != pivot) {
        cout << dummy->key << " ";
        dummy = dummy->prev;
    }
    cout << endl;
}
void dbList::insert_node(int k) {
    dbListNode *newNode = new dbListNode(k);
    newNode->next = pivot->next;
    pivot->next->prev = newNode;
    pivot->next = newNode;
    newNode->prev = pivot;
}
dbListNode * dbList::search(int k) {
    dbListNode *dummy = pivot->next;
    while(dummy != pivot && dummy->key != k) {
        dummy = dummy->next;
    }
    if(dummy == pivot) {
        return nullptr;
    } else {
        return dummy;
    }
}
void dbList::delete_node(dbListNode *target) {
    dbListNode *toBeDelete = target;
    target->prev->next = target->next;
    target->next->prev = target->prev;
    delete toBeDelete;
}

