#ifndef _GLIBCXX_HTABLE_H
#define _GLIBCXX_HTABLE_H 1

#pragma GCC system_header

#ifndef __GXX_EXPERIMENTAL_CXX0X__
#include <bits/c++0x_warning.h>
#else

#include <bits/stl_algobase.h>
#include <bits/range_access.h>
#include <iostream>
#include <ios>
#include <cstdint>
#include <cstring>
#include <sstream>
#include <cmath>
#include <vector>
#include <openssl/sha.h>
using namespace std;


namespace exl _GLIBCXX_VISIBILITY (default){
_GLIBCXX_BEGIN_NAMESPACE_VERSION
	// experiment library namespace
	//compilation code: g++ -g Htable.cpp -Wno-deprecated-declarations -o Htable -lssl -lcrypto
	//g++ -o my_program my_program.cpp -lssl -lcrypto

template < typename K, typename V >
class HashNode {

public:
	K key;
	V value;
	HashNode* next;

	HashNode(K key, V value): key(key), value(value), next(nullptr) {}


	// modifying operations:


	void kupdate(K key_ = {}) {
		if (!key_.empty()) {
			key = key_;
		}
	}


	void vupdate(V value_ = {}) {
		if (value_ != V{}) {
			value = value_;
		}
	}


	~HashNode() {}

};


template < typename K, typename V >
class Htable {
private:
	int size;
	vector<K> _keys;

public:
	HashNode < K, V > **linkedList;

	// Hash table constructor
	Htable(int _size): size(_size) {

		// allocate memory with size _size(collision resolution type: chaining)

		linkedList = new HashNode < K , V > *[size];

		for (int i; i < _size; i++) {
			linkedList[i] = NULL;
			size = _size;
		}

		cout << endl << typeid(Htable).name() << " memory allocated successfully\n";
	}


	// query operations:
	template < typename Key >
	unsigned int h(const Key& key)
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

		unsigned int size_ = static_cast< unsigned int > (size);

		// return a sigmoid of the index. returns values between 0 and size_public - 1
		index = static_cast< unsigned int > ((size - 1) * (1 / (1 + exp(-(index / 10e10)))));
		return index;
	}

	int
	len()
	{ return size; }

	vector<K>
	keys()
	{return _keys;}

	void
	append(const K& key_, const V& value_)
	{
		unsigned int index = h(key_);
		HashNode< K, V >* current = linkedList[index];

		while (current != nullptr) {

			// see if the same value with the same key already exists
			if ((current->key == key_) && (current->value == value_)) {
				return;
			}

			current = current->next;
		}

		HashNode< K, V >* newNode = new HashNode< K, V >(key_, value_);
		newNode->next = linkedList[index];
		linkedList[index] = newNode;
		_keys.push_back(key_);
	}

	void
	remove(const K &key)
	{
		int index = h(key);

		HashNode< K, V > *prev = nullptr;
		HashNode< K, V > *node = linkedList[index];

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
				linkedList[index] = node->next;
			}

			else
			{
				int index_to_remove = -1;

				// Find the index of the element to remove
				for (int i = 0; i < _keys.size(); i++) {
					if (_keys[i] == key) {
						index_to_remove = i;
						break;
					}
				}

				// If the element was found, remove it from the vector
				if (index_to_remove != -1) {
					_keys.erase(_keys.begin() + index_to_remove);
				}
				prev->next = node->next;
			}

			delete node;
		}


	}


	const V& operator[] (const K& key_) const {
		unsigned int index = h(key_);
		HashNode< K, V > *node = linkedList[index];

		while (node)
		{
			if (node->key == key_) {
				return node->value;
			}

			node = node->next;
		}

		throw std::out_of_range(std::string("Index out of range. ")
		        + __FILE__ + ":" + std::to_string(__LINE__));
	}


	V&
	operator[] (const K& key_)
	 {
		unsigned int index = h(key_);
		HashNode< K, V > *node = linkedList[index];
		while (node)
		{
			if (node->key == key_) {
				return node->value;
			}

			node = node->next;
		}

		throw std::out_of_range(std::string("Index out of range. ")
		        + __FILE__ + ":" + std::to_string(__LINE__));
	}

	~Htable() {
		int size;

		for (int i; i < size; i++)
			{
				HashNode < K, V > **linkedList;
				linkedList = linkedList;
				HashNode < K, V > *node = linkedList[i];

				while (node)
				{
					HashNode < K, V > *prev = node;
					node = node->next;
					delete prev;
				}
			}

		delete[] linkedList;

		cout << endl << typeid(Htable).name() << " memory successfuly reallocated\n";
	}


	void
	push(int amount)
	{

		size += amount;
	}

};


_GLIBCXX_END_NAMESPACE_VERSION
}

#endif // __GXX_EXPERIMENTAL_CXX0X__
#endif // _GLIBCXX_HTABLE_H
