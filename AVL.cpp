/*
@author Cedomir Spalevic
AVL Tree implementation
*/

#include "AVL.h"

template<class T>
AVL<T>::AVL()
{
	head = 0;
	size = 0;
}

template<class T>
AVL<T>::AVL(const AVL<T> &avl)
{
	head = new Node<T>(*avl.head);
	size = avl.size;
}

template<class T>
AVL<T>::~AVL()
{
	delete head;
}

template<class T>
AVL<T>& AVL<T>::operator=(const AVL<T> &avl)
{
	delete head;
	head = new Node<T>(*avl.head);
	size = avl.size;
}

template<class T>
void AVL<T>::insert(T data)
{
	if(head == 0) head = new Node<T>(0, 0, 0, data); 
	else
	{
		insert(head, data);
		int hd = head->getHeightDifference();
		if(hd == 2 || hd == -2)
		{
			head = rotate(head);
			head->setParent(0);
		}
	}
	size++;
}

template<class T>
void AVL<T>::insert(Node<T> *node, T data)
{
	if(node->getData() > data)
	{
		if(node->getLeft() != 0)
		{
			insert(node->getLeft(), data);
			int lh = (node->getLeft() == 0 ? 0 : node->getLeft()->getHeightDifference());
			if(lh == 2 || lh == -2) node->setLeft(rotate(node->getLeft()));
		}
		else node->setLeft(new Node<T>(node, 0, 0, data));
	}
	else
	{
		if(node->getRight() != 0)
		{
			insert(node->getRight(), data);
			int rh = (node->getRight() == 0 ? 0 : node->getRight()->getHeightDifference());
			if(rh == 2 || rh == -2) node->setRight(rotate(node->getRight()));
		}
		else node->setRight(new Node<T>(node, 0, 0, data));
	}
}

template<class T>
bool AVL<T>::remove(T data)
{
	try
	{
		remove(head, data);
		size--;
		return 1;
	}
	catch(const char* exception)
	{
		return 0;
	}
}

template<class T>
Node<T>* AVL<T>::remove(Node<T> *node, T data)
{
	if(node->getData() > data)
	{
		if(node->getLeft() == 0) throw "Node does not exist";
		else node->setLeft(remove(node->getLeft(), data));
	}
	else if(node->getData() < data)
	{
		if(node->getRight() == 0) throw "Node does not exist";
		else node->setRight(remove(node->getRight(), data));
	}
	else
	{
		if(node->getRight() == 0 && node->getLeft() == 0)
		{
			delete node;
			return 0;
		}
		else if(node->getRight() == 0)
		{
			Node<T> *temp = node->getLeft();
			node->setLeft(0);
			delete node;
			return temp;
		}
		else if(node->getLeft() == 0)
		{
			Node<T> *temp = node->getRight();
			node->setRight(0);
			delete node;
			return temp;
		}
		else
		{
			Node<T> *temp = node->getRight();
			while(temp->getLeft() != 0) temp = temp->getLeft();
			node->setData(temp->getData());
			node->setRight(remove(node->getRight(), temp->getData()));
		}
	}
	return node;
}

template<class T>
bool AVL<T>::exists(T data)
{
	if(exists(head, data) != 0) return 1;
	else return 0;
}

template<class T>
Node<T>*  AVL<T>::exists(Node<T> *node, T data)
{
	if(node->getData() > data)
	{
		if(node->getLeft() == 0) return 0;
		else return(exists(node->getLeft(), data));
	}
	else if(node->getData() < data)
	{
		if(node->getRight() == 0) return 0;
		else return(exists(node->getRight(), data));
	}
	else return node;
}

template<class T>
int AVL<T>::getSize()
{
	return size;
}

template<class T>
int AVL<T>::getHeight()
{
	return head->getHeight();
}

template<class T>
T* AVL<T>::max()
{
	Node<T> *node = head;
	while(node->getRight()) node->getRight();
	return &(node->getData());
}

template<class T>
T* AVL<T>::min()
{
	Node<T> *node = head;
	while(node->getLeft()) node->getLeft();
	return &(node->getData());
}

template<class T>
T* AVL<T>::toArray()
{
	return inorder();
}

template<class T>
T* AVL<T>::inorder()
{
	T* array = new T[size];
	int index = 0;
	array = inorder(head, array, index);
	return array;
}

template<class T>
T* AVL<T>::inorder(Node<T> *node, T* array, int &index)
{
	if(node == 0) return 0;
	inorder(node->getLeft(), array, index);
	array[index] = node->getData();
	index++;
	inorder(node->getRight(), array, index);
	return array;
}

template<class T>
T* AVL<T>::preorder()
{
	T* array = new T[size];
	int index = 0;
	array = preorder(head, array, index);
	return array;
}

template<class T>
T* AVL<T>::preorder(Node<T> *node, T* array, int &index)
{
	if(node == 0) return 0;
	array[index] = node->getData();
	index++;
	preorder(node->getLeft(), array, index);
	preorder(node->getRight(), array, index);
	return array;
}

template<class T>
T* AVL<T>::postorder()
{
	T* array = new T[size];
	int index = 0;
	array = postorder(head, array, index);
	return array;
}

template<class T>
T* AVL<T>::postorder(Node<T> *node, T* array, int &index)
{
	if(node == 0) return 0;
	postorder(node->getLeft(), array, index);
	postorder(node->getRight(), array, index);
	array[index] = node->getData();
	index++;
	return array;
}

template<class T>
Node<T>* AVL<T>::rotate(Node<T> *node)
{
	if(node->getHeightDifference() > 0 && node->getRight()->getHeightDifference() > 0) return RRrotation(node);
	if(node->getHeightDifference() > 0 && node->getRight()->getHeightDifference() <= 0) return RLrotation(node);
	if(node->getHeightDifference() < 0 && node->getRight()->getHeightDifference() < 0) return LLrotation(node);
	if(node->getHeightDifference() < 0 && node->getRight()->getHeightDifference() >= 0) return LRrotation(node);
}

template<class T>
Node<T>* AVL<T>::RRrotation(Node<T> *node)
{
	Node<T> *left = node;
	Node<T> *parent = node->getRight();
	left->setRight(parent->getLeft());
	parent->setLeft(left);
	return parent;
}

template<class T>
Node<T>* AVL<T>::RLrotation(Node<T> *node)
{
	Node<T> *left = node;
	Node<T> *right = node->getRight();
	Node<T> *parent = right->getLeft();
	left->setRight(parent->getLeft());
	right->setLeft(parent->getRight());
	parent->setLeft(left);
	parent->setRight(right);
	return parent;
}

template<class T>
Node<T>* AVL<T>::LLrotation(Node<T> *node)
{
	Node<T> *right = node;
	Node<T> *parent = node->getLeft();
	right->setLeft(parent->getRight());
	parent->setRight(right);
	return parent;
}

template<class T>
Node<T>* AVL<T>::LRrotation(Node<T> *node)
{
	Node<T> *right = node;
	Node<T> *left = node->getLeft();
	Node<T> *parent = left->getRight();
	right->setLeft(parent->getRight());
	left->setRight(parent->getLeft());
	parent->setLeft(left);
	parent->setRight(right);
	return parent;
}
