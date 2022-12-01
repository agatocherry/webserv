#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class File {
	public:
		void								initialise(char *filename);
		std::string					getName();
		int									getMaxLine();
		int									getEnd();
		std::string					getLine();
		//get the next(s) line(s)
		//line is how much line you want, let 1 by default
		//if the return is empty, there are no much line
	private:
		std::string 				name;
		vector<std::string>	content;
		int									lineHistory;
		int									maxLine;
		int									end;
};
