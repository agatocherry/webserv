#ifndef CLIENT_REQUEST_HPP
#define CLIENT_REQUEST_HPP

#include "webserv.hpp"

class	ClientRequest {

	public:
		ClientRequest(ServerInfo infos, std::string request = "");
		~ClientRequest(void);

		int	getStatus() const;
		std::string	getFile() const;

	private:
		int			_status;
		std::string	_file;

}

#endif