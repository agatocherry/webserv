#include "../includes/File.hpp"

void	File::initialise(char *filename)
{
	string tmp;
	this->name = filename;
	this->lineHistory = 0;
	this->maxLine = 0;
	this->isEnd = 0;
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
		this->isEnd = 1;
	return line;
}

// Example for use :
int	main(int argc, char **argv)
{
	File file;

	file.initialise(argv[argc - 1]);
	std::cout << "File name : " << std::endl << file.getName() << std::endl << std::endl;
	std::cout << "File getline :" << std::endl;
	std::string tmp;
	while(file.isEnd == 0)
		std::cout << file.getLine() << std::endl;
	return 0;
}
