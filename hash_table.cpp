#include <iostream>
#include <ios>
#include <cstdint>
#include <cstring>
#include <openssl/sha.h>

using namespace std;


/* 
Hash node class:
	Uses a template with two custom datatypes, K for key and V for Value,
	and a pointer to the next value.
	This class defines a typical node of the Hash Table
 */

template < typename K, typename V > class HashNode 
{ public:
	K key;
	V value;
	HashNode *next;

	// HashNode Constructor
	HashNode(K key, V value) : key(key), value(value), next(NULL) {}

	// HashNode Deconstructor
	~HashNode() {}
};


/*
HashTable class:
	Uses a template with the two K and V custom datatypes.
	This class includes The following methods:
		

						┌┴─┐

					┌──────────HashTable class─────────┐
					|                                  |
			     Methods                           __init__?
					|
		┌───────────┴───────────┐
		|                 		|
	 Queries     	   Modifying operators
		|                       |
	  Search             ┌──────┴──────┐
	  				   insert        remove


*/

template < typename K, typename V > class HashTable
{ private:
	int size;

	HashNode < K, V > **table;

public:

	// Constructor: Allocates memory creating [size] amount of empty hash nodes.
	HashTable(int size) : size(size) 
	{
		table = new HashNode< K, V > *[size];

		for (int i = 0; i < size; i++) 
		{
			table[i] = NULL;
		} 
	} 

	// Deconstructor: Reallocates and frees allocated memory
	~HashTable() 
	{
		for (int i; i < size; i++) 
		{
			HashNode < K, V > *node = table[i];

			while (node) {
				HashNode < K, V > *prev = node;
				node = node->next; // go to the next node in the linked list
				delete prev->value;
				delete prev;
			}
		}

		delete[] table;
	}

	unsigned int hash(const K &key) 
	{
		unsigned char hash[SHA_DIGEST_LENGTH];
		SHA1((unsigned char*)&key, sizeof(key), hash);
		unsigned int index = 0;

		for (int i=0; i < 4; i++)
		{
			index += hash[i] << (i * 8);
		}
		return index % size;
	}

    void insert(const K& key, const V& value) {
        int index = hashFunc(key);
        HashNode< K, V >* current = table[index];
        
        while (current != NULL) 
        {
            if (current->key == key) 
            {
                current->value = value;
                return;
            }
            current = current->next;
        }
        HashNode< K, V >* newNode = new HashNode<K, V>(key, value);
        newNode->next = table[index];
        table[index] = newNode;
    }

	void remove(const K &key) {
	    int index = hashFunction(key);

	    HashNode<K, V> *prev = nullptr;
	    HashNode<K, V> *node = table[index];

	    while (node != nullptr && node->key != key) {
	        prev = node;
	        node = node->next;
	    }

	    if (node == nullptr) 
	    {
	        // The key is not present in the hash table
	        return;
	    } 

	    else
	    {
	        
	        if (prev == nullptr)
	        {
	            // The node with the given key is the head of the linked list
	            table[index] = node->next;
	        } 

	        else
	        {
	            prev->next = node->next;
	        }

	        delete node;
	    }
	}


	V search(const K &key)
	{
		unsigned int index = hash(key);
		HashNode < K, V > *node = table[index];

		// search through the linked list
		while (node)
		{
			if (node->key == key) {
				return node->value;
			}
			node = node->next;
		}

		return NULL;
	}

};

int main() 
{
	cout << "Loob";
	return 1;
}
