
#pragma once

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class File {
	public:
		File(char *filename);
		std::string	getName();
		int	getMaxLine();
		int	getEnd();
		std::string	getLine();
		//get the next(s) line(s)
		//line is how much line you want, let 1 by default
		//if the return is empty, there are no much line
		~File(){};

//	private:			
// Makes the whole object useless because
// imposible to use, must be public.

		std::string name;
		vector<std::string>	content;
		int	lineHistory;
		int	maxLine;
		int	end;
};
