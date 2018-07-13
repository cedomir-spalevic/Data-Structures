/*
@author Cedomir Spalevic
Red-Black Tree implementation
*/

#ifndef RBT_H_
#define RBT_H_
#include "Node.h"

template<typename T>
class RBT
{
	public:
		RBT();
		RBT(const RBT<T> &rbt);
		~RBT();
		RBT<T>& operator=(const RBT<T> &rbt);
		void insert(T data);
		bool remove(T data);
		bool exists(T data);
		int getSize();
		int getHeight();
		T* max();
		T* min();
		T* toArray();
		T* inorder();
		T* preorder();
		T* postorder();
	private:
		Node<T> head;
		int size;
		void insert(Node<T> *node, Node<T> *newNode);
		void remove(Node<T> *node, Node<T> *parent, Node<T> *sibling, T data);
		Node<T>* exists(Node<T> *node, T data);
		T* inorder(Node<T> *node, T* array, int &index);
		T* preorder(Node<T> *node, T* array, int &index);
		T* postorder(Node<T> *node, T* array, int &index);
		void rotate(Node<T> *node);
		Node<T>* RRrotation(Node<T> *grandparent, Node<T> *parent, Node<T> *node);
		Node<T>* RLrotation(Node<T> *grandparent, Node<T> *parent, Node<T> *node);
		Node<T>* LLrotation(Node<T> *grandparent, Node<T> *parent, Node<T> *node);
		Node<T>* LRrotation(Node<T> *grandparent, Node<T> *parent, Node<T> *node);
};

#endif