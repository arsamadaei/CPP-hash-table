#include "Htable.h"
#include <iostream>
#include <ios>
#include <cstdint>
#include <cstring>
#include <sstream>
#include <openssl/sha.h>

using namespace std;
using namespace exl;

int main() {
	HashNode<string, int> no("loob", 23);
	HashNode<string, int> yes("fari", 22);
	Htable <int, int> loob(10);
	int ind = loob.h(30);
	Htable < string, int > 

	no.kupdate("asghar");

	int la = loob[1];
	cout << endl << "::: "<<  la + 2 << endl;

	//cout << endl << no._key.name << endl << loob.h(30);
	return 0;
}
