/*  Project 3 - dll.cpp
 *  Written by Andy Hansen 25 Febreaury 2020
 *  arhansen@crimson.ua.edu
 */

#include "stack.h"
#include "dll.h"
#include <iostream>

#define _DEBUG_

template<typename T>
Stack<T>::Stack()
    : _count(0), _head(nullptr)
{

}

template<typename T>
void Stack<T>::push(T value)
{
    
}

template<typename T>
T Stack<T>::pop()
{
    return 
}

template<typename T>
T Stack<T>::peek()
{
    return 
}

template<typename T>
int Stack<T>::size() const
{
    return _count;
}

template<typename T>
bool Stack<T>::empty() const
{
    return (_count == 0);
}

template<typename T>
void Stack<T>::display(ostream &os) const
{
    
}

template<typename T>
ostream &operator<<(ostream &os, const Stack<T> &stack)
{
    
    return os;
}

template class Stack<int>;
template class Stack<short>;
template class Stack<long>;
template class Stack<long long>;

template class Stack<float>;
template class Stack<double>;
template class Stack<long double>;

template class Stack<string>;
template class Stack<char>;
