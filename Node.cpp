/*
@author Cedomir Spalevic
Node class implementation
*/

#include "Node.h"

template<class T>
Node<T>::Node(Node<T> *nparent, Node<T> *nleft, Node<T> *nright, T ndata)
{
	setParent(nparent);
	setLeft(nleft);
	setRight(nright);
	setData(ndata);
	setHeight();
}

template<class T>
Node<T>::Node(Node<T> *nparent, Node<T> *nleft, Node<T> *nright, T ndata, char* ncolor)
{
	setParent(nparent);
	setLeft(nleft);
	setRight(nright);
	setData(ndata);
	setHeight();
	setColor(ncolor);
}

template<class T>
Node<T>::Node(const Node<T> &node)
{
	setParent(node.getParent());
	setLeft(node.getLeft());
	setRight(node.getRight());
	setData(node.getData());
	setHeight();
}

template<class T>
Node<T>& Node<T>::operator=(const Node<T> &node)
{
	return new Node<T>(node.getParent(), node.getLeft(), node.getRight(), node.getData());
}

template<class T>
Node<T>::~Node()
{
	parent = 0;
	delete left;
	delete right;
}

template<class T>
void Node<T>::setParent(Node<T> *nparent)
{
	parent = nparent;
}

template<class T>
Node<T>* Node<T>::getParent()
{
	return parent;
}

template<class T>
void Node<T>::setLeft(Node<T> *nleft)
{
	left = nleft;
	setHeight(nleft->height);
}

template<class T>
Node<T>* Node<T>::getLeft()
{
	return left;
}

template<class T>
void Node<T>::setRight(Node<T> *nright)
{
	right = nright;
	setHeight(nright->height);
}

template<class T>
Node<T>* Node<T>::getRight()
{
	return right;
}

template<class T>
void Node<T>::setData(T ndata)
{
	data = ndata;
}

template<class T>
T Node<T>::getData()
{
	return data;
}

template<class T>
void Node<T>::setColor(char* ncolor)
{
	color = ncolor;
}

template<class T>
char* Node<T>::getColor()
{
	return color;
}

template<class T>
void Node<T>::setHeight()
{
	height = max(left, right);
	if(parent != 0) parent->setHeight();
}

template<class T>
int Node<T>::getHeight()
{
	return height;
}

template<class T>
int Node<T>::getHeightDifference()
{
	int lh = (left == 0 ? 0 : left>getHeight());
	int rh = (right == 0 ? 0 : right->getHeight());
	return (lh - rh);
}

template<class T>
int Node<T>::max()
{
	int lh = (left == 0 ? 0 : left>getHeight());
	int rh = (right == 0 ? 0 : right->getHeight());
	return (lh > rh ? lh : rh);
}