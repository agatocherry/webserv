

#include "webserv.hpp"
#include "HttpResponse.hpp"

HttpResponse::HttpResponse(std::string file, int status, int autoindex)
{
	// Constructor
	// 1st : Verify if file exists
	// 2nd : Open it and retrieve its content into a string
	// 3rd : DEBUG, print the content in outstream
	
	int	pid;

//	pid = fork();
//	if (pid == 0)
	{
		std::string	path = "../" + file;
		std::ifstream	filestream;

		filestream.open(path.c_str());
		filestream >> this->_file_content; 
		std::cout << this->file_content << std::endl; 	//DEBUG
		this->_status = 200;				//SUCCESS
		
	}
}
