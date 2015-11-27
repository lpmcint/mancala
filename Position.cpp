/*
Name: Lauren McIntyre
Class: cpsc212
Assignment: 3
Date: April 19, 2015 */

#include "Position.h"
#include <iostream>

using namespace std;

//redefining constructed and destructed starting with 0
int Position::constructed=0;
int Position::destructed=0;

//constructor if given initial values
Position::Position(int array[5]) {

	for(int i=0; i<5; i++) {
		A[i]=array[i];
	}

	A[5]=0;
	parent=nullptr;
	move=0;
	constructed++;
}

//default constructor 
Position::Position() {
	for(int i = 0; i < 5; i++) {
		A[i]=0;
	}
	move=0;
	parent = nullptr;
	constructed++;
}

//destructor
Position::~Position() {

	destructed++;
}

//returns true if every value in A is 0
bool Position::isDone() {
	if (A[0]==0 && A[1]==0 && A[2]==0 && A[3]==0 && A[4]==0) {
		return true;
	}
	else return false;
}

//returns pointer to new position
Position * Position::afterMove(int hole) {
	//redefine index
	int i = hole-1;
	
	//if given hole is zero, retun nullptr
	if(A[i]==0) {
		return nullptr;
	}

	//create a new position
	Position *child = new Position;

	//fill with current marbles
	for(int i = 0; i < 5; i++) {
		child->A[i] = A[i];
	}

	//get the number of marbles in desired hole
	int count = child->A[i];

	//replace with 0
	child->A[i]=0;

	//while there are still marbles
	while(count > 0) {
	//if at last viable position reset to 0
		if (i==4) {
			i=0;
			count--;
		}
		else {
			i++;
		}
	//recheck to assure count>0 
		if (count > 0) {
			child->A[i] = child->A[i]+1;
			count--;
		}
	}

	//set new Positions move and parent values
	child->move = hole+1;
	child->parent = this;

	//return new Position
	return child;
}

//test for equality, if same marbles in positions
bool Position::operator==(const Position & rhs) const {
	for(int i = 0; i < 5; i++) {
		if (A[i]!=rhs.A[i]) {
			return false;
		}
	}
	return true;
}

//out operator for printing Positions
ostream & operator<< (ostream &out, const Position &pos) {
	out << "[";
	for(int i=0; i<4;i++) {
		cout << pos.A[i] << ".";
	}
	out << pos.A[4] <<"]"<<endl;

	return out;
}


