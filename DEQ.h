//File: DEQ.h

//Name:Islam Osama Nwsihy
//ID#:900170200
//Assignment 1 - Part (1)

#ifndef DEQ_H
#define DEQ_H


template <class Type>
class DEQ {
private:
	//the node of the linked list
	class Node{
	public:
		//var is for variable, the value in the node
		Type var;
		//next points to the node after it
		Node *Next;
		//prev points to the node before it
		Node *Prev;
	};
	typedef Node * NodePointer;
	NodePointer front, rear;
	//size is the size of the deque
	int size;
public:
	DEQ();
	~DEQ();
	bool DEQisEmpty();
	void Add_Front(Type e);
	void Add_Rear(Type e);
	Type Remove_Front();
	Type Remove_Rear();
	Type View_Front();
	Type View_Rear();
	int DEQ_Lenght();
};


#endif //DEQ_H!

