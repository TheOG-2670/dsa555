
#pragma once

#include <iostream>
/*
Doubly Linked List Data Structure-> insert, remove and access nodes (containing data) from front and back
*/
template <typename T>
class DList
{		
		
	public:
		//creates a node with data_ to store the node's data, next_ and prev_ pointer to link one node to another
		struct Node
		{
			T data_;
			Node* next_;
			Node* prev_;

			//constructor creates node in initial state
			/*const T &data = T{} -> const: data cannot be modified;
									 T -> defined data type of the list;
									 &data -> reference to original data;
									 T{} -> creation of empty object of type T
			*/
			Node(const T& data = -1, Node* next = nullptr, Node* prev = nullptr)
			{
				data_ = data;
				next_ = next;
				prev_ = prev;
			}

			bool isEmpty() const
			{
				return data_ == -1;
			}

			
		};
		
		//pointers pointing to first and last nodes in list
		Node* front_;
		Node* back_;
		//-------------------------------------------------------
		DList(); 
		~DList();
		void push_front(const T &data); 
		void push_back(const T &data);  
		void pop_front(); 
		void pop_back(); 
		void print() const; 
		void reversePrint() const;

};

//constructor of list object (front_ and back_ initially point to nothing)
template <typename T>
DList<T>::DList() 
{
	front_ = nullptr;
	back_ = nullptr;
}

//adds new node to front of list
template <typename T>
void DList<T>::push_front(const T &data) 
{
	Node *nn = new Node(data, front_); 

	//check if front node exists and set its prev_ to point to new node; otherwise set new node as back_
	if (front_ != nullptr) 
	{
		front_->prev_ = nn; 
	}
	else
	{
		
		back_ = nn; 
	}

	front_ = nn; //make front_ point to new node
}

//adds new node to back of list
template<typename T>
void DList<T>::push_back(const T & data)
{
	
	Node *newNode = new Node(data, nullptr, back_);

	/*check if back node exists and set its next_ to point to new node; otherwise if back_ doesn't exist (doesn't point 
	to any node), set front_ to new node*/
	if (back_ != nullptr)
	{
		back_->next_ = newNode;
	}
	else
	{
		front_ = newNode;
	}

	back_ = newNode; //set back_ to new node
}

//removes existing node from front of list
template<typename T>
void DList<T>::pop_front()
{

	/*check if front node exists and set it as removal node;
	make next node after removal node as new front node;*/
	if (front_ != nullptr)
	{
		
		Node* removedNode = front_;

		
		front_ = removedNode->next_;

		/*check if front node exists and set back_ to null;
		otherwise set front node's prev_ to null (as it previously pointed to the removed node)*/
		if (front_ == nullptr)
		{
			back_ = nullptr; 
		}
		else
		{
			front_->prev_ = nullptr; 
		}
		
		
		delete removedNode; //release removed node
	}

}

//removes existing node from back of list
template<typename T>
void DList<T>::pop_back()
{
	/*check if back node exists and select it as node to remove;
	set node before back node to become new back node*/
	if (back_ != nullptr)
	{
		
		Node* removedNode = back_;

		back_ = removedNode->prev_; 

		/*check if new back node doesn't exist and set front_ to null;
		otherwise, if the back_ node does exist, set its next_ pointer to null (since it won't be pointing to the 
		removed node anymore)*/
		if (back_ == nullptr)
		{
			front_ = nullptr; 
		}
		else
		{
			back_->next_ = nullptr; 
		}
		
		
		delete removedNode; //release removed node
	}

	
}

//prints nodes in list starting from front
template <typename T>
void DList<T>::print() const
{
	Node *currentNode = front_; //select front_ node to being printing list
		
	//print one node and move to next until back_ node reached
	while (currentNode != nullptr) 
	{
		std::cout << currentNode->data_ << " "; 
		currentNode = currentNode->next_;
	}

	//print if list is empty (front_ node doesn't exist)
	if (front_ == nullptr)
		std::cout << "empty list";
	std::cout << std::endl;
}

//prints nodes in list starting from back
template <typename T>
void DList<T>::reversePrint() const
{
	Node* currentNode = back_; //select back_ node to being printing list

	//print one node and  move to next until front_ node is reached
	while (currentNode)
	{
		std::cout << currentNode->data_ << " "; 
		currentNode = currentNode->prev_; 
	}
	
	//print if list is empty (front_ node doesn't exist)
	if (front_ == nullptr)
		std::cout << "empty list";
	std::cout << std::endl;
}


template <typename T>
DList<T>::~DList()
{
	while (front_ != nullptr)
	{
		pop_back();
	}
}