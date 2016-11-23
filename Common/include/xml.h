#ifndef XML_H
#define XML_H


int GetXMLDataInt(TiXmlElement *element, const char* name);
const char* GetXMLDataStr(TiXmlElement *element, const char* name);
float GetXMLDataFloat(TiXmlElement *element, const char* name);
TiXmlElement* GetXMLElement(TiXmlElement *element, const char* name);
TiXmlElement* GetXMLElement(TiXmlDocument *xmlDoc, const char* name);

#endif
