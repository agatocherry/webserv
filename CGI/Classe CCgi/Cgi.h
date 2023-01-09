/**********************************************************************************

	Déclaration de la classe CCgi

	But  :  Récupérer les variables d'environement 
	        Récupérer les valeurs d'un formulaire avec la méthode  :  Get  et Post

	Notes d'utilisation  :  Pour obtenir les valeurs des variables d'un formulaire 
							Il faut d'abbord appelé la fonction LoadFormVar
							Ensuite appeler la fonction GetVarValue 
							pour chaque variable du formulaire.
							--Pour plus de renseignements voir les commentaires à
							--la définition de ces fonctions

**********************************************************************************/

#pragma once
#include <Windows.h>
#include <math.h>

//Sous vc++.net
#include <iostream>
using namespace std;

//structure contenant les variables du formulaire
struct S_VARFORM
{
	char* tcName;
	char* tcVal;
	S_VARFORM* pNext;
};

#define METHOD_ERR 0
#define METHOD_POST 1
#define METHOD_GET 2

class CCgi
{
public:
	CCgi(void);
	~CCgi(void);

	bool GetClientIp(char* tcBuf,DWORD dwSize);
	bool LoadFormVar();
	bool GetVarValue(char* tcVarName,char* tcValue,DWORD dwSize);

	UINT GetMethod(){return m_uMethod;}

private:
	UINT m_uMethod;
	S_VARFORM* m_pVar;

	bool GetEnv(char* tcName,char* tcBuf,DWORD dwSize);
	void ConvertValue(char* tcVal);
	bool LoadVarFormPost();
	bool LoadVarFormGet();
};
