

#include "webserv.hpp"
#include "HttpResponse.hpp"

//HttpResponse::HttpResponse(std::string file, ConfigInfo conf, int status, int autoindex)
HttpResponse::HttpResponse(std::string file, ConfigInfo conf, int autoindex)
{
	// Constructor
	// PARAM : 	file = path to file to open ("/test" for example)
	// 		conf = param file containing the map to [error_files] + [clientSize]
	// 		autoindex = 1 or 0, indicator of auto-generation of an index
	// 			if a folder is set as param-1 [file-to-open]
	// 1st : Verify if file exists, if not set error to 404.
	// 2nd : Open it and retrieve its content into a string
	// 3rd : DEBUG, print the content in outstream,
	// 4th : Generate a header + body according to situation (ongoing)
	
	int	pid;

//	pid = fork();
//	if (pid == 0)
	(void)pid;	//Not necessary due to open?
			//Subject to change with autoindex implementation
	//Why is status a parameter ? Isn't it blank ?
	{
		std::string	path = "../" + file;
		std::ifstream	filestream;

		int	ret = open(path.c_str());
		if (ret < 0)
		{
			perror("");
			char		*tmp;
			read(2, tmp, 99999);
			std::string	tmp_string = tmp;
			free(tmp);
			if (tmp_string == "Not found")		//exact same error description
				this->_status = 404;			// TEMPORARY 404
		}
		else
		{	
			filestream.open(path.c_str());
			filestream >> this->_file_content; 
			std::cout << this->file_content << std::endl; 	// DEBUG
			this->_status = 200;				// SUCCESS
		}
		close(ret);
	}
	// Specific Error file detection
	// 400, 404, 405 & 408 ONLY (for now)
	// to be determined...
	// temporary 400 set
	if (this->_status >= 400)
	{
		this->_header = "HTTP/1.1 ";
		this->header = this->header + this->status + " ";
		this->header = this->header + "ERROR\r\n";
		this->_body = "Error 400 temporary\r\n";	// specific error file body
	}
	if (this->_status >= 200 && this->_status < 300)
	{
		this->_header = "HTTP/1.1 ";
		this->header = this->header + this->status + " ";
		this->_header = this->header + "OK\r\n";
		this->_body = this->file_content;
	}
	this->_header = this->_header + "Content-Lenght: ";	// Content-length = clientSize
	this->_header = this->_header + ConfigInfo.size;
	this->_header = this->_header + "\r\n";	
	// When HEADER + BODY are generated, join both to
	// create the response
	this->_response = this->_header;
	this->_response = this->_response + "\r\r\n\n";
	this->_response = this->_response + this->_body;
}

HttpResponse::~HttpResponse(void)
{
	return ;
}

std::string	HttpResponse::getResponse(void) const
{
	return (this->_response);
}
