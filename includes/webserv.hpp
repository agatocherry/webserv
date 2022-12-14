#ifndef WEBSERV_HPP
#define WEBSERV_HPP

#include <iostream>
#include <ostream>
#include <fstream>
#include <string>
#include <cstring>
#include <map>
#include <vector>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "ClientRequest.hpp"
#include "ConfigInfo.hpp"
#include "File.hpp"
#include "HttpResponse.hpp"
#include "Server.hpp"
#include "ServerInfo.hpp"
#include "WebServer.hpp"

#define BLANK "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define PURPLE "\033[35m"
#define CYAN "\033[36m"

#endif