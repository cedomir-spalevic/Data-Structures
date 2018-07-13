/*
@author Cedomir Spalevic
Binary Search Tree implementation
*/

#include "BST.h"

template<class T>
BST<T>::BST()
{
	head = 0;
	size = 0;
}

template<class T>
BST<T>::BST(const BST<T> &bst)
{
	head = new Node<T>(*bst.head);
	size = bst.size;
}

template<class T>
BST<T>::~BST()
{
	delete head;
}

template<class T>
BST<T>& BST<T>::operator=(const BST<T> &bst)
{
	delete head;
	head = new Node<T>(*bst.head);
	size = bst.size;
}

template<class T>
void BST<T>::insert(T data)
{
	if(head == 0) head = new Node<T>(0, 0, 0, data); 
	else insert(head, data);
	size++;
}

template<class T>
void BST<T>::insert(Node<T> *node, T data)
{
	if(node->getData() > data)
	{
		if(node->getLeft() != 0) insert(node->getLeft(), data);
		else node->setLeft(new Node<T>(node, 0, 0, data));
	}
	else
	{
		if(node->getRight() != 0) insert(node->getRight(), data);
		else node->setRight(new Node<T>(node, 0, 0, data));
	}
}

template<class T>
bool BST<T>::remove(T data)
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
Node<T>* BST<T>::remove(Node<T> *node, T data)
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
bool BST<T>::exists(T data)
{
	if(exists(head, data) != 0) return 1;
	else return 0;
}

template<class T>
Node<T>*  BST<T>::exists(Node<T> *node, T data)
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
int BST<T>::getSize()
{
	return size;
}

template<class T>
int BST<T>::getHeight()
{
	return head->getHeight();
}

template<class T>
T* BST<T>::max()
{
	Node<T> *node = head;
	while(node->getRight()) node->getRight();
	return &(node->getData());
}

template<class T>
T* BST<T>::min()
{
	Node<T> *node = head;
	while(node->getLeft()) node->getLeft();
	return &(node->getData());
}

template<class T>
T* BST<T>::toArray()
{
	return inorder();
}

template<class T>
T* BST<T>::inorder()
{
	T* array = new T[size];
	int index = 0;
	array = inorder(head, array, index);
	return array;
}

template<class T>
T* BST<T>::inorder(Node<T> *node, T* array, int &index)
{
	if(node == 0) return 0;
	inorder(node->getLeft(), array, index);
	array[index] = node->getData();
	index++;
	inorder(node->getRight(), array, index);
	return array;
}

template<class T>
T* BST<T>::preorder()
{
	T* array = new T[size];
	int index = 0;
	array = preorder(head, array, index);
	return array;
}

template<class T>
T* BST<T>::preorder(Node<T> *node, T* array, int &index)
{
	if(node == 0) return 0;
	array[index] = node->getData();
	index++;
	preorder(node->getLeft(), array, index);
	preorder(node->getRight(), array, index);
	return array;
}

template<class T>
T* BST<T>::postorder()
{
	T* array = new T[size];
	int index = 0;
	array = postorder(head, array, index);
	return array;
}

template<class T>
T* BST<T>::postorder(Node<T> *node, T* array, int &index)
{
	if(node == 0) return 0;
	postorder(node->getLeft(), array, index);
	postorder(node->getRight(), array, index);
	array[index] = node->getData();
	index++;
	return array;
}


