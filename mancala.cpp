/*
Name: Lauren McIntyre
Class: cpsc212
Assignment: 3
Date: April 19, 2015 */


#include "Position.h"
#include <iostream>

//stl for queue, stack, assert, unordered_set
#include <queue>
#include <stack>
#include <assert.h>
#include <unordered_set>

using namespace std;

//defining and implementing hashing function for unordered_set
//so that it will know how to hash Position class
namespace std {
template<> struct hash<Position> {
	size_t operator()(const Position &pos) const {
		//Hashing code from Hashing lab
		int prime = 313;
		unsigned long long int hasher = prime*pos.A[0] + pos.A[1];
		for(int i = 2; i<5; i++) {
			hasher = hasher*prime + pos.A[i];
		}
		//return value calculated
		return (hasher);
	}
};
}

int main(int argc, char* argv[]) {

	//define stuctures used from stl
	queue <Position*> Q;
	stack <Position*> S;
	stack <Position*> Print;
	unordered_set <Position> H;

	//variable to record number of possible positions
	int numMoves=0;

	//assert that at least 6 or 7 arguments given
	assert(argc == 6 || argc == 7);

	//fill int array with given arguments
	int arr[5];
	for(int i = 1; i < 6; i++) {
		arr[i-1] = atoi(argv[i]);
	}

	//Define starting Position and Position pointer
	Position test(arr);
	Position *hold = new Position;

	//push the first position into the queue and insert into the 
	//unordered set
	Q.push(&test);
	H.insert(test);

	//if no hash argument given, run without hashing
	if (argc == 6) {
		//while queue not empty
		while(!Q.empty()) {
			//set hold to remember value at front of queue
			hold = Q.front();
			if(hold->isDone()) {
				Q.push(Q.front());
				//if found desired Position break loop
				break;
			}
			//pop value off top of queue
			Q.pop();
			//increment number of moves
			numMoves++;
			//try all possible moves
			for(int i=1; i<6; i++) {
				//define new Position for each possible move
				Position *temp = hold->afterMove(i);
				//make sure new position isnt null
				if (temp != nullptr) {
					//set move
					temp->move = i;
					//set parent
					temp->parent=hold;
					//push into queue and stack to be deleted
					Q.push(temp);
					S.push(temp);
				}
			}
		}
	}
	//will run if hash is given
	else {
		//same as above
		while(!Q.empty()) {
			hold = Q.front();
			if(hold->isDone()) {
				Q.push(Q.front());
				break;
			}
			Q.pop();
			numMoves++;
			for(int i=1; i<6; i++) {
				Position *temp = hold->afterMove(i);
				if (temp != nullptr) {
					//Check to see if hash is unique, if it is
					//push onto stack and into unordered set
					if(H.count(*temp) < 1) {
						temp->move = i;
						Q.push(temp);
						H.insert(*temp);
					}
				//push onto stack to be deleted
				S.push(temp);
				}
			}
		}
	}

	//new position for iterating, let it equal front of queue
	//which will be [0.0.0.0.0]
	Position *temp =  new Position();
	temp = Q.front();

	//push first value into a Stack so that they print in 
	//reverse order from parent pointers
	Print.push(temp);

	//push parents onto stack 
	int i = 0;
	while(temp->parent !=nullptr) {
		i++;
		temp=temp->parent;
		Print.push(temp);
	}

	//reset temp to front
	temp = Q.front();
	//print mancala and startin position
	cout << "\nRunning: Mancala ";
	for(int i = 0; i < 5; i ++) {
		cout << arr[i] << " ";
	}

	//print more stuff
	cout << "\nPositions Found: " << numMoves << endl;
	cout << "NUMBER OF MOVES: " << i << "\n";
	cout << test << endl;

	//pop top of stack because I printed it above
	Print.pop();
	//while the stack is not empty, print move and Position
	while(!Print.empty()) {
		cout << "Move:" << Print.top()->move << " yields" << *Print.top();
		Print.pop();
	}

	//destruct values held in other stack
	while(!S.empty()) {
		S.top()->~Position();
		S.pop();
	}

	//destruct iterating Positions
	temp->~Position();
	hold->~Position();
	test.~Position();

	//print values for constructed and destructed
	cout << "Constructed " << Position::constructed << endl;
	cout << "Destructed " << Position::destructed << endl;


	return 0;
}
