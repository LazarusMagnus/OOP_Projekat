#include "Operation.h"
#include"Memory.h"
#include"Machine.h"
#include<string>
#include<iostream>
#include<fstream>
#include"Sched.h"

double Add::evaluate()
{
	double a = getVar1().getVal();
	double b = getVar2().getVal();
	return  a + b;
}

double Mul::evaluate()
{
		double a = getVar1().getVal();
		double b = getVar2().getVal();
		return  a * b;
}

double Pov::evaluate(){
		double a = getVar1().getVal();
		double b = getVar2().getVal();
		return  pow(a, b);
}

void Equal::assign(){
	Memory::getInstance()->set(var1.getName(), var2.getVal());
}

void Equal::notify(ID id){

	ofstream out("l.log", ios::app);
	out << "(" + to_string(id) + ")\t" << Scheduler::Instance()->getCurTime() - this->getTime() << "ns/" << Scheduler::Instance()->getCurTime() << "ns" << endl;

	assign();
	Machine::remove(getId()); 
	Machine::Nw++;
	Machine::update(var1.getName(), var2.getVal());

}

void ArithmeticOperation::notify(ID id)
{
	ofstream out("l.log", ios::app);
	out << "(" + to_string(id) + ")\t" << Scheduler::Instance()->getCurTime() - this->getTime() << "ns/" << Scheduler::Instance()->getCurTime() << "ns" << endl;

	string ime = "(" + to_string(getId()) + ")";
	double val = evaluate();
	Machine::remove(getId());
	Machine::update(ime, val);
}
