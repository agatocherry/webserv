#ifndef SERVER_HPP
#define SERVER_HPP

#pragma once

#include "webserv.hpp"

class ServerInfo;

class Server {
	public:
		Server(void){};
		Server(ServerInfo infos, int port = 80);
		Server(Server& copy, int new_socket);
		Server&	operator=(Server& copy);
		void	addNewInfo(ServerInfo& new_infos);
		void	setSocket(int socket_descriptor);
		int	accept_fd();
		int	getSocket();
		void	close_socket();
		int	parseRequest();
		int	sendResponse();
		int	chunkedRequest();
		void	parseChunked();
		ServerInfo	requestInfos();
		std::string	getError();
		ServerInfo	*_default;
		std::vector<ServerInfo>	_infos;
		~Server(void);
	private:
		std::string	_error;
		struct sockaddr_in	_addr;
		std::string	_file_request;
		std::string	_request;
		int	_socket;
		int	_status;
		int	_size;
};

std::ostream	&operator<<(std::ostream &x, Server serv);

#endif
