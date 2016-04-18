#pragma once
#include <string>
#include "TinyXML/tinyxml.h"

template<typename T>
	std::string ToString(T val)
	{
		std::string str;
		std::stringstream ss;
		ss << val;
		ss >> str;
		return str;
	}

std::string MyCStringToStr(const CString& cstr);


TiXmlElement* CreateInfoNode(const std::string& NodeName, const std::string& NodeVal);
TiXmlElement* CreateInfoNode(const std::string& NodeName, const CString& NodeVal);
TiXmlElement* CreateInfoNode(const std::string& NodeName, int Nodeval);
TiXmlElement* CreateInfoNode(const std::string& NodeName, float Nodeval);





