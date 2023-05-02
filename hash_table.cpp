#include <iostream>
#include <ios>
#include <cstdint>
#include <cstring>
#include <cmath>
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


					┌──────────HashTable class─────────┐
					|                                  |
			  Methods                          attributes
					|                                  |
┌───────────┴───────────┐              private
		|                    		|                      |
	 Queries     	   Modifying operators       ┌─────┴─────┐
		|                       |               size      **table
	Search()             ┌──────┴──────┐
	  				 insert()        remove()


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

			while (node)
			{
				HashNode < K, V > *prev = node;
				node = node->next;
				delete prev->value;
				delete prev;
			}
		}

		delete[] table;
	}


	// Hash function using sha3-256: converts key to a hash(lines 94-102) and converts the hash to an index(lines 104-111).

	unsigned int sigmoid(unsigned int x) {
		return 	1 / (1 + e)
	}

	template < typename K >
	unsigned int h(const K& key)
	{
	    std::stringstream ss;
	    ss << key;
	    std::string str = ss.str();

	    unsigned char hash[SHA256_DIGEST_LENGTH];
	    SHA256_CTX sha256;
	    SHA256_Init(&sha256);
	    SHA256_Update(&sha256, str.c_str(), str.length());
	    SHA256_Final(hash, &sha256);

	    unsigned int index = 0;

	    for (int i = 0; i < 4; i++)
	    {
	        index += hash[i] << (i * 8);
	    }

	    return index;
	}

	/*
	The insert modifying operation(key, value):
		# The following lines 124 to 137 exectes the following algorithm:
		1. Create hash for the given key (line 127).
		2. Search for an empty hash node with the [current] pointer (line 131).
		3.1. If the key already exists, the value is inserted (lines 132-137).
		3.2. If the key does not exist, a new hash node is created where the value lies (lines 142-144).
	*/

    void append(const K& key, const V& value) {
        int index = h(key);
        HashNode< K, V >* current = table[index];

        while (current != nullptr)
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

	/*
	The remove modifying operation(key, value):
		# The following lines 153 to 183 exectes the following algorithm:
		1. Create hash for the given key (line 153).
		2. Loop through the table until given key is reached (lines 156-162).
		3.1. if the node is a nullptr, it means the node has never existed(lines 165-168).
		3.2. If the key does not exist, a new hash node is created where the value lies (lines 142-144).
	*/

	void remove(const K &key)
	{
	    int index = h(key);

	    HashNode< K, V > *prev = nullptr;
	    HashNode< K, V > *node = table[index];

	    while (node != nullptr && node->key != key)
	    {
	        prev = node;
	        node = node->next;
	    }

	    if (node == nullptr)
	    {
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
		unsigned int index = h(key);
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
