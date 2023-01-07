#ifndef CLIENT_REQUEST_HPP
#define CLIENT_REQUEST_HPP

#include "webserv.hpp"
#include "ServerInfo.hpp"

class	ClientRequest {

	public:
		ClientRequest(ServerInfo info, std::string request = "");
		~ClientRequest(void);

		int			checkSyntax();
		int			checkMethod();
		int			isMethod(std::string word)
		Location	getLoc();
		std::string	determinateFile();

	// 1: Verifier que la syntaxe du message est correct -> sinon regarder code erreur
	// 2: Verifier que la methode est autorise et taille client autorise -> sinon code erreur
	// 3: Determiner la location a utiliser
	// 4: Determiner le fichier

		int			getStatus() const;
		std::string	getFile() const;

	private:
		ServerInfo	_info;
		Location	_loc;
		std::string	_request;
		std::string	_method;
		std::string	_uri;
		std::string	_file;
		int			_status;

}

#endif
