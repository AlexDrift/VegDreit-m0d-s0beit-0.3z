/*
	@PROJECTNAME: Z_License
	@VERSION: 0.3
	@AUTHOR: Z0REK AKA THE_Z
*/

#include "z_license.h"

char* ZLicense::getSoftwareKey(int iCode)
{
	if (iCode > 2000000000)
		return "CODE_TOO_HIGH";

	char* szEncrypted = new char[30];
	char* szAlphabet = "QWER12345TYUIOPASDFG67890HJKLZXCVBNM";

	for (int i = 0; i < 29; i++)
	{
		szEncrypted[i] = szAlphabet[((iCode ^ i) * 3) & 0x1D];
		if (i % 5 <= 0 && i != 0)
		{
			i++;
			szEncrypted[i] = '-';
		}
	}
	szEncrypted[29] = '\0';

	return szEncrypted;
}

DWORD ZLicense::getSoftwareID()
{
	DWORD Result = 0;

	Result += getCPUID();
	Result += getNetworkID();
	Result -= (Result - (getCPUID() & 0x1D)) * ((DWORD)floor(log10(abs((int)Result))) + 1);

	return ~Result;
}

bool ZLicense::checkLicense(int iKey, char* szURL)
{
	bool bRegistered = false;

	if (strcmp(szURL, "none"))
	{
		char *szKeys[MAX_KEYS_IN_BASE] = { NULL };
		int iKeys = 0;

		szKeys[iKeys] = strtok(openURL(szURL), "/");

		while (szKeys[iKeys] != NULL)
		{
			iKeys++;
			szKeys[iKeys] = strtok(NULL, "/");
		}

		for (int i = 0; i < iKeys; i++)
			if (atoi(szKeys[i]) == getSoftwareID())
				bRegistered = true;
	}
	else 
		bRegistered = true;

	if (getSoftwareID() == NULL)
		bRegistered = false;

	if ( bRegistered == false || strcmp(getSoftwareKey(getSoftwareID()), getSoftwareKey(iKey)) )
		return false;

	return true;
}

//

int ZLicense::getCPUID()
{
	int _cpu_id = 0;
	__asm
	{
		pusha
			xor eax, eax
			inc eax
			cpuid
			mov eax, _cpu_id
			popa
	}
	return _cpu_id;
}

unsigned char ZLicense::getLanaEnum(PLANA_ENUM LanaEnum)
{
	NCB LanaEnumNCB;
	FillMemory(&LanaEnumNCB, sizeof(LanaEnumNCB), 0);
	LanaEnumNCB.ncb_buffer = (PUCHAR) LanaEnum;
	LanaEnumNCB.ncb_length = sizeof(LANA_ENUM);
	LanaEnumNCB.ncb_command = (UCHAR) NCBENUM;
	Netbios(&LanaEnumNCB);
	return LanaEnumNCB.ncb_cmd_cplt;
}

unsigned char ZLicense::getMACAddress(unsigned char LanaNum, unsigned char *MACAddress)
{
	unsigned char Result;
	PADAPTER_STATUS AdapterStatus;
	NCB StatNCB;

	FillMemory(&StatNCB, sizeof(StatNCB), 0);
	StatNCB.ncb_lana_num = LanaNum;
	StatNCB.ncb_command = NCBRESET;

	Netbios(&StatNCB);

	FillMemory(&StatNCB, sizeof(StatNCB), 0);
	StatNCB.ncb_length = sizeof(ADAPTER_STATUS) + 255 * sizeof(NAME_BUFFER);
	AdapterStatus = (PADAPTER_STATUS) malloc(StatNCB.ncb_length);

	FillMemory(MACAddress, MACAddrSize*sizeof(unsigned char), 0);
	StatNCB.ncb_buffer = (PUCHAR) AdapterStatus;

	MoveMemory(StatNCB.ncb_callname, "*              ", 16);
	StatNCB.ncb_lana_num = LanaNum;
	StatNCB.ncb_command = NCBASTAT;

	Netbios(&StatNCB);

	Result = StatNCB.ncb_cmd_cplt;

	if (Result == NRC_GOODRET)
		MoveMemory(MACAddress, AdapterStatus, MACAddrSize*sizeof(unsigned char));

	free(AdapterStatus);

	return Result;
}

DWORD ZLicense::getNetworkID()
{
	LANA_ENUM LanaEnum;
	unsigned char MACAddress[MACAddrSize];
	DWORD Result;
	Result = 0;

	if (getLanaEnum(&LanaEnum) == NRC_GOODRET)
		if ((unsigned char) LanaEnum.length > 0)
			if (getMACAddress((unsigned char) LanaEnum.lana[0], MACAddress) == NRC_GOODRET)
				Result = *(DWORD*) MACAddress ^ *(DWORD*) (MACAddress + 2);

	return Result;
}

char* ZLicense::openURL(char* szURL)
{
	WSADATA lpWSAData;
	SOCKET s;

	if (WSAStartup(MAKEWORD(1, 1), &lpWSAData) != 0) return(NULL);

	char *http_host = new char[128];
	int port_num = 80;
	char *http_path = NULL;
	char *pch = strchr(http_host, ':');

	strcpy(http_host, szURL);

	if (!pch)
	{
		pch = strchr(http_host, '/');

		if (pch)
		{
			*pch = 0;
			http_path = strdup(pch + 1);
		}
		else 
			http_path = strdup("");
	}
	else
	{
		*pch = 0; 
		pch++;

		char *pch1 = strchr(pch, '/');

		if (pch1)
		{
			*pch1 = 0;
			http_path = strdup(pch1 + 1);
		}
		else 
			http_path = strdup("");

		port_num = atoi(pch);

		if (port_num == 0) port_num = 80;
	}

	struct hostent* hp;
	if (!(hp = gethostbyname(http_host)))
	{
		free(http_host);
		free(http_path);
		return(NULL);
	}

	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s == INVALID_SOCKET)
	{
		free(http_host);
		free(http_path);
		return(NULL);
	}

	struct sockaddr_in ssin;

	memset((char *) &ssin, 0, sizeof(ssin));
	ssin.sin_family = AF_INET;

	ssin.sin_addr.S_un.S_un_b.s_b1 = hp->h_addr[0];
	ssin.sin_addr.S_un.S_un_b.s_b2 = hp->h_addr[1];
	ssin.sin_addr.S_un.S_un_b.s_b3 = hp->h_addr[2];
	ssin.sin_addr.S_un.S_un_b.s_b4 = hp->h_addr[3];
	ssin.sin_port = htons(port_num);

	if (connect(s, (struct sockaddr *)&ssin, sizeof(ssin)) == -1)
	{
		free(http_host);
		free(http_path);
		return(NULL);
	}

	char *query = (char*) malloc(2048);
	strcpy(query, "GET /");
	strcat(query, http_path);
	strcat(query, " HTTP/1.0\nHost: ");
	strcat(query, http_host);
	strcat(query, "\nUser-agent: Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1)");
	strcat(query, "\nAccept: */*\n\n");

	int cnt = send(s, query, strlen(query), 0);
	free(http_host);
	free(http_path);
	free(query);

	if (cnt == SOCKET_ERROR) 
		return(NULL);

	cnt = 1;

	int size = 1024 * 1024; // 1Mb
	char *result = (char*) malloc(size);

	strcpy(result, "");

	char *result_ptr = result;

	while (cnt != 0 && size > 0)
	{
		cnt = recv(s, result_ptr, sizeof(size), 0);
		if (cnt > 0)
		{
			result_ptr += cnt;
			size -= cnt;
		}
	}

	*result_ptr = 0;

	WSACleanup();

	strcpy(result, strstr(result, "\r\n\r\n") + 4);

	return(result);
}