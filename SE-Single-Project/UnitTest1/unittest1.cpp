#include "stdafx.h"
#include "CppUnitTest.h"
#include "../SE-Single-Project/InputHandler.h"
#include "../SE-Single-Project/Output.h"
#include "../SE-Single-Project/Sudoku.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

/*
	@overview:unit test for sudoku project
*/

namespace UnitTest1
{		
	
	TEST_CLASS(UnitTest1)
	{
		/*
		@overview:test InputHandler
		@to be test:
					InputHandler(int argc,char** argv);
					void analyze();
					char get_mode();
					char* get_filename();
					int get_number();
					bool get_board(fstream &file,char board[][LEN+1]);
		*/
	public:
		int argc;
		char** argv1, **argv2;
		TEST_METHOD(TestMethod1)
		{
			//@test:Constructor(argc,argv)
			InputHandler input(argc,argv1);
			Assert::AreEqual(input.argc, argc);
			Assert::AreEqual(input.argv==argv1,true);
		}

		TEST_METHOD(TestMethod2)
		{
			//@test:void analyze();
			InputHandler input(argc, argv1);
			input.analyze();
			Assert::AreEqual(input.mode=='c',true);
			Assert::AreEqual(input.number, 123213);
		}
		TEST_METHOD(TestMethod3)
		{
			//@test:char get_mode();
			InputHandler input(argc, argv1);
			input.analyze();
			Assert::AreEqual(input.get_mode(), 'c');
		}
		TEST_METHOD(TestMethod4)
		{
			//@test:char* get_filename();
			InputHandler input(argc, argv2);
			input.analyze();
			Assert::AreEqual(strcmp("puzzle.txt",input.get_filename()),0);
		}
		TEST_METHOD(TestMethod5)
		{
			//@test:int get_number()
			InputHandler input(argc, argv1);
			input.analyze();
			Assert::AreEqual(input.get_number(), 123213);
		}
		TEST_METHOD(TestMethod6)
		{
			//@test:bool get_board(fstream &file,char board[][LEN+1])
			char temp[10][10];
			fstream file("e:\\puzzle.txt", ios::in);
			InputHandler input(argc, argv2);
			input.analyze();
			bool outcome;
			outcome = input.get_board(file, temp);
			Assert::AreEqual(outcome, true);
			file.close();
			file.open("e:\\puzzle.txt", ios::out);
			file << "error" << endl;
			outcome = input.get_board(file, temp);
			Assert::AreEqual(outcome, false);
			file.close();
		}

		/*
		@overview:test InputHandler
		@to be test:
							bool check();
							void generate_output_n(int n,char* filename);
							bool solve();			
		*/

		TEST_METHOD(TestMethod7)
		{
			//@test:bool check();
			char* filename = "e:\\sudoku.txt";
			char temp[10][10];
			fstream file(filename, ios::in);
			InputHandler input(argc, argv2);
			Assert::AreEqual(input.get_board(file, temp), true);
			Sudoku sudoku;
			sudoku.set(temp);
			bool outcome = sudoku.check();
			Assert::AreEqual(outcome, true);
			Assert::AreEqual(input.get_board(file, temp), true);
			sudoku.set(temp);
			outcome = sudoku.check();
			Assert::AreEqual(outcome, false);
			file.close();
			file.open(filename, ios::out);
			file.close();
		}
		TEST_METHOD(TestMethod8)
		{
			//@test:void generate_output_n(int n,char* filename);
			char* filename = "e:\\sudoku.txt";
			Sudoku sudoku;
			sudoku.generate_output_n(1000, filename);
			fstream file(filename, ios::in);
			int length = 0;
			string s;
			while (getline(file, s)) {
				length++;
			}
			Assert::AreEqual(length, 10 * 1000);
			file.close();
		}
		TEST_METHOD(TestMethod9)
		{
			//@test:bool solve();
			char* filename = "e:\\puzzle2.txt";
			char temp[10][10];
			fstream file(filename, ios::in);
			InputHandler input(argc, argv2);
			Assert::AreEqual(input.get_board(file, temp), true);
			Sudoku sudoku;
			sudoku.set(temp);
			bool outcome = sudoku.solve();
			Assert::AreEqual(outcome, true);
			Assert::AreEqual(input.get_board(file, temp), true);
			sudoku.set(temp);
			outcome = sudoku.solve();
			Assert::AreEqual(outcome, false);
			file.close();
			file.open(filename, ios::out);
			file.close();
		}

		 UnitTest1() {
			argc = 3;
			argv1 = new char*[3];
			argv2 = new char*[3];
			for (int i = 0; i < 3; ++i) {
				argv1[i] = new char[100];
				argv2[i] = new char[100];
			}
			strcmp(argv1[0], "sudoku.exe");
			strcmp(argv1[1], "-c");
			strcmp(argv1[2], "123213");

			strcmp(argv2[0], "sudoku.exe");
			strcmp(argv2[1], "-s");
			strcmp(argv2[2], "puzzle.txt");
		}

	};
}