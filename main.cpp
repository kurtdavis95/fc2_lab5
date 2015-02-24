//Lab 5, Part 2-3		main.cpp	2/21/15	Author: Kurt Davis

#include<iostream>
#include<string>
#include<vector>
using namespace std;
#include"puzzle.h"

int main(){
	//Part 2 - display sudoku and wordoku
	Puzzle<int> sudoku("sudoku.txt");
	Puzzle<char> wordoku("wordoku.txt");
	
	//for quick demonstration of checking for completed game
	Puzzle<int> finished("finished.txt");
	

	cout << "Sudoku Puzzle: " << endl;
	sudoku.display();
	cout << endl << "Wordoku Puzzle: " << endl;
	wordoku.display();
	cout << endl;

	//Part 3 - play sudoku
	cout << "Example of finished game/game over detection: " << endl;
	finished.play();

	cout << endl << "Now playing sudoku..." << endl;
	sudoku.play();

	return 0;
}
