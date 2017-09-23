#include "stdafx.h"
#include "Sudoku.h"
#include "assert.h"
#include "string"
#include "memory.h"
#include "fstream"
#include "iostream"
#include "Output.h"

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
	file.open(filename, ios::out);
	if (file.is_open()) {
		//start from (1,2) since START has been filled
		trace_back_n(1,2,n, file);
	}
	else 
		Output::error(4);
	file.close();
	
}


bool Sudoku::solve()
{
	/*
	@overview:solve a sudoku game in this board
	*/

	//start from (1,1)
	return trace_back_solve(1, 1);
}

void Sudoku::solve_and_output(InputHandler input,char* filename)
{
	/*
	@overview:solve sudoku in input.filename and output to file with filename
	*/
	fstream infile(input.get_filename(), ios::in);
	fstream file(filename, ios::out | ios::app);
	if (!infile.is_open()) Output::error(4);
	char board[LEN + 1][LEN + 1];
	while (input.get_board(infile, board)) {
		set(board);
		if (solve()) {
			string outcome = toString();
			file << outcome << endl;
		}
		else Output::error(6);
	}
	infile.close();	
	file.close();
}

//some useful method

void Sudoku::set(char b[][LEN+1])
{
	//@overview:copy a board from b
	assert(b != NULL);
	for (int i = 1; i <= LEN; ++i) {
		for (int j = 1; j <= LEN; ++j) {
			board[i][j] = b[i][j];
		}
	}
}


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
		if (!check()) Output::error(7);
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

bool Sudoku::trace_back_solve(int i, int j)
{
	/*@overview:trace back function when solve sudoku
	   @param:
	*/
	if (i == LEN && j == LEN + 1) return true;
	if (i != LEN && j == LEN + 1) {
		j = 1;
		++i;
	}
	if (board[i][j] != '0') return trace_back_solve(i, j + 1);
	bool outcome;
	for (int k = 1; k <= LEN ; ++k) {
		if (check_solve_pos(i, j, k)) {
			board[i][j] = k + '0';
			outcome = trace_back_solve(i, j + 1);
			if (outcome) return true;
		}
	}
	board[i][j] = '0';
	return false;
}

bool Sudoku::check_generate_pos(int i, int j,int k)
{
	/*@overview:check if the board is valid when board[i][j] = k,this method omit 0 in the board
	   @param:
	*/

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

bool Sudoku::check_solve_pos(int i, int j, int k)
{
	/*@overview:check if k in (i,j) is valid when solving a sudoku
	   @param:
	*/
	
	//init
	//check row
	for (int a = 1; a <= LEN; ++a) {
		if (board[i][a] == k + '0') return false;
	}
	//check col
	for (int a = 1; a <= LEN; ++a) {
		if (board[a][j] == k + '0') return false;
	}
	//check 3x3 block
	int row, col;
	row = get_block(i);
	col = get_block(j);

	for (int a = row; a <= row+2; ++a) {
		for (int b = col; b <= col + 2; ++b) {
			if (board[a][b] == k + '0') return false;
		}
	}

	return true;
}