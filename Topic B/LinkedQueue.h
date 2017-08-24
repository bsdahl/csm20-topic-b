//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** ADT queue: Link-based implementation.
 Listing 14-3.
 @file LinkedQueue.h */
#ifndef _LINKED_QUEUE
#define _LINKED_QUEUE

#include "Node.h"
#include "PrecondViolatedExcep.h"

template<class ItemType>
class LinkedQueue
{
private:
   // The queue is implemented as a chain of linked nodes that has 
   // two external pointers, a head pointer for front of the queue and
   // a tail pointer for the back of the queue.
   Node<ItemType>* backPtr;
   Node<ItemType>* frontPtr;

public:
   LinkedQueue();
   LinkedQueue(const LinkedQueue& aQueue);
   ~LinkedQueue();

	bool isEmpty() const;
	bool enqueue(const ItemType& newEntry);
	bool dequeue();
   
   /** @throw PrecondViolatedExcep if the queue is empty */
	ItemType peekFront() const throw(PrecondViolatedExcep);
    
    LinkedQueue<ItemType> & operator= (const LinkedQueue& aQueue);
}; // end LinkedQueue

#include "LinkedQueue.cpp"
#endif
