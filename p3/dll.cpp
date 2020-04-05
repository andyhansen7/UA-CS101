/*  Project 3 - dll.cpp
 *  Written by Andy Hansen 25 Febreaury 2020
 *  arhansen@crimson.ua.edu
 */

#include "dll.h"
#include <iostream>

using namespace std;

//#define _DEBUG_


template<typename T>
Dll<T>::Dll()
  : _count(0), _head(nullptr)
{
  #ifdef _DEBUG_
  cout << "New DLL constructed, count="  << _count << " head=" << _head << endl;
  #endif
}

template<typename T>
Dll<T>::Dll(const Dll<T> &src)
{
  _count = src.size();

  // construct head node

    _head = new DllNode<T>();
    _head->value = src.at(0);

    #ifdef _DEBUG_
    cout << "New DLL constructed, count="  << _count << " head=" << _head << endl;
    #endif

    #ifdef _DEBUG_
    cout << "Head constructed with value " << _head->value << endl;
    #endif

    DllNode<T> *_last = _head;

    // construct nodes from array
    for(int i = 1; i < _count; i++)
    {
      DllNode<T> *_new = new DllNode<T>();
      _new->value = src.at(i);
      _new->prev = _last;
      _new->next = nullptr;
      _last->next = _new;

      #ifdef _DEBUG_
      cout << "New node constructed with value " << _new->value << ", count=" << i << endl;
      #endif

      _last = _new;
    }
}

template<typename T>
Dll<T>::Dll(const T arr[], int size)
  : _count(size)
{
  #ifdef _DEBUG_
  cout << "New DLL constructed, count="  << _count << " head=" << _head << endl;
  #endif


  if(size > 0)  // safety first
  {
    // construct head node

    _head = new DllNode<T>();
    _head->value = arr[0];

    #ifdef _DEBUG_
    cout << "Head constructed with value " << _head->value << endl;
    #endif

    DllNode<T> *_last = _head;

    // construct nodes from array
    for(int i = 1; i < size; i++)
    {
      DllNode<T> *_new = new DllNode<T>();
      _new->value = arr[i];
      _new->prev = _last;
      _new->next = nullptr;
      _last->next = _new;

      #ifdef _DEBUG_
      cout << "New node constructed with value " << _new->value << ", count=" << i << endl;
      #endif

      _last = _new;
    }
  }
}

template<typename T>
Dll<T>& Dll<T>::operator=(const Dll &src)
{
  clear();
  _count = src.size();

  // construct head node

    _head = new DllNode<T>();
    _head->value = src.at(0);

    #ifdef _DEBUG_
    cout << "Overloaded assignment operator called with source " << src << endl;
    #endif

    #ifdef _DEBUG_
    cout << "Head constructed with value " << _head->value << endl;
    #endif

    DllNode<T> *_last = _head;

    // construct nodes from array
    for(int i = 1; i < _count; i++)
    {
      DllNode<T> *_new = new DllNode<T>();
      _new->value = src.at(i);
      _new->prev = _last;
      _new->next = nullptr;
      _last->next = _new;

      #ifdef _DEBUG_
      cout << "New node constructed with value " << _new->value << ", count=" << i << endl;
      #endif

      _last = _new;
    }
  return *this;
}

template<typename T>
Dll<T>::~Dll()
{
  DllNode<T> *_curr = _head, *_next = nullptr;
  while(_curr != nullptr)
  {
    _next = _curr->next;

    #ifdef _DEBUG_
    cout << "Delete called for node " << _curr << " with value " << _curr->value << endl;
    #endif

    delete _curr;
    _curr = _next;
  }
}

template<typename T>
bool Dll<T>::empty() const
{
  #ifdef _DEBUG_
  cout << "Empty function accessed, returned " << (_count == 0) << endl;
  #endif

  return _count == 0;
}

template<typename T>
int Dll<T>::size() const
{
  #ifdef _DEBUG_
  cout << "Size function accessed, returned " << _count << endl;
  #endif

  return _count;
}

template<typename T>
T& Dll<T>::at(int rank) const
{
  if(rank < 0 || rank > (_count - 1)) // error case
  {
    throw new InvalidOperationException("at(): Index was outside the bounds of the linked list.");
  }
  else
  {
    DllNode<T> *_node = _head;
  for(int i = 0; i < rank; i++)  _node = _node->next;

  #ifdef _DEBUG_
  cout << "At function accessed, returned " << _node->value << endl;
  #endif

  return _node->value;
  }
}

template<typename T>
void Dll<T>::insert(int rank, T value)
{
  if(rank < 0 || rank > _count)
  {
    throw new InvalidOperationException("insert(): Index was outside the bounds of the linked list.");
  }
  else
  {
    DllNode<T> *_new = new DllNode<T>();
    _new->value = value;
    _count++;

    DllNode<T> *_tmp = _head;

    if(rank == 0) // insert as head
    {
      #ifdef _DEBUG_
      cout << "Insert function accessed for head with value " << value << endl;
      #endif

      _new->prev = nullptr;
      _new->next = _tmp;
      _tmp->prev = _new;
      _head = _new; 
    }
    else if(rank == _count - 1) // insert as tail
    {
      #ifdef _DEBUG_
      cout << "Insert function accessed for tail with value " << value << endl;
      #endif

      while(_tmp->next != nullptr) _tmp = _tmp->next; 

      _tmp->next = _new;
      _new->prev = _tmp;
      _new->next = nullptr;
    }
    else // node is somewhere in the middle
    {
      #ifdef _DEBUG_
      cout << "Insert function accessed for node " << rank << " with value " << value << endl;
      #endif

      for(int i = 0; i < rank - 1; i++) _tmp = _tmp->next;
      
      _new->prev = _tmp;
      _new->next = _tmp->next;
      _tmp->next = _new;
      _new->next->prev = _new;
    }
    return;
  }
}

template<typename T>
T Dll<T>::remove(int rank)
{
  if(rank < 0 || rank > _count - 1)
  {
    throw new InvalidOperationException("remove(): Index was outside the bounds of the linked list.");
  }
  else
  {
    DllNode<T> *_tmp = _head;
    T val;

    if(rank == 0) // cut the head off like a french revolution
    {
      val = _head->value;
      _head = _head->next;

      #ifdef _DEBUG_
      cout << "Remove function accessed for head, value returned was " << val << endl;
      #endif

      delete _tmp;
    }
    else if(rank == _count - 1)   // cut the tail off 
    {
      while(_tmp->next != nullptr) _tmp = _tmp->next; 

      val = _tmp->value;
      _tmp->prev->next = nullptr;

      #ifdef _DEBUG_
      cout << "Remove function accessed for tail, value returned was " << val << endl;
      #endif

      delete _tmp;
    }
    else // not the head or tail
    {
      for(int i = 0; i < rank - 1; i++) _tmp = _tmp->next;

      DllNode<T> *_del = _tmp->next;

      val = _del->value;

      _tmp->next = _del->next;
      _tmp->next->prev = _tmp;

      #ifdef _DEBUG_
      cout << "Remove function accessed for node " << rank << ", value returned was " << val << endl;
      #endif

      delete _del;
    }
    _count--;
    return val;
  }
}

template<typename T>
void Dll<T>::clear()
{
  #ifdef _DEBUG_
  cout << "Clear called, clearing all nodes" << endl;
  #endif

  while(_count > 0) remove(0);

  return;
}

template<typename T>
void Dll<T>::display(ostream &os) const
{
  DllNode<T> *_curr = _head;

  os << "[ ";
  while(_curr != nullptr)
  {
    os << _curr->value << ' ';
    _curr = _curr->next;
  }
  os << "]" << endl;
  return;
}

template<typename T>
ostream &operator<<(ostream &os, const Dll<T> &list)
{
  list.display(os);
  return os;
}

template class Dll<int>;
template class Dll<short>;
template class Dll<long>;
template class Dll<long long>;

template class Dll<float>;
template class Dll<double>;
template class Dll<long double>;

template class Dll<string>;
template class Dll<char>;