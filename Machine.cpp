#include "Machine.h"
#include "Event.h"
#include"Operation.h"
#include"Memory.h"
#include"Sched.h"
#include<iostream>
#include<fstream>
Time Machine::Ta = 10;
Time Machine::Tm = 10;
Time Machine::Tw = 10;
Time Machine::Te = 10;
Time Machine::Nw = 1;
list<Operation*> Machine::elemets;
void excecute(string prg,string conf) {
	string s1, s3, s4,s=" ";
	config(conf + ".txt");
	char s2;
	int id = 1;
	ifstream prog(prg + ".imf");
	ofstream out;
	out.open("l.log");
	out.close();

	while (!prog.eof()) {
		prog >> s1 >> s2 >> s3 >> s4;
		if (s == s1)
			break;
		s = s1;
		switch (s2){
		case '=':Machine::elemets.push_back(new Equal(s3, s4, Machine::Tw,id++));
			break;
		case '+':Machine::elemets.push_back(new Add(s3, s4, Machine::Ta, id++));
			break;
		case '*':Machine::elemets.push_back(new Mul(s3, s4, Machine::Tm, id++));
			break;
		case '^':Machine::elemets.push_back(new Pov(s3, s4, Machine::Te, id++));
			break;
		}
	}
	

	while (Machine::elemets.size() > 0) {
		for (auto it = Machine::elemets.begin(); it != Machine::elemets.end();) {
			if ((*it)->isReady()) {
				Event::create((*it), (*it)->getTime(), (*it)->getId());
				if ((*it)->isEqual()) {
					Machine::Nw--;
				}
				it = Machine::elemets.erase(it);
			}
			else {
				it++;
			}
		}
		Time t=Scheduler::Instance()->getCurTime();

		while (Scheduler::Instance()->processNow());
	
	}
	string ime = prg + ".log";
	rename("l.log", ime.c_str());
}

void config(string config)
{
	ifstream in(config);
	string s;
	int n,br=0;
	char c1, c2, c3;
	while (!in.eof()) {
		in >> c1 >> c2 >> c3 >> n;
		getline(in, s);

		switch (br){
		case 0: Machine::Ta = n;
			break;
		case 1: Machine::Tm = n;
			break;
		case 2: Machine::Te = n;
			break;
		case 3: Machine::Tw = n;
			break;
		case 4: Machine::Nw = n;
			break;
		}
		br++;
	}
}

void Machine::remove(ID id)
{
	for  (auto it = elemets.begin();  it != elemets.end(); it++){
		if ((*it)->getId() == id) {
			elemets.erase(it);
			break;
		}
	}
}

void Machine::update(string name, double val)
{
	for (auto it : elemets) {
		if (it->getVar1().getName() == name) {
			it->setVar1(val);
		}
		if (it->getVar2().getName() == name) {
			it->setVar2(val);
		}
	}
	for (auto it = Machine::elemets.begin(); it != Machine::elemets.end();) {
		if ((*it)->isReady()) {
			Event::create((*it), (*it)->getTime(), (*it)->getId());
			it = Machine::elemets.erase(it);
		}
		else {
			it++;
		}
	}
}
