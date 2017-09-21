#pragma once
#include "cstdio"
#include "iostream"

#define LEN 9
#define START 2

using namespace std;

class Sudoku
{
private:
	Sudoku();
	Sudoku(int * sudoku);
	int board[LEN][LEN];
public:
	void toString();
	void toFile(string filename);
	void generate();
	void solve();
};

Sudoku::Sudoku()
{

}