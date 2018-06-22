//
//  Sequence.cpp
//  CS32Project2
//
//  Created by Tim Yu on 4/19/18.
//  Copyright © 2018 CS32. All rights reserved.
//
#include "Sequence.h"
#include <iostream>
using namespace std;

Sequence::Sequence() // an empty sequence represented by a circularly doubly linked list, next and prev pointers point back to dummy node
{
    head = new Node;
    head->next = head;
    head->prev = head;
    m_size = 0;
}

bool Sequence::empty() const
{
    bool result = false;
    if(head->next == head && head->prev == head && m_size == 0) // checks to see if sequence meets all criteria of an empty sequence constructed in constructor
    {
        result = true;
    }
    return result;
}

// returns the size of the sequence
int Sequence::size() const
{
    return m_size;
}

// Insert value into the sequence so that it becomes the item at
// position pos.  The original item at position pos and those that
// follow it end up at positions one higher than they were at before.
// Return true if 0 <= pos <= size() and the value could be
// inserted.Otherwise, leave the sequence unchanged and return false.  Notice that
// if pos is equal to size(), the value is inserted at the end.
bool Sequence::insert(int pos, const ItemType& value)
{
    bool result = false;
    if(pos == 0)
    {
        if(empty() == true) // empty sequence!
        {
            Node *insert_node = new Node;
            insert_node->value = value;
            
            // connecting dummy and insert node
            head->next = insert_node;
            head->prev = insert_node;
            insert_node->next = head;
            insert_node->prev = head;
            m_size++;
            result = true;
        }
        else // must be a non-empty sequence, but inserting in the front!
        {
            Node *p = head->next; // this should be the first node of the sequence
            Node *insert_node = new Node;
            insert_node->value = value;
            
            // connecting insert node between dummy and first node
            head->next = insert_node;
            insert_node->next = p;
            insert_node->prev = head;
            p->prev = insert_node;
            m_size++;
            result = true;
        }
    }
    else if(pos > 0 && pos < size())
    {
        int increment = 0;
        Node *p = head->next; // set this pointer to point to first node initially
        while(increment < pos)
        {
            p = p->next; // shift pointer to point to next node
            increment++;
        }
        Node *insert_node = new Node;
        insert_node->value = value;
        
        // connecting insert node to the two nodes around it
        insert_node->next = p;
        insert_node->prev = p->prev;
        p->prev->next = insert_node;
        p->prev = insert_node;
        m_size++;
        result = true;
    }
    else if(pos == size()) // insert at the rear
    {
        Node *p = head->prev; // this should be the last node of the sequence
        Node *insert_node = new Node;
        insert_node->value = value;
        
        // connecting insert node to the dummy node and the last node
        insert_node->next = head;
        insert_node->prev = p;
        p->next = insert_node;
        head->prev = insert_node;
        m_size++;
        result = true;
    }
    else
    {
        result = false;
    }
    return result;
}

// Let p be the smallest integer such that value <= the item at
// position p in the sequence; if no such item exists (i.e.,
// value > all items in the sequence), let p be size().  Insert
// value into the sequence so that it becomes the item at position
// p.  The original item at position p and those that follow it end
// up at positions one higher than before.  Return p if the value
// was actually inserted.  Return -1 if the value was not inserted
// (perhaps because the sequence has a fixed capacity and is full).
int Sequence::insert(const ItemType& value)
{
    int loc = 0; // keep track where to insert
    for (Node* p = head->next; p != head; p = p->next)
    {
        if(value <= p->value)
        {
            break;
        }
        else if(loc == size()) // if loc equals size just insert...code should stop after this
        {
            break;
        }
        loc++;
    }
    insert(loc, value); // insert at that loc...
    return loc;
}

// If 0 <= pos < size(), remove the item at position pos from
// the sequence (so that all items that followed that item end up at
// positions one lower than they were at before), and return true.
// Otherwise, leave the sequence unchanged and return false.
bool Sequence::erase(int pos)
{
    bool result = false;
    if(pos >= 0 && pos < size())
    {
        Node *kill = head->next; // set to first node
        for(int i = 0; i < pos; i++)
        {
            kill = kill->next; // set kill to point to node at pos
        }
        kill->prev->next = kill->next; // node before kill next points to node after kill
        kill->next->prev = kill->prev; // node after kill prev points to node before kill
        delete kill;
        m_size--;
        result = true;
    }
    return result;
}

// Erase all items from the sequence that == value.  Return the
// number of items removed (which will be 0 if no item == value).
int Sequence::remove(const ItemType& value)
{
    int count = 0;
    int loc = 0;
    Node* p = head->next;
    
    if(size() > 0) // cannot remove a sequence of negative size
    {
        while(loc < size())
        {
            if(p->value == value) // iterating through the sequence by loc, if we find that one of its node values is equal to the value specified, then first advance the pointer ahead one, erase the node at loc, increment count (# nodes removed), and decrement loc since we justs removed a node and we're technically still at the same position.
            {
                p = p->next;
                erase(loc);
                count++;
                loc--;
            }
            else
            {
                p = p->next; // if nothing, keep traversing
            }
            
            loc++;
        }
    }
    return count;
}

// If 0 <= pos < size(), copy into value the item at position pos
// in the sequence and return true.  Otherwise, leave value unchanged
// and return false.
bool Sequence::get(int pos, ItemType& value) const
{
    bool result = false;
    if(pos >= 0 && pos < size())
    {
        Node* p = head->next; // set to first node initially
        for(int i = 0; i < pos; i++)
        {
            p = p->next;
        }
        value = p->value; // set value to what the pointer value is at that node
        result = true;
    }
    else
    {
        result = false;
    }
    return result;
}

