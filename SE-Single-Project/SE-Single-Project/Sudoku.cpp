#include "stdafx.h"
#include "Sudoku.h"
#include "assert.h"
#include "string"
#include "memory.h"
#include "fstream"
#include "iostream"
#define START 2
#define LEN 9

using namespace std;
long int Sudoku::count = 0;
/*
@overview:this file implement the class Sudoku in Sudoku.h
*/

//Constructor
Sudoku::Sudoku()
{
	//@overview:init a board with 0 and START in board[1][1]
	init();
}

Sudoku::Sudoku(char **b)
{
	//@overview:init a board in terms of b
	assert(b != NULL);
	for (int i = 1; i <= LEN; ++i) {
		for (int j = 1; j <= LEN; ++j) {
			board[i][j] = b[i][j];
		}
	}
}
Sudoku::Sudoku(Sudoku &b)
{
	//@overview:copy constructor
	for (int i = 1; i <= LEN; ++i) {
		for (int j = 1; j <= LEN; ++j) {
			board[i][j] = b.board[i][j];
		}
	}
}
//main method,including generate and solve method.
void Sudoku::generate_output_n(int n,char* filename)
{
	//@overview:generate n sudoku 
	//do some prepare
	assert(Sudoku::count == 0);
	fstream file;
	file.open(filename, ios::app | ios::out);
	if (file.is_open()) {
		//start from (1,2) since START has been filled
		trace_back_n(1,2,n, file);
	}
	else {
		cout << "bad filename:" << filename << endl;
	}
	file.close();
	
}
void solve()
{
	return;
}

//some useful method

string Sudoku::toString()
{
	//@overview:turn the board into a standard string.
	string outcome = "";
	for (int i = 1; i <= LEN ; ++i) {
		for (int j = 1; j <= LEN ; ++j) {
			outcome += board[i][j];
			if (j != LEN) outcome += " ";
		}
		outcome += "\n";
	}
	return outcome;
}

bool Sudoku::check()
{
	//@overview:check if the whole sudoku is valid
	for (int i = 1; i <= LEN; ++i) {
		for (int j = 1; j <= LEN; ++j) {
			if (!check_pos(i, j)) return false;
		}
	}
	return true;
}

bool Sudoku::check_pos(int i, int j)
{
	//@overview:check the num in pos (i,j) is valid or not
	bool used[LEN + 1];
	memset(used, 0, sizeof(used));
	int num;
	//check row
	for (int k = 1; k <= LEN; ++k) {
		num = board[i][k] - '0';
		if (num == 0) return false;
		if (!used[num]) used[num] = true;
		else return false;
	}
	//check column
	memset(used, 0, sizeof(used));
	for (int k = 1; k <= LEN; ++k) {
		num = board[k][j] - '0';
		if (num == 0) return false;
		if (!used[num]) used[num] = true;
		else return false;
	}

	//check the 3x3 block
	memset(used, 0, sizeof(used));
	int row, col;
	row = get_block(i);
	col = get_block(j);
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			num = board[row + i][col + j] - '0';
			if (num == 0) return false;
			if (!used[num]) used[num] = true;
			else return false;
		}
	}
	return true;
}


//private method
void Sudoku::init()
{
	//@overview:init  a board with START number
	for (int i = 0; i <= LEN; ++i) {
		for (int j = 0; j <= LEN; ++j) {
			board[i][j] = '0';
		}
	}
	board[1][1] = START + '0';
}

inline int Sudoku::get_block(int i)
{
	/*@overview:get the first row or col in the block of row or col i
	   @param:	
	*/
	return ((i - 1) / 3) * 3 + 1;
}

void Sudoku::trace_back_n(int i ,int j,int n, fstream& file)
{
	//@overview:trace back method for generate_output_n method.
	if (i == 9 && j == 10) {
		if (Sudoku::count >= n) return;
		string outcome = toString();
		file << outcome << endl;
		Sudoku::count++;
		return;
	}
	if (i != 9 && j == 10) {
		++i;
		j = 1;
	}

	for (int k = 1; k <= LEN; ++k) {
		if (Sudoku::count >= n) return;
		if (check_generate_pos(i, j, k)) {
			board[i][j] = k + '0';
			trace_back_n(i, j + 1, n, file);
		}
	}
	board[i][j] = '0';
}

bool Sudoku::check_generate_pos(int i, int j,int k)
{
	/*@overview:check if the board is valid when board[i][j] = k,this method omit 0 in the board
	   @param:
	*/

	bool used[LEN + 1];
	memset(used, 0, sizeof(used));
	//check row
	for (int a = 1; a < j; ++a) {
		if (board[i][a] == k + '0') return false;
	}
	//check col
	for (int a = 1; a < i; ++a) {
		if (board[a][j] == k + '0') return false;
	}
	//check 3x3 block
	int row, col;
	row = get_block(i);
	col = get_block(j);

	for (int a = row; a <= i; ++a) {
		for (int b = col; b <= col +2; ++b) {
			if (a == i && b == j) continue;
			if (board[a][b] == k + '0') return false;
		}
	}

	return true;
}
