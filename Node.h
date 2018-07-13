/*
@author Cedomir Spalevic
Node class implementation
*/

#ifndef NODE_H_
#define NODE_H_

template<typename T>
class Node
{
	public:
		Node(Node<T> *nparent, Node<T> *nleft, Node<T> *nright, T ndata);
		Node(Node<T> *nparent, Node<T> *nleft, Node<T> *nright, T ndata, char* ncolor);
		Node(const Node<T> &node);
		~Node();
		Node<T>& operator=(const Node<T> &node);
		void setParent(Node<T> *nparent);
		Node<T>* getParent();
		void setLeft(Node<T> *nleft);
		Node<T>* getLeft();
		void setRight(Node<T> *nright);
		Node<T>* getRight();
		void setData(T ndata);
		T getData();
		void setColor(char* ncolor);
		char* getColor();
		void setHeight();
		int getHeight();
		int getHeightDifference();
	private:
		Node<T> *parent;
		Node<T> *left;
		Node<T> *right;
		T data;
		int height;
		char* color;
		int max();
};

#endif