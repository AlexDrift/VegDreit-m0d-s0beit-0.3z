/*
	@PROJECTNAME: Z_License
	@VERSION: 0.3
	@AUTHOR: Z0REK AKA THE_Z
*/

#pragma once

#include <Windows.h>
#include <iostream>
#include <nb30.h>
#include <math.h>

#pragma comment(lib,"Netapi32.lib")
#pragma comment(lib,"ws2_32.lib")

#define MACAddrSize 6
#define MAX_KEYS_IN_BASE 100

class ZLicense
{
private:
	int				getCPUID();
	DWORD			getNetworkID();
	unsigned char	getLanaEnum(PLANA_ENUM LanaEnum);
	unsigned char	getMACAddress(unsigned char LanaNum, unsigned char *MACAddress);
	char			*openURL(char* szURL);

public:
	DWORD			getSoftwareID();
	char			*getSoftwareKey(int iCode);
	bool			checkLicense(int iKey, char* szURL);
};

extern ZLicense *ZLic;