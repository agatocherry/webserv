#ifndef SERVER_HPP
#define SERVER_HPP

#include "webserv.hpp"
#include "ServerInfo.hpp"

class Server {

	public:
		Server(ServerInfo infos, int port = 80);
		Server(Server& copy);
		~Server(void);

		Server&	operator=(Server& copy);

		int	getSocket();
		int	accept();
		int	addNewinfo(ServerInfo& new_infos);

		void	close();
		int		parseRequest();
		int		sendResponse();

	private:
		int					_socket;
		int					_size;
		ServerInfo			*_default;
		struct sockaddr_in	_addr;

		std::vector<ServerInfo>	_infos;
};

#endif