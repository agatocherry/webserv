#ifndef SERVERINFO_HPP
#define SERVERINFO_HPP

struct Location
{
	char	*uri;
	char	*root;
	char	*index;
	int		allow[3];
};


class ServerInfo {

	public:
		ServerInfo(void);

		// Setters

	private:
		int		ip;
		char	*server_name;
		Location	_loc;
		int			allow[3];
		long		clientSize;
		int			autoindex;

};

#endif