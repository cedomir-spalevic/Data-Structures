/*
@author Cedomir Spalevic
Binary Search Tree implementation
*/

#ifndef BST_H_
#define BST_H_
#include "Node.h"

template<typename T>
class BST
{
	public:
		BST();
		BST(const BST<T> &bst);
		~BST();
		BST<T>& operator=(const BST<T> &bst);
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
		void insert(Node<T> *node, T data);
		Node<T>* remove(Node<T> *node, T data);
		Node<T>* exists(Node<T> *node, T data);
		T* inorder(Node<T> *node, T* array, int &index);
		T* preorder(Node<T> *node, T* array, int &index);
		T* postorder(Node<T> *node, T* array, int &index);
};

#endif