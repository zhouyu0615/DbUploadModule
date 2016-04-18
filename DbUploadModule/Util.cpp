#include "stdafx.h"
#include "Util.h"



std::string MyCStringToStr(const CString& cstr)
{
	USES_CONVERSION;
	std::string str(W2A(cstr));
	return str;
}


TiXmlElement* CreateInfoNode(const std::string& NodeName, const std::string& NodeVal)
{
	TiXmlText* Text = new TiXmlText(NodeVal);
	TiXmlElement* infoNode = new TiXmlElement(NodeName);
	infoNode->LinkEndChild(Text);

	return infoNode;
}

TiXmlElement* CreateInfoNode(const std::string& NodeName, const CString& NodeVal)
{
	return CreateInfoNode(NodeName, MyCStringToStr(NodeVal));
}

TiXmlElement* CreateInfoNode(const std::string& NodeName, int Nodeval)
{
	std::string strVal = ToString(Nodeval);

	return CreateInfoNode(NodeName, strVal);
}

TiXmlElement* CreateInfoNode(const std::string& NodeName, float Nodeval)
{
	std::string strVal = ToString(Nodeval);
	return CreateInfoNode(NodeName, strVal);
}



