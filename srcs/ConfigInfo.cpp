#include "../includes/webserv.hpp"

ConfigInfo::ConfigInfo(){
	this->setSize(0);
	this->_maxFd = 0;
	this->setErrorFiles();
}

ConfigInfo::ConfigInfo(ConfigInfo& copy){
	this->_maxFd = 0;
	this->setSize(0);
	this->setErrorFiles();
}

ConfigInfo::ConfigInfo(char *filename){
	this->setSize(0);
	this->_maxFd = 0;
	this->setErrorFiles();
	this->_servers = this->parse(filename);
}

ConfigInfo& ConfigInfo::operator=(ConfigInfo& copy){
	*this = copy;
	return (*this);
}

std::map<int, Server>	ConfigInfo::parse(char *filename){
	File	file(filename);
	int	i = 0;
	int	server = 0;
	std::map<int, Server>	tmp;
	ServerInfo	tmpInfo = ServerInfo();
	while (i < file.getMaxLine()){
		std::string	line = file.getLine();
		if (line.find("server {") != std::string::npos){
			if (server > 0)
			{
				Server tmpServer = Server(tmpInfo, 80);
				tmp.insert(std::pair<int, Server>(server, tmpServer));
				tmpInfo = ServerInfo();
			}
			server++;
		}
		else{
			if (line.find("server_name") != std::string::npos)
				tmpInfo.setServerName(line);
			if (line.find("listen") != std::string::npos)
				tmpInfo.setIp(line);
			if (line.find("client_body_buffer_size") != std::string::npos)
				tmpInfo.setClientSize(line);
			if (line.find("allow_methods") != std::string::npos)
				tmpInfo.setAllow(line);
			while (line.find("location") != std::string::npos)
			{
				std::string uri = line;
				std::string root = "";
				std::string index = "";
				std::string allow = "";
				while (line.find("}") == std::string::npos)
				{
					line = file.getLine();
					if (line.find("location") != std::string::npos)
						break ;
					if (line.find("root") != std::string::npos)
						root = line;
					if (line.find("index") != std::string::npos)
						index = line;
					if (line.find("allow_methods") != std::string::npos)
						allow = line;
					i++;
				}
				tmpInfo.setLoc(uri, root, index, allow);
			}
			i++;
		}
	}
	if (server > 0)
	{
		Server tmpServer = Server(tmpInfo, 80);
		tmp.insert(std::pair<int, Server>(server, tmpServer));
	}
	return (tmp);
}

void	ConfigInfo::setErrorFiles(){
	std::map<int, std::string>	tmp;
	int i = 100;
	while (i < 600){
		tmp[i] = "./data/error_files/404.html";
		i++;
	}
	tmp[400] = "./data/error_files/400.html";
	tmp[403] = "./data/error_files/403.html";
	tmp[404] = "./data/error_files/404.html";
	tmp[405] = "./data/error_files/405.html";
	tmp[500] = "./data/error_files/500.html";
	this->_errorFiles = tmp;
}

void ConfigInfo::setSize(int size){
		this->_size = size;
}

std::string ConfigInfo::getError(){
		return (this->_error);
}

int ConfigInfo::getSize(){
		return (this->_size);
}

int ConfigInfo::getMaxFd(){
    return (this->_maxFd);
}

ConfigInfo::~ConfigInfo(){
}

std::ostream	&operator<<(std::ostream &x, ConfigInfo inf)
{
	x << "**** ConfigInfo ****" << std::endl;
	x << "Size : " << inf.getSize() << std::endl;
	x << "MaxFd : " << inf.getMaxFd() << std::endl;
	return (x);
}
