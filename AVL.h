/*
@author Cedomir Spalevic
AVL Tree implementation
*/

#ifndef AVL_H_
#define AVL_H_
#include "Node.h"

template<typename T>
class AVL
{
	public:
		AVL();
		AVL(const AVL<T> &avl);
		~AVL();
		AVL<T>& operator=(const AVL<T> &avl);
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
		Node<T>* rotate(Node<T> *node);
		Node<T>* RRrotation(Node<T> *node);
		Node<T>* RLrotation(Node<T> *node);
		Node<T>* LLrotation(Node<T> *node);
		Node<T>* LRrotation(Node<T> *node);
};

#endif