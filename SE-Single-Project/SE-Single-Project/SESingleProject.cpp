// SESingleProject.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "iostream"
#include "fstream"
#include "string"
#include "memory.h"
#include "fstream"
#include "Sudoku.h"
#include "time.h"

using namespace std;


int main(int argc,char* argv[])
{
	char* filename = "e:\\sudoku.txt";
	Sudoku temp;
	temp.generate_output_n(1000000, filename);
    return 0;
}

