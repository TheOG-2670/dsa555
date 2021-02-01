#define _CRT_SECURE_NO_WARNINGS
/*************************************************************/
/*                                                           */
/*    starter file for a2                                    */
/*    													     */
/*                                                           */
/*************************************************************/

#include <string>
#include <cstring>
#include <utility>
#include <functional>
#include "mylist.h"
using namespace std;

template <class TYPE>
class Table {
public:
	Table() {}
	virtual void update(const string& key, const TYPE& value) = 0;
	virtual bool remove(const string& key) = 0;
	virtual bool find(const string& key, TYPE& value) = 0;
	virtual int numRecords() const = 0;
	virtual bool isEmpty() const = 0;
	virtual ~Table() {}
};

template <class TYPE>
class SimpleTable :public Table<TYPE> {

	struct Record {
		TYPE data_;
		string key_;
		Record(const string& key, const TYPE& data) {
			key_ = key;
			data_ = data;
		}

	};

	Record** records_;   //the table
	int capacity_;       //capacity of the array

	void grow() {
		Record** tmp = new Record * [capacity_ + 10];
		for (int i = 0; i < capacity_; i++) {
			tmp[i] = records_[i];
		}
		for (int i = capacity_; i < capacity_ + 10; i++) {
			tmp[i] = nullptr;
		}
		delete[] records_;
		records_ = tmp;
		capacity_ += 10;
	}
public:
	SimpleTable(int capacity);
	SimpleTable(const SimpleTable& other);
	SimpleTable(SimpleTable&& other);
	virtual void update(const string& key, const TYPE& value);
	virtual bool remove(const string& key);
	virtual bool find(const string& key, TYPE& value);
	virtual const SimpleTable& operator=(const SimpleTable& other);
	virtual const SimpleTable& operator=(SimpleTable&& other);
	virtual ~SimpleTable();
	virtual bool isEmpty() const { return numRecords() == 0; }
	virtual int numRecords() const;
};

template <class TYPE>
int SimpleTable<TYPE>::numRecords() const {
	int rc = 0;
	for (int i = 0; records_[i] != nullptr; i++) {
		rc++;
	}
	return rc;
}



template <class TYPE>
SimpleTable<TYPE>::SimpleTable(int capacity) : Table<TYPE>() {
	records_ = new Record * [capacity];
	capacity_ = capacity;
	for (int i = 0; i < capacity_; i++) {
		records_[i] = nullptr;
	}
}

template <class TYPE>
SimpleTable<TYPE>::SimpleTable(const SimpleTable<TYPE>& other) {
	records_ = new Record * [other.capacity_];
	capacity_ = other.capacity_;
	for (int i = 0; i < other.numRecords(); i++) {
		update(other.records_[i]->key_, other.records_[i]->data_);
	}
}
template <class TYPE>
SimpleTable<TYPE>::SimpleTable(SimpleTable<TYPE>&& other) {
	capacity_ = other.capacity_;
	records_ = other.records_;
	other.records_ = nullptr;
	other.capacity_ = 0;
}

template <class TYPE>
void SimpleTable<TYPE>::update(const string& key, const TYPE& value) {
	int idx = -1;
	int size = numRecords();
	for (int i = 0; i < size; i++) {
		if (records_[i]->key_ == key) {
			idx = i;
		}
	}
	if (idx == -1) {
		if (size == capacity_) {
			grow();
		}
		records_[size++] = new Record(key, value);
		for (int i = 0; i < size - 1; i++) {
			for (int j = 0; j < size - 1 - i; j++) {
				if (records_[j]->key_ > records_[j + 1]->key_) {
					Record* tmp = records_[j];
					records_[j] = records_[j + 1];
					records_[j + 1] = tmp;
				}
			}
		}
	}
	else {
		records_[idx]->data_ = value;
	}

}

template <class TYPE>
bool SimpleTable<TYPE>::remove(const string& key) {
	int idx = -1;
	for (int i = 0; i < numRecords(); i++) {
		if (records_[i]->key_ == key) {
			idx = i;
		}
	}
	if (idx != -1) {
		delete records_[idx];
		int size = numRecords();
		for (int i = idx; i < size - 1; i++) {
			records_[i] = records_[i + 1];
		}
		records_[size - 1] = nullptr;
		return true;
	}
	else {
		return false;
	}
}

template <class TYPE>
bool SimpleTable<TYPE>::find(const string& key, TYPE& value) {
	int idx = -1;
	for (int i = 0; i < numRecords(); i++) {
		if (records_[i]->key_ == key) {
			idx = i;
		}
	}
	if (idx == -1)
		return false;
	else {
		value = records_[idx]->data_;
		return true;
	}
}

