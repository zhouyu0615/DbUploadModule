#pragma once
#include "DataProvider.h"
#include "Util.h"

class CXmlTransform
{

private:
	CDataProvider* m_pData;
public:
	CXmlTransform();
	~CXmlTransform();



public:
	void xmlTest();


	int CreateXmlUpdateFile();

};

