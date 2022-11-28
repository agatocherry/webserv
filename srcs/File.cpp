#include "../includes/File.hpp"

void	File::initialise(char *filename)
{
	string tmp;
	this->name = filename;
	this->lineHistory = 0;
	this->maxLine = 0;
	ifstream fd(filename);
	while (getline (fd, tmp))
	{
		this->content = content + tmp + '\n';
		maxLine++;
	}
	fd.close(); 
}

std::string	File::getName()
{
	return (this->name);
}

std::string	File::getContent()
{
	return (this->content);
}

int	File::getMaxLine()
{
	return (this->maxLine);
}

std::string File::getLine(int nbLine)
{
	std::string line;
	if (lineHistory >= maxLine)
		return line;
	int	i = 0;
	int	j = 0;
	int k = 0;
	while (j < lineHistory)
	{
		while (this->content[i] != '\n')
			i++;
		i++;
		j++;
	}
	while (k < nbLine && this->content[i])
	{
		while (this->content[i] != '\n')
		{
			line = line + this->content[i];
			i++;
		}
		line = line + '\n';
		i++;
		k++;
		lineHistory++;
	}
	return line;
}

// Example for use :
// int	main(int argc, char **argv)
// {
// 	File file;

// 	file.initialise(argv[argc - 1]);
// 	std::cout << "File name : " << std::endl << file.getName() << std::endl << std::endl;
// 	std::cout << "File content : " << std::endl << file.getContent() << std::endl;
// 	std::cout << "File get line :" << std::endl;
// 	std::string tmp;
// 	while((tmp = file.getLine(10)) != "")
// 		std::cout << tmp;
// 	return 0;
// }
