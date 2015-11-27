/*
Name: Lauren McIntyre
Assignment: 4
Class: Cpsc 2121
Date: 4/15/2014*/

#ifndef POSITION_H
#define POSITION_H

#include <string>

using namespace std;

class Position {
	public:
		//Constructors and destructor
		Position();
		Position(int array[5]);
		~Position();
		//returns true if a position is [0.0.0.0.0]
		bool isDone();
		//returns new position after given move
		Position *afterMove(int hole);
		//compares if two positions are equal
		bool operator==(const Position & rhs) const;
		//out stream overloaded operator
		friend ostream & operator<< (ostream &out, const Position &pos);
		//pointer to parent Position
		Position *parent;
		//holds marbles in given positions
		int A[6];
		//static values to count how many Positions construted and 
		//destructed
		static int constructed;
		static int destructed;
		//records move taken to get current Position from parent
		int move;

};



#endif
