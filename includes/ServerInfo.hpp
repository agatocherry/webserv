#ifndef SERVERINFO_HPP
#define SERVERINFO_HPP

#include <iostream>
#include <ostream>
#include <string>
#include <stdlib.h>

struct Location
{
	char	*uri;
	char	*root;
	char	*index;
	int		allow[3]; // GET POST DELETE : 0 si interdit, 1 si autorise
};

class ServerInfo 
{
	public:
		ServerInfo(void);
		ServerInfo(std::string ip);
		void				setIp(std::string line);
		std::string	getIp();
		void				setName(std::string line);
		std::string	getName();
		void				setClientSize(std::string line);
		long int		getClientSize();
	private:
		std::string	_ip;
		std::string _name;
		long				_clientSize;
		int			_autoIndex; //0 si off, 1 si on
		Location	_loc;
		int					_allow[3];
};

#endif
