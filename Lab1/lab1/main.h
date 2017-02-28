#pragma once

//signature functions
void TogglePause();
void Restart();
void DrawDeathScreen();


//for sorting values to display in the scoreboard
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
