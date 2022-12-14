#ifndef SERVER_HPP
#define SERVER_HPP

#pragma once

#include "Webserv.hpp"

class ServerInfo;

class Server {
	public:
		Server(ServerInfo infos, int port = 80);
		Server(Server& copy);
		~Server(void);
		Server&	operator=(Server& copy);
		int	accept();
		int			getSocket();
//		ServerInfo		getDefaultInfos(void);
//		std::vector<ServerInfo>	getAllInfos(void);
		void	addNewInfo(ServerInfo& new_infos);
		void	setSocket(int socket_descriptor);
		ServerInfo		*_default;	//what if ?
	//	ServerInfo		_default;	//no more a pointer
		std::vector<ServerInfo>	_infos;
		void		close_socket(void);//close -> close_socket
		int		parseRequest();
		int		sendResponse();
	private:
		struct sockaddr_in	_addr;
		int			_socket;
		int			_size;
};

std::ostream	&operator<<(std::ostream &x, Server serv);

#endif
