#include "RF3d_LogFile.h"
#include "strfunctions.h"
#include <time.h>


void cLogFile::Create(std::string filename)
 {
	m_strFileName =  filename;

	//	const char* cBuffer = "RF3d RPG Engine\n";
	std::string cBuffer = "Random Features 3D RPG Engine\n\n";

    // Open file, write size and data
    if((m_logfile = fopen(filename.c_str(), "w")) != NULL) 
	{
      fwrite(cBuffer.c_str(), 1, cBuffer.length(), m_logfile );
    }


 }


void cLogFile::Close()
{
//	m_strList.Clear();
	fclose(m_logfile);
}


void cLogFile::WriteTimeStamp()
{
// write the current time stamp into the log file
	char tstr[50];	
    // Write time into log
    struct tm *pTime;
    time_t ltime; time(&ltime);
    pTime = localtime( &ltime );
    sprintf(tstr, "%d:%d:%d :  ", pTime->tm_hour, pTime->tm_min, pTime->tm_sec);

	fwrite(tstr,1,strlen(tstr), m_logfile);


}

//log receives a std:string
BOOL cLogFile::Log (std::string LogEntry)
{
	if (m_logfile)
	{
		char strTemp[256];

		sprintf(strTemp, "%s\n", LogEntry.c_str());

		WriteTimeStamp();
		fwrite(strTemp, 1, strlen(strTemp), m_logfile );

		//In Memory value
		LogDebug(strTemp);

		fflush(m_logfile);

		return TRUE;
	}
	else return FALSE;
}

//log receives a name = value pair for an int with std::string
BOOL cLogFile::Log (std::string Name, int Value)
{
	if (m_logfile)
	{
		char strTemp[256];

		sprintf(strTemp, "%s = %d\n", Name.c_str(), Value);

    	WriteTimeStamp();
		fwrite(strTemp,1,strlen(strTemp),m_logfile);

		//In Memory value
		LogDebug(strTemp);

		fflush(m_logfile);

		return TRUE;
	}
	else return FALSE;
}


//log receives a name = value pair for an int with char
BOOL cLogFile::Log (char* Name, int Value)
{
	if (m_logfile)
	{
		char strTemp[256];

		sprintf(strTemp, "%s = %d\n", Name, Value);

    	WriteTimeStamp();
		fwrite(strTemp,1,strlen(strTemp),m_logfile);

		//In Memory value
		LogDebug(strTemp);

		fflush(m_logfile);

		return TRUE;
	}
	else return FALSE;
}


//log receives a char
BOOL cLogFile::Log (char* LogEntry)
{
	if (m_logfile)
	{
		char strTemp[256];

        sprintf(strTemp, "%s\n", LogEntry);

        WriteTimeStamp();
		fwrite(strTemp, 1, strlen(strTemp), m_logfile );

		//In Memory value
		LogDebug(strTemp);

		fflush(m_logfile);
		return TRUE;
	}
	else return FALSE;
}


//log receives a int
BOOL cLogFile::Log (int LogEntry)
{

	if (m_logfile)
	{
		char strTemp[25];
		sprintf(strTemp, "%d\n", LogEntry);

        WriteTimeStamp();
		fwrite(strTemp,1,strlen(strTemp),m_logfile);

		//In Memory value
		LogDebug(strTemp);
		
		fflush(m_logfile);

		return TRUE;
	}
	else return FALSE;
}

BOOL cLogFile::Log (char* Name, std::string LogEntry)
{
	if (m_logfile)
	{
		char strTemp[256];
		sprintf(strTemp, "%s = %s\n", Name, LogEntry.c_str());


    	WriteTimeStamp();
		fwrite(strTemp,1,strlen(strTemp),m_logfile);

		//In Memory value
		LogDebug(strTemp);

		fflush(m_logfile);

		return TRUE;
	}
	else return FALSE;


}

BOOL cLogFile::Log (char* Name, char* LogEntry)
{
	if (m_logfile)
	{
		char strTemp[256];
	
		sprintf(strTemp, "%s = %s\n", Name, LogEntry);

    	WriteTimeStamp();
		fwrite(strTemp,1,strlen(strTemp),m_logfile);

		//In Memory value
		LogDebug(strTemp);

		fflush(m_logfile);

		return TRUE;
	}
	else return FALSE;


}


void cLogFile::LogDebug(std::string LogEntry)
{
//	m_strList.Add(LogEntry);
}

void cLogFile::LogDebug(char* LogEntry)
{
		std::string tmpstr = LogEntry;
//		m_strList.Add(tmpstr);
}
