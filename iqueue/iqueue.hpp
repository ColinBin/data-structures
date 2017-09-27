//
//  iqueue.hpp
//  iqueue
//
//  Created by Colin on 27/09/2017.
//  Copyright © 2017 Colin. All rights reserved.
//

#ifndef iqueue_hpp
#define iqueue_hpp

#include <iostream>
#include <vector>
#include <stdexcept>
/*
 @brief a fixed-size queue storing ints
 */
class iQueue {
public:
    iQueue(std::vector<int>::size_type sz) : arr(sz, 0), head(0), tail(0), size(sz) {  }
    void enque(int ele);
    int deque();
    bool empty() { return head == tail; }
private:
    std::vector<int> arr;
    std::vector<int>::size_type head, tail, size;
};
inline void iQueue::enque(int ele) {
    if((tail + 1) % size == head) {
        throw std::overflow_error("Queue overflow: no room for more elements!");
    } else {
        arr[tail] = ele;
        if(tail == size -1) {
            tail = 0;
        } else {
            ++tail;
        }
    }
}
inline int iQueue::deque() {
    if(empty()) {
        throw std::underflow_error("Queue underflow: empty queue!");
    } else {
        if(tail == 0) {
            tail = size - 1;
        } else {
            --tail;
        }
        return arr[tail];
    }
}

#endif /* iqueue_hpp */
