#include "../includes/webserv.hpp"

File::File(char *filename)
{
	string tmp;
	this->name = filename;
	this->lineHistory = 0;
	this->maxLine = 0;
	this->end = 0;
	ifstream fd(filename);
	while (getline (fd, tmp))
	{
		this->content.push_back(tmp);
		maxLine++;
	}
	fd.close(); 
}

std::string	File::getName()
{
	return (this->name);
}

int	File::getMaxLine()
{
	return (this->maxLine);
}

int	File::getEnd()
{
	return (this->end);
}

std::string File::getLine()
{
	std::string line;
	if (lineHistory >= maxLine)
		return line;
	int	i = 0;
	while (i < lineHistory)
		i++;
	line = content[i];
	lineHistory++;
	if (lineHistory >= maxLine)
		this->end = 1;
	return line;
}

