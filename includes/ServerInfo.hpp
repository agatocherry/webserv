#ifndef SERVERINFO_HPP
#define SERVERINFO_HPP

struct Location
{
	std::string	*uri;
	std::string	*root;
	std::string	*index;
	int		allow[3]; // GET POST DELETE : 0 si interdit, 1 si autorise
};


class ServerInfo {

	public:
		ServerInfo(void);
		// Setters
		void	setIp(std::string ip);
		void	setServerName(std::string name);
		void	setClentSize(long x);

	private:
		std::string			ip; // :)
		std::string			server_name;
		std::string::vector<Location>	_loc;
		int				allow[3];
		long				client_body_buffer_size;
		int				autoindex; //0 si off, 1 si on

};

#endif
