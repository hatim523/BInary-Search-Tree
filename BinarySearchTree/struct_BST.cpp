#include<iostream>

using namespace std;

/************************************************************************************/
/* Author: Hatim																	*/
/* Last Modified: 26 November 2018													*/
/* Purpose: Implementation of Binary Search Tree									*/
/* Functions: Insert()  || Delete() || Height() || Min() || Max() || BalanceTree()	*/
/* Traversal Functions: Inorder() || Preorder() || PostOrder() || BreadthFirst()	*/
/************************************************************************************/

template<class T>
class DynamicSafeArray
{
private:
	T *data;
	int size;
	void DeleteAll()
	{
		if (data != 0)
			delete[] data;
		data = 0;
		size = 0;
	}
public:
	DynamicSafeArray()	//default
	{
		size = 10;
		data = new T[size];
		memset(data, 0, sizeof(T) * size);
	}
	DynamicSafeArray(int pSize)	//parametrize
	{
		setSize(pSize);
		data = new T[size];
		memset(data, 0, sizeof(T) * size);
	}
	DynamicSafeArray(const DynamicSafeArray &rhs)	//copy constructor
	{
		setSize(rhs.size);
		data = new T[size];
		memcpy(data, rhs.data, sizeof(T) * size);
	}
	DynamicSafeArray& operator = (const DynamicSafeArray &rhs)
	{
		if (this != &rhs)
		{
			DeleteAll();
			setSize(rhs.size);
			data = new T[size];
			memcpy(data, rhs.data, sizeof(T) * size);
		}
		return *this;
	}
	int getSize() const
	{
		return size;
	}
	T& operator [] (int i)
	{
		T returnVal = NULL;
		if (i >= 0 && i < size)
			return data[i];
		else
		{
			try
			{
				throw "Array out of Bound.";
			}
			catch (const char* msg)
			{
				cout << msg << endl;
				return returnVal;
			}
		}
	}
	const T& operator [] (int i) const	//for rval
	{
		ReSize(i);
		return *(data + i);
	}
	void ReSize(int pSize)	const
	{
		if (pSize >= size)
		{
			T *temp = new T[size];
			int prev_size = size;
			memcpy(temp, data, sizeof(T) * size);
			DeleteAll();
			size = pSize + 1;
			data = new T[size];
			memset(data, 0, sizeof(T) * size);
			memcpy(data, temp, sizeof(T) * prev_size);
		}
	}
	void setSize(int pSize)
	{
		if (pSize > 0)
			size = pSize;
		else
			size = 10;
	}
	~DynamicSafeArray()
	{
		DeleteAll();
	}
};

template<class S>
class ArrayStack
{
private:
	DynamicSafeArray<S> *stackData;
	int top;
public:
	ArrayStack()
	{
		stackData = new DynamicSafeArray<S>(10);
		top = -1;
	}
	ArrayStack(int pSize)	//Stack of user defined size
	{
		stackData = new DynamicSafeArray<S>(pSize);
		top = -1;
	}
	void Push(S data)
	{
		top++;
		(*stackData)[top] = data;	//
	}
	S& Pop()
	{
		return (*stackData)[top--];	//solved: first dereferenced pointer than used [] operator
	}
	S Peek()
	{
		if (top != -1)
			return (*stackData)[top];
		else
			return NULL;
	}
	bool IsEmpty()
	{
		bool empty = false;
		if (top == -1)
			empty = true;
		return empty;
	}
	bool IsFull()
	{
		bool full = false;
		if (top == stackData->getSize())
			full = true;
		return full;
	}
	~ArrayStack()
	{
		if (stackData != 0)
			delete stackData;
	}
};

