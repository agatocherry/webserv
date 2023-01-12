#include "../includes/webserv.hpp"

int main()
{
	ServerInfo info;

	info.setIp("	listen 127.0.0.1.0.0.0.127:81");
	// ConfigInfo config((char *)"./config/default.conf");
	// std::cout << config;
	return 0;
}

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
// 	if (server.parsefile(filename)) {
// 		server.launch();
//	}
// 	server.clean();
// 	return 0;
// }