// If 0 <= pos < size(), replace the item at position pos in the
// sequence with value and return true.  Otherwise, leave the sequence
// unchanged and return false.
bool Sequence::set(int pos, const ItemType& value)
{
    bool result = false;
    if(pos >= 0 && pos < size())
    {
        Node* p = head->next; // set to first node initially
        for(int i = 0; i < pos; i++)
        {
            p = p->next;
        }
        p->value = value; // set pointer value to what value is
        result = true;
    }
    else
    {
        result = false;
    }
    return result;
}

// Let p be the smallest integer such that value == the item at
// position p in the sequence; if no such item exists, let p be -1.
// Return p
int Sequence::find(const ItemType& value) const
{
    int loc = 0;
    for (Node* p = head->next; p != head; p = p->next)
    {
        if(value == p->value)
        {
            break;
        }
        loc++;
    }
    return loc;
}

// Exchange the contents of this sequence with the other one.
void Sequence::swap(Sequence& other)
{
    // create temp head to exchange addresses of dummy node
    Node* temp_head = head;
    head = other.head;
    other.head = temp_head;
    
    // create temp size to exchange sizes of two sequences
    int temp_size = m_size;
    m_size = other.m_size;
    other.m_size = temp_size;
}

// DESTRUCTOR
Sequence::~Sequence()
{
    while(head->next != head && head->prev != head) // when it's not just the dummy node
    {
        Node* kill = head->prev; // set to last node
        kill->prev->next = head; // change the next pointer going into the last node
        head->prev = kill->prev; // change the prev pointer going into last node
        delete kill; // delete last node and its next/prev pointers
    }
    delete head; // once the dummy node is the only left, delete it too
}

// COPY CONSTRUCTOR
Sequence::Sequence(const Sequence& other)
{
    m_size = other.m_size; // copy the other sequence's size
    head = new Node;       // initialize a new dummy node
    head->next = head;     // set the next and prev pointers to head so it's empty
    head->prev = head;
    
    int loc = 0;
    for (Node* p = other.head->next; p != other.head; p = p->next) // traverse through the other sequence and insert the value held at each position into the new sequence
    {
        insert(loc, p->value);
        loc++;
    }
}

// ASSIGNMENT OPERATOR
Sequence& Sequence::operator=(const Sequence& rhs)
{
    if(this != &rhs)
    {
        Sequence temp(rhs);
        swap(temp);
    }
    return *this;
}

// FOR TESTING PURPOSES
void Sequence::dump() const
{
    for (Node* p = head->next; p != head; p = p->next)
    {
        cerr << p->value << endl;
    }
}

// When comparing two sequences, if seq2 is a subsequence of seq1, return the position in seq1 where that subsequence is located
int subsequence(const Sequence& seq1, const Sequence& seq2)
{
    int subseq_start = 0;
    // values held for each node of each sequence
    ItemType seq1_val;
    ItemType seq2_val;
    
    //subsequence cannot be bigger than seq1, and it can't be empty either
    if(seq2.size() > seq1.size() || seq2.empty() == true)
    {
        return -1;
    }
    
    for(int i = 0; i < seq1.size(); i++) // start looping through seq1
    {
        // get the value at position i in seq1 to compare with the value at pos = 0 in seq2
        if(seq1.get(i, seq1_val) == seq2.get(0, seq2_val)) //possible subsequence!
        {
            subseq_start = i; // temporarily store this as a possible subsequence start position
            for(int j = 0; seq1_val == seq2_val; i++, j++) // looping through the rest of seq1
            {
                if(j == seq2.size())  // if this statement is true, we have finished looping through seq2 and if we haven't broken out of the for loop yet it must be a subsequence
                {
                    return subseq_start;
                }
                seq1.get(i, seq1_val); // advance to next seq1 value
                seq2.get(j, seq2_val); // advance to next seq2 value
            }
        }
    }
    return -1; // if it broke out of the for loop and isn't a valid subsequence
}

// Produces a result sequence that contains the 1st item of seq1 -> 1st item of seq2 -> 2nd item of seq2 -> 2nd item of seq2 -> ...
void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result)
{
    Sequence interleave;
    ItemType seq1_val;
    ItemType seq2_val;
    
    if(seq1.empty() == true) // if seq1 is empty, return all of seq2
    {
        interleave = seq2;
    }
    else if(seq2.empty() == true) // if seq2 is empty, return all of seq1
    {
        interleave = seq1;
    }
    else if(seq1.size() < seq2.size()) // if seq2 is larger than seq1, loop through the entire size of seq2...
    {
        int pos = 0;
        for(int i = 0; i < seq2.size(); i++)
        {
            if(seq1.get(i, seq1_val) == true) // if there is a value at pos i in seq1, insert into temp
            {
                interleave.insert(pos, seq1_val);
                pos++;
            }
            if(seq2.get(i, seq2_val) == true) // if there is a value at pos i in seq2, insert into temp
            {
                interleave.insert(pos, seq2_val);
                pos++;
            }
        }
    }
    else if(seq2.size() < seq1.size()) // if seq1 is larger than seq2, loop through entire size of seq1...
    {
        int pos = 0;
        for(int i = 0; i < seq1.size(); i++)
        {
            if(seq1.get(i, seq1_val) == true)  // if there is a value at pos i in seq1, insert into temp
            {
                interleave.insert(pos, seq1_val);
                pos++;
            }
            if(seq2.get(i, seq2_val) == true)  // if there is a value at pos i in seq2, insert into temp
            {
                interleave.insert(pos, seq2_val);
                pos++;
            }
        }
    }
    result = interleave;
}


