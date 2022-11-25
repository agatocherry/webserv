#include "../includes/WebServer.hpp"

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