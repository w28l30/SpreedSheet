/*
Node.h
Node class for a linked list

Written by Bernhard Firner
*/

//Preprocessor guards
#ifndef __NODE_H__
#define __NODE_H__


template <typename T>
class Node 
{

private:
	//The value being held
	T val;
	//Pointers to the next and previous nodes
	Node* next;
	Node* prev;
public:
	//Constructor
	Node(T val) 
	{
		Node::val = val;
		next = nullptr;
		prev = nullptr;
	}

	//Return a reference to the value
	T& getVal() 
	{
		return val;
	}

	void setVal(T& val)
	{
		Node::val = val;
	}

	void insert(Node* n)
	{
		if (nullptr != next) 
		{
			next->prev = n;
		}
		n->next = next;

		n->prev = this;
		next = n;
	}

	void insertBefore(Node* n) 
	{
		if (nullptr != prev) 
		{
			prev->next = n;
		}
		n->prev = prev;

		n->next = this;
		prev = n;
	}

	Node* getPrev() 
	{
		return prev;
	}

	Node* getNext() 
	{
		return next;
	}

	void setPrev(Node* prev) 
	{
		this->prev = prev;
	}

	void setNext(Node* next) 
	{
		this->next = next;
	}

	~Node() 
	{
		//Clean up the links
		if (nullptr != next)
		{
			next->prev = prev;
		}
		if (nullptr != prev) 
		{
			prev->next = next;
		}
	}

};

#endif
