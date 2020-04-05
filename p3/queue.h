
/*  Project 3 - Queue.h
 *  Written by Andy Hansen 25 February 2020
 *  arhansen@crimson.ua.edu
 */

#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "exceptions.h"
#include "dll.h"

template <typename T>
class Queue {
public:
    Queue(); // create an empty stack
    void enqueue(T value); // add an item to the front of the queue
    T dequeue(); // remove the value at the front of the queue and return its value
    T peek(); // return the value at the front of the queue, keeping it in the queue
    int size() const; // return how many items are in the queue
    bool empty() const; // return if the queue is empty
    void display(ostream &os) const; // write the contents of the queue to the ostream

private:
    Dll<T> *_queue = new Dll<T>();
};

template <typename T>
ostream &operator<<(ostream &os, const Queue<T> &queue); // write the contents of the queue to the ostream

template<typename T>
Queue<T>::Queue()
{

}

template<typename T>
void Queue<T>::enqueue(T value)
{
    _queue->insert(_queue->size(), value);
    return;
}

template<typename T>
T Queue<T>::dequeue()
{
    if(_queue->empty()) throw InvalidOperationException("Queue empty.");
    return _queue->remove(0);
}

template<typename T>
T Queue<T>::peek()
{
    if(_queue->empty()) throw InvalidOperationException("Queue empty.");
    return _queue->at(0);
}

template<typename T>
int Queue<T>::size() const
{
    return _queue->size();
}

template<typename T>
bool Queue<T>::empty() const
{
    return _queue->empty();
}

template<typename T>
void Queue<T>::display(ostream &os) const
{
    _queue->display(os);
    return;
}

template<typename T>
ostream& operator<<(ostream &os, const Queue<T> &queue)
{
    queue.display(os);
    return os;
}

#endif
