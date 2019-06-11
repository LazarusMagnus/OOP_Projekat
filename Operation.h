#pragma once
#include<string>
#include"Interfaces.h"
#include"Event.h"
#include"Memory.h"
#include"Machine.h"
using namespace std;
class Variable{
public:
	Variable(string e) :name(e) {
		isValue = false;
	}
	~Variable() {}
	bool isReady() {
		return isValue;
	}
	string getName() {
		return name;
	}
	double getVal() {
		return val;
	}
	void setReady() {
		isValue = true;
	}
	void setValue(double v) {
		val = v;
		isValue = true;
	}

private:
	string name;
	double val;
	bool isValue;
};


class Operation: public ITimedElement{
public:
	virtual void notify(ID id) {};
	~Operation() {};
	ID getId() {
		return id;
	}
	Time getTime() {
		return T;
	}
	virtual bool isEqual() {
		return false;
	}
	virtual Variable getVar1() =0;
	virtual Variable getVar2() =0;
	virtual bool isReady()=0;
	virtual void setVar1(double b) = 0;
	virtual void setVar2(double b) = 0;

protected:
	Operation(Time t,ID i):T(t),id(i) {};
	
private:
	Time T;
	ID id;
	
};

class Equal:public Operation{
public:
	Equal(string v1, string v2, Time t, ID i):Operation(t,i),var1(v1),var2(v2){
		var1.setReady();
		if (isdigit(v2[0])) {
			var2.setValue(stod(v2));
			var2.setReady();
		}
	}
	bool isEqual() {
		return true;
	}
	bool isReady() {
		return var2.isReady() && Machine::Nw>0.0;
	}
	~Equal(){}
	Variable getVar1() {
		return var1;
	};
	Variable getVar2() {
		return var2;
	};
	void setVar1(double b) {
		var1.setValue(b);
	}
	void setVar2(double b) {
		var2.setValue(b);
	}
	void assign();
	void notify(ID id);
private:
	Variable var1;
	Variable var2;
};


class ArithmeticOperation:public Operation {
public:
	ArithmeticOperation(string v1, string v2, Time t, ID i):Operation(t,i),var1(v1),var2(v2){
		if (isdigit(v1[0])) {
			var1.setValue(stod(v1));
		}
		if (isdigit(v2[0])) {
			var2.setValue(stod(v2));
		}
	} ;
	~ArithmeticOperation() {};

	void notify(ID id);

	virtual double evaluate() = 0;

	Variable getVar1() {
		return var1;
	}
	Variable getVar2() {
		return var2;
	}
	void setVar1(double b) {
		var1.setValue(b);
	}
	void setVar2(double b) {
		var2.setValue(b);
	}
	bool isReady() {
		return var1.isReady() && var2.isReady();
	}

private:
	Variable var1;
	Variable var2;
};
class Mul:public ArithmeticOperation
{
public:
	Mul( string v1, string v2, Time t, ID i) :ArithmeticOperation( v1, v2,t,i) {};
	~Mul() {};
	double evaluate();

private:

};
class Add :public ArithmeticOperation
{
public:
	Add( string v1, string v2, Time t, ID i) :ArithmeticOperation( v1, v2,t,i) {};
	~Add(){}
	double evaluate(); 

private:

};
class Pov :public ArithmeticOperation
{
public:
	Pov( string v1, string v2, Time t, ID i) :ArithmeticOperation( v1, v2,t,i) {};
	~Pov(){}

	double evaluate();

private:

};

