#ifndef _MEMORY_H_
#define _MEMORY_H_
#include<list>
using namespace std;
class Variable;


class Memory {
public:
	static Memory* getInstance() {
		if (Instance == nullptr) { Instance = new Memory(); }
		return Instance;
	}
	static	void set(string varName, double val);
	static  double get(string varName) ;

private:
	static Memory* Instance;
	Memory() {};
	list<Variable*> memo;
	int Nw = 1;
};



class VariableNotFoundException :public exception {
public:VariableNotFoundException(const char* msg) :exception(msg) {};
};
#endif