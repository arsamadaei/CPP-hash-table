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
	HashNode<string, int> no("asb");
	HashNode<string, int> yes("khar");
	Htable <int, int> loob(10);
	int ind = loob.h(30);
	no.kupdate("asghar");

	//cout << endl << no._key.name << endl << loob.h(30);
	return 0;
}
