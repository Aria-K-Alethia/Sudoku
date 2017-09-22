#pragma once
#include "stdafx.h"
#include "fstream"
#include "string"
#define LEN 9

using namespace std;

/*
@overview:The Sudoku class a mutable.It has a sudoku board of size 9x9 and can generate or solve a sudoku
*/

class Sudoku
{
private:
	char board[LEN+1][LEN+1];
	void init();
	void trace_back_n(int i,int j,int n, fstream& file);
	void trace_back_solve(int i, int j);
	inline int get_block(int i);
	static long int count;
public:
	Sudoku();
	Sudoku(char **b);
	Sudoku(Sudoku &b);
	string toString();
	void generate_output_n(int n,char* filename);
	void get(char** b);
	void solve();
	bool check();
	bool check_pos(int i, int j);
	bool check_generate_pos(int i, int j,int k);
};


