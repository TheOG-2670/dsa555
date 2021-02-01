/************************************************************/
/*  Lab 3 tester                                            */
/*  To compile:                                             */
/*     g++ lab3tester.cpp -std=c++0x                        */
/*  To run:                                                 */
/*     ./a.out                                              */
/************************************************************/

#include "lab3.h"
#include <iostream>

int main(void){
	DList<int> regular;
	Sentinel<int> sentinel;

	std::cout << "testing regular doubly linked list" << std::endl;

	for(int i=0;i<3;i++){
		regular.push_front(i);
		regular.print();       //0
		                       //1 0
							   //2 1 0
	}
	regular.reversePrint(); //output:
							//0 1 2

	for(int i=3;i<6;i++){
		regular.push_back(i);
		regular.print(); 	//output:
							//2 1 0 3
							//2 1 0 3 4
							//2 1 0 3 4 5
	}
	
	regular.reversePrint(); //output:
							//5 4 3 0 1 2

	for(int i=0;i<7;i++){
		if(i%2==0){
			regular.pop_front();
		}
		else{
			regular.pop_back();
		}
		regular.print();	//output:
							//1 0 3 4 5
							//1 0 3 4
							//0 3 4
							//0 3
							//3
							//
							//empty list
	}
	regular.reversePrint();	//output:
							//empty list

	for(int i=0;i<3;i++){
		regular.push_back(i);
		regular.print();	//output:
							//0
							//0 1
							//0 1 2
	}
	regular.reversePrint();	//output:
							//2 1 0

	for(int i=3;i<6;i++){
		regular.push_front(i);
		regular.print();	//output:
							//3 0 1 2
							//4 3 0 1 2
							//5 4 3 0 1 2
	}
	regular.reversePrint();	//output:
							//2 1 0 3 4 5
	
	for(int i=0;i<7;i++){
		if(i%2){
			regular.pop_front();
		}
		else{
			regular.pop_back();
		}
		regular.print();	//output:
							//4 3 0 1 2
							//4 3 0 1
							//3 0 1
							//3 0
							//0
							//
							//empty list
	}
	regular.reversePrint();	//output:
							//empty list

	for(int i=0;i<3;i++){
		regular.push_front(i);
		regular.print();	//output:
							//0
							//1 0
							//2 1 0
	}	
	regular.reversePrint();	//output:
							//0 1 2

	std::cout << "testing sentinel list" << std::endl;

	for(int i=0;i<3;i++){
		sentinel.push_front(i);
		sentinel.print();
	}
	sentinel.reversePrint();
	for(int i=3;i<6;i++){
		sentinel.push_back(i);
		sentinel.print();
	}
	sentinel.reversePrint();

	for(int i=0;i<7;i++){
		if(i%2==0){
			sentinel.pop_front();
		}
		else{
			sentinel.pop_back();
		}
		sentinel.print();
	}
	sentinel.reversePrint();

	for(int i=0;i<3;i++){
		sentinel.push_back(i);
		sentinel.print();
	}
	sentinel.reversePrint();
	for(int i=3;i<6;i++){
		sentinel.push_front(i);
		sentinel.print();
	}
	sentinel.reversePrint();
	for(int i=0;i<7;i++){
		if(i%2){
			sentinel.pop_front();
		}
		else{
			sentinel.pop_back();
		}
		sentinel.print();
	}
	sentinel.reversePrint();
	for(int i=0;i<3;i++){
		sentinel.push_front(i);
		sentinel.print();
	}
	sentinel.reversePrint();
	return 0;
}
