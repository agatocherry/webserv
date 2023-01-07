#include "../includes/ClientRequest.hpp"

ClientRequest::ClientRequest(ServerInfo info, std::string request) : _info(info), _request(request), _status(200), _file("") {
	checkSyntax();
	checkMethod();
	_file = determinateFile();
}

ClientRequest::~ClientRequest() {

}

int	ClientRequest::checkMethod() {

}

int	ClientRequest::isMethod(std::string word) {
	if (word == "GET" || word == "POST" || word == "PUT" ||
		word == "HEAD" || word == "PATCH" || word == "DELETE" ||
		word == "CONNECT" || word == "OPTIONS" || word == "TRACE")
			return 1;
	return 0;
}

int	ClientRequest::checkSyntax() {
	
	if (!_request || _request == "") {
		_status = 305; // a verifier
		return _status;
	}
	
	std::string	firstLine = _request.substr(0, _request.find("\r\n") + 2);
	std::string	word = firstLine.substr(0, firstLine.find(" "));
	
	for (int count = 1; count < 4; count++) {
		if (count == 1) {
			if (!isMethod(word))
				_status = 305;
				return _status;
		}
		if (count == 2) {
			_uri = word;
		}
		if (count == 3) {
			if (word != "HTTP/1.1\r\n") {
				_status = 305;
				return _status;
			}
		}
		firstLine.erase(0, word.length() + 1);
		word = firstLine.substr(0, firstLine.find(" "));
	}

	std::string copy_request = _request;
	std::string	bodyLine;

	copy_request.erase(0, firstLine.length());
	bodyLine = copy_request.substr(0, copy_request.find("\r\n"));
	

}

std::string	ClientRequest::determinateFile() {
	Location	loc = getLoc();
	std::string	file_uri = _uri.substr(loc.uri.lenght());

	_file = loc.root + file_uri;
	if (loc.index && loc.index != "" && _file.back() == '/')
		_file += loc.index;
	return _file;
}

Location	ClientRequest::getLoc() {
	std::string	copy_uri = _uri.substr(0, _uri.find_last_of('/') + 1);
	Location	def;

	for (std::vector<Location>::iterator it = _info._loc.begin(); it !+ info._loc.end(); it++) {
		if (it->uri == "/") {
			def = *it;
			break ;
		}
	}
	while (copy_uri != "/") {
		for (std::vector<Location>::iterator it = _info._loc.begin(); it !+ info._loc.end(); it++) {
			if (it->uri == copy_uri) {
				return *it;
			}
		}
		copy_uri.erase(copy_uri.find_last_of('/'), 1);
		copy_uri = copy_uri.substr(0, copy_uri.find_last_of('/') + 1);
	}
	return def;
}

int	ClientRequest::getStatus() const {
	return _status;
}

int	ClientRequest::getFile() const {
	return _file;
}