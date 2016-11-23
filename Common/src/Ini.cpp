#include "ini.h"

cIniFile::cIniFile()
{

}


cIniFile::cIniFile(std::string filename)
{
	m_strFileName = filename;
}

cIniFile::~cIniFile()
{
	
}


BOOL cIniFile::WriteString (std::string section,std::string key,std::string value)
{
	//write out a string to the ini file
	return (WritePrivateProfileString ( section.c_str(), key.c_str(),value.c_str(),m_strFileName.c_str()));
}


int cIniFile::ReadInteger (std::string section,std::string key,int def)
{
	//get an integer from the ini file
//	value = GetPrivateProfileInt ( section.c_str(), key.c_str(), def, m_strFileName.c_str());
	return GetPrivateProfileInt ( section.c_str(), key.c_str(), def, m_strFileName.c_str());
}


std::string cIniFile::ReadString (std::string section,std::string key)
{
	//get a std::string from the ini file
	char strBuffer[256];
	
	GetPrivateProfileString (section.c_str(),key.c_str(), NULL, strBuffer, 255, m_strFileName.c_str());
	
//	buffer = strBuffer;

//	delete []strBuffer;

	return strBuffer;
}

BOOL cIniFile::ReadBool (std::string section,std::string key)
{
  //get a true false value from the ini file
  std::string buffer;

  buffer = cIniFile::ReadString(section,key);
  LowerCase(buffer);
  return (buffer.compare("true")==0);
 
}
