/**************************************************
strfunctions.cpp
Random Features 3D RPG Common Code

by Allen Halsted (12 June 2002)
simple string manulipation routines
Overloaded function to take either str::string or char
**************************************************/


#include "strfunctions.h"


// conversion of integers
void IntToStr(int integer,char* buff,int base)
{
	itoa(integer,buff,base);
}

void IntToStr(int integer,char* buff)
{
	itoa(integer,buff,10);
}


void IntToStr(int integer,std::string buff)
{
	char strtmp[256];
	
	itoa(integer,strtmp,10);
	
	buff = strtmp;

}

// conversion of strings
int StrToInt(char* buff)
{
	return atoi(buff);
}

int StrToInt(const char* buff)
{
	return atoi(buff);
}

int StrToFloat(char* buff)
{
	return atof(buff);
}

int StrToFloat(const char* buff)
{
	return atof(buff);
}


// lower case
void LowerCase(char* buffer)
{
	int len = strlen(buffer);

	for(int i = 0; i < len; i++)
	{
		buffer[i] = tolower(buffer[i]);
	}
}

void LowerCase(std::string& buffer)
{
	char strTemp[256];

	strcpy(strTemp, buffer.c_str());
	int len = strlen(strTemp);

	for(int i = 0; i < len; i++)
	{
		strTemp[i] = tolower(strTemp[i]);
	}
	buffer.assign(strTemp);
}

// upercase
void UpperCase(char* buffer)
{
	int len = strlen(buffer);

	for(int i = 0; i < len; i++)
	{
		buffer[i] = toupper(buffer[i]);
	}
}

void UpperCase(std::string& buffer)
{
	char strTemp[256];

	strcpy(strTemp, buffer.c_str());
	int len = strlen(strTemp);

	for(int i = 0; i < len; i++)
	{
		strTemp[i] = toupper(strTemp[i]);
	}
	buffer.assign(strTemp);

}


void stdStrToChar(std::string base, char *buffer)
{
  strcpy(buffer, base.c_str());
}


bool StrIsTrue(char* buff)
{
    LowerCase(buff);
	return (strcmp("true", buff) == 0);
}

bool StrIsFalse(char* buff)
{
	LowerCase(buff);
	return (strcmp("false", buff) == 0);

}


bool StrIsTrue(const char* buff)
{
    char tmpstr[64];
	strcpy(tmpstr, buff);
	LowerCase(tmpstr);
	return (strcmp("true", tmpstr) == 0);
}

bool StrIsFalse(const char* buff)
{
    char tmpstr[64];
	strcpy(tmpstr, buff);
	LowerCase(tmpstr);
	return (strcmp("false", tmpstr) == 0);
}

char* BoolToStr(BOOL value)
{
	if (value)
	{
		return "true";
	}
	else 
		return "false";
}


inline void Upper(std::string &a_Data)
{
//    std::transform(a_Data.begin(), a_Data.end(), a_Data.begin(),toupper);
}

inline void Lower(std::string &a_Data)
{
//	std::transform(a_Data.begin(), a_Data.end(), a_Data.begin(),tolower);
}

inline void LTrim(std::string &a_Data)
{
    a_Data.erase(0,a_Data.find_first_not_of(" "));
}

inline void RTrim(std::string &a_Data)
{
    a_Data.resize(a_Data.find_last_not_of(" ") + 1);
}

inline void Trim(std::string &a_Data)
{
	RTrim(a_Data);
	LTrim(a_Data);
}
