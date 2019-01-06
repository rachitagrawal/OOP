// CPP_Deallocate.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
int const n = 10;
#define WORDSIZE 4

class Base {
public:
	int b_var;
};


int main()
{
	//Usual way to create an array of User-defined Object
	//Base *b = new Base[10];
	//Usual way to delete the memory for this array of objects
	//delete[] b;

	char *tmp = static_cast<char *>(operator new[](sizeof(int) + n * sizeof(Base)));
	Base *p = reinterpret_cast<Base *>(tmp + WORDSIZE);
	*reinterpret_cast<int *>(tmp) = n;
	for (int i = 0; i < n; i++) {
		new(p + i) Base();
	}

	size_t n = *reinterpret_cast<size_t *>(reinterpret_cast<char*>(p) - WORDSIZE);
	while (n-- != 0) {
		(p + n)->~Base();
	}
	operator delete[](reinterpret_cast<char*>(p) - WORDSIZE);
	
	return 0;
}
