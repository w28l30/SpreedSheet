/*
List class

Written by Bernhard Firner
*/

#ifndef __LIST_H__
#define __LIST_H__

#include "node.h"
template <typename T>
class LList 
{

protected:
	int size;
	Node<T>* head;
	Node<T>* tail;

public:

	LList() 
	{
		head = nullptr;
		tail = nullptr;
		size = 0;
	}

	virtual ~LList() 
	{	
		//Here is another way to delete all of the nodes
		Node<T>* target = head;
		while (nullptr != target)
		{
			Node<T>* next = target->getNext();
			delete target;
			target = next;
		}
		
	}

	/*
		insert node at the end of list
	*/
	void push_back(T& val) 
	{
		Node<T>* n = new Node<T>(val);
		if (nullptr == head) 
		{
			head = n;
			tail = n;
		}
		else 
		{
			tail->insert(n);
			tail = n; 
		}
		size++;
	}

	/*
		insert node at the front of list
	*/
	void push_front(T& val) 
	{
		Node<T>* n = new Node<T>(val);
		if (nullptr == head) 
		{
			head = n;
			tail = n;
		}
		else 
		{
			head->insertBefore(n);
			head = n;
		}
		size++;
	}

	/*
		insert node at the position index
	*/
	bool insert(T& val, int index)
	{
		// invalid index 
		if(index < 0  || index >= size)
		{
			return false;
		}

		if(index == 0)
		{
			push_front(val);
		}
		else
		{
			Node<T>* node = new Node<T>(val);
			Node<T>* pNode = head;
			while(index-- > 1)
			{
				pNode = pNode->getNext();
			}
			pNode->insert(node);
			pNode = node;

			//increase size
			size++;
		}

		return true;
	}

	/*
		remove the node at the position index
	*/
	bool remove(int index)
	{
		// invalid index 
		if(index < 0 || index >= size)
		{
			return false;
		}
	
		// find the node to be deleted
		Node<T>* pNode = head;
		while(index--)
		{
			pNode = pNode->getNext();
		}
		
		// if the node is the head
		if(head == pNode)
		{
			head = head->getNext();
		}

		// if the node is the tail
		if(tail == pNode)
		{
			tail = tail->getPrev();
		}

		// release node
		delete pNode;

		// decrease size
		size--;
		return true;
	}

	/*
		set value of the node at position index 
	*/
	void set(T& val, int index)
	{
		// invalid index 
		if(index < 0  || index >= size)
		{
			return;
		}

		LList<T>::iterator ita = begin();
		while(index--)
		{
			ita++;
		}
		*ita = val;
	}

	/*
		get value of the node at position index 
	*/
	T* get(int index)
	{
		// invalid index 
		if(index < 0  || index >= size)
		{
			return nullptr;
		}

		LList<T>::iterator ita = begin();
		while(index--)
		{
			ita++;
		}

		return &(*ita);
	}

	bool isEmpty()
	{
		return size == 0;
	}

	int getSize()
	{
		return size;
	}

	//friend class iterator;
	//Iterator class for the linked list
	class iterator 
	{
	private:
		Node<T>* location;
		LList* container;
	public:
		//Remember the kind of thing this iterator will fetch with operator*
		typedef T value_type;

		//The iterator starts at some node
		iterator(Node<T>* start, LList* container)
		{
			location = start;
			iterator::container = container;
		}

		//prefix operator--
		iterator& operator--() 
		{
			//If we are at the end then go to the tail (the last element)
			if (nullptr == location) 
			{
				location = container->tail;
			}
			else 
			{
				if (nullptr != location->getPrev()) 
				{
					location = location->getPrev();
				}
				//otherwise we should really throw an exception because we can't go before the beginning
			}
			return *this;
		}

		//prefix operator++
		iterator& operator++() 
		{
			if (nullptr != location)
			{
				location = location->getNext();
			}
			return *this;
		}

		//postfix operator++
		iterator operator++(int unused) 
		{
			iterator cur = *this;
			++(*this);
			return cur;
		}

		T& operator*() 
		{
			if (nullptr != location) 
			{
				return location->getVal();
			}
		}

		bool operator!=(const iterator& other)
		{
			if (container != other.container) 
			{
				//Then throw an exception and make your program crash
			}
			return location != other.location;
		}
	};

	//begin and end iterator functions
	iterator begin() 
	{
		return iterator(head, this);
	}

	iterator end() 
	{
		return iterator(nullptr, this);
	}
};



#endif
