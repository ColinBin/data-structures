//
//  istack.hpp
//  data-structures
//
//  Created by Colin on 27/09/2017.
//  Copyright © 2017 Colin. All rights reserved.
//

#ifndef istack_hpp
#define istack_hpp

#include <iostream>
#include <stdexcept>
#include <vector>
/*
 @brief a fixed-size stack storing ints
 */
class iStack{
public:
    iStack(std::vector<int>::size_type sz): arr(sz, 0), top(0), size(sz) {  }
    void push(int ele);
    int pop();
    bool empty() { return top == 0; }
private:
    std::vector<int>::size_type top, size;
    std::vector<int> arr;
};
inline void iStack::push(int ele) {
    if(top == size) {
        throw std::overflow_error("Stack overflow: cannot push any elements!");
    } else {
        arr[top++] = ele;
    }
}
inline int iStack::pop() {
    if(empty()) {
        throw std::underflow_error("Stack underflow: the stack is empty");
    } else {
        return arr[--top];
    }
}

#endif /* istack_hpp */
