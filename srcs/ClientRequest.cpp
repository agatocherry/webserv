#include "../includes/ClientRequest.hpp"

ClientRequest::ClientRequest(ServerInfo info, std::string request) : _info(info), _request(request), _status(200), _file("") {
	checkSyntax();
	determinateLoc();
	checkMethod();
	checkSize();
	determinateFile();
}

ClientRequest::~ClientRequest() {

}

int	ClientRequest::checkMethod() {
	if (_method == "GET" || !_loc.allow[0])
		_status = 405;
	if (_method == "POST" || !_loc.allow[1])
		_status = 405;
	if (_method == "DELETE" || !_loc.allow[2])
		_status = 405;
	// if (_method == "PUT" || !_loc.allow[3])
	// 	_status = 405;
	return _status;
}

int	ClientRequest::isMethod(std::string word) {
	if (word == "GET" || word == "POST" || word == "PUT" ||
		word == "HEAD" || word == "PATCH" || word == "DELETE" ||
		word == "CONNECT" || word == "OPTIONS" || word == "TRACE")
			return 1;
	return 0;
}

int	ClientRequest::checkSyntax() {
	
	if (!_request.length() || (_request.find("Host:") == std::string::npos && _request.find("HOST:") == std::string::npos)) {
		_status = 400;
		return _status;
	}

	std::string	firstLine = _request.substr(0, _request.find("\r\n") + 2);
	std::string	word = firstLine.substr(0, firstLine.find(" "));
	
	for (int count = 1; count < 4; count++) {
		if (count == 1) {
			if (!isMethod(word)) {
				_status = 400;
				return _status;
			}
			_method = word;
		}
		if (count == 2) {
			_uri = word;
		}
		if (count == 3) {
			if (word != "HTTP/1.1\r\n") {
				_status = 400;
				return _status;
			}
		}
		firstLine.erase(0, word.length() + 1);
		word = firstLine.substr(0, firstLine.find(" "));
	}

	std::string copy_request = _request;
	std::string	bodyLine;
	std::string	header_field;
	std::string	value;
	int			body_size = 0;

	copy_request.erase(0, copy_request.find("\r\n") + 2);
	bodyLine = copy_request.substr(0, copy_request.find("\r\n") + 2);
	
	while (bodyLine.length() && bodyLine != "\r\n") {
		if (bodyLine.find(":") == std::string::npos) {
			_status = 400;
			return _status;
		}
		
		header_field = bodyLine.substr(0, bodyLine.find(":"));
		value = bodyLine.substr(bodyLine.find(":") + 1);

		if (value.find("\r\n") == std::string::npos || !header_field.length() || !value.length()) {
			_status = 400;
			return _status;
		}

		if (header_field.find("Content-Length") != std::string::npos || header_field.find("CONTENT-LENGTH") != std::string::npos) {
			if (value.front() == ' ')
				value.erase(0, 1);
			body_size = atoi(value);
		}

		copy_request.erase(0, copy_request.find("\r\n") + 2);
		bodyLine = copy_request.substr(0, copy_request.find("\r\n") + 2);
	}

	if (!bodyLine.length())
		return 200;
	
	copy_request.erase(0, 2);
	if (copy_request.size() != body_size) {
		_status = 400;
		return _status;
	}

	return 200;
}

int	ClientRequest::checkSize() {
	return _status;
}

std::string	ClientRequest::determinateFile() {
	std::string	file_uri = _uri.substr(_loc.uri.lenght());

	_file = _loc.root + file_uri;
	if (!_info.getAutoIndex() && _file.back() == '/') {
		if (_loc.index.size() && _loc.index != "")
			_file += _loc.index;
		else
			_file += "index.html";
	}
	return _file;
}

int	ClientRequest::determinateLoc() {
	std::string	ext;
	std::string	tmp_uri;
	std::vector<Location>	tmp_vec = _info.getLoc();

	_loc.root = _info.getRoot();
	_loc.index = _info.getIndex();
	_loc.uri = "/";
	_loc.allow[0] = _info.getAllow("GET");
	_loc.allow[1] = _info.getAllow("POST");
	_loc.allow[2] = _info.getAllow("DELETE");
	_loc.clientSize = _info.getClientSize();

	if (_uri.find(".") != std::string::npos)
		ext = _uri.substr(_uri.find("."));
	_uri.erase(_uri.find_last_of('/'));
	tmp_uri = _uri;

	while (tmp_vec.size() != 0) {
		int	loop = 1;
		for (std::vector<Location>::iterator it = tmp_vec.begin(); it != tmp_vec.end() && loop; it++) {
			if (_uri == it->uri || ext == it->uri) {
				if (it->root.size())
					_loc.root = it->root;
				if (it->index.size())
					_loc.index = it->index;
				if (it->clientSize != _loc.clientSize)
					_loc.clientSize = it->clientSize;
				if (it->cgi.size())
					_loc.cgi = it->cgi;
				if (it->allow[0] || it->allow[1] || it->allow[2]) {
					_loc.allow[0] = it->allow[0];
					_loc.allow[1] = it->allow[1];
					_loc.allow[2] = it->allow[2];
				}
				if (ext == it->uri)
					return _status;
				tmp_vec = it->loc;
				loop = 0;
				_uri = tmp_uri;
			}
		}
		if (loop)
			_uri.erase(_uri.find_last_of('/') + 1);
	}
	return _status;
}

int	ClientRequest::getStatus() const {
	return _status;
}

int	ClientRequest::getFile() const {
	return _file;
}