#pragma once
#include<string>
#include"Types.h"
#include<list>

class Operation;
using namespace std;
class Machine{
public:
	Machine(){
	}
	friend void excecute(string prg,string config);
	~Machine(){
	}
	friend void config(string config);
	static void remove(ID id);
	static void update(string name, double val);
	static list<Operation*> getlist() {
		return elemets;
	}
private:
	static Time Ta, Tm, Tw, Te, Nw;
	static list<Operation*> elemets;
	friend class Operation;
	friend class Equal;
};
//class Config {
//	static void config(string config);
//	~Config() {};
//	static Time getTa() {
//		return Ta;
//	}
//	static Time getTm() {
//		return Tm;
//	}
//	static Time getTe() {
//		return Te;
//	}
//	static Time getTw() {
//		return Tw;
//	}
//	static Time getNw() {
//		return Nw;
//	}
//private:
//	Config();
//	friend class Machine;
//	static Time Ta, Tm, Tw, Te, Nw;
//};
