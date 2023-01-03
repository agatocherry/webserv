#include "../includes/webserv.hpp"

int main()
{
	ConfigInfo config((char *)"./config/default.conf");
	std::cout << config;
	return 0;
}

// int	main()
// {
// 	ServerInfo	si;
// 	Server		serv(si, 8080);
//	std::cout << si << std::endl;
// 	std::cout << serv << std::endl;
// 	return 0;
// }

// int main(int argc, char **argv)
// {
// 	WebServer	server;
// 	char	*filename;
// 	if (argc == 1)
// 		filename = "./config/default.conf";
// 	else if (argc == 2)
// 		filename = argv[1];
// 	else
// 		std::cerr << "Usage : ./webserv [configuration file]" << std::endl;
// 	server.parsefile(filename);
// 	server.launch();
// 	server.clean();
// 	return 0;
// }
