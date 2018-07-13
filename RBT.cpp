/*
@author Cedomir Spalevic
Red-Black Tree implementation
*/

#include "RBT.h"

template<class T>
RBT<T>::RBT()
{
	head = 0;
	size = 0;
}

template<class T>
RBT<T>::RBT(const RBT<T> &rbt)
{
	head = new Node<T>(*rbt.head);
	size = rbt.size;
}

template<class T>
RBT<T>::~RBT()
{
	delete head;
}

template<class T>
RBT<T>& RBT<T>::operator=(const RBT<T> &rbt)
{
	delete head;
	head = new Node<T>(*rbt.head);
	size = rbt.size;
}

template<class T>
void RBT<T>::insert(T data)
{
	if(head == 0) head = new Node<T>(0, 0, 0, data, "Black"); 
	else
	{
		Node<T> *node = new Node<T>(0, 0, 0, data, "Red");
		insert(head, node);
		rotate(node);
	}
	if(head->getColor() == "Red") head->setColor("Black");
	size++;
}

template<class T>
void RBT<T>::insert(Node<T> *node, Node<T> *newNode)
{
	if((node->getRight() != 0 && node->getRight()->getColor() == "Red") 
		&& (node->getLeft() != 0 && node->getLeft()->getColor() == "Red"))
	{
		node->getRight()->setColor("Black");
		node->getLeft()->setColor("Black");
		node->setColor("Red");
		rotate(node);
	}
	if(node->getData() > newNode->getData())
	{
		if(node->getLeft() != 0) insert(node->getLeft(), newNode);
		else node->setLeft(newNode);
	}
	else
	{
		if(node->getRight() != 0) insert(node->getRight(), newNode);
		else node->setRight(newNode);
	}
}

template<class T>
bool RBT<T>::remove(T data)
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
void RBT<T>::remove(Node<T> *node, Node<T> *parent, Node<T> *sibling, T data)
{
	if(parent != 0 && parent->getColor() == "Red" && node->getColor() == "Black" && sibling != 0 && sibling->getColor() == "Black"
		&& ((node->getRight() == 0 || node->getRight()->getColor() == "Black") 
			&& (node->getLeft() == 0 || node->getLeft()->getColor() == "Black")))
	{
		if(sibling != 0 && (sibling->getRight() == 0 || sibling->getRight()->getColor() == "Black") 
			&& (sibling->getLeft() == 0 || sibling->getLeft()->getColor() == "Black"))
		{
			parent->setColor("Black");
			node->setColor("Red");
			sibling->setColor("Red");
		}
		else
		{
			Node<T> *ggparent = parent->getParent();
			Node<T> *newNode;
			if(parent->getRight() == sibling)
			{
				if(sibling->getLeft() != 0 && sibling->getLeft()->getColor() == "Red")
				{
					parent->setColor("Black");
					node->setColor("Red");
					newNode = RLrotation(parent, sibling, sibling->getLeft());
				}
				else
				{
					sibling->getRight()->setColor("Black");
					sibling->setColor("Red");
					parent->setColor("Black");
					node->setColor("Red");
					newNode = RRrotation(parent, sibling, sibling->getRight());
				}
			}
			else if(parent->getLeft() == sibling)
			{
				if(sibling->getRight() != 0 && sibling->getRight()->getColor() == "Red")
				{
					parent->setColor("Black");
					node->setColor("Red");
					newNode = LRrotation(parent, sibling, sibling->getRight());
				}
				else
				{
					sibling->getLeft()->setColor("Black");
					sibling->setColor("Red");
					parent->setColor("Red");
					node->setColor("Red");
					newNode = LLrotation(parent, sibling, sibling->getLeft());
				}
			}
			else if(ggparent != 0)
			{
				if(ggparent->getLeft() == parent) ggparent->setLeft(newNode);
				else ggparent->setRight(newNode);
			}
			else head = newNode;
		}
	}
	else if(parent == 0 && (node->getRight() == 0 || node->getRight()->getColor() == "Black") && 
		(node->getLeft() == 0 || node->getLeft()->getColor() == "Black"))
	{
		node->setColor("Black");
		if(node->getRight() != 0) node->getRight()->setColor("Red");
		if(node->getLeft() != 0) node->getLeft()->setColor("Red");
	}

	if(node->getData() > data)
	{
		if(node->getLeft() == 0) throw "Node does not exist";
		else remove(node->getLeft(), node, node->getRight(), data);
	}
	else if(node->getData() < data)
	{
		if(node->getRight() == 0) throw "Nodes does not exists";
		else remove(node->getRight(), node, node->getLeft(), data);
	}
	else
	{
		if(node->getLeft() == 0 && node->getRight() == 0)
		{
			if(parent != 0)
			{
				if(parent->getRight() == node) parent->setRight(0);
				else parent->setLeft(0);
				delete node;
			}
			else head = 0;
			return;
		}
		else if(node->getLeft() == 0)
		{
			if(node->getColor() == "Black") node->getRight()->setColor("Black");
			if(parent != 0)
			{
				if(parent->getRight() == node) parent->setRight(node->getRight());
				else parent->setLeft(node->getRight());
			}
			else head = node->getRight();
			node->setRight(0);
			delete node;
			return;
		}
		else if(node->getRight() == 0)
		{
			if(node->getColor() == "Black") parent->setRight(node->getLeft());
			if(parent != 0)
			{
				if(parent->getRight() == node) parent->setRight(node->getLeft());
				else parent->setLeft(node->getLeft());
			}
			else head = node->getLeft();
			node->setLeft(0);
			delete node;
			return;
		}
		else
		{
			Node<T> *temp = node->getLeft();
			while(temp->getRight() != 0) temp = temp->getRight();
			node->setData(temp->getData());
			remove(node->getLeft(), node, node->getRight(), temp->getData());
		}
	}
}

template<class T>
bool RBT<T>::exists(T data)
{
	if(exists(head, data) != 0) return 1;
	else return 0;
}

template<class T>
Node<T>* RBT<T>::exists(Node<T> *node, T data)
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
int RBT<T>::getSize()
{
	return size;
}

template<class T>
int RBT<T>::getHeight()
{
	return head->getHeight();
}

template<class T>
T* RBT<T>::max()
{
	Node<T> *node = head;
	while(node->getRight()) node->getRight();
	return &(node->getData());
}

template<class T>
T* RBT<T>::min()
{
	Node<T> *node = head;
	while(node->getLeft()) node->getLeft();
	return &(node->getData());
}

template<class T>
T* RBT<T>::toArray()
{
	return inorder();
}

template<class T>
T* RBT<T>::inorder()
{
	T* array = new T[size];
	int index = 0;
	array = inorder(head, array, index);
	return array;
}

template<class T>
T* RBT<T>::inorder(Node<T> *node, T* array, int &index)
{
	if(node == 0) return 0;
	inorder(node->getLeft(), array, index);
	array[index] = node->getData();
	index++;
	inorder(node->getRight(), array, index);
	return array;
}

template<class T>
T* RBT<T>::preorder()
{
	T* array = new T[size];
	int index = 0;
	array = preorder(head, array, index);
	return array;
}

template<class T>
T* RBT<T>::preorder(Node<T> *node, T* array, int &index)
{
	if(node == 0) return 0;
	array[index] = node->getData();
	index++;
	preorder(node->getLeft(), array, index);
	preorder(node->getRight(), array, index);
	return array;
}

template<class T>
T* RBT<T>::postorder()
{
	T* array = new T[size];
	int index = 0;
	array = postorder(head, array, index);
	return array;
}

template<class T>
T* RBT<T>::postorder(Node<T> *node, T* array, int &index)
{
	if(node == 0) return 0;
	postorder(node->getLeft(), array, index);
	postorder(node->getRight(), array, index);
	array[index] = node->getData();
	index++;
	return array;
}

template<class T>
void RBT<T>::rotate(Node<T> *node)
{
	if(node->getParent() == 0) return;
	Node<T> *parent = node->getParent();
	if(parent->getParent() == 0) return;
	Node<T>*grandparent = parent->getParent();
	if(node->getColor() == "Red" && parent->getColor() == "Red")
	{
		Node<T> *newNode;
		Node<T> *ggparent = grandparent->getParent();
		if(grandparent->getData() > node->getData())
		{
			if(parent->getData() > node->getData())
			{
				parent->setColor("Black");
				grandparent->setColor("Red");
				newNode = LLrotation(grandparent, parent, node);
			}
			else
			{
				node->setColor("Black");
				grandparent->setColor("Red");
				newNode = LRrotation(grandparent, parent, node);
			}
		}
		else
		{
			if(parent->getData() > node->getData())
			{
				node->setColor("Black");
				grandparent->setColor("Red");
				newNode = RLrotation(grandparent, parent, node);
			}
			else
			{
				parent->setColor("Black");
				grandparent->setColor("Red");
				newNode = RRrotation(grandparent, parent, node);
			}
		}

		if(ggparent != 0)
		{
			if(ggparent->getLeft() == grandparent) ggparent->setLeft(newNode);
			else ggparent->setRight(newNode);
		}
		else head = newNode;
	}
}

