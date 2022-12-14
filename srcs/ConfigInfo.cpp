#include "../includes/Webserv.hpp"

ConfigInfo::ConfigInfo(){
}

ConfigInfo::ConfigInfo(ConfigInfo& copy){
}

//ConfigInfo& ConfigInfo::operator=(ConfigInfo& copy){
//}

//std::map<int, Server>   parse(char *filename){
//}

int ConfigInfo::getMaxFd(){
    return (this->_maxFd);
}

ConfigInfo::~ConfigInfo(){
}