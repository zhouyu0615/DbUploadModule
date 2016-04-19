#include "stdafx.h"
#include "CdbUpdateLog.h"


CdbUpdateLog::CdbUpdateLog()
{
	m_lId=0;
	m_strUdTbName="";
	m_lUdId=0;
	m_strUdOperType="";
	m_UdDatetime = CTime::GetCurrentTime();
}


CdbUpdateLog::~CdbUpdateLog()
{
}

CdbUpdateLog::CdbUpdateLog(const CtbDbUpdateLog& tbLog)
{
	this->m_lId =tbLog.m_Id ;
	this->m_strUdTbName = tbLog.m_ud_TbName;
	this->m_lUdId = tbLog.m_ud_id;
	this->m_strUdOperType = tbLog.m_ud_OperType;
	this->m_UdDatetime = tbLog.m_ud_Datetime;
}



TiXmlElement* CdbUpdateLog::GetDeleteXmlInfo()
{
	TiXmlElement* InfoNode = new TiXmlElement("InfoNode");

	InfoNode->LinkEndChild(CreateInfoNode("tbName", this->m_strUdTbName));

	InfoNode->LinkEndChild(CreateInfoNode("Id", this->m_lUdId));

	InfoNode->LinkEndChild(CreateInfoNode("DataTime", m_UdDatetime.Format(_T("%Y-%m-%d %H:%M:%S"))));

	return InfoNode;
}


