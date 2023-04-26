#ifndef HTABLE_H
#define HTABLE_H

#include <iostream>
#include <ios>
#include <cstdint>
#include <cstring>
#include <sstream>
#include <cmath>
#include <openssl/sha.h>

using namespace std;


namespace exl {
	// experiment library namespace
	//compilation code: g++ -g Htable.cpp -Wno-deprecated-declarations -o Htable -lssl -lcrypto


template < typename K, typename V >
struct key {
	K name;
	V* vptr; // pointer to value
};

template < typename K, typename V >
class HashNode {
public:
	bool _public;
	V value_public;
	HashNode* next;

	key < K, HashNode <K, V> > _key;

	HashNode(K n): value_public(value_public), next(nullptr) {
		_key.name = n;
		_key.vptr = this;
	}


	// modifying operations:


	void kupdate(K key_ = {}) {
		if (!key_.empty()) {
			_key.name = key_;
		}
	}


	void vupdate(V value_ = {}) {
		if (value_ != V{}) {
			value_public = value_;
		}
	}


	~HashNode() {}

};


template < typename K, typename V >
class Htable {

public:
	bool _public;
	int size_public;

	HashNode < K, V > **linkedList_public;

	// Hash table constructor
	Htable(int _size): size_public(_size) {
		
		// allocate memory with size _size(collision resolution type: chaining)
	
		linkedList_public = new HashNode < K , V > *[size_public];
		
		for (int i; i < _size; i++) {
			linkedList_public[i] = NULL;
			size_public = _size;
		}

		cout << "size " << _size;
		cout << "sids " << size_public;
		cout << endl << typeid(Htable).name() << " memory allocated successfully\n";
	}


	// query operations:
	template < typename Key >
	int h(const Key& key)
	{
	    stringstream ss;
	    ss << key;
	    string str = ss.str();

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

		unsigned int size_ = static_cast< unsigned int > (size_public);


		cout << index;
		
		// return a sigmoid of the index. returns values between 0 and size_public - 1
		index = static_cast< int > ((size_public - 1) * (1 / (1 + exp(-(index / 10e10)))));
		return index;
	}
	

	~Htable() {
		int size;

		for (int i; i < size; i++)
			{
				HashNode < K, V > **linkedList;
				linkedList = linkedList_public;
				HashNode < K, V > *node = linkedList[i];

				while (node)
				{
					HashNode < K, V > *prev = node;
					node = node->next;
					delete prev;
				}
			}

		delete[] linkedList_public;

		cout << endl << typeid(Htable).name() << " memory successfuly reallocated\n";
	}
};

}

#endif
