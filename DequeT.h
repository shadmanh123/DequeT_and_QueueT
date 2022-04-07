#pragma once
#include<stdexcept>
using std::runtime_error;

template <class T>
class Node
{
  public: //Class Node contains data, pointer to next node and another pointer to previous node
  T data;
  Node* next;
  Node* prev;
  Node(T value){ //Initialized the node
    data = value;
    next = nullptr;
    prev = nullptr;
  }
};

template <class T>
class DequeT
{
  private:
    Node<T>* front_ptr; //Class Deque contains a pointer to front of Deque and another pointer to end of Deque
    Node<T>* back_ptr;
    void copyDequeT(const DequeT &dq); //helper function for copying Deque
    void deleteDequeT(); //helper function for deleting Deque

  public: //various public attributes of Deque class
    DequeT();
    DequeT(const DequeT &dq);
    ~DequeT();
    DequeT& operator=(const DequeT &dq);
    void insertFront(T value);
    void insertBack(T value);
    T removeFront();
    T removeBack();
    T peekFront()const;
    T peekBack()const;
    bool empty()const;
    int size()const;
};

//Implementations of Deque
template <class T>
DequeT<T>::DequeT(){ //Initializing Deque with the front and back pointers set to null
  front_ptr = nullptr;
  back_ptr = nullptr;
}

template <class T>
void DequeT<T>::copyDequeT(const DequeT &dq){
  front_ptr = new Node<T>(dq.front_ptr->data); //front pointer is pointing to a new node created with the value of parameter Deque's front pointer
  Node<T>* calling_ptr = front_ptr; //calling pointer is pointing to calling object's front pointer
  Node<T>* param_ptr = dq.front_ptr -> next; //parameter pointer is pointing to parameter's second node
  while(param_ptr != nullptr){
    Node<T>* newNode = new Node<T>(param_ptr -> data); //creating nodes with data from the parameter's node value
    newNode -> prev = calling_ptr; //connecting the new node to the calling object Deque
    calling_ptr -> next = newNode;
    calling_ptr = newNode;
    back_ptr = calling_ptr; //this allows us to find the back pointer of calling object after copying is complete
    param_ptr = param_ptr -> next;
  }
}

template <class T>
DequeT<T>::DequeT(const DequeT &dq){ //copy constructor
  copyDequeT(dq);
}

template <class T>
void DequeT<T>::deleteDequeT(){
  Node<T>* temp = front_ptr; //temp pointer created to point to node we will delete
  while(temp!= nullptr){
    front_ptr = front_ptr -> next; //Updating front pointer
    delete temp;
    temp = front_ptr;
    }
}

template <class T>
DequeT<T>::~DequeT(){ //destructor
  deleteDequeT();
}

template <class T>
DequeT<T>& DequeT<T>::operator=(const DequeT &dq){
  if(this != &dq){ //checks to see that both calling object and parameter Deque are not the same
    deleteDequeT();
    copyDequeT(dq);
  }
  return *this;
}

template <class T>
void DequeT<T>::insertFront(T value){
  if(empty() == 1){ //situation when we have no nodes
    Node<T>* newNode = new Node<T>(value);
    front_ptr = newNode;
    back_ptr = newNode;
  }
  else{
    Node<T>* newNode = new Node<T>(value);
    newNode -> next = front_ptr; //allows new node to be in front of the node that was the previous front node
    front_ptr -> prev = newNode;
    front_ptr = newNode; //Updates front pointer
    }
}

template <class T>
void DequeT<T>::insertBack(T value){
  if(empty() == 1){
    Node<T>* newNode = new Node<T>(value);
    front_ptr = newNode;
    back_ptr = newNode;
  }
  else{
    Node<T>* newNode = new Node<T>(value);
    newNode->prev = back_ptr; //Making the new node the last element in the node
    back_ptr -> next = newNode; //makes previous last node point to new last node
    back_ptr = newNode; //Updates back pointer
  }
}

template <class T>
T DequeT<T>::removeFront(){
  if(empty() == 1){
    throw runtime_error("No Nodes available to remove");
  }
  else{
    Node<T>* temp = front_ptr; //temp is a pointer that points to the first node
    T value = front_ptr -> data; //value will store the value in node so we can return it after deleting node 
    if(front_ptr == back_ptr){ //When we have only one node in the Deque
      front_ptr = nullptr;
      back_ptr = nullptr;
      delete temp;
      return value;
    }
    else{
      front_ptr = front_ptr -> next; //When we have more than one node, we update the front pointer to point to new front after deletion 
      front_ptr -> prev = nullptr;
      delete temp; //deleting the first node
      return value; //returning value of that first node that was deleted
    }
  }
}

template <class T>
T DequeT<T>::removeBack(){
  if(empty() == 1){
    throw runtime_error("No Nodes available to remove");
  }
  else{
    Node<T>* temp = back_ptr;
    T value = back_ptr -> data;
    if(back_ptr == front_ptr){ //When we have only one node in Deque
      back_ptr = nullptr;
      front_ptr = nullptr;
      delete temp;
      return value;
    }
    else{
      back_ptr = back_ptr -> prev; //Updating the back pointer
      back_ptr -> next = nullptr;
      delete temp; //deleting the last node
      return value; //returning the value in the node
    }
  }
}

template <class T>
T DequeT<T>::peekFront() const{
  if(empty() == 1){
    throw runtime_error("No Nodes available to peek");
  }
  else{
    T value = front_ptr -> data; //value stores the data from the first node
    return value;
    }
}

template <class T>
T DequeT<T>::peekBack() const{
  if(empty() == 1){
    throw runtime_error("No Nodes available to peek");
  }
  else{
    T value = back_ptr -> data; //value stores the data from the last node
    return value;
    }
}

template <class T>
bool DequeT<T>::empty()const{
  if(front_ptr == nullptr){ //When there are no nodes then the front pointer will be a null pointer
    return 1; //returns true
  }
  else{
    return 0; //returns false
  }
}

template <class T>
int DequeT<T>::size()const{
  int counter = 0; //counts how many nodes that my pointer has iterated through
  Node<T>* ptr = front_ptr; //pointer that points to first node
  
  while(ptr != nullptr){
    counter++; //increment counter each times pointer points to a new node
    ptr = ptr -> next; //update pointer
  }
  return counter;
}