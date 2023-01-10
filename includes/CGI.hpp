#ifndef CGI_HPP
# define CGI_HPP

#include "webserv.hpp"

class	CGI {
	CGI(std::string	path, std::string request);
	~CGI();

	int	execute();
}

#endif