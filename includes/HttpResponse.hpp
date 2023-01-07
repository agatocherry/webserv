#ifndef HTTP_RESPONSE_HPP
#define HTTP_RESPONSE_HPP

#pragma once

#include "webserv.hpp"

class	HttpResponse {

	public:
		HttpResponse(std::string file, int status, int autoindex);
		~HttpResponse(void);

	// 1: Verifier si le ficher demande existe -> soit c'est un fichier, soit c'est un dossier et autoindex est "on", sinon status = 404
    // 2: Ouvrir le fichier ou generer Autoindex ou ouvrir fichier d'erreur si status >= 300 (appeler fonction qui renvoit un tableau des fichiers d'erreurs) -> mettre dans body
    // 3: Generer un Header avec HTTP/1.1, le status et OK ou ERROR
    // 4: Mettre une ligne Content_length avec la taille du body;
    // 5: Verifier s'il y a d'autres ligne obligatoires
    // 6: Ajouter le header et le body dans la variable response (attention a la syntaxe requise "\r\n"...)

		std::string	getResponse() const;

	private:
        int         _autoindex;
		int			_status;
		std::string	_file;

        std::header _header;
        std::string _body;
        std::string _response;

};

#endif
