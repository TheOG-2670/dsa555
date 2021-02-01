#include "disjointset.h"

DisjointSet::DisjointSet(int max)
{
    if (max > 0)
    {
        maxValue = max;
    }

    //allocates memory for disjoint set array and sets first pointer to null (for initial while loop check)
    disjointSetArray = new DList<int>::Node[max];
}

//accepts an int
//creates linked lists with 'object' as the first node and representative of the list
bool DisjointSet::makeSet(int object)
{


    //check if incoming object is within range
    if ( (0 <= object && object < maxValue) && (disjointSetArray[object].isEmpty()) )
    {
        disjointSetArray[object].data_ = object;

        //add the object to the back of the current (empty) linked list
        DList<int> list;
        list.push_back(object);

        //return true upon successful addition of the node
        return true;
    }
    else
    {
        return false;
    }


}


//accepts an int
//finds the representative of a linked list using the provided member of that list
int DisjointSet::findSet(int object) const
{
    
    //check if incoming object is within range
    if (object >= 0 && object < maxValue)
    {
        DList<int>::Node *rep = &disjointSetArray[object];
        DList<int>::Node *rep_copy = rep;
        while (rep_copy)
        {
            rep = rep_copy;
            rep_copy = rep_copy->prev_;
        }
           
        return rep->data_;

    }
    else
    {
        return -1;
    }

}

//accepts two ints
/*unionizes two linked lists using their representatives, given that the representatives are within the valid range of acceptable values and
neither representative appears as a member in the other's list*/
bool DisjointSet::unionSets(int rep1, int rep2)
{

    //check if the reps are within the valid value range and that their values are not -1 (indicating they are empty)
    if ((rep1 >= 0 && rep1 < maxValue) 
        && (rep2 >= 0 && rep2 < maxValue) 
        && !disjointSetArray[rep1].isEmpty() && (!disjointSetArray[rep2].isEmpty()))
    {
        //node-linking for single-node lists
        if (disjointSetArray[rep1].next_ == nullptr && disjointSetArray[rep1].prev_ == nullptr
            && disjointSetArray[rep2].next_ == nullptr && disjointSetArray[rep2].prev_ == nullptr)
        {
            disjointSetArray[rep1].next_ = &disjointSetArray[rep2];
            disjointSetArray[rep2].prev_ = &disjointSetArray[rep1];
        }
        else
        {
            DList<int>::Node* rep1_ = &disjointSetArray[rep1];
            DList<int>::Node* rep1_copy = rep1_;
            //find last node in rep1 list
            while (rep1_)
            {
                //check if rep2 is in rep1's list
                if (rep1_->data_ == rep2)
                {
                    //if rep2 is in rep1's list, return true and don't combine the lists
                    return true;
                }

                rep1_copy = rep1_;
                rep1_ = rep1_->next_;
            }


            //find first node in rep2's list
            int rep2_ = findSet(rep2);
           
            //if rep1 and rep2 are in different lists, unionize their lists (link rep1's last node to rep2's first node)
            disjointSetArray[rep1_copy->data_].next_ = &disjointSetArray[rep2_];
            disjointSetArray[rep2_].prev_ = rep1_copy;
        }

        return true;
	}
	else
	{
		return false;
	}
}

DisjointSet::~DisjointSet() 
{

    if (this->disjointSetArray != nullptr)
    {
        delete[] disjointSetArray;
    }
}

//copy constructor
DisjointSet::DisjointSet(const DisjointSet& other) : disjointSetArray{nullptr}
{
    if (this != &other)
        *this = other;
}

//copy-assignment operator
DisjointSet& DisjointSet::operator=(const DisjointSet& other) 
{

    
    //check for self-assignment (same addresses)
    if (this != &other)
    {

        this->maxValue = other.maxValue;
		this->currentSize = other.currentSize;
        this->disjointSetArray = new DList<int>::Node [this->maxValue];

        for (int i = 0; i < other.maxValue; i++)
        {
			this->disjointSetArray[i].data_ = -1;
            this->makeSet(other.disjointSetArray[i].data_);
            
        }

        for (int i = 0; i < 100; i += 2) {
            this->unionSets(i, i + 1);
        }

        for (int i = 0; i < 50; i += 2) {
            this->unionSets(i * 2, (i + 1) * 2);
        }

        for (int i = 0, j = 99; i < 48; i += 4, j -= 4) {
            this->unionSets(i, j);
        }
        
    }

    return *this;
}

//move constructor
DisjointSet::DisjointSet(DisjointSet&& other) 
{
    //check for self-assignment
    if (this != &other)
    {
        //call move assignment operator
        *this = std::move(other);
    }
}

//move-assignment operator
DisjointSet& DisjointSet::operator=(DisjointSet&& other) 
{
    if (this != &other)
    {
        this->maxValue = other.maxValue;
        this->disjointSetArray = other.disjointSetArray;

       
        other.disjointSetArray = nullptr;
        other.maxValue = 0;
    }

    return *this;
}