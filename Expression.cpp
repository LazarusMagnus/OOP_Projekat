#include "Expression.h"
#include<vector>
#include <list>
#include<stack>
#include<algorithm>

Expression::Expression(string s)
{
	double br;
	double dec;
	vector<TreeNode*> niz;
	for ( int i = 0;s[i]!='\0' ;i++)
	{
		if (isdigit(s[i])) {
			br = 0;
			dec = 1;
			while (isdigit(s[i])) {
				br = br * 10 + s[i] - '0';
				i++;
			}
			if (s[i] == '.') {
				i++;
				while (isdigit(s[i])) {
					dec /= 10;
					br = br  + (s[i] - '0')* dec;
					i++;
				}
			}
			niz.push_back(new TreeNodeNum(br));
			if (s[i] == '\0')
				break;
			i--;
		}else if (s[i] == '+' || s[i] == '*' || s[i] == '^') {
			niz.push_back(new TreeNodeOp(s[i]));
		}
		else {
			niz.push_back(new TreeNodeVar(s[i]));
		}

	}
	char op[2]{ '*', '+' };
	int n = niz.size();
	for (int i = n-1; i!=-1; i--) {
		if (niz[i]->whatIs() == OP) {

			if (niz[i]->getChar() == '^') {

				niz[i]->setLeft(niz[i - 1]);
				niz[i]->setRight(niz[i + 1]);

				niz[i - 1] = niz[i];
				for (int j = i; j < n - 2; j++) {
					niz[j] = niz[j + 2];
				}
				niz.pop_back();
				niz.pop_back();
				n -= 2;
				i--;
			}

		}
	}
	for (int k = 0; k < 2; k++) {
		int n = niz.size();
		for (int i = 0; i < n;i++) {
			if (niz[i]->whatIs() == OP) {

				if (niz[i]->getChar() == op[k]) {

					niz[i]->setLeft(niz[i-1]);
					niz[i]->setRight(niz[i+1]);
					
					niz[i - 1] = niz[i];
					for(int j = i; j < n-2; j++){
						niz[j] = niz[j + 2];
					}
					niz.pop_back();
					niz.pop_back();
					n -= 2;
					i--;
				}

			}
		}
	}

	root = niz[0];
}

vector<TreeNode*> Expression::postFix()
{
	vector<TreeNode*> postf;

	stack<TreeNode*> post;
	post.push(root);

	//stack<int> pout;
	while (!post.empty()) {
		TreeNode *curr = post.top();
		post.pop();
		postf.push_back(curr);


		if (curr->left) {
			post.push(curr->left);
		}
		if (curr->right) {
			post.push(curr->right);
		}
	}
	reverse(postf.begin(), postf.end());
	return postf;
}



//void TreeNode::postorder(TreeNode * node)
//{
//	list<TreeNode*> lista;
//	if (node == nullptr)
//		return ;
//
//	// first recur on left subtree 
//	postorder(node->left);
//
//	// then recur on right subtree 
//	postorder(node->right);
//
//	postfix.push_back(node);
//	
//	
//	

