#include "Compiler.h"
#include"Expression.h"
#include<iostream>
#include<string>

#include<fstream>
void compile(string prg){

	ifstream program(prg+".txt");
	char c, var;
	int br = 1;
	ofstream out;
	out.open(prg+".imf");

	string expr;
	vector<TreeNode*> pfix;

	while (!program.eof()) {
		program >> var>> c;
		TreeNodeVar* novi;
		string ime,s;
		getline(program, expr);
		Expression *e= new Expression(expr);
		pfix = e->postFix();
		while (pfix.size() > 1) {
			for (int i = 0; i < pfix.size();i++) {
				if (pfix[i]->whatIs() == OP) {
					out << '(' << br++ <<") "<< pfix[i]->getChar()<<' ';

					if (pfix[i - 2]->whatIs() == VAR) {
						s = pfix[i - 2]->getString();
						out << s<<" "  ;
					}

					if (pfix[i - 2]->whatIs() == NUM)
						out << pfix[i - 2]->getNum()<<" ";

					if (pfix[i - 1]->whatIs() == VAR) {
						s = pfix[i - 1]->getString();
						out << s << endl;
					}

					if (pfix[i-1]->whatIs() == NUM)
						out << pfix[i-1]->getNum()<<endl;

					
					i -= 2;

					ime = "(" + to_string(br-1) + ")";
					novi = new TreeNodeVar(ime);

					pfix[i] = novi;

					for (int j = i + 1; j < pfix.size()-2; j++) {
						pfix[j] = pfix[j + 2];
					}
					pfix.pop_back();
					pfix.pop_back();
					break;
				}
			}
		}
		out <<"("<<br++<<") "<< "= " << var<< ' ';
		if (pfix[0]->whatIs() == VAR)
			out << pfix[0]->getString() << endl;

		if (pfix[0]->whatIs() == NUM)
			out << pfix[0]->getNum() << endl;

	}
	out.close();
	program.close();
}
