#pragma once
#include<string>
#include<list>
#include<vector>
using namespace std;
enum type
{
	OP, NUM, VAR
};

class TreeNodeOp;
class TreeNodeVar;
class TreeNodeNum;

class TreeNode{
	
public:
	virtual type whatIs() { return OP; };
	virtual char getChar() { return ' '; };
	virtual double getNum() { return ' '; };
	virtual string getString() { return " "; };

	void setRight(TreeNode* t) {
		right = t;
	};
	void setLeft(TreeNode* t) {
		left = t;
	};
	
	~TreeNode() {};
protected:
	TreeNode() {
		left = nullptr;
		right = nullptr;
	};
private:
	friend class Expression;
	TreeNode* left;
	TreeNode* right;
};


class TreeNodeOp : public TreeNode
{

public:
	TreeNodeOp(char c) :TreeNode(), op(c) {};
	type whatIs() {
		return OP;
	}
	char getChar() {
		return op;
	}
	~TreeNodeOp() {};

private:
	char op;
};


class TreeNodeNum: public TreeNode
{
public:
	TreeNodeNum(double d) :TreeNode(), val(d) {};
	type whatIs() {
		return NUM;
	}
	double getNum() {
		return val;
	}

	~TreeNodeNum() {};

private:
	double val;
};


class TreeNodeVar: public TreeNode
{
public:
	TreeNodeVar(char c) :TreeNode(){
		name = c;
	};
	TreeNodeVar(string c) :TreeNode() {
		name = c;
	};
	type whatIs() {
		return VAR;
	}
	string getString() {
		return name;
	}
	~TreeNodeVar() {};

private:
	string name;
};

class Expression
{
public:
	Expression(string s);
	vector<TreeNode*> postFix();
	~Expression();

private:
	friend class TreeNode;
	TreeNode *root;
	//list<TreeNode*> postfix;
};
