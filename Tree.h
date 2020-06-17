#pragma once
#include "TreeNode.h"
#include <fstream>
#include <stdlib.h>


template <class T>
class Tree
{
	TreeNode<T>* _root;
	int _numNodes;//size of tree
public:
	Tree() 
	{
		_root = nullptr;
		_numNodes = 0;
	}
	Tree(TreeNode<T>* root, int numNodes) { _root = root; _numNodes = numNodes; };
	~Tree() { _root->~TreeNode(); };

	void save(ofstream& out) const
	{
		out.write((char*)&_numNodes, sizeof(_numNodes));
		out.write((char*)&_root, sizeof(_root));

		TreeNode<T>* tmp;
		tmp = _root->getNextChild();
		for (size_t i = 1; i <(size_t) _numNodes; i++)
		{
			if (tmp != nullptr) {
				out.write((char*)tmp->getData(), sizeof(T));
				tmp = tmp->getNextChild();
			}
		}
		

	}
	void load(ifstream& in)
	{

		in.read((char*)&_numNodes, sizeof(_numNodes));

		for (size_t i = 0; i < (size_t)_numNodes; i++)
		{
			_root->getChild(i)->getNextChild()->getData()->load(in);
		}
	}
	
	void freeMemory()
	{
		~Tree();
	}
	
	bool treeContains(const T& item)
	{

		if (_root==nullptr)
			return false;
		int tmp = _numNodes;

		Tree* t = new Tree(_root, tmp);
		while (tmp > 0 && t->_root != nullptr)
		{
			if (item == *(t->_root->getData()))
				return true;
			t->_root = t-> _root->getNextChild();
			tmp--;

		}

		return false;

	}
	

	TreeNode<T>* getplace()
	{
		if (_root==nullptr)
			return NULL;
		if (_root->getNumChildren() < 4)
			return _root;
		vector< TreeNode<T>* > vec;
		vec.push_back(_root);
		while (!vec.empty())
		{
			int n = vec.size();
			while (n > 0)
			{
				TreeNode<T>* tree = vec.front();
				vec.erase(vec.begin());
				if (tree->getNumChildren() == 4)
				{

					for (size_t i = 0; i < (size_t)tree->getNumChildren(); i++)
					{
						vec.push_back(tree->getChild(i));
					}
					n--;
				}
				else
				{

					return tree;
				}
			}
		}

		return NULL;
	}


	void addNode(const T& item)
	{
		T* it = new T(item);
		TreeNode<T>* node = new TreeNode<T>(it);
		if (getplace() == NULL) 
			_root = node;		
		else
		{
			TreeNode<T>* root = new TreeNode<T>();
			root= getplace();
			root->addChild(node);
			node->setParent(root);

		}

		_numNodes++;


	}

	const T& getNodeData(int index)
	{
		TreeNode<T> *t = _root->getChild(index);
		return *t->getData();
	}


	TreeNode<T>* begin() const
	{
		return _root;
	}
	

	class Iterator {
		TreeNode<T>* _p;
		friend class Tree<T>;
	public:
		Iterator(TreeNode<T>* pt = 0) : _p(pt) {}


		int operator!=(Iterator itr) const {
			return (_p != itr._p);
		}

		int operator==(Iterator itr) const {
			return (_p == itr._p);
		}

		Iterator& operator++() {
			if (_p == NULL)
				throw "null ptr";
			_p = _p->getNextChild();
			return *this;
		}

		Iterator& operator++(int) {
			if (_p == NULL)
				throw "null ptr";
			Iterator& tmp(*this);
			_p = _p->getNextChild();
			return tmp;

		}

		Iterator& operator--() {
			if (_p == NULL)
				throw "null ptr";
			_p = _p->getPrevChild();
			return *this;
		}

		Iterator& operator--(int) {
			if (_p == NULL)
				throw "null ptr";
			Iterator& tmp(*this);
			_p = _p->getPrevChild();
			return tmp;


		}

		T& operator*() {
			if (_p == NULL || _p->getData() == NULL)
				throw "null ptr";
			return *(_p->getData());
		}

	};
};

