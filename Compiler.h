#pragma once
#include<iostream>
#include<fstream>
using namespace std;
class Compiler
{
public:
	Compiler() {};
	friend void compile(string prg);

	~Compiler(){}

private:

};

