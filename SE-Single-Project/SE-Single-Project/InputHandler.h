#pragma once
/*
@overview:The InputHandler is mutable.This class is used to processing the input and save necessary info.
*/
class InputHandler
{
public:
	InputHandler(int argc,char** argv);
	void analyze();
	char get_mode();
	char* get_filename();
	int get_number();

private:
	int argc;
	char** argv;
	char mode;
	char* filename;
	int number;
};

