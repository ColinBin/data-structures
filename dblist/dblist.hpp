//
//  dblist.hpp
//  dblist
//
//  Created by Colin on 27/09/2017.
//  Copyright © 2017 Colin. All rights reserved.
//

#ifndef dblist_hpp
#define dblist_hpp

#include <iostream>
/*
 @brief list node for doubly-linked list
 */
struct dbListNode{
    int key;
    dbListNode *prev;
    dbListNode *next;
    dbListNode(int k): key(k), prev(this), next(this) {  }
};
/*
 @brief doubly-linked list with a pivot
 */
class dbList {
public:
    dbList(): pivot(new dbListNode(-1)) {  }
    ~dbList();
    void insert_node(int key);  // insert in the front
    bool empty() { return pivot->next == nullptr; }
    void print();
    void print_reverse();
    dbListNode *search(int k);
    void delete_node(dbListNode *target);
private:
    dbListNode *pivot;
};

#endif /* dblist_hpp */