template<class T>
class Queue
{
private:
	T *data;
	int rear, front, size;
public:
	Queue(int pSize = 10)
	{
		size = pSize;
		rear = -1;
		front = -1;
		data = new T[size];
	}
	void EnQueue(T &element)
	{
		if (isFull())
			cout << "Queue is Full." << endl;
		else
		{
			rear = (rear + 1) % size;
			data[rear] = element;
			if (front == -1)
				front = rear;
		}
	}
	T& DeQueue()
	{
		int temp = front;
		if (front == rear)
			front = rear = -1;
		else
			front = (front + 1) % size;
		return data[temp];
	}
	T Peek()
	{
		return data[front];
	}
	void DisplayQueue()
	{
		for (int i = front; i < rear; i++)
			cout << data[i] << endl;
	}
	bool isFull()
	{
		if (rear + 1 % size == front)
			return true;
		else
			return false;
	}
	bool isEmpty()
	{
		if (rear == front && rear == -1)
			return true;
		else
			return false;
	}
};

template<class T>
class BTNode
{
private:
	T data;
public:
	BTNode<T> *lChild, *rChild;
	BTNode(T pdata = 0, BTNode<T> *l = 0, BTNode<T> *r = 0)	//parametrize + default constructor
	{
		data = pdata;
		lChild = l;
		rChild = r;
	}
	T& Data()
	{
		return data;
	}
};

template<class T>
class BinarySearchTree
{
private:
	BTNode<T> *root;
	BTNode<T> *parent;
	int length;
	//helper functions
	void Insert(T &d, BTNode<T> *parent)
	{
		if (d < parent->Data())	//left insertion
		{
			if (parent->lChild == 0)
			{
				BTNode<T> *node = new BTNode<T>(d);
				parent->lChild = node;
			}
			else
			{
				Insert(d, parent->lChild);
			}
		}
		else		//right insertion
		{
			if (parent->rChild == 0)
			{
				BTNode<T> *node = new BTNode<T>(d);
				parent->rChild = node;
			}
			else
			{
				Insert(d, parent->rChild);
			}
		}
	}
	void DeleteNodes(BTNode<T> *leaf)
	{
		if (leaf != 0)
		{
			DeleteNodes(leaf->lChild);
			DeleteNodes(leaf->rChild);
			cout << "Deleting node at Address: " << leaf << " with Data: " << leaf->Data() << endl;
			delete leaf;
		}
	}
	BTNode<T>* Search(BTNode<T> *leaf, BTNode<T> *parent, T key)	//helper function for delete node || returns parent node

	{
		if (leaf != 0 && key == leaf->Data())
			return parent;
		else if (leaf != 0 && key < leaf->Data())
		{
			parent = leaf;
			leaf = parent->lChild;
			Search(leaf, parent, key);
		}
		else if (leaf != 0 &&  key > leaf->Data())
		{
			parent = leaf;
			leaf = parent->rChild;
			Search(leaf, parent, key);
		}
		else
			return NULL;
	}
	//helper-traversals
	void Visit(BTNode<T> *node)
	{
		cout << "Node Data: " << node->Data() << endl;
	}
	void Inorder(BTNode<T> *leaf)
	{
		if (leaf != 0)
		{
			Inorder(leaf->lChild);
			Visit(leaf);
			Inorder(leaf->rChild);
		}
	}
	void PreOrder(BTNode<T> *leaf)
	{
		if (leaf != 0)
		{
			Visit(leaf);
			PreOrder(leaf->lChild);
			PreOrder(leaf->rChild);
		}
	}
	void PostOrder(BTNode<T> *leaf)
	{
		if (leaf != 0)
		{
			PostOrder(leaf->lChild);
			PostOrder(leaf->rChild);
			Visit(leaf);
		}
	}
	//end of helper-traversals
	bool Search(T key, BTNode<T> *leaf)
	{
		if (leaf != 0)
		{
			if (key == leaf->Data())
				return true;
			else if (key < leaf->Data())
				return Search(key, leaf->lChild);
			else
				return Search(key, leaf->rChild);
		}
		return false;
	}
	void CopyArray(BTNode<T>* leaf, T *data)
	{
		static int i;
		if (leaf != 0)
		{
			CopyArray(leaf->lChild, data);
			data[i++] = leaf->Data();
			CopyArray(leaf->rChild, data);
		}
	}
	int Min(BTNode<T> *leaf)	//Minimum node will be to extreme left
	{
		if (leaf->lChild != 0)
			Min(leaf->lChild);
		else
			return leaf->Data();
	}
	int Max(BTNode<T> *leaf)	//Maximum number node will be to extreme right
	{
		if (leaf->rChild != 0)
			Max(leaf->rChild);
		else
			return leaf->Data();
	}
	int WidthTree(BTNode<T> *leaf)
	{
		Queue<BTNode<T>*> queue;
		queue.EnQueue(root);
		int width = 0;
		int MaxWidth = 0;
		int count = 0;
		int i = 0;
		while (queue.isEmpty())
		{
			while (count >= 0)
			{
				BTNode<T> *temp = queue.Peek();
				if (temp->lChild != 0)
				{
					queue.EnQueue(temp->lChild);
					width++;
				}
				if (temp->rChild != 0)
				{
					width++;
				}
				count--;
			}
			i++;
			count = i * 2;
		}
	}
	
