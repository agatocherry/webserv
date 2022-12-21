#include "../includes/WebServer.hpp"
#include "../includes/Server.hpp"
#include "../includes/ServerInfo.hpp"

/*
int main(int argc, char **argv) {

	WebServer	server;
	char	*filename;

	if (argc == 1)
		filename = "./config/default.conf";
	else if (argc == 2)
		filename = argv[1];
	else
		std::cerr << "Usage : ./webserv [configuration file]" << std::endl;
	
	server.parsefile(filename);
	server.launch();
	server.clean();

	return 0;
}
*/
int	main()
{
	std::cout << "hello";
	ServerInfo	fofo;
	Server		baba(fofo, 8080);

	std::cout << "---FOFO = ";
	std::cout << fofo << std::endl;
	std::cout << "---BABA = ";
	std::cout << baba << std::endl;
}

/*
int	main(void)
{
	ServerInfo si;
	
	si.setIp("	listen www.localhost");
	std::cout << "Ip : " << si.getIp() << std::endl;
	si.setServerName("	server_name YoupiBanane");
	std::cout << "Name : " << si.getServerName() << std::endl;
	si.setClientSize("	client_body_buffer_size 100");
	std::cout << "Client size : " << si.getClientSize() << std::endl;
	si.setAutoIndex(0);
	std::cout << "Auto index : " << si.getAutoIndex() << std::endl;
	si.setAllow("	allow_methods GET");
	std::cout << "Allow : " << si.getAllow("GET") << ", " << si.getAllow("POST") << ", " << si.getAllow("DELETE") << std::endl;
	si.setLoc("	location *.bla {", "		root YoupiBanane/", "		index youpi.bad_extension", "		allow_methods POST");
	si.setLoc("	location *.here {", "		root Yo/", "		index youpi.html", "		allow_methods DELETE");
	si.setLoc("	location *.c {", "		root Prout/", "		index youpi.bad", "		allow_methods GET");
	std::cout << "Size loc : " << si.sizeLoc() << std::endl;
	//getloc
	//getlocallow
	return (0);
}
*/
