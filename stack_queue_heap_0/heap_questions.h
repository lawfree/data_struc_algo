#ifndef HEAP_QUESTIONS_H
#define HEAP_QUESTIONS_H

#include <iostream>
#include <queue>

using namespace std;

class Heap_Ques
{
public:
    Heap_Ques();

    int findKthLargestInHeap();
};

class MedianFinder
{
public:
    MedianFinder();

    void addNumber(int num); //add a integer to the data structure

    double finMedian();     //return the median of the array
private:
    priority_queue<int ,vector<int> ,greater<int>> big_queue;
};

#endif // HEAP_QUESTIONS_H
