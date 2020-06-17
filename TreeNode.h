#pragma once
#include <vector>
#include <iostream>
#include <string.h>
#include <stdlib.h>
using namespace std;

#define MAX_CHILDREN 4
template<class T>
class TreeNode {

private:

	T* _data;
	TreeNode<T>* _parent;
	vector< TreeNode<T>* > _children;

public:

	TreeNode(TreeNode<T>* parent, T* data) : _parent(parent),  _data (data), _children(0,0) {}
	TreeNode(): _parent(nullptr), _data(nullptr), _children(0, 0) {}
	TreeNode(T* data) : _data(data), _parent(nullptr),  _children(0,0) {}
	TreeNode(const TreeNode<T>& other) { _data = other.getData(); _parent = other.getParent(); _children = other._children; }
	~TreeNode() { delete _data; delete _parent; _children.clear(); }

	T* getData() const
	{
		if (this!=NULL)
			return _data;
		return NULL;
	}


	vector< TreeNode<T>* > getChildren() const
	{
		if (this != NULL)
			return _children;
	}

	void setData(T* data)
	{
		_data = new T(*data);
		*_data = *data;
	}

	void addChild(T* data)
	{
		TreeNode<T> *t = new TreeNode<T>(data);
		if (getNumChildren()< MAX_CHILDREN)
			_children.push_back(t);
	}
	void addChild(TreeNode<T>* newChild)
	{
		if (getNumChildren() < MAX_CHILDREN)
			_children.push_back(newChild);
	}
	void removeChild() //removes the nodes last entered child or if no children - does nothing
	{
		if (getNumChildren() == 0)
			return;
		_children.pop_back();
	}
	
	TreeNode<T>* findChild(T* data) const // returns ptr or NULL
	{
		for (size_t i = 0; i < getNumChildren(); ++i)
		{
			if (_children.at(i)->getData() == data)
				return _children[i];

		}
	}
	int findChildIndx(T* data) const // returns childs indx or -1
	{
		
		for (size_t i=0; i< (size_t)getNumChildren() ;i++)
		{
			T* tmp = _children[i]->getData();
			if (tmp==data)
				return i;
		}
		return -1;
	}
	TreeNode<T>* getChild(int indx) const
	{
		return _children.at(indx);
	}

	TreeNode<T>* getNextGrandson() const
	{
		
		for (size_t i = 0; i < (size_t)getNumChildren(); i++)
		{
			if (_parent->_children[i]->getNumChildren() > 0)
				return _parent->_children[i]->_children[0];
		}

		return NULL;
	}


	TreeNode<T>* getNextChild() const 
	{
		if (this == nullptr)
			return NULL;
		
		if (getParent() == NULL && getNumChildren()==0)	// im the root & dont have children
			return NULL;
		if (getParent() == NULL)	// im the root
			return getChild(0);
		int index = _parent->findChildIndx(_data);	//my index

		if ((_parent->getNumChildren()) > (index+1))
		{
			return _parent->getChild(index + 1);	// return the brother
		}

		TreeNode<T>* res = getNextGrandson();
		if (_parent->getNumChildren()==(findChildIndx(_data)+1) && res==nullptr)	//im the last & no grandsons
			return NULL;

		if ((_parent->getNumChildren())==1)		//im the only child
			return NULL;
		

		if (_parent->getNumChildren() == (index + 1))
		{
			return res;	//return the grandson
		}

		return NULL;
		
	}
	TreeNode<T>* getPrevChild() const
	{
		if (this == NULL)
			return NULL;
		if (_parent == nullptr)		//im the root
			return NULL;
		int index = _parent->findChildIndx(_data);
		if (_parent->_children[0]!=this)
			return _parent->getChild(index - 1);		//return my prev bro
		else
		{
			return _parent;		//im the first son, return my parent
		}
	}
	TreeNode<T>* getParent() const
	{
		if (this!=NULL)
			return _parent;
		return NULL;
	}
	void setParent(TreeNode<T>* parent)
	{
		_parent = new TreeNode<T>(*parent);
		*_parent = *parent;
	
	}
	int getNumChildren() const
	{
		if (this!=NULL)
			return _children.size();
		return NULL;

	}
	bool operator==(const T& other)
	{
		return (other == *getData());
	}

	bool operator==(const TreeNode& other)
	{
		bool res=true;
		for (size_t i = 0; i < getNumChildren(); ++i)
		{
			if (other.getChild(i) != getChild(i)) {
				res = false;
				break;
			}		
		}
		return (other.getData() == getData() && other.getParent()==getParent() && other.getNumChildren()==getNumChildren()
			& res==true);
	}

};
