#include "PriorityQueue.hpp"
#include <limits.h>

using namespace std;

void swap(ReviewInfo *a, ReviewInfo *b)
{
    //*a = *b
    ReviewInfo *temp = a;

    a->restaurantName = b->restaurantName;
    a->customer = b->customer;
    a->review = b->review;
    a->time = b->time;

    b->restaurantName = temp->restaurantName;
    b->customer = temp->customer;
    b->review = temp->review;
    b->time = temp->time;

    delete temp;
    temp = nullptr;
}

/*
Constructor for our MinHeap implementation
*/
PriorityQ::PriorityQ(int cap)
{
    capacity = cap;
    currentSize = 0;
    heapArr = new ReviewInfo[cap];
}

/*
Destructor
*/
PriorityQ::~PriorityQ()
{
    delete[] heapArr;
    heapArr = nullptr;
}

/*
Finds the parent of a node, given its index.
*/
int PriorityQ::parent(int index)
{
    if(index % 2 == 0){
        return ((index - 2) / 2);
    }
    else{
        return ((index - 1) / 2);
    }
}

/*
Returns the left child of a node.
*/
int PriorityQ::leftChild(int index)
{
    return ((2*index) + 1);
}

/*
Returns the right child of a node.
*/
int PriorityQ::rightChild(int index)
{
    return ((2*index) + 2);
}

void PriorityQ::peek()
{
    if(currentSize == 0){
        cout << "no record found" << endl;
    }
    else{
        cout << "\t" << "Restaurant Name: " << heapArr[0].restaurantName << endl;
        cout << "\t" << "Customer: " << heapArr[0].customer << endl;
        cout << "\t" << "Review: " << heapArr[0].review << endl;
        cout << "\t" << "Time: " << heapArr[0].time << endl;
    }
}

void PriorityQ::heapify(int i)
{
    if(i == 0){
        return;
    }
    
    int parentTime = heapArr[parent(i)].time;
    int childTime = heapArr[i].time;

    if(parentTime > childTime){
        return;
    }
    else{
        swap(heapArr[i], heapArr[parent(i)]);
        heapify(parent(i));
    }
}

void PriorityQ::insertElement(ReviewInfo restaurant)
{
    if(currentSize == capacity){
        cout << "Maximum heap size reached. Cannot insert anymore." << endl;
    }
    else{
        heapArr[currentSize] = restaurant;
        heapify(currentSize);
        currentSize++;
    }
}

/*
Prints the elements in the heap
*/
void PriorityQ::print()
{
    for(int i = 0; i < currentSize; i++){
        cout << "\t" << "Customer: " << heapArr[i].customer << endl;
        cout << "\t" << "Review: " << heapArr[i].review << endl;
        cout << "\t" << "Time: " << heapArr[i].time << endl;
        cout << "\t" << "=====" << endl;
    }
}

// Method to remove minimum element (or root) from min heap
void PriorityQ::pop()
{
    int currentIndex = 0;

    currentSize--;
    swap(heapArr[0], heapArr[currentSize]);

    while(leftChild(currentIndex) <= currentSize && rightChild(currentIndex) <= currentSize){
        int greaterIndex;
        if(leftChild(currentIndex) > rightChild(currentIndex)){
            greaterIndex = leftChild(currentIndex);
        }
        else{
            greaterIndex = rightChild(currentIndex);
        }

        if(heapArr[currentIndex].time > heapArr[greaterIndex].time){
            return;
        }
        else{
            swap(heapArr[currentIndex], heapArr[greaterIndex]);
        }
    }
}
