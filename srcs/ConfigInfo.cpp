#include "../includes/webserv.hpp"

ConfigInfo::ConfigInfo(){
	this->setSize(0);
	this->_maxFd = 0;
	this->_err = 0;
	this->setErrorFiles();
}

ConfigInfo::ConfigInfo(ConfigInfo& copy){
	this->_err = 0;
	this->_maxFd = 0;
	this->setSize(0);
	this->setErrorFiles();
}

ConfigInfo::ConfigInfo(char *filename){
	this->_err = 0;
	this->setSize(0);
	this->_maxFd = 0;
	this->setErrorFiles();
	this->_servers = this->parse(filename);
}

std::map<int, Server>	ConfigInfo::parse(char *filename){
	File		file(filename);
	int			ret = 0;
	std::string	line;

	while (file.lineHistory < file.getMaxLine()){
		
		line = file.getLine();
		
		if (line.find("server {") != std::string::npos){
			ServerInfo	tmpInfo;
			line = file.getLine();

			while (line.find("server {") == std::string::npos) {

				if (line.find("server_name ") != std::string::npos)
					ret = tmpInfo.setServerName(line);
				else if (line.find("listen ") != std::string::npos) {
					int	port;
					if (line.find(":")) {
						port = atoi(&line[line.find(":") + 1]);
						ret = tmpInfo.setIp(line);
					}
					else
						port = atoi(&line[line.find(" ") + 1]);
					try {
						_servers.at(port).addNewInfo(&tmpInfo);
					}
					catch (std::out_of_range& e) {
						_servers.insert(std::make_pair(port, Server(&tmpInfo, port)));
					}
				}
				else if (line.find("root ") != std::string::npos)
					ret = tmpInfo.setRoot(line);
				// else if (line.find("index ") != std::string::npos)
				// 	ret = tmpInfo.setIndex(line); NOT WORKING
				else if (line.find("client_body_buffer_size ") != std::string::npos)
					ret = tmpInfo.setClientSize(line);
				else if (line.find("allow_methods ") != std::string::npos)
					ret = tmpInfo.setAllow(line);
				// else if (line.find("location ") != std::string::npos)
				// 	ret = tmpInfo.setLoc(setupLoc(file, line)); NOT WORKING
				// else if (line.find("autoindex ") != std::string::npos)
				// 	ret = tmpInfo.setAutoIndex(line); NOT WORKING
				else if (line != "\n") {
					std::cerr << "Error: Parsing configuration file : unknown directive" << std::endl;
					_err = 1;
					return _servers;
				}
				if (ret) {
					std::cerr << "Error: Parsing configuration file : syntax" << std::endl;
					_err = 1;
					return _servers;
				}
				line = file.getLine(); 
			}
		}
		else if (line.find("error_page ") != std::string::npos) {
			if (setErrorFile(line)) {
				std::cerr << "Error: Parsing configuration file : error_page" << std::endl;
				_err = 1;
				return _servers;
			}
			line = file.getLine();
		}
		else if (line == "\n") {
			line = file.getLine();
		}
		else {
			std::cerr << "Error: Parsing configuration file : unknown directive" << std::endl;
			_err = 1;
			return _servers;
		}
	}
	_size = _servers.size();
	for (std::map<int, Server>::iterator it = _servers.begin(); it != _servers.end(); it++) {
		if (it->second.getSocket() > _maxFd)
			_maxFd = it->second.getSocket();
	}
	return (_servers);
}

Location	ConfigInfo::setupLoc(File& file, std::string curr_line) {
	Location	tmp;
	std::string	line = file.getLine();

	tmp.uri = curr_line.substr(curr_line.find(" " + 1), curr_line.find("{") - 1);
	// if (tmp.uri.find(".") == std::string::npos && tmp.uri.back() != '/') NOT WORKING (back is C++11)
	// 	tmp.uri += "/";
	tmp.allow[0] = 0;
	tmp.allow[1] = 0;
	tmp.allow[2] = 0;
	tmp.cgi = "";
	tmp.clientSize = 100;
	tmp.index = "";
	tmp.root = "";

	while (line.find("}") == std::string::npos) {
		if (line.find("location ") != std::string::npos)
			tmp.loc.push_back(setupLoc(file, line));
		else if (line.find("root ") != std::string::npos) {
			tmp.root = line.substr(line.find(" " + 1), line.find("\n"));
			// if (tmp.uri.back() != '/') // NOT WORKING
				// tmp.uri += "/";
		}
		else if (line.find("index ") != std::string::npos)
			tmp.index = line.substr(line.find(" " + 1), line.find("\n"));
		else if (line.find("cgi_pass ") != std::string::npos)
			tmp.cgi = line.substr(line.find(" " + 1), line.find("\n"));
		else if (line.find("client_body_buffer_size ") != std::string::npos)
			tmp.clientSize = atoi(line.substr(line.find(" " + 1)).c_str());
			// tmp.clientSize = atoi(line.substr(line.find(" " + 1).c_str(), line.find("\n").c_str())); // NOT WORKING
		else if (line.find("allow_methods ") != std::string::npos) {
			if (line.find("GET") != std::string::npos)
				tmp.allow[0] = 1;
			if (line.find("POST") != std::string::npos)
				tmp.allow[1] = 1;
			if (line.find("DELETE") != std::string::npos)
				tmp.allow[2] = 1;
		}
		line = file.getLine();
	}
	return tmp;
}

int	ConfigInfo::setErrorFile(std::string line) {
	int error = atoi(line.substr(line.find(" " + 1)).c_str());
	if (error < 400 || error >= 600)
		return 1;
	else {
		line.erase(0, line.find_last_of(" ") + 1);
		// line.erase(back()); // NOT WORKING
		_errorFiles[error] = line;
	}
	return 0;
}

void	ConfigInfo::setErrorFiles(){
	_errorFiles[400] = "./data/error_files/400.html";
	_errorFiles[403] = "./data/error_files/403.html";
	_errorFiles[404] = "./data/error_files/404.html";
	_errorFiles[405] = "./data/error_files/405.html";
	_errorFiles[500] = "./data/error_files/500.html";
}

void ConfigInfo::setSize(int size){
		this->_size = size;
}

int ConfigInfo::getError(){
		return (this->_err);
}

std::map<int, std::string>	ConfigInfo::getErrors(){
		return (this->_errorFiles);
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
