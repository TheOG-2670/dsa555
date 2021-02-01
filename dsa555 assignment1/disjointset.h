#pragma once

#include "DoublyLinkedList.h"

class DisjointSet {
	
private:
	int maxValue = 0;
	int currentSize = 0;
	DList<int>::Node *disjointSetArray;
	

public:
	DisjointSet(int max);
	bool makeSet(int object);
	int findSet(int object) const;
	bool unionSets(int rep1, int rep2);
	~DisjointSet();
	DisjointSet(const DisjointSet& other);
	DisjointSet& operator=(const DisjointSet& other);
	DisjointSet(DisjointSet&& other);
	DisjointSet& operator=(DisjointSet&& other);

};