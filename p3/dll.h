/*  Project 3 - Dll.h
 *  Written by Andy Hansen 25 February 2020
 *  arhansen@crimson.ua.edu
 */

#ifndef __DLL_H__
#define __DLL_H__

#include "exceptions.h"
#include <iostream>

//#define _DEBUG_

using namespace std;

template <typename T>
class DllNode {
public:
    T value;
    DllNode *prev;
    DllNode *next;
};

template <typename T>
class Dll {
public:
    Dll(); // create an empty list
    Dll(const Dll &src); // create a deep copy of the src list
    Dll(const T arr[], int size); // create a linked list containing the elements of the array
    Dll &operator=(const Dll &src); // create a deep copy of the src list
    ~Dll(); // free all memory

    bool empty() const; // return if the list is empty in O(1)
    int size() const; // return how many items are in the list in O(1)

    T& at(int rank) const; // return a reference to the value of the list at a rank/index
    void insert(int rank, T value); // insert a value at the rank/index
    T remove(int rank); // remove the node at the rank/index and return its value

    void clear(); // reset the list to an empty list
    void display(ostream &os) const; // write the contents of the list to the ostream

private:
    int _count;
    DllNode<T> *_head, *_tail;
};

template <typename T>
ostream &operator<<(ostream &os, const Dll<T> &list); // write the contents of the list to the ostream

template<typename T>
Dll<T>::Dll()
  : _count(0), _head(nullptr), _tail(nullptr)
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
  if(_count > 0)
  {
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

    _tail = new DllNode<T>();
    _tail->prev = _last;
  }
  else
  {
    _head = nullptr;
    _tail = nullptr;
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

    _tail = new DllNode<T>();
    _tail->prev = _last;
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

    _tail = new DllNode<T>();
    _tail->prev = _last;

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
  delete _tail;
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
    throw IndexOutOfRangeException("at(): Index was outside the bounds of the linked list.", rank);
  }
  else
  {
    if(rank < _count / 2)
    {
      DllNode<T> *_node = _head;
      for(int i = 0; i < rank; i++)  _node = _node->next;

      #ifdef _DEBUG_
      cout << "At function accessed, returned " << _node->value << endl;
      #endif

      return _node->value;
    }
    else
    {
      DllNode<T> *_node = _tail;
      for(int i = _count; i > rank; i--)  _node = _node->prev;

      #ifdef _DEBUG_
      cout << "At function accessed, returned " << _node->value << endl;
      #endif

      return _node->value;
    }
  }
  // unreachable
  return _head->value;
}

template<typename T>
void Dll<T>::insert(int rank, T value)
{
  if(rank < 0 || rank > _count)
  {
    throw IndexOutOfRangeException("insert(): Index was outside the bounds of the linked list.", rank);
  }
  else
  {
    if(_head == nullptr)
    {
      /*DllNode<T> *_new = new DllNode<T>();

      _new->value = value;
      _new->next = nullptr;
      _new->prev = nullptr;
      _head = _new;
      _count++;*/
      _head = new DllNode<T>();
      _tail = new DllNode<T>();
      _head->value = value;
      _head->next = nullptr;
      _head->prev = nullptr;
      _tail->prev = _head;
      _tail->next = nullptr;
      _count++;

      #ifdef _DEBUG_
      cout << "Insert function accessed for head with value " << value << endl;
      #endif
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

        //while(_tmp->next != nullptr) _tmp = _tmp->next; 
        _tmp = _tail->prev;
        _tmp->next = _new;
        _new->prev = _tmp;
        _new->next = nullptr;
        _tail->prev = _new;
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
}

template<typename T>
T Dll<T>::remove(int rank)
{
  if(rank < 0 || rank > _count - 1)
  {
    throw IndexOutOfRangeException("remove(): Index was outside the bounds of the linked list.", rank);
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
      //while(_tmp->next != nullptr) _tmp = _tmp->next; 
      _tmp = _tail->prev;
      val = _tmp->value;
      _tmp->prev->next = nullptr;
      _tail->prev = _tmp->prev;

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

  _tail->prev = nullptr;

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

#endif
