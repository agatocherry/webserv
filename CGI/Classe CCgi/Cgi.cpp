/***************************************************************************************
	Définition des fonctions de la classe CCgi
***************************************************************************************/
#include ".\cgi.h"

//Constructeur
CCgi::CCgi(void)
{
	char tcMethod[10];
	m_pVar = NULL;

	if(!GetEnv("REQUEST_METHOD",tcMethod,10))
		m_uMethod = METHOD_ERR;
	else
		if(strcmp(strupr(tcMethod),"POST") == 0)
			m_uMethod = METHOD_POST;
		else
			if(strcmp(strupr(tcMethod),"GET") == 0)
				m_uMethod = METHOD_GET;
			else
				m_uMethod = METHOD_ERR;
}

//Destructeur
CCgi::~CCgi(void)
{
	S_VARFORM* pVar;
	while(m_pVar != NULL)
	{
		pVar = m_pVar;
		m_pVar = m_pVar->pNext;

		delete[] pVar->tcName;
		delete[] pVar->tcVal;
		delete pVar;
	}
}

//Obtenir l'adresse ip du client
//Retourne faux si échec
bool CCgi::GetClientIp(char* tcBuf,DWORD dwSize)
{
	return GetEnv("REMOTE_ADDR",tcBuf,dwSize);
}

//Charger les variables du formulaire envoyé au script cgi
//retourne faux si la méthode est différente de post ou de get
//retourne faux si toutes autres erreurs surviennent
bool CCgi::LoadFormVar()
{
	static bool bLoad = false;

	if(bLoad)
		return true;

	if(m_uMethod == METHOD_ERR)
		return false;

	if(m_uMethod == METHOD_POST)
		bLoad = LoadVarFormPost();
	else
		bLoad = LoadVarFormGet();

	return bLoad;
}

//Fonction pour obtenir la valeur d'une variable d'un formulaire
//Paramètres  :  tcVarName  -->  Le nom d la variable
//               tcValue  -->  Buffer qui recevra la valeur
//               dwSize  -->  Taille du buffer tcValue
//Note  -->  La fonction LoadVarForm doit préalablement être appelé avec succès.
bool CCgi::GetVarValue(char* tcVarName,char* tcValue,DWORD dwSize)
{
	S_VARFORM* pVar;
	if(m_pVar == NULL)
		return false;

	pVar = m_pVar;
	while(pVar != NULL && strcmp(tcVarName,pVar->tcName) != 0)
		pVar = pVar->pNext;

	if(pVar == NULL || strcmp(tcVarName,pVar->tcName) != 0)
		return false;

	if((DWORD)strlen(pVar->tcVal) + 1 > dwSize)
		return false;

	strcpy(tcValue,pVar->tcVal);

	return true;
}

//Fonctions pour obtenir les variables d'environements.
bool CCgi::GetEnv(char* tcName,char* tcBuf,DWORD dwSize)
{
	if(tcName == NULL || tcBuf == NULL || dwSize == 0)
		return false;

	if(GetEnvironmentVariable(tcName,NULL,0) > dwSize)
		return false;

	if(GetEnvironmentVariable(tcName,tcBuf,dwSize) == 0 && 
		GetLastError() == ERROR_ENVVAR_NOT_FOUND)
		return false;

	return true;
}

//Fonction pour charger les variables d'un formulaire : Post
bool CCgi::LoadVarFormPost()
{
	S_VARFORM* pVar;
	int i;
	char tcTmp[256];
	char tcLine[256];

	if(m_uMethod != METHOD_POST)
		return false;

	cin.getline(tcLine,256,'&');
	while(strcmp(tcLine,"") != 0)
	{
		pVar = new S_VARFORM;
		i = 0;
		while(i < (int)strlen(tcLine) && tcLine[i] != '=')
		{
			tcTmp[i] = tcLine[i];
			i++;
		}

		if(i == (int)strlen(tcLine))
		{
			delete pVar;
			return false;
		}

		tcTmp[i] = '\0';
		pVar->tcName = new char[(int)strlen(tcTmp) + 1];
		strcpy(pVar->tcName,tcTmp);
		pVar->tcVal = new char[((int)strlen(tcLine) + 1) - (int)strlen(tcTmp)];
		strcpy(pVar->tcVal,&tcLine[i + 1]);
		ConvertValue(pVar->tcVal);
		pVar->pNext = m_pVar;
		m_pVar = pVar;

		cin.getline(tcLine,256,'&');
	}

	return true;
}

//Fonction pour charger les variables d'un formulaire : Get
bool CCgi::LoadVarFormGet()
{
	S_VARFORM* pVar;
	char* pLine;
	char* pTmp;
	DWORD dwSize,i,j = 0;

	if(m_uMethod != METHOD_GET)
		return false;


	dwSize = GetEnvironmentVariable("QUERY_STRING",NULL,0);
	pLine = new char[dwSize + 1];
	if(!GetEnv("QUERY_STRING",pLine,dwSize + 1))
	{
		delete[] pLine;
		return false;
	}

	pTmp = new char[dwSize + 1];

	for(i = 0; i < dwSize; i++)
	{
		if(pLine[i] == '=')
		{
			pTmp[j] = '\0';
			pVar = new S_VARFORM;
			pVar->tcName = new char[(int)strlen(pTmp) + 1];
			strcpy(pVar->tcName,pTmp);

			//trouver la valeur
			i++;
			j = 0;
			while(i < dwSize && pLine[i] != '&')
			{
				pTmp[j] = pLine[i];
				i++;
				j++;
			}

			pTmp[j] = '\0';
			j = 0;

			pVar->tcVal = new char[(int)strlen(pTmp) + 1];
			strcpy(pVar->tcVal,pTmp);
			ConvertValue(pVar->tcVal);
			pVar->pNext = m_pVar;
			m_pVar = pVar;
		}
		else
		{
			pTmp[j] = pLine[i];
			j++;
		}
	}

	delete[] pLine;
	delete[] pTmp;

	return true;
}

//Fonction pour décortiquer une valeur
void CCgi::ConvertValue(char* tcVal)
{
	char tcEx[3];
	int nEx;
	int i,j,nNb = 0,nLen = (int)strlen(tcVal);

	tcEx[2] = '\0';

	for(i = 0; i < nLen; i++)
	{
		if(tcVal[i] == '%')
		{
			tcEx[0] = tcVal[i + 1];
			tcEx[1] = tcVal[i + 2];
			strupr(tcEx);
			nEx = 0;
			//Convertir l'exadécimal en décimal
			for (j = 0; j < 2; j++)
				nEx += ((tcEx[j]>57)? tcEx[j]-55 : tcEx[j]-48)*(int)pow(16,1 - j);
			tcVal[nNb] = (char)nEx;
			i+=2;
		}
		else
		{
			if(tcVal[i] == '+')
				tcVal[nNb] = ' ';
			else
				tcVal[nNb] = tcVal[i];
		}
		nNb++;
	}

	tcVal[nNb] = '\0';
}