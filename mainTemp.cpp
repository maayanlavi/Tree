/*
#include <iostream>
#include <fstream>
#include <string>
#include "Tree.h"
#include "Student.h"

using namespace std;


int main() {

	int* t1 = new int[1];
	t1[0] = 1;

	int* t2 = new int[1];
	t2[0] = 2;

	int* t3 = new int[1];
	t3[0] = 3;

	int* t4 = new int[1];
	t4[0] = 4;

	int* t5 = new int[1];
	t5[0] = 5;

	TreeNode<int>* tmp1 = new TreeNode<int>(t1);
	TreeNode<int>* tmp2 = new TreeNode<int>(tmp1, t2);
	TreeNode<int>* tmp3 = new TreeNode<int>(tmp1, t3);

	tmp1->addChild(tmp2);
	tmp1->addChild(tmp3);

	TreeNode<int>* tmp4 = new TreeNode<int>(t4);

	tmp2->addChild(tmp4);
	int x = tmp1->findChildIndx(t3);

	Tree<int> intTree;
	intTree.addNode(tmp1);



	TreeNode<int>* tmp5 = new TreeNode<int>(tmp1,nullptr);

	tmp5=


}

*/

