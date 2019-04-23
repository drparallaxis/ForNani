#pragma once
#include <iostream>
#include <conio.h>
#include <random>
#include <ctime>
#include <Windows.h>
using namespace std;

class Map
{
	int size1, size2;
public:
	char** arr;
public:
	Map();
	Map(int, int);
	void zeroer();
	void assign(Map);
	void getsize(int&, int&);
	void newshow();
	void find(char, int&, int&, int&);
};
class Universe : public Map
{
	char symbol;
public:
	Universe();
	void test();
	void add(Map, int);
	void NewBirthAndDeath(Map);
	void buttons(Map, char sym);
	bool check(Map, int, int, int);
};

