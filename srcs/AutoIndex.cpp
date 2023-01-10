#include "../includes/AutoIndex.hpp"

AutoIndex::AutoIndex() {};
AutoIndex::~AutoIndex() {};

std::string	AutoIndex::renderPage(std::string directory, std::string path, int port, std::string host) {
	
	std::string	html =\
	"<!DOCTYPE html>\n\
    	<html>\n\
   			<head>\n\
            	<title>" + directory + "</title>\n\
    		</head>\n\
    		<body>\n\
    			<h1>Directory Index</h1>\n";
	/*
	Ouvrir le dossier qui se trouve dans "path"
	verifier que le dossier se soit ouvert sinon erreur
	pour chaque fichier/dossier dans le dossier ouvert :
		html += "<a href=\"http://" + host + ":" + port.str() + directory + "/" + (nom du fichier ou dossier) + "\">" + (nom du fichier ou dossier) + "</a>\n";
	*/
	html +=\
	"		</body>\n\
		</html>\n";
	return html;
}