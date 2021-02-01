#include <iostream>
#include <cstring>
#include <string>
using namespace std;
template <typename T>
class DList {
	template <typename TT>
	friend class ChainingTable;


	struct Node {
		T data_;
		string key_;
		Node* next_;
		Node* prev_;
		Node(const T& data = T{}, const string& key = {}, Node * next = nullptr, Node * prev = nullptr) {
			data_ = data;
			key_ = key;
			next_ = next;
			prev_ = prev;
		}
	};
	int count = 0;
	Node* front_;
	Node* back_;
public:
	DList() {
		front_ = nullptr;
		back_ = nullptr;
	}
	void push_front(const T& data, const string& key);
	~DList();

	class const_iterator {
		friend class DList;
	protected:
		Node* curr_;
		const DList* theList_;

		const_iterator(const DList* theList, Node* n) {
			curr_ = n;
			theList_ = theList;
		}

	public:
		const_iterator() {
			curr_ = nullptr;
			theList_ = nullptr;
		}

		const_iterator operator++() {
			if (curr_ != nullptr) {
				curr_ = curr_->next_;
			}
			else {
				curr_ = theList_->front_;
			}
			return *this;
		}

		const_iterator operator++(int) {
			const_iterator rc = *this;
			if (curr_ != nullptr) {
				curr_ = curr_->next_;
			}
			else {
				curr_ = theList_->front_;
			}
			return rc;
		}

		const_iterator operator--() {
			if (curr_ != nullptr) {
				curr_ = curr_->prev_;
			}
			else {
				curr_ = theList_->back_;
			}
			return *this;
		}

		const_iterator operator--(int) {
			const_iterator rc = *this;
			if (curr_ != nullptr) {
				curr_ = curr_->prev_;
			}
			else {
				curr_ = theList_->back_;
			}
			return rc;
		}

		bool operator==(const_iterator rhs) {
			return curr_ == rhs.curr_;
		}

		bool operator!=(const_iterator rhs) {
			return curr_ != rhs.curr_;
		}

		const T& operator*()const {
			return curr_->data_;
		}
	};
	class iterator :public const_iterator {
		friend class DList;
		iterator(DList* theList_, Node* n) :
			const_iterator(theList_, n) {}
	public:
		iterator() :const_iterator() {
		};

		iterator operator++() {
			if (this->curr_ != nullptr) {
				this->curr_ = this->curr_->next_;
			}
			else {
				this->curr_ = this->theList_->front_;
			}
			return *this;
		}

		iterator operator++(int) {
			iterator rc = *this;
			if (this->curr_ != nullptr) {
				this->curr_ = this->curr_->next_;
			}
			else {
				this->curr_ = this->theList_->front_;
			}
			return rc;
		}

		iterator operator--() {
			if (this->curr_ != nullptr) {
				this->curr_ = this->curr_->prev_;
			}
			else {
				this->curr_ = this->theList_->back_;
			}
			return *this;
		}

		iterator operator--(int) {
			iterator rc = *this;
			if (this->curr_ != nullptr) {
				this->curr_ = this->curr_->prev_;
			}
			else {
				this->curr_ = this->theList_->back_;
			}
			return rc;
		}

		T& operator*() {
			return (this->curr_)->data_;
		}

		const T& operator*()const {
			return this->curr_->data_;
		}
	};

	const_iterator cbegin() const {
		return const_iterator(this, front_);
	}

	iterator begin() {
		return iterator(this, front_);
	}

	const_iterator cend() const {
		return const_iterator(this, nullptr);
	}

	iterator end() {
		return iterator(this, nullptr);
	}
};


template <typename T>
void DList<T>::push_front(const T& data, const string& key) {
	Node* nn = new Node(data,key, front_);
	if (front_ != nullptr) {
		front_->prev_ = nn;
	}
	else {
		back_ = nn;
	}
	front_ = nn;
}


template <typename T>
DList<T>::~DList() {
	if (front_ != nullptr) {
		Node* rm = front_;
		while (rm) {
			front_ = front_->next_;
			delete rm;
			rm = front_;
		}

	}
}
template <typename T>
class Sentinel {
	struct Node {
		T data_;
		Node* next_;
		Node* prev_;
		Node(const T& data = T{}, Node* next = nullptr, Node* prev = nullptr) {
			data_ = data;
			next_ = next;
			prev_ = prev;
		}
	};
	Node* front_;
	Node* back_;
public:
	Sentinel() {
		front_ = new Node();
		back_ = new Node();
		front_->next_ = back_;
		back_->prev_ = front_;
	}
	void push_front(const T& data);
	~Sentinel();

	class const_iterator {
		friend class Sentinel;
	protected:
		Node* curr_;
		const_iterator(Node* curr) {
			curr_ = curr;
		}

	public:
		const_iterator() {
			curr_ = nullptr;
		}

		const_iterator operator++() {
			curr_ = curr_->next_;
			return *this;
		}

		const_iterator operator++(int) {
			const_iterator rc = *this;
			curr_ = curr_->next_;
			return rc;
		}

		const_iterator operator--() {
			curr_ = curr_->prev_;
			return *this;
		}

		const_iterator operator--(int) {
			const_iterator rc = *this;
			curr_ = curr_->prev_;
			return rc;
		}

		bool operator==(const_iterator rhs) {
			return curr_ == rhs.curr_;
		}

		bool operator!=(const_iterator rhs) {
			return curr_ != rhs.curr_;
		}

		const T& operator*()const {
			return curr_->data_;
		}
	};

	class iterator :public const_iterator {
		friend Sentinel;
		iterator(Node* n) :
			const_iterator(n) {
		}

	public:

		iterator();

		iterator operator++() {
			this->curr_ = this->curr_->next_;
			return *this;
		}

		iterator operator++(int) {
			iterator rc = *this;
			this->curr_ = this->curr_->next_;
			return rc;
		}

		iterator operator--() {
			this->curr_ = this->curr_->prev_;
			return *this;
		}

		iterator operator--(int) {
			iterator rc = *this;
			this->curr_ = this->curr_->prev_;
			return rc;
		}

		T& operator*() {
			return this->curr_->data_;
		}

		const T& operator*()const {
			return this->curr_->data_;
		}
	};
	const_iterator cbegin() const {
		return const_iterator(front_->next_);
	}

	iterator begin() {
		return iterator(front_->next_);
	}

	const_iterator cend() const {
		return const_iterator(back_);
	}

	iterator end() {
		return iterator(back_);
	}
};


template <typename T>
void Sentinel<T>::push_front(const T& data) {
	Node* nn = new Node(data, front_->next_, front_);
	front_->next_ = nn;
	nn->next_->prev_ = nn;
}


template <typename T>
Sentinel<T>::~Sentinel() {
	if (front_ != nullptr) {
		Node* rm = front_;
		while (rm) {
			front_ = front_->next_;
			delete rm;
			rm = front_;
		}
		delete rm;
	}
}