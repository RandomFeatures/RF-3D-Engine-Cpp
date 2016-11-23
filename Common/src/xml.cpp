/**************************************************
XML.cpp
Random Features 3D RPG Common Code

by Allen Halsted (26 Sept 2002)
Functions to simplfy some of the TinyXMLCode
**************************************************/


#include "strfunctions.h"
#include "tinyxml.h"
#include "XML.h"

int GetXMLDataInt(TiXmlElement *element, const char* name)
{
	if (name)
	{	
	  return StrToInt(((element->FirstChildElement( name ))->FirstChild()->ToText())->Value());
	}
	else
       return StrToInt((element->FirstChild()->ToText())->Value());
}

const char* GetXMLDataStr(TiXmlElement *element, const char* name)
{
	if (name)
	{
	  return ((element->FirstChildElement( name ))->FirstChild()->ToText())->Value();
	}
	else
	  return (element->FirstChild()->ToText())->Value();
	
}


float GetXMLDataFloat(TiXmlElement *element, const char* name)
{
	if (name)
	{	
	  return StrToFloat(((element->FirstChildElement( name ))->FirstChild()->ToText())->Value());
	}
	else
       return StrToFloat((element->FirstChild()->ToText())->Value());
}



TiXmlElement* GetXMLElement(TiXmlElement *element, const char* name)
{
  return (element->FirstChildElement( name ))->ToElement();	
}

TiXmlElement* GetXMLElement(TiXmlDocument *xmlDoc, const char* name)
{
	return (xmlDoc->FirstChild( name ))->ToElement();
}
