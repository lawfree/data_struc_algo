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

    void addMedianFinder(); //add a integer to the data structure

    double finMedian();
};

#endif // HEAP_QUESTIONS_H