template <class TYPE>
const SimpleTable<TYPE>& SimpleTable<TYPE>::operator=(const SimpleTable<TYPE>& other) {
	if (this != &other) {
		if (records_) {
			int sz = numRecords();
			for (int i = 0; i < sz; i++) {
				remove(records_[0]->key_);
			}
			delete[] records_;
		}
		records_ = new Record * [other.capacity_];
		capacity_ = other.capacity_;
		int size = other.numRecords();
		for (int i = 0; i < size; i++) {
			update(other.records_[i]->key_, other.records_[i]->data_);
		}

	}
	return *this;
}
template <class TYPE>
const SimpleTable<TYPE>& SimpleTable<TYPE>::operator=(SimpleTable<TYPE>&& other) {
	swap(records_, other.records_);
	swap(capacity_, other.capacity_);
	return *this;
}
template <class TYPE>
SimpleTable<TYPE>::~SimpleTable() {
	if (records_) {
		int sz = numRecords();
		for (int i = 0; i < sz; i++) {
			remove(records_[0]->key_);
		}
		delete[] records_;
	}
}

//ChainingTable class inherits from Table
template <class TYPE>
class ChainingTable :public Table<TYPE> {
	template <typename TT>
	friend class DList; //allows access to DList's private members (for chaining collision resolution)

	hash<string> hasher; //function object to hash keys
	DList<TYPE>* table; //for chaining
	int capacity_; //total size of table
	double maxLoadFactor_; //threshold for reconfiguration to use chaining
	int filled = 0; //current number of records in table
public:
	ChainingTable(int maxExpected, double maxLoadFactor);
	ChainingTable(const ChainingTable& other);
	ChainingTable(ChainingTable&& other);
	virtual void update(const string& key, const TYPE& value);
	virtual void grow();
	virtual bool remove(const string& key);
	virtual bool find(const string& key, TYPE& value);
	virtual const ChainingTable& operator=(const ChainingTable& other);
	virtual const ChainingTable& operator=(ChainingTable&& other);
	int capacity() const {
		return capacity_;
	}
	virtual ~ChainingTable();
	
	virtual bool isEmpty() const { return filled==0; } //check if the table is empty
	virtual int numRecords() const { return filled; } //get the current number of records in the table

};

/*Accepts two integers:
integer 1: initial capacity of the table
integer 2: max load factor threshold before the table is reconfigured to use double the capacity with linked lists 
for chaining collision resolution

This constructor calls default constructor of parent class and then initializes its data members
*/
template <class TYPE>
ChainingTable<TYPE>::ChainingTable(int maxExpected, double maxLoadFactor) : Table<TYPE>()
{
	capacity_ = maxExpected;
	maxLoadFactor_ = maxLoadFactor;
	table = new DList<TYPE>[capacity_];
}

//copy constructor
template <class TYPE>
ChainingTable<TYPE>::ChainingTable(const ChainingTable<TYPE>& other) 
{
	this->capacity_ = other.capacity_;
	this->filled = other.filled;
	this->maxLoadFactor_ = other.maxLoadFactor_;
	this->table = new DList<TYPE> [this->capacity_];

	//deep-copy all elements to new table by re-hashing their hash values, finding their corresponding indices and copying linked lists
	for (int i = 0; i < other.capacity_; i++)
	{
		if (other.table[i].front_ != nullptr)
		{

			typename DList<TYPE>::Node* curr = other.table[i].front_;

			size_t hash1 = hasher(curr->key_);
			size_t idx1 = hash1 % capacity_;
			this->table[idx1].count = other.table[i].count;

			while (curr != nullptr)
			{
				size_t hash = hasher(curr->key_);
				size_t idx = hash % capacity_;
				this->table[idx].push_front(curr->data_, curr->key_);
				curr = curr->next_;
			}
		}

	}
}

//move constructor
template <class TYPE>
ChainingTable<TYPE>::ChainingTable(ChainingTable<TYPE>&& other) 
{
	this->capacity_ = other.capacity_;
	this->filled = other.filled;
	this->maxLoadFactor_ = other.maxLoadFactor_;
	this->table = other.table;

	other.capacity_ = 0;
	other.filled = 0;
	other.maxLoadFactor_ = 0;
	other.table = nullptr;

}


/*
Accepts no parameters.
This function doubles the table's current capacity of slots
*/
template <class TYPE>
void ChainingTable<TYPE>::grow() 
{
	//creates new table with double capacity of current table
	DList<TYPE>* newTable = new DList<TYPE>[capacity_ * 2];
	int oldCapacity_ = capacity_;
	capacity_ = capacity_ * 2;
	//

	//deep-copy all elements to new table by re-hashing their hash values, finding their corresponding indices and copying linked lists
	for (int i = 0; i < oldCapacity_; i++)
	{
		if (table[i].front_ != nullptr)
		{

			typename DList<TYPE>::Node* curr = table[i].front_; 

			size_t hash1 = hasher(curr->key_);
			size_t idx1 = hash1 % capacity_; 
			newTable[idx1].count = table[i].count; 

			while (curr != nullptr) 
			{
				size_t hash = hasher(curr->key_); 
				size_t idx = hash % capacity_; 
				newTable[idx].push_front(curr->data_, curr->key_); 
				curr = curr->next_; 
			}
		}

	}
	//

	table = newTable; 
}


/*
Accepts a string reference and a generic data type reference:
string reference: key of the record
generic data type reference: value of the record

This function will find and update the value of an existing record, or add a new record
*/
template <class TYPE>
void ChainingTable<TYPE>::update(const string& key, const TYPE& value) 
{
	
	//hash key and find its index
	size_t hash = hasher(key);
	size_t idx = hash % capacity_;
	TYPE val = value;

	bool found = find(key, val); //search for record

	//new record insertion
	if (!found) 
	{
		//grow table capacity
		if (((double)filled / (double)capacity_) >= maxLoadFactor_) 
		{
			grow();
			idx = hash % capacity_;
		}
		
		table[idx].push_front(value, key);
		table[idx].count++;
		filled++;
	}
	//update existing record
	else 
	{
		typename DList<TYPE>::Node* curr = table[idx].front_;
		while (curr != nullptr) 
		{
			if (curr->key_ == key) 
			{
				curr->data_ = value;
				break;
			}
			else
				curr = curr->next_;
		}
	}

}

/*
Accepts a string reference:
string reference: key of the record

This function will find and remove an existing record, if the record exists
*/
template <class TYPE>
bool ChainingTable<TYPE>::remove(const string& key) 
{

	TYPE val;
	bool res = find(key, val); //searches for record with given key

	//if record is found
	if (res) 
	{
		//hash key and find its index position
		size_t hash = hasher(key); 
		size_t idx = hash % capacity_; 
		
		typename DList<TYPE>::Node* curr = table[idx].front_; 
		
		//loop through linked list
		while (curr != nullptr) 
		{
			//current node in list is the key
			if (curr->key_ == key) 
			{

				typename DList<TYPE>::Node* rm = curr; 
				
				//removal  of single-node linked list
				if (rm->prev_ == nullptr && rm->next_ == nullptr) 
				{
					table[idx].front_ = nullptr;
					table[idx].back_ = nullptr;
				}

				//removal of multi-node linked list
				else
				{
					//remove front node of linked list
					if (rm->prev_ == nullptr)
					{
						table[idx].front_ = rm->next_;
						rm->next_->prev_ = nullptr;
					}
					else
					{
						//remove back node
						if (rm->next_ == nullptr)
						{
							table[idx].back_ = rm->prev_;
							rm->prev_->next_ = nullptr;
						}
						//remove node inside linked list
						else if (rm->next_ != nullptr && rm->prev_ != nullptr)
						{
							rm->prev_->next_ = rm->next_;
							rm->next_->prev_ = rm->prev_;
						}
					}
				}

				delete rm; 
				return true;
			}

			//move to next node in list
			curr = curr->next_;
		}
	}

	return false;
}

/*
Accepts a string reference and a generic data type reference:
string reference: key of the record
generic data type reference: value of the record

This function will search for a record, given its key and value
*/
template <class TYPE>
bool ChainingTable<TYPE>::find(const string& key, TYPE& value) 
{
	//hash key and find index in table
	size_t hash = hasher(key);
	size_t idx = hash % capacity_;

	typename DList<TYPE>::Node* curr = table[idx].front_;

	//search for node in linked list matching key and value
	while (curr != nullptr) 
	{
		if (curr->key_ == key) 
		{
			value = curr->data_;
			return true;
		}
		else
		{
			curr = curr->next_;
		}
			
	}
	
		return false;
}

//copy-assignment operator
template <class TYPE>
const ChainingTable<TYPE>& ChainingTable<TYPE>::operator=(const ChainingTable<TYPE>& other) 
{
	if (this != &other)
	{
		if (this->table)
			delete[] table;


		capacity_ = other.capacity_; 
		maxLoadFactor_ = other.maxLoadFactor_;
		filled = other.filled;
		
		table = new DList<TYPE>[capacity_]; 
		
		for (int i = 0; i < capacity_; i++) 
		{
			if (other.table[i].front_ != nullptr) 
			{ 
				typename DList<TYPE>::Node* curr = other.table[i].front_; 

				size_t hash1 = hasher(curr->key_); 
				size_t idx1 = hash1 % capacity_; 
				table[idx1].count = other.table[i].count; 

				while (curr != nullptr) 
				{ 

					size_t hash = hasher(curr->key_); 
					size_t idx = hash % capacity_; 
					table[idx].push_front(curr->data_, curr->key_); 
					curr = curr->next_; 
				}
			}
		}
	}
	return *this;
}

//move-assignment operator
template <class TYPE>
const ChainingTable<TYPE>& ChainingTable<TYPE>::operator=(ChainingTable<TYPE>&& other) 
{
	swap(this->capacity_, other.capacity_);
	swap(this->filled, other.filled);
	swap(this->maxLoadFactor_, other.maxLoadFactor_);
	swap(this->table, other.table);

	return *this;
}

//destructor
template <class TYPE>
ChainingTable<TYPE>::~ChainingTable() 
{
	if (this->table != nullptr)
	{	
		delete[] table;
		table = nullptr;
	}
}


