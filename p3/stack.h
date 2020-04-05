/*  Project 3 - Stack.h
 *  Written by Andy Hansen 25 February 2020
 *  arhansen@crimson.ua.edu
 */

#ifndef __STACK_H__
#define __STACK_H__

#include "exceptions.h"
#include "dll.h"

template <typename T>
class Stack {
public:
    Stack(); // create an empty stack
    void push(T value); // add an item to the top of the stack
    T pop(); // remove of the value at the top of the stack and return its value
    T peek(); // return the value at the top of the stack, keeping it in the stack
    int size() const; // return how many items are in the stack
    bool empty() const; // return if the stack is empty
    void display(ostream &os) const; // write the contents of the stack to the ostream
private:
    Dll<T> *_stack = new Dll<T>();
};

template <typename T>
ostream &operator<<(ostream &os, const Stack<T> &stack); // write the contents of the stack to the ostream

template<typename T>
Stack<T>::Stack()
{

}

template<typename T>
void Stack<T>::push(T value)
{
    _stack->insert(0, value);
}

template<typename T>
T Stack<T>::pop()
{
    if(_stack->empty()) throw InvalidOperationException("Stack empty.");
    return _stack->remove(0);
}

template<typename T>
T Stack<T>::peek()
{
    if(_stack->empty()) throw InvalidOperationException("Stack empty.");
    return _stack->at(0);
}

template<typename T>
int Stack<T>::size() const
{
    return _stack->size();
}

template<typename T>
bool Stack<T>::empty() const
{
    return _stack->empty();
}

template<typename T>
void Stack<T>::display(ostream &os) const
{
    _stack->display(os);
}

template<typename T>
ostream &operator<<(ostream &os, const Stack<T> &stack)
{
    stack.display(os);
    return os;
}

#endif
