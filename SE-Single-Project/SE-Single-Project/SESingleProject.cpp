// SESingleProject.cpp: 定义控制台应用程序的入口点。
//

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
using namespace std;


int main(int argc, char* argv[])
{
	/*clock_t on, off;
	InputHandler input(argc,argv);
	char* filename = "e:\\sudoku.txt";
	Sudoku temp;
	on = clock();
	//temp.generate_output_n(1000000, filename);
	off = clock();
	cout << "total time:" << (off - on) / CLOCKS_PER_SEC << endl;
	*/
	cout << argc << endl;
	
	InputHandler input(argc, argv);
	input.analyze();
	if (input.get_mode() == 'c') {
		cout << input.get_number() << endl;
	}
	else if (input.get_mode() == 's') {
		cout << input.get_filename() << endl;
	}
    return 0;
}

