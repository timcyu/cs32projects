//
//  Sequence.h
//  CS32Project2
//
//  Created by Tim Yu on 4/19/18.
//  Copyright © 2018 CS32. All rights reserved.
//
#ifndef Sequence_h
#define Sequence_h
#include <string>

using ItemType = std::string;

class Sequence
{
public:
    Sequence();
    bool empty() const;
    int size() const;
    bool insert(int pos, const ItemType& value);
    int insert(const ItemType& value);
    bool erase(int pos);
    int remove(const ItemType& value);
    bool get(int pos, ItemType& value) const;
    bool set(int pos, const ItemType& value);
    int find(const ItemType& value) const;
    void swap(Sequence& other);
    ~Sequence();
    Sequence(const Sequence& other);
    Sequence& operator=(const Sequence& rhs);
    void dump() const;

private:
    ItemType value;
    struct Node
    {
        ItemType value;
        Node* next;
        Node* prev;
    };
    Node* head;
    int m_size;
};

int subsequence(const Sequence& seq1, const Sequence& seq2);
void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result);

#endif /* Sequence_h */
