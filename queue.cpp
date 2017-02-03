/*****************************************************************************
 Queue class

 NAME:queue.cpp
 DATE:29/10/96
 AUTHOR: Z.A. Nolan

 ****************************************************************************/

#include "queue.h"
#include "iostream.h"

// Create the first node of the list, and ensure that the list is circular
template <class T> TNode<T>::TNode ( T Item)
  : _Item(Item)
{
  _Next=_Prev=this;
}

// Create a new node containing the data item and inserts it between the
// previous and next nodes.
template <class T> TNode<T>::TNode (T Item,TNode *Next,TNode *Prev)
: _Next(Next),
  _Prev(Prev),
  _Item(Item)
{
 Prev->_Next=Next->_Prev=this;
}

// Delete the node and links the previous and next nodes
template <class T>TNode<T>::~TNode()
{
 _Prev->_Next=_Next;
 _Next->_Prev=_Prev;
}

// Create an empty queue
template <class T> TQueue<T>::TQueue()
: _Head(NULL),
  _NumOfElements(0),
  _CurrentNode(NULL),
  _CurrentIndex(0)
{}

// Destroy the queue
template <class T> TQueue<T>::~TQueue()
{
 Flush();
}

// Add an item to the queue
template <class T> void TQueue<T>::Add(T Item)
{
  if (_NumOfElements++>0)  // Check if the queue is currently empty
    {
     new TNode<T>(Item,_Head,_Head->Prev());
                           // Create a new node on the tail of the queue
    }
  else
    {
      _Head=new TNode<T> (Item) ; // Create the first node on the queue
    }
}

template <class T> void TQueue<T>::Delete ()
{
 TNode<T> *Ptr=_Head;
 if ( _Head != NULL)
   {
    if (--_NumOfElements >0) // Check if the queue contains one item
      {
       _Head=_Head->Next() ; // The Head of the queue moves to the next node
      }
    else
      {
       _Head=NULL ;
      }

    delete Ptr; // Delete the node

   }
}

template <class T> void TQueue<T>::Flush()
{
  while (Size()) // Delete the head node until the queue is empty
   {
    Delete();
   }
}

template <class T> void TQueue<T>::ResetIterator()
{
 _CurrentNode=_Head ;
 _CurrentIndex=0 ;
}

template <class T> T TQueue<T>::operator[](int Index)
{
 if (_CurrentIndex==Index)
   {
    return (_CurrentNode->Item()) ;
   }

 else if (_CurrentIndex>Index)
   {
    // the current position is greater than the required position
    // so move back along the list to the right place

    while (_CurrentIndex>Index)
      {
       _CurrentNode=_CurrentNode->Prev() ;
       _CurrentIndex-- ;
      }

    // now we are in the right place so return the item
    return (_CurrentNode->Item()) ;
   }

 else
   {
    // the current node is less than the required position
    // so move forwards to it

    while (_CurrentIndex<Index)
      {
       _CurrentNode=_CurrentNode->Next() ;
       _CurrentIndex++ ;
      }

    // now we are in the right place  return the item
    return (_CurrentNode->Item()) ;

   }
}
