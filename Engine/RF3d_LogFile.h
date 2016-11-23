#ifndef RF3DLOG_H
#define RF3DLOG_H

#include "string"
#include "windows.h"
// Standard ANSI-C includes
#include <stdio.h>
//#include "ListControl.h"

class cLogFile
{
public :

	
//	List <std::string> m_strList;	
	
	std::string DebugLog;

	void Create(std::string filename);
	void Close();
	void LogDebug(std::string LogEntry);
	void LogDebug(char* LogEntry);

	//lets write out a simple string
	BOOL Log (std::string LogEntry);
	BOOL Log (char* LogEntry);
	BOOL Log (std::string Name, int Value);
	BOOL Log (char* Name, int Value);
	BOOL Log (char* Name, std::string LogEntry);
	BOOL Log (char* Name, char* LogEntry);
	//write out an int
	BOOL Log (int LogEntry);
	
	

private :
	//my file name
	std::string m_strFileName;
	FILE *m_logfile;

	void WriteTimeStamp();

};


#endif