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
	HashNode<string, int> no("asb", true);
	HashNode<string, int> yes("khar", true);
	Htable <int, int> loob(10);
	int ind = loob.h(30);
	ind = abs(ind);
	no.kupdate("asghar");

	cout << endl << no._key.name << endl << "Hash:" << ind << endl;
	cout << "build success\n";
	return 0;
}