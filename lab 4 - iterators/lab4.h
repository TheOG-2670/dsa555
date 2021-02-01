#include <iostream>

template <typename T>
class DList{
protected:
	struct Node{
		T data_;
		Node* next_;
		Node* prev_;
		Node(const T& data=T{},Node* next=nullptr, Node* prev=nullptr){
			data_=data;
			next_=next;
			prev_=prev;
		}
	};
	Node* front_;
	Node* back_;
public:
	DList(){
		front_=nullptr;
		back_=nullptr;
	}
	void push_front(const T& data);
	~DList();

	class const_iterator
	{
		//allows const_iterator class to access DList private data members
		friend class DList<T>;
	protected:
		//protected members allow iterator class to access them through inheritance with const_iterator
		Node* currentNode;
		const DList<T>* currentList;
		//special const_iterator constructor to be used by iterator constructor (parameter passing from derived to base class)
		const_iterator(Node* aNode, const DList<T>* aList) //const DList<T>* aList -> don't want to modify aList, just access its nodes
		{
			currentNode = aNode;
			currentList = aList;
		}
	public:
		const_iterator()
		{
			currentNode = nullptr;
			currentList = nullptr;
		}

		const_iterator operator++() //prefix (++x)
		{
			currentNode = currentNode->next_;
			return *this;
		}

		const_iterator operator++(int) //postfix (x++)
		{
			const_iterator current = *this;
			currentNode = currentNode->next_;
			return current;
		} 


		const_iterator operator--() //prefix (--x)
		{
			
			if (currentNode != nullptr)
				currentNode = currentNode->prev_;
			else
				currentNode = currentList->back_;
			return *this;
		}


		const_iterator operator--(int) //postfix (x--)
		{
			const_iterator current = *this;
			if(currentNode == nullptr)
				currentNode = this->currentList->back_;
			else
				currentNode = currentNode->prev_;
			
			return current;
		}
		
		bool operator==(const_iterator rhs)
		{
			return this->currentNode == rhs.currentNode;
		}

		bool operator!=(const_iterator rhs)
		{
			return this->currentNode != rhs.currentNode;
		}

		const T& operator*() const
		{
			return currentNode->data_;
		}
	};
	class iterator:public const_iterator
	{
		friend class DList;
		//overloaded constructor for iterator class to pass node and list pointers to const_iterator overloaded constructor
		iterator(Node* aNode, const DList<T>* aList) : const_iterator(aNode, aList) {}

		public:
			iterator() :const_iterator() {};

		iterator operator++() //prefix (++x)
		{
			this->currentNode = this->currentNode->next_;
			return *this;
		}

		iterator operator++(int) //postfix (x++)
		{
			iterator current = *this;
			this->currentNode = this->currentNode->next_;
			return current;
		}

		iterator operator--() //prefix (--x)
		{
			if (this->currentNode != nullptr)
			{
				this->currentNode = this->currentNode->prev_;
			}
			else
			{
				this->currentNode = this->currentList->back_;
			}
			return *this;
		}
		
		iterator operator--(int) //postfix (x--)
		{
			iterator current = *this;
			const_iterator::currentNode = const_iterator::currentNode->prev_;
			return current;
		}


		T& operator*()
		{
			return const_iterator::currentNode->data_;
		}


		const T& operator*()const
		{
			return const_iterator::operator*();
		}

	};

	const_iterator cbegin() const
	{
		//pass to protected overloaded constructor
		return const_iterator(front_, this); //this -> current list for which the iterator will be used
	}

	iterator begin()
	{
		return iterator(this->front_, this);
	}

	const_iterator cend() const
	{
		return const_iterator(nullptr, this); //points to empty position after last node (back_->next_ = nullptr)
	}

	iterator end()
	{
		return iterator(nullptr, this);
	}
};


template <typename T>
void DList<T>::push_front(const T& data)
{
	Node* nn = new Node(data, front_);

	if (front_ != nullptr)
	{
		front_->prev_ = nn;
	}
	else
	{

		back_ = nn;
	}

	front_ = nn;
}


template <typename T>
DList<T>::~DList()
{
	Node* removed = front_;
	Node* removed_next;
	while(removed)
	{
		removed_next=removed->next_;
		delete removed;
		removed = removed_next;
	}
}

template <typename T>
class Sentinel{
	struct Node{
		T data_;
		Node* next_;
		Node* prev_;
		Node(const T& data=T{},Node* next=nullptr, Node* prev=nullptr){
			data_=data;
			next_=next;
			prev_=prev;
		}
	};
	Node* front_;
	Node* back_;
public:
	Sentinel(){
		front_=new Node();
		back_=new Node();
		front_->next_=back_;
		back_->prev_=front_;
	}
	void push_front(const T& data);
	~Sentinel();

	class const_iterator{
		friend Sentinel<T>;

	protected:
		Node *currentNode;
		const Sentinel<T> *currentList;
		
		const_iterator(Node *aNode, const Sentinel<T> *aList)
		{
			this->currentList = aList;
			this->currentNode = aNode;
		}
	public:
		const_iterator()
		{
			this->currentList = nullptr;
			this->currentNode = nullptr;
		}

		const_iterator operator++() //prefix (++x)
		{
			currentNode = currentNode->next_;
			return *this;
		}

		const_iterator operator++(int) //postfix (x++)
		{
			const_iterator ci = *this;
			currentNode = currentNode->next_;
			
			return ci;
		}

		const_iterator operator--() //prefix (--x)
		{
			if (this->currentNode != nullptr)
				this->currentNode = this->currentNode->prev_;
			else
				this->currentNode = this->currentList->back_->prev_;
			return *this;
		}

		const_iterator operator--(int) //postfix (x--)
		{
			const_iterator ci = *this;
			if(this->currentNode == nullptr)
				this->currentNode = this->currentList->back_->prev_;
			else
				this->currentNode = this->currentNode->prev_;
			
			return ci;
		}


		bool operator==(const_iterator rhs)
		{
			return this->currentNode == rhs.currentNode;
		}


		bool operator!=(const_iterator rhs)
		{
			return this->currentNode != rhs.currentNode;
		}


		const T& operator*()const
		{
			return this->currentNode->data_;
		}

	};
	class iterator:public const_iterator{
	public:
		iterator(Node *aNode, Sentinel<T> *aList) : const_iterator(aNode, aList){}
		iterator();

		iterator operator++()
		{
			this->currentNode = this->currentNode->next_;
			return *this;
		}

		iterator operator++(int)
		{
			iterator current = *this;
			this->currentNode = this->currentNode->next_;
			return current;
		}

		iterator operator--()
		{
			if (this->currentNode != nullptr)
			{
				this->currentNode = this->currentNode->prev_;
			}
			else
			{
				this->currentNode = this->currentList->back_->prev_;
			}
			return *this;
		}

		iterator operator--(int)
		{
			iterator current = *this;
			const_iterator::currentNode = const_iterator::currentNode->prev_;
			return current;
		}


		T& operator*()
		{
			return const_iterator::currentNode->data_;
		}


		const T& operator*()const
		{
			return const_iterator::operator*();
		}

	};

	const_iterator cbegin() const
	{
		return const_iterator(front_->next_, this);
	}

	iterator begin()
	{
		return iterator(front_->next_, this);
	}

	const_iterator cend() const
	{
		return const_iterator(back_, this);
	}

	iterator end()
	{
		return iterator(back_, this);
	}

};


template <typename T>
void Sentinel<T>::push_front(const T& data)
{
	Node* newNode = new Node(data, front_->next_, front_);

	front_->next_ = newNode;
	newNode->next_->prev_ = newNode;
}


template <typename T>
Sentinel<T>::~Sentinel()
{
	Node* removed = front_;
	Node* removed_next;
	while(removed)
	{
		removed_next=removed->next_;
		delete removed;
		removed = removed_next;
	}
}