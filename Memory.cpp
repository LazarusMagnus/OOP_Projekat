#include "Memory.h"
#include"Operation.h"
Memory* Memory::Instance = nullptr;
void Memory::set(string varName, double val) {
	/*if (getInstance()->get(varName) != 0.0) {
		throw;
	}*/
	Variable* nova = new Variable(varName);
	nova->setValue(val);
	getInstance()->memo.push_back(nova);
}

double Memory::get(string varName)
{
	try {
		for (auto it : getInstance()->memo) {
			if (it->getName() == varName) {
				return it->getVal();
			}
		}
		throw VariableNotFoundException("nije u bazi");
	}
	catch (const VariableNotFoundException &e) {
		return 0.0;
	}
}


