#include "stdafx.h"
#include "InputHandler.h"
#include "regex"
#include "Output.h"
#include "string"
#include "sstream"

using namespace std;
/*
@overview:this file implement the class InputHandler in InputHandler.h
*/

//Constructor
InputHandler::InputHandler(int argc,char** argv)
{
	/*
		@overview:init inputhandler
	*/
	this->argc = argc;
	this->argv = argv;
}

void InputHandler::analyze()
{
	/*
	@overview:analyze the param in argv to get attr of inputhandler.
	*/
	//check the number of param
	if (argc != 3) Output::error(1);
	//check the format of the param and save them if valid
	string m(argv[1]);
	if (m == "-s") mode = 's';
	else if (m == "-c") mode = 'c';
	else Output::error(2);

	if (mode == 's')  filename = argv[2];
	else {
		regex p("^\\d+$");
		smatch m;
		string num(argv[2]);
		if (regex_match(num, m, p)) {
			stringstream ss;
			ss << num;
			ss >> number;
		}
		else Output::error(3);
	}
}
char InputHandler::get_mode()
{
	/*
	@overview:getter of mode
	*/

	return mode;
}
char* InputHandler::get_filename()
{
	/*
	@overview:getter of filename
	*/

	return filename;
}
int InputHandler::get_number()
{
	/*
	@overview:getter of number
	*/

	return number;
}



