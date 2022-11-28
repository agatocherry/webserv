#include <iostream>
#include <fstream>
using namespace std;

class File {
	public:
		void				initialise(char *filename);
		std::string	getName();
		std::string	getContent();
		int					getMaxLine();
		std::string	getLine(int line);
		//get the next(s) line(s)
		//line is how much line you want, let 1 by default
		//if the return is empty, there are no much line
	private:
		std::string name;
		std::string	content;
		int					lineHistory;
		int					maxLine;
};
