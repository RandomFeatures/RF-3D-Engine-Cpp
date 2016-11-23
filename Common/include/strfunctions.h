/**************************************************
strfunctions.h
Random Features 3D RPG Common Code

by Allen Halsted (12 June 2002)
Header for my simple string manulipation routines
Overloaded function to take either str::string or char
**************************************************/


#ifndef STRFUNC_H
#define STRFUNC_H

#include "string"
#include "windows.h"
// Standard ANSI-C includes
#include <stdio.h>

// conversion of integers
void IntToStr(int integer,char* buff,int base);
void IntToStr(int integer,char* buff);
void IntToStr(int integer,std::string buff);

// conversion of strings
int StrToInt(char* buff);
int StrToInt(const char* buff);

int StrToFloat(char* buff);
int StrToFloat(const char* buff);

bool StrIsTrue(char* buff);
bool StrIsFalse(char* buff);
bool StrIsTrue(const char* buff);
bool StrIsFalse(const char* buff);


//string stuff
void LowerCase(std::string& buffer);
void LowerCase(char* buffer);
void UpperCase(std::string& buffer);
void UpperCase(char* buffer);
void stdStrToChar(std::string base, char *buffer);

char* BoolToStr(BOOL value);


void Upper(std::string &a_Data);
void Lower(std::string &a_Data);
void LTrim(std::string &a_Data);
void RTrim(std::string &a_Data);
void Trim(std::string &a_Data);


#endif