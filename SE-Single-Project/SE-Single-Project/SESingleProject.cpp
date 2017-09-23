
#include "stdafx.h"
#include "iostream"
#include "fstream"
#include "string"
#include "memory.h"
#include "fstream"
#include "Sudoku.h"
#include "InputHandler.h"
#include "time.h"
#include "regex"
#include "sstream"
#include "Output.h"
using namespace std;


int main(int argc, char* argv[])
{
	InputHandler input(argc,argv);
	char* filename = "sudoku.txt";
	Sudoku sudoku;
	input.analyze();
	//mode c to generate sudoku in file
	if (input.get_mode() == 'c') {
		sudoku.generate_output_n(input.get_number(), filename);
	}
	//mode s to solve sudoku in file and output
	else if (input.get_mode() == 's') {
		sudoku.solve_and_output(input, filename);
	}
	
    return 0;
}

