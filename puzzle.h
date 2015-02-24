//Lab 5, Part 2		puzzle.h	2/21/15	Author: Kurt Davis

#ifndef PUZZLE_H
#define PUZZLE_H

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<typeinfo>
using namespace std;

template <typename T>
class Puzzle{
	public:
		Puzzle(string);			//constructor; requires valid filename
		void display();			//print current board to stdout
		void play();			//start taking user input and changing board

	private:
		int checkVert(int, int, int);	//checks column about specified location for passed value, returns true if value is not present
		int checkHori(int, int, int);	//checks row about specified location for passed value, returns true if value is not present
		int checkGrid(int, int, int);	//checks grid around specified location for passed value, returns true if value is not present
		int checkBoard();		//returns true if game is completed
		int getInput(int*, int*, int*);//receives input, checks if input is a correct possibility, places number

		vector<vector <T> > board;	//2D vector to hold board
};

//function definintions

//constructor
template <typename T>
Puzzle<T>::Puzzle(string filename){
	//initialize file pointer
	ifstream ifp(filename.c_str());
	
	string line;
	T type;
	//dummy variables for type detection
	char test0;
	int test1;

	int j = 0;

	//read input from valid file
	while(getline(ifp, line)){
		board.push_back(vector < T > ());
		for(int i = 0; i < 9; i++){
			//detect type of sudoku (char or int)
			if(typeid(type) == typeid(test1)){
				board[j].push_back(line[i] - '0');	//digit
			}else if(typeid(type) == typeid(test0)){
				board[j].push_back((char)line[i]);	//character
			}
		}
		j++;
	}
}

//print board
template <typename T>
void Puzzle<T>::display(){
	for(int i = 0; i < 9; i++){
		for(int j = 0; j < 9; j++){
			cout << board[i][j];
		}
		cout << endl;
	}
}

//templated, but only implemented for number sudoku
template <typename T>
void Puzzle<T>::play(){
	int complete = 0;
	
	int x, y, numIn, status;

	while(!complete){
		status = 0;	//variable to check if game is being exited	

		//check if game is finished
		if(checkBoard()){
			cout << "Puzzle completed!" << endl;
			display();
			return;
		}
		
		//show board and get input
		display();
		status = getInput(&x, &y, &numIn);
		
		//quit game if needed
		if(status == -1){
			cout << "Quitting..." << endl;			
			return;
		}
	}
	
	display();	//show finished board
	return;
}

//check if value is already present in row
template <typename T>
int Puzzle<T>::checkHori(int x, int y, int value){
	int valid = 1;
	
	for(int i = 0; i < 9; i++){
		if(board[x][i] == value){
			valid = 0;
		}
	}
	
	return valid;
}

//check if value if already present in column
template <typename T>
int Puzzle<T>::checkVert(int x, int y, int value){
	int valid = 1;
	
	for(int i = 0; i < 9; i++){
		if(board[i][y] == value){
			valid = 0;
		}
	}
	
	return valid;
}

//check if value is already present in mini-grid
template <typename T>
int Puzzle<T>::checkGrid(int x, int y, int value){
	int valid = 1;	

	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			//This line relies on the truncation of integer division to determine which mini-grid the position is in
			if(board[3*(x / 3) + i][3*(y / 3) + j] == value){
				valid = 0;
			}
		}
	}
	
	return valid;
}

//get user input, check if move is valid, place new number
template <typename T>
int Puzzle<T>::getInput(int *x, int *y, int *value){
	int valid = 0;
	int moveComplete = 0;

	cout << "Note: coordinate origin is in upper left." << endl;

		//get user input
		while(!valid){
			cout << "Enter the x position 0-8 (or -1 to exit):";
			cin >> (*x);
			
			if(((*x) > -2) && ((*x) < 9)){
				if((*x) == -1){
					return -1;
				}else{
					valid = 1;
				}
			}
		}

		valid = 0;
		while(!valid){
			cout << "Enter the y position 0-8:";
			cin >> (*y);
			
			if(((*y) > -2) && ((*y) < 9)){
				if((*y) == -1){
					return -1;
				}else{
					valid = 1;
				}
			}
		}

		valid = 0;
		while(!valid){
			cout << "Enter the value 1-9:";
			cin >> (*value);
			
			if(((*value) > 0) && ((*value) < 10)){
				if((*value) == -1){
					return -1;
				}else{
					valid = 1;
				}
			}
		}

		//check if move is possible, place if possible 
		/*
			This program does not currently allow the user to change already placed values. Only 0's on the board may be modified
		*/
		if(checkVert((*y), (*x), (*value))){
			if(checkHori((*y), (*x), (*value))){
				if(checkGrid((*y), (*x), (*value))){
					if(board[(*y)][(*x)] == 0){
						board[(*y)][(*x)] = (*value);
						moveComplete = 1;
					}else{
						cout << "Cannot place; position already occupied." << endl;
					}
				}else{
					cout << "Cannot place; value already present in mini-grid." << endl;
				}
			}else{
				cout << "Cannot place; value already present in column." << endl;
			}	
		}else{
			cout << "Cannot place; value already present in row." << endl;
		}

		return moveComplete;
	
}

//determine if game is complete
template <typename T>
int Puzzle<T>::checkBoard(){
	int complete = 1;
	int i, j, k, l, sum;

	//check all rows
	for(i = 0; i < 9; i++){
		//Every row should only have one instance of each number, so there is only one
		//correct sum for all numbers in a finished row/column.
		sum = 0;
		for(j = 0; j < 9; j++){
			sum += board[i][j];
		}
		if(sum != 45){
			complete = 0;
			return complete;
		}
	}

	//check all columns
	for(i = 0; i < 9; i++){
		//Every row should only have one instance of each number, so there is only one
		//correct sum for all numbers in a finished row/column.
		sum = 0;
		for(j = 0; j < 9; j++){
			sum += board[j][i];
		}
		if(sum != 45){
			complete = 0;
			return complete;
		}
	}

	//check all grids
	//iterate through each of 9 mini-grids
	for(i = 0; i < 3; i++){
		for(j = 0; j < 3; j++){
			sum  = 0;			

			//iterate through current mini-grid
			for(k = 0; k < 3; k++){
				for(l = 0; l < 3; l++){
					sum += board[((i * 3) + k)][((j * 3) + l)];
				}
			}

			if(sum != 45){
				complete = 0;
				return complete;
			}
		}
	}
	
	return complete;
}

#endif
