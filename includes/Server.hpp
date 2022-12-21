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
		
    int accept();
		int getSocket();
		void	close_socket();
		
    int		parseRequest();
		int		sendResponse();
		int		chunkedRequest();
		void	parseChunked();

		ServerInfo	requestInfos();

		void	addNewInfo(ServerInfo& new_infos);
		void	setSocket(int socket_descriptor);
		
    ServerInfo		*_default;
		std::vector<ServerInfo>	_infos;
	
  private:
		struct sockaddr_in	_addr;
		std::string	_file_request;
		std::string	_request;
		int			_socket;
		int			_status;
		int			_size;
};

std::ostream	&operator<<(std::ostream &x, Server serv);

#endif