	int HeightTree(BTNode<T> *leaf) {
		static int h = 0, i = 0;
		if (leaf == 0)
			return 0;
		
		h = HeightTree(leaf->lChild);
		h++;
		i = HeightTree(leaf->rChild);
		i++;
		if (i > h)
			return i;
		else
			return h ;
	}
public:
	BinarySearchTree()	//default constructor
	{
		root = 0;
		parent = 0;
		length = 0;
	}
	BinarySearchTree(const BinarySearchTree<T> *rhs)	//copy constructor
	{
		if (rhs.root != 0)
		{
			Queue<BTNode<T>*> nodes;
			nodes.EnQueue(rhs.root);

			while (!nodes.isEmpty())
			{
				BTNode<T> *temp = nodes.Peek();
				Insert(temp->Data());
				if (temp->lChild != 0)
				{
					nodes.EnQueue(temp->lChild);
				}
				if (temp->rChild != 0)
				{
					nodes.EnQueue(temp->rChild);
				}
				nodes.DeQueue();
			}
		}
	}
	void Insert(T d)
	{
		if (!root)
		{
			BTNode<T> *node = new BTNode<T>(d);
			root = node;
		}
		else
			Insert(d, root);
		length++;
	}
	int WidthTree()
	{
		if (root != 0)
			return WidthTree(root);
		else
			return 0;
	}
	//traversal functions
	void BreadthFirstTraversal()	//Create a parameter size and update it while inserting
	{
		cout << "Breadth First Traversal" << endl;
		Queue<BTNode<T> * > Unexplored(20);		//change 20 to size

		Unexplored.EnQueue(root);
		while (!Unexplored.isEmpty())
		{
			BTNode<T> *temp = Unexplored.Peek();
			cout << temp->Data() << " ";
			if (temp->lChild != 0)
				Unexplored.EnQueue(temp->lChild);
			if (temp->rChild != 0)
				Unexplored.EnQueue(temp->rChild);
			Unexplored.DeQueue();
		}
		cout << endl;
	}
	int Min()
	{
		if (root != 0)
			return Min(root);
		else
			return -1;	//indicates Tree is empty
	}
	int Max()
	{
		if (root != 0)
			return Max(root);
		else
			return -1;
	}
	int HeightTree()
	{
		if (root != 0)
		{
			return HeightTree(root);
		}
		else
			return 0;
	}
	void BalanceTree()	//balances tree by changing root to avg.number
	{
		//copying contents of tree in an array by Inorder Traversal i.e sorted results
		if (root != 0)
		{
			T *data = new T[length];
			CopyArray(root, data);
			//deleting previos tree
			DeleteNodes(root);
			root = 0;
			int temp = length;
			length = 0;
			//creating new balanced tree
			Insert(data[temp / 2]);
			data[temp / 2] = -1;
			for (int i = 0; i < temp; i++)
			{
				if (data[i] != -1)
					Insert(data[i]);
			}
			delete[] data;
		}
	}
	void Delete(T key)
	{
		BTNode<T> *parent = root;
		BTNode<T> *leaf = root;
		if (parent = Search(leaf, parent, key))
		{

			if (parent->lChild != 0 && parent->lChild->Data() == key)
				leaf = parent->lChild;
			else if (parent->rChild != 0 && parent->rChild->Data() == key)
				leaf = parent->rChild;
			else		//when the node to be deleted is root
				leaf = parent;
			//Now looking for cases

			//Case 1: When node is leaf
			if (leaf->rChild == 0 && leaf->lChild == 0)
			{
				if (parent->rChild->Data() == key)
				{
					parent->rChild = 0;
					delete leaf;
				}
				else
				{
					parent->lChild = 0;
					delete leaf;
				}
			}
			//Case 2: When Node has one Child
			else if ((leaf->lChild == 0 && leaf->rChild != 0) || (leaf->rChild == 0 && leaf->lChild != 0))
			{
				if (leaf->lChild != 0)
				{
					T max = Max(leaf->lChild);	//extracting largest node from left child
					Delete(max);	//delete the max node
					leaf->Data() = max;	//replace the value of key with deleted max node
				}
				else
				{
					T min = Min(leaf->rChild);
					Delete(min);
					leaf->Data() = min;
				}
			}
			//Case 3: When the node to be deleted has both pointers occupied i.e has two Children
			else if (leaf->lChild != 0 && leaf->rChild != 0)
			{
				//choosing min value from right child		//can also choose max value from left child
				T min = Min(leaf->rChild);
				Delete(min);
				leaf->Data() = min;
			}
		}
		else
			cout << "Entered key is not in tree." << endl;
	}
	void Inorder()
	{
		if (root != 0)
		{
			cout << "Inorder Traversal (Sorted Results): " << endl;
			Inorder(root);
		}
		else
			cout << "Empty Tree" << endl;
		cout << endl;
	}
	void PreOrder()
	{
		if (root != 0)
		{
			cout << "PreOrder Traversal: " << endl;
			PreOrder(root);
		}
		else
			cout << "Empty Tree" << endl;
		cout << endl;
	}
	void PostOrder()
	{
		if (root != 0)
		{
			cout << "PostOrder Traversal: " << endl;
			PostOrder(root);
		}
		else
			cout << "Empty Tree" << endl;
		cout << endl;
	}
	void PreOrder_Stack()
	{
		if (root != 0)
		{
			ArrayStack<BTNode<T>*> stack(50);
			stack.Push(root);
			while (!stack.IsEmpty())
			{
				BTNode<T> *temp = stack.Peek();
				stack.Pop();
				if (temp != 0)
					Visit(temp);
				if (temp != 0)
					stack.Push(temp->rChild);
				if (temp != 0)
					stack.Push(temp->lChild);

			}
		}
	}
	void PostOrder_Stack()	//not understood
	{
		if (root != 0)
		{
			ArrayStack<BTNode<T> *> stack(50);
			stack.Push(root);
			
			

			while (!stack.IsEmpty())
			{
				while (stack.Peek()->lChild)
				{
					stack.Push(stack.Peek()->lChild);
				}
				while (stack.Peek()->rChild)
				{
					stack.Push(stack.Peek()->rChild);
				}
				Visit(stack.Pop());
			}
		}
	}
	//end of traversal functions
	bool Search(T key)
	{
		if (root == 0)
			return false;
		else
			return Search(key, root);
	}
	const int& getLength()
	{
		return length;
	}
	~BinarySearchTree()
	{
		if (root != 0)
			DeleteNodes(root);
		root = 0;
	}
};

int main()
{
	BinarySearchTree<int> *tree = new BinarySearchTree<int>();
	tree->Insert(25);
	tree->Insert(6);
	tree->Insert(5);
	tree->Insert(10);
	tree->Insert(8);
	tree->Insert(15);
	tree->Insert(35);
	tree->Insert(26);
	tree->Insert(9);

	tree->PostOrder();
	tree->PreOrder();
	return 0;
}