#pragma once

#include <iostream>
#include <string>

using namespace std;

struct priorityData
{
	string dataValue;
	int    priorityValue;
};




class ArrayHeap {
protected:
    priorityData* heapArray;
    int capacity;
    int currentSize;



    void heapUp(int index) {
        while (index > 1 && heapArray[index].priorityValue < heapArray[index / 2].priorityValue) {
            counters[7]++; // Total heap up actions
            swap(heapArray[index], heapArray[index / 2]);
            index /= 2;
        }
    }



    void heapDown(int index) {
        while (2 * index <= currentSize) {
            int child1 = 2 * index;
            int child2 = 2 * index + 1;
            if (child2 <= currentSize && heapArray[child2].priorityValue < heapArray[child1].priorityValue) {
                child1++; // Sets child1 to child2 since child2 is the smaller value of the 2 (because of the if statement)
            }
            if (heapArray[index].priorityValue > heapArray[child1].priorityValue) {
                swap(heapArray[index], heapArray[child1]);
                counters[8]++; // Total heap down actions
            }
            else {
                break;
            }
            index = child1;
        }
    }



public:

    int counters[9];



    int getCurrentSize() {
        return currentSize;
    }



    int getCapacity(){
        return capacity;
    }



    ArrayHeap(int initialCapacity = 10) {
        capacity = initialCapacity;
        if (initialCapacity == 0) {
            capacity = 10; // Default size of 10
        }
        for (int i = 0; i < 9; i++) {
            counters[i] = 0;
        }
        currentSize = 0;
        heapArray = new priorityData[capacity + 1]; // Index 0 is not used
    }



    ~ArrayHeap() {
        delete[] heapArray;
        heapArray = nullptr;
    }



    void addInitialValues(priorityData p) {
        // Resize the array if necessary
        if (currentSize + 1 > capacity) {
            cout << "\nHeap size doubled from " << capacity << " to " << capacity * 2;
            capacity *= 2;
            priorityData* newArray = new priorityData[capacity + 1];
            for (int i = 1; i <= currentSize; i++) {
                newArray[i] = heapArray[i];
            }
            delete[] heapArray;
            heapArray = newArray;
        }
        currentSize++;
        heapArray[currentSize] = p; // Add the new element to the array
        counters[0]++;
    }



    void initialize() { // Heapifies the entire array after initial inserts in order they came in
        for (int i = currentSize / 2; i >= 1; i--) {
            heapDown(i);
        }
        counters[1] = counters[8]; // Stores total heap down actions up to this point which is only initialization
    }



    void addElement(priorityData p) {
        if (currentSize == capacity) {
            // Resize the array if it's full
            cout << "\nHeap size doubled from " << capacity << " to " << capacity * 2;
            int newCapacity = capacity * 2;
            priorityData* newArray = new priorityData[newCapacity + 1];
            for (int i = 1; i <= currentSize; i++) {
                newArray[i] = heapArray[i];
            }
            delete[] heapArray;
            heapArray = newArray;
            capacity = newCapacity;
        }
        currentSize++; // Add the new element at the end
        counters[2]++; // Requested inserts (from actions file or user)
        heapArray[currentSize] = p;
        heapUp(currentSize); // Restore heap by heaping up
    }



    priorityData removeMin() {
        if (currentSize == 0) {
            throw "Attempt to remove element from empty heap";
        }
        swap(heapArray[1], heapArray[currentSize]); // Swap root with the last element
        currentSize--;
        counters[3]++; // Requested removes (from actions file or user)
        heapDown(1); // Restore heap property
        return heapArray[currentSize + 1];
    }



    priorityData returnMin() {
        if (currentSize == 0) {
            throw "Attempt to return element from empty heap";
        }
        // Counter in Source.cpp since testing calls this function in cases other than returnMin
        return heapArray[1];
    }



    string toString() {
        if (currentSize == 0) {
            return "\n[The heap is empty]";
        }
        string result = "\n[";
        for (int i = 1; i <= currentSize; i++) {
            result += "(" + heapArray[i].dataValue + ", " + to_string(heapArray[i].priorityValue) + ")";
            if (i < currentSize) {
                result += ";\n";
            }
        }
        // Counter is in Source.cpp since testing calls this function multiple other times
        result += "]\n";
        return result;
    }

    

};



