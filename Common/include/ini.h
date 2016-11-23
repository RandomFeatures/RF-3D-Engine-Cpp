#ifndef INI_H
#define INI_H

#include "string"
#include "windows.h"
#include "strfunctions.h"
#include <stdio.h>

class cIniFile
{
public :

	//Constructor
	cIniFile();

	cIniFile(std::string filename);

	//what was that file name again??
	void GetFileName (std::string& filename) {filename=m_strFileName;};
	void SetFileName (std::string filename) {m_strFileName=filename;};
	void Create (std::string filename) {m_strFileName=filename;};

	//lets write out a simple string
	BOOL WriteString (std::string section,
					  std::string key,
					  std::string value);

	
	//read in a int
	int ReadInteger (std::string section,
					 std::string key,
					 int defaultValue =0);

	//read in a string
	std::string ReadString (std::string section,
						    std::string key);

	//read in a bool  true/false
	BOOL ReadBool (std::string section,std::string key);


	virtual ~cIniFile();

private :
	//my file name
	std::string m_strFileName;
};

#endif