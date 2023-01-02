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

//ConfigInfo& ConfigInfo::operator=(ConfigInfo& copy){
//}

//std::map<int, Server>   parse(char *filename){
//}

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
