#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <vector>
#include "ServerInfo.hpp"

class Server {

	public:
		Server(ServerInfo infos, int port = 80);
		Server(Server& copy);
		~Server(void);

		Server&	operator=(Server& copy);

		int	getSocket();
		int	addNewinfo(ServerInfo& new_infos);

		ServerInfo	getDefaultInfos(void);
		ServerInfo	*getAllInfos(void);

	private:
		int			_socket;
		int			_size;
		ServerInfo	*_default;

		std::vector<ServerInfo>	_infos;
};

#endif
