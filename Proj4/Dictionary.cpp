//
//  Dictionary.cpp
//  Proj4
//
//  Created by Tim Yu on 6/2/18.
//  Copyright © 2018 CS32. All rights reserved.
//

// This is a correct but horribly inefficient implementation of Dictionary
// functionality.  Your job is to change DictionaryImpl to a more efficient
// correct implementation.  You can change it any way you like, subject to
// restrictions in the spec (e.g., that the only C++ library container you
// are allowed to use are vector, list, stack, and queue (and string); if you
// want anything fancier, implement it yourself).

#include "Dictionary.h"
#include <string>
#include <list>
#include <cctype>
#include <utility>  // for swap
using namespace std;

const int BUCKET_NUMBER = 49999; // wanted a prime number to avoid as many collisions as possible
                     // a  b  c  d  e   f   g   h   i   j   k   l   m    n   o  p   q    r  s   t   u
const int primes[26] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73,
    79, 83, 89, 97, 101};
//  v   w   x   y   z

void removeNonLetters(string& s);
void generateNextPermutation(string& permutation);

struct HashNode
{
    HashNode(int key, string val, unsigned long uniqueproduct) : key(key), val(val), next(nullptr), unique(uniqueproduct)
    {}
    int key;
    string val;
    HashNode* next;
    unsigned long unique; // POSSIBLE that non-anagrams get assigned the same bucket, thus important to use another check using this member variable to ensure that the products of the prime numbers in the words are different when using lookup function. Prevents additional problems (if this wasn't here, permutation yields (permutation whisper brief importunate)
        // *** made it unsigned long because int doesn't go that high
};

// This class does the real work of the implementation.

class DictionaryImpl
{
public:
    DictionaryImpl();
    ~DictionaryImpl();
    void insert(string& word);
    void lookup(string& letters, void callback(string));
    int hashFunc(string& word); // returns an int key that corresponds to bucket number storing word
private:
    HashNode* m_hashtable[BUCKET_NUMBER];
    unsigned long m_product; // product of prime numbers
    
    //list<string> m_words;
};

// constructs an empty hash table for storing dictionary words
DictionaryImpl::DictionaryImpl()
{
    for(int i = 0; i < BUCKET_NUMBER; i++)
    {
        m_hashtable[i] = nullptr;
    }
}

// delete everything in the hash table
DictionaryImpl::~DictionaryImpl()
{
    for(int i = 0; i < BUCKET_NUMBER; i++)
    {
        HashNode* kill = m_hashtable[i];
        while(kill != nullptr)
        {
            HashNode* prev = kill;
            kill = kill->next;
            delete prev;
        }
    }
}

void DictionaryImpl::insert(string& word)
{
    int key = hashFunc(word); // get the key from hashfunction
    HashNode*& bucket = m_hashtable[key]; // this bucket node is the node in the hashtable array at which we want to insert the word
    if(bucket == nullptr)
    {
        // if there's nothing at that bucket atm, then create a new node there with the key and the word.
        bucket = new HashNode(key, word, m_product);
    }
    else
    {
        // advance along the linked list until we get to the last node, then create a new node there with key and word.
        HashNode* advance = bucket;
        while(advance->next != nullptr)
        {
            advance = advance->next;
        }
        advance->next = new HashNode(key, word, m_product);
    }
    /*
    removeNonLetters(word);
    if ( ! word.empty())
        m_words.push_back(word);
    */
}

void DictionaryImpl::lookup(string& letters, void callback(string))
{
    if (callback == nullptr)
        return;
    
    if (letters.empty())
        return;
    
    int key = hashFunc(letters);
    HashNode* anagrams = m_hashtable[key]; // all anagrams of the specified word should be located at this node
    while(anagrams != nullptr) // traverse through that linked list and callback all stored words
    {
        if(anagrams->unique == m_product) // sometimes, they might have same bucket #, but different unique product. this is a check
        {
            callback(anagrams->val);
            anagrams = anagrams->next;
        }
        else
        {
            anagrams = anagrams->next;
        }
    }
    
    /*
    string permutation = letters;
    
    do
    {
        for (list<string>::const_iterator wordp = m_words.begin();
             wordp != m_words.end(); wordp++)
        {
            if (permutation == *wordp)
                callback(*wordp);
        }
        generateNextPermutation(permutation);
    } while (permutation != letters);
    */
}

// convert the characters of the word into a unique product of primes. Also get a key to use when accessing the hashtable by taking that product and dividing it by the number of buckets.
int DictionaryImpl::hashFunc(string& word)
{
    removeNonLetters(word); // first remove any non-letters, don't want these messing up our product calculation
    m_product = 1;
    for(int i = 0; i < word.length(); i++)
    {
        m_product = m_product * (primes[word[i] - 'a']);
    }
    return m_product % BUCKET_NUMBER;
}

void removeNonLetters(string& s)
{
    string::iterator to = s.begin();
    for (string::const_iterator from = s.begin(); from != s.end(); from++)
    {
        if (isalpha(*from))
        {
            *to = tolower(*from);
            to++;
        }
    }
    s.erase(to, s.end());  // chop everything off from "to" to end.
}

// Each successive call to this function generates the next permutation of the
// characters in the parameter.  For example,
//    string s = "eel";
//    generateNextPermutation(s);  // now s == "ele"
//    generateNextPermutation(s);  // now s == "lee"
//    generateNextPermutation(s);  // now s == "eel"
// You don't have to understand this function's implementation.
void generateNextPermutation(string& permutation)
{
    string::iterator last = permutation.end() - 1;
    string::iterator p;
    
    for (p = last; p != permutation.begin()  &&  *p <= *(p-1); p--)
        ;
    if (p != permutation.begin())
    {
        string::iterator q;
        for (q = p+1; q <= last  &&  *q > *(p-1); q++)
            ;
        swap(*(p-1), *(q-1));
    }
    for ( ; p < last; p++, last--)
        swap(*p, *last);
}

//******************** Dictionary functions ********************************

// These functions simply delegate to DictionaryImpl's functions.
// You probably don't want to change any of this code

Dictionary::Dictionary()
{
    m_impl = new DictionaryImpl;
}

Dictionary::~Dictionary()
{
    delete m_impl;
}

void Dictionary::insert(string word)
{
    m_impl->insert(word);
}

void Dictionary::lookup(string letters, void callback(string)) const
{
    m_impl->lookup(letters,callback);
}
