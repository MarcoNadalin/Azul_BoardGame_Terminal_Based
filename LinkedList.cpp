#include "LinkedList.h"

#include <exception>
#include <iostream>

LinkedList::LinkedList() 
{
   head = nullptr;
}

LinkedList::LinkedList(const LinkedList& other) 
{
   // TODO
}

LinkedList::~LinkedList() {
   // TODO
}

unsigned int LinkedList::size() const {
   int count = 0;
   Node* current = head;
   while(current != nullptr) {
      ++count;
      current = current->getNext();
   }

   return count;
}

Tile* LinkedList::get(const unsigned int index) const {
   int unsigned count = 0;
   Node* current = head;
   Tile* returnValue = nullptr;
   // int returnValue = std::numeric_limits<int>::min();
   if (index < size()) {
      while(count < index) {
         ++count;
         current = current->getNext();
      }
      returnValue = current->getValue();
   } else {
      throw std::out_of_range("Linked List get - index out of range");
   }
   
   return returnValue;
}

void LinkedList::remove(const unsigned int index) {
   //int unsigned count = 0;
   Node* current = head;
   // int returnValue = std::numeric_limits<int>::min();
   if (index < size()) {

      if(index == 0) {
         head = head->getNext();
      } else {
         for(unsigned int i = 0; i < size(); i++) {
            if(i + 1 == index) {
               current->setNext(current->getNext()->getNext());
            } else {
               current = current->getNext();
            }
         }
      }

      
   } else {
      throw std::out_of_range("Linked List get - index out of range");
   }
}

void LinkedList::addFront(Tile* tile) {
   if(head == nullptr) {
       Node* newNode = new Node(tile, nullptr);
       head = newNode;
   } else {
       Node* newNode = new Node(tile, head);
       head = newNode;
   }
   length++;
}

Tile* LinkedList::getFront() {
   Tile* front = nullptr;
   if(head != nullptr) {
      front = head->getValue();
      head = head->getNext();
   } 
   return front;
}

void LinkedList::addBack(Tile* tile) {
   Node* toAdd = new Node(tile, nullptr);

   if (head == nullptr) {
      head = toAdd;
   } else {
      Node* current = head;
      while(current->getNext() != nullptr) {
         current = current->getNext();
      }
      current->setNext(toAdd);
      delete current;
   }
   length++;
}



void LinkedList::removeBack() {
   Node* current = head;
   while(current->getNext() != nullptr) {
       current = current->getNext();
   }
   length--;
}

void LinkedList::removeFront() {
   
   if(head != nullptr) {
       Node* temp = head;   
       head = head->getNext();
       delete temp;
   }
}

void LinkedList::clear() {

   // head->setNext(nullptr);
   // head = nullptr;
   // removeFront();

   unsigned int length = size();
   for(unsigned int i = 0; i < length; ++i) {
      removeFront();
   }
   head = nullptr;
   
}

Node* LinkedList::getHead(){
   return head;
}