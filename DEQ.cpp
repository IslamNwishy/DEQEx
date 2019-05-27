//File: DEQ.cpp

//Name:Islam Osama Nwsihy
//ID#:900170200
//Assignment 1 - Part (1)

#include <iostream>
#include "DEQ.h"
using namespace std;

//Instantiates the front and rear pointers to NULL and the size to 0
template<class Type>
DEQ<Type>::DEQ() {
	front = NULL;
	rear = NULL;
	size = 0;
}

//Resets the values of the front, rare and size
template<class Type>
DEQ<Type>::~DEQ() {
	front = NULL;
	rear = NULL;
	size = 0;
}

//Returns true if the size is 0
template<class Type>
bool DEQ<Type>::DEQisEmpty() {
	return (size==0);
}

//Adds an element to the front of the deque
template<class Type>
void DEQ<Type>::Add_Front(Type e) {
	//if the deque is empty, create a new node in the front and make it point at NULL from both sides
	//Make that node the rear node as well, since it is the only node
	if (DEQisEmpty()) {
		front = new Node;
		front->var = e;
		front->Next = NULL;
		front->Prev = NULL;
		rear = front;
	}
	//if the deque is not empty, create a new node to be the new front and make it point and nothing before it
	//make the old front point to this as the one before it, and make the pointer front point at the new front
	else {
		
		NodePointer NewFront = new Node;
		NewFront->var = e;
		NewFront->Prev = NULL;
		front->Prev = NewFront;
		NewFront->Next = front;
		front = NewFront;
	}
	//increment the size by 1
	size++;
}

//Adds an element to the rear of the deque
template<class Type>
void DEQ<Type>::Add_Rear(Type e) {
	//if the deque is empty, create a new node in the front and make it point at NULL from both sides
	//Make that node the rear node as well, since it is the only node
	if (DEQisEmpty()) {
		front = new Node;
		front->var = e;
		front->Next = NULL;
		front->Prev = NULL;
		rear = front;
	}
	//if the deque is not empty, create a new node to be the new rear and make it point and nothing after it
	//make the old rear point to this new node as the one after it, and make the pointer rear point at the new rear
	else {
		NodePointer NewRear = new Node;
		NewRear->var = e;
		NewRear->Next = NULL;
		rear->Next = NewRear;
		NewRear->Prev = rear;
		rear = NewRear;
	}
	size++;
}

//Return and remove the front node
template<class Type>
Type DEQ<Type>::Remove_Front() {
	//if the deque is not empty, decrement the size, hold the value of the front, move the front to the next element
	//if then the deque is empty this means the front is now NULL so make the rear as the front once more as there are no values there
	//if not then make the front point at nothing before it and return the value
	if (!DEQisEmpty()) {
		size--;
		Type temp = front->var;
		front = front->Next;
		if (!DEQisEmpty()) front->Prev = NULL;
		else rear = front;
		return temp;
	}
	else
		cout << "Underflow!" << endl;
}

//Return and remove the rear node
template<class Type>
Type DEQ<Type>::Remove_Rear() {
	//if the deque is not empty, decrement the size, hold the value of the rear, move the rear to the previous element
	//if then the deque is empty this means the rear is now NULL so make the rear as the front once more as there are no values there
	//if not then make the rear point at nothing after it and return the value
	if (!DEQisEmpty()) {
		size--;
		Type temp = rear->var;
		rear = rear->Prev;
		if (!DEQisEmpty()) rear->Next = NULL;
		else front = rear;
		return temp;
	}
	else
		cout << "Underflow!" << endl;
}

//Returns the front value
template<class Type>
Type DEQ<Type>::View_Front() {
	if (!DEQisEmpty())
		return front->var;
	else
		cout << "Underflow!" << endl;
}

//Returns the rear value
template<class Type>
Type DEQ<Type>::View_Rear() {
	if (!DEQisEmpty())
		return rear->var;
	else
		cout << "Underflow!" << endl;
}

//Returns the size of the deque
template<class Type>
int DEQ<Type>::DEQ_Lenght() {
	return size;
}

