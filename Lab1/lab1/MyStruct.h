#pragma once
#include <string.h>

using namespace std;


struct MyStruct
{
	int key;
	std::string stringValue;

	MyStruct(int k, const std::string& s) : key(k), stringValue(s) {}
};

struct less_than_key
{
	inline bool operator() (const MyStruct& struct1, const MyStruct& struct2)
	{
		return (struct1.key < struct2.key);
	}
};