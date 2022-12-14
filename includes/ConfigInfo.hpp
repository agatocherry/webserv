#ifndef CONFIGINFO_HPP
#define CONFIGINFO_HPP

#pragma once

#include "Webserv.hpp"

class Server;

class ConfigInfo {
public:
    ConfigInfo(void);
    ConfigInfo(ConfigInfo& copy);
    ~ConfigInfo(void);
    ConfigInfo&    operator=(ConfigInfo& copy);
    std::map<int, Server>    parse(char *filename);
    int    getMaxFd();
private:
    std::map<int, Server>    _servers;
    int                        _maxFd;
    int                        _size;
};

#endif