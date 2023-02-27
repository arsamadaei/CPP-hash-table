#include <iostream>
#include <ios>
#include <cstdint>
#include <cstring>
#include <openssl/sha.h>

using namespace std;

typedef enum { False, True } boolean;

// Task data type
struct task
{
    // Inputs
    uint64_t key;
    uint32_t estimated_time;
    time_t date_begin;
    time_t date_due;
    uint8_t priority;
    char subtasks;
    boolean overdue;
    boolean finished;
    uint64_t uuid;
};

// Declaring task data type
typedef struct task task_t;


// Hash node class template

template < typename K, typename V > class HashNode 
{ public:
	K key;
	V value;
	HashNode *next;

	HashNode(K key, V value) : key(key), value(value), next(NULL) {}
	~HashNode() {}
};

template < typename K, typename V > class HashTable
{ private:
	int size;

	// **table double pointer for indexing
	HashNode < K, V > **table;

public:
	// Hash node has NULL hash nodes
	HashTable(int size) : size(size) 
	{
		table = new HashNode< K, V > *[size];

		for (int i = 0; i < size; i++) 
		{
			table[i] = NULL;
		} 
	} 

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
