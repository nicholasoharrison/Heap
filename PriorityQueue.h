#pragma once
#include "ArrayHeap.h"



class PriorityQueue : public ArrayHeap{
public:
    PriorityQueue(int enteredCapacity = 10) {
       /* if (enteredCapacity == 0) {
            ArrayHeap::capacity = 10;
        }
        else {
            ArrayHeap::capacity = enteredCapacity;
        }
        ArrayHeap::currentSize = 0;
        ArrayHeap::heapArray = new priorityData[ArrayHeap::capacity + 1];*/
    }

    void addInitialValues(priorityData p) {
        ArrayHeap::addInitialValues(p);
    }

    void initialize(){
        ArrayHeap::initialize();
    }

    void insert(priorityData p) {
        ArrayHeap::addElement(p);
    }

    
    priorityData remove() {
        return ArrayHeap::removeMin(); 
    }

    priorityData returnMin() {
        return ArrayHeap::returnMin(); 
    }


    string toString() {
        return ArrayHeap::toString(); 
    }
};

