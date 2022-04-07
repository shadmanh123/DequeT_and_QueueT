#include "DequeT.h"
#pragma once
template <class T>
class QueueT{
  private:
    DequeT<T>Dq;

  public:
    QueueT();
    void enqueue(T value);
    T dequeue();
    bool empty()const;
    int size()const;
};

//Queue Method Implementation
template <class T>
QueueT<T>::QueueT(){ //constructor for Queue
}

template <class T>
void QueueT<T>::enqueue(T value){ //inserting nodes to back of Queue using function from Deque
  Dq.insertBack(value);
}

template <class T>
T QueueT<T>::dequeue(){ //removing nodes from front of Queue using function from Deque
  return Dq.removeFront();
}

template <class T>
bool QueueT<T>::empty()const{ //checks if Queue is empty using function from Deque
  return Dq.empty();
}

template <class T>
int QueueT<T>::size() const{ //Checks size of Queue using function from Deque
  return Dq.size();
}