#include "../includes/webserv.hpp"

ConfigInfo::ConfigInfo(){
	this->setSize(0);
}

ConfigInfo::ConfigInfo(ConfigInfo& copy){
}

//ConfigInfo& ConfigInfo::operator=(ConfigInfo& copy){
//}

//std::map<int, Server>   parse(char *filename){
//}

void ConfigInfo::setSize(int size){
		this->_size = size;
}

int ConfigInfo::getSize(){
		return (this->_size);
}

int ConfigInfo::getMaxFd(){
    return (this->_maxFd);
}

ConfigInfo::~ConfigInfo(){
}
