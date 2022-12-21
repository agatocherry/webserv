#ifndef CONFIGINFO_HPP
#define CONFIGINFO_HPP

#pragma once

#include "webserv.hpp"

class Server;

class ConfigInfo {
public:
    ConfigInfo(void);
    ConfigInfo(ConfigInfo& copy);
    ~ConfigInfo(void);
    ConfigInfo&    operator=(ConfigInfo& copy);
    std::map<int, Server>    parse(char *filename);
    int    getMaxFd();

    std::map<int, std::string>  getErrors();

private:
    std::map<int, Server>      _servers;
    std::map<int, std::string>  _error_files;
    int                        _maxFd;
    int                        _size;
};

#endif