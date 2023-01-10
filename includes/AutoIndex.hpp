#ifndef AUTOINDEX_HPP
# define AUTOINDEX_HPP

#include "webserv.hpp"

class	AutoIndex {

	public:
		AutoIndex();
		~AutoIndex();

		std::string	renderPage(std::string directory, std::string path, int port, std::string host);
}

#endif