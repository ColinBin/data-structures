//
//  slist.hpp
//  slist
//
//  Created by Colin on 27/09/2017.
//  Copyright © 2017 Colin. All rights reserved.
//

#ifndef slist_hpp
#define slist_hpp

#include <iostream>

/*
 @brief list node for singly-linked list
 @attributes int key, sListNode *next
 */
struct sListNode {
    int key;
    sListNode *next;
    sListNode(int k): key(k), next(nullptr) {  }
};
/*
 @brief singly-linked list, support search, insert and delete
 */
class sList {
public:
    sList(): head(new sListNode(-1)) {  }
    ~sList();
    void insert_node(int key);  // always insert into the front
    sListNode *search_prev(int k);  // use prev for further deleting
    void delete_node(sListNode *prev);  // use prev for deleting
    bool empty() { return head->next == nullptr; }
    void print();
private:
    sListNode *head;
};
#endif /* slist_hpp */
