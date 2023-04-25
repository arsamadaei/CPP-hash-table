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

unsigned int sigmoid(unsigned int x) {
	return 	1 / (1 + exp(-x));
}

// experiment library namespace
//compilation code: g++ -g Htable.cpp -Wno-deprecated-declarations -o Htable -lssl -lcrypto

namespace exl {


template < typename K, typename V >
struct key {
	K name;
	V* vptr; // pointer to value
};

template < typename K, typename V >
class HashNode {
private:
	V value_private;
public:
	bool _public;
	V value_public;
	HashNode* next;

	key < K, HashNode <K, V> > _key;

	HashNode(K n, bool public_=true): value_public(value_public), value_private(value_private), next(nullptr), _public(public_){
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
			if(_public) { value_private = value_; }
			else { value_public = value_; }
		}
	}


	~HashNode() {}

};


template < typename K, typename V >
class Htable {
private:
	int size_private;
	HashNode < K, V > **linkedList_private;

public:
	bool _public;
	int size_public;

	HashNode < K, V > **linkedList_public;

	// Hash table constructor
	Htable(int _size, bool public_=true): size_public(_size), size_private(size_private), _public(public_) {
		// allocate memory with size _size(collision resolution type: chaining)

		if (!_public) { linkedList_private = new HashNode < K , V > *[size_private]; }
		else { linkedList_public = new HashNode < K , V > *[size_public]; }

		for (int i; i < _size; i++) {
			if (!_public) {
				linkedList_private[i] = NULL;
				size_private = _public;
			}

			else {
				linkedList_public[i] = NULL;
				size_public = _size;
			}
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
		index = static_cast< int > (size_public * (1 / (1 + exp(-(index / 10e10)))) + 1);
		cout << endl << "epijwpifpweifjqweqweqpiwejfp :  :" <<  index;
		cout << "qwep";
		return index;
	}

	~Htable() {
		int size;
		if(_public) { size = size_public; }
		else { size = size_private; }

		for (int i; i < size; i++)
			{
				HashNode < K, V > **linkedList;

				if (!_public) { linkedList = linkedList_private; }
				else { linkedList = linkedList_public; }

				HashNode < K, V > *node = linkedList[i];

				while (node)
				{
					HashNode < K, V > *prev = node;
					node = node->next;
					delete prev;
				}
			}

		delete[] linkedList_public;
		delete[] linkedList_private;

		cout << endl << typeid(Htable).name() << " memory successfuly reallocated\n";
	}
};

}

#endif
