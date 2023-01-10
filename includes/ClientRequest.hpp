#ifndef CLIENT_REQUEST_HPP
#define CLIENT_REQUEST_HPP

#include "webserv.hpp"
#include "ServerInfo.hpp"

class	ClientRequest {

	public:
		ClientRequest(ServerInfo info, std::string request = "");
		~ClientRequest(void);

		int			checkSyntax();
		int			checkMethod();
		int			checkSize();
		int			isMethod(std::string word)
		int			determinateLoc();
		std::string	determinateFile();

		int			getStatus() const;
		std::string	getFile() const;

	private:
		ServerInfo	_info;
		Location	_loc;
		std::string	_request;
		std::string	_method;
		std::string	_uri;
		std::string	_file;
		int			_status;

}

#endif
