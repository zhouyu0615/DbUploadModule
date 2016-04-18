#include "stdafx.h"
#include "ProcessPara.h"
#include <string>
#include <sstream>

#include "Util.h"


CProcessPara::CProcessPara()
{
	m_Id = 0;
	m_ProcessModuleId = 0;
	m_ProductionLineId = 0;
	m_strProductionLineName = _T("");
	m_strProcessModuleName = _T("");
	m_strPlcName = _T("");
	m_strDescription = _T("");
	m_ParaValue = 0;
	m_strParaName = _T("");
	m_IsConfig = 0;
	m_IsVisible = 0;
	m_ValueType = 0;
	m_strReadAddrIndex = _T("");
	m_strAddressType = _T("");
	m_PlcId = 0;
	m_strCreatedDateTime = _T("");
	m_strLastUpdatedDateTime = _T("");
	m_strUnit = _T("");
	m_strWriteAddrIndex = _T("");
	m_fSetValue = -3001;
	m_IsRecord = 0;
}


CProcessPara::~CProcessPara()
{
}




CProcessPara::CProcessPara(const CtbProcessPara& ProPara)
{
	m_Id = ProPara.m_Id;
	m_strCreatedDateTime = ProPara.m_CreatedDateTime.Format(_T("%Y-%m-%d %H:%M:%S"));
	m_strLastUpdatedDateTime = ProPara.m_LastUpdatedDateTime.Format(_T("%Y-%m-%d %H:%M:%S"));
	m_strProductionLineName = ProPara.m_ProductionLineName;
	m_strProcessModuleName = ProPara.m_ProcessModuleName;
	m_ProductionLineId = ProPara.m_ProductionLineId;
	m_ProcessModuleId = ProPara.m_ProcessModuleId;
	m_strPlcName = ProPara.m_PlcName;
	m_PlcId = ProPara.m_PLCId;
	m_strReadAddrIndex = ProPara.m_ReadAddressIndex;
	m_strWriteAddrIndex = ProPara.m_WriteAddressIndex;
	m_strUnit = ProPara.m_Units;
	m_strAddressType = ProPara.m_AddressType;
	m_ParaValue = ProPara.m_ParaValue;
	m_strParaName = ProPara.m_ParaName;
	m_strDescription = ProPara.m_Description;
	m_ValueType = ProPara.m_ValueType;
	m_IsConfig = ProPara.m_IsConfig;
	m_IsVisible = ProPara.m_IsVisible;

	m_IsRecord = ProPara.m_IsRecord;

}



CString CProcessPara::ConvertValTypeToString()
{
	switch (m_ValueType)
	{
	case VALUETYPE_BOOL:
		return _T("Bool");
	case VALUETYPE_BYTE:
		return _T("Byte");
	case VALUETYPE_SHORT:
		return _T("Short");
	case VALUETYPE_LONG:
		return _T("Long");
	case VALUETYPE_FLOAT:
		return _T("Float");
	case VALUETYPE_DOUBLE:
		return _T("Double");
	default:
		return _T("Null");
	}

}

CString CProcessPara::ConvertIsConfigToString()
{
	if (m_IsConfig)
	{
		return _T("是");
	}

	return _T("否");
	
}


CString CProcessPara::ConvertIsVisibleToString()
{
	if (m_IsVisible)
	{
		return _T("是");
	}

	return _T("否");
	
}



CString CProcessPara::ConvertIsRecordToString()
{

	if (m_IsRecord==TRUE)
	{
		return _T("是");
	}
	return _T("否");
}


CString CProcessPara::ConvertParaValueToString()
{

	CString strParaValue;
	switch (m_ValueType)
	{
	case CProcessPara::VALUETYPE_BOOL:
		strParaValue.Format(_T("%d"), (int)m_ParaValue);
		break;
	case CProcessPara::VALUETYPE_BYTE:
		strParaValue.Format(_T("%d"), (int)m_ParaValue);
		break;
	case CProcessPara::VALUETYPE_SHORT:
		strParaValue.Format(_T("%hd"), (short)m_ParaValue);
		break;
	case CProcessPara::VALUETYPE_LONG:
		strParaValue.Format(_T("%d"), (int)m_ParaValue);
		break;
	case CProcessPara::VALUETYPE_FLOAT:
		strParaValue.Format(_T("%.2f"), (float)m_ParaValue);
		break;
	case CProcessPara::VALUETYPE_DOUBLE:
		strParaValue.Format(_T("%.2lf"), (double)m_ParaValue);
		break;
	default:
		break;
	}
	return strParaValue;

}

CString CProcessPara::ConvertSetValueToString()
{
	CString strSetValue;

	switch (m_ValueType)
	{
	case CProcessPara::VALUETYPE_BOOL:
		strSetValue.Format(_T("%d"), (int)m_fSetValue);
		break;
	case CProcessPara::VALUETYPE_BYTE:
		strSetValue.Format(_T("%d"), (int)m_fSetValue);
		break;
	case CProcessPara::VALUETYPE_SHORT:
		strSetValue.Format(_T("%hd"), (short)m_fSetValue);
		break;
	case CProcessPara::VALUETYPE_LONG:
		strSetValue.Format(_T("%d"), (int)m_fSetValue);
		break;
	case CProcessPara::VALUETYPE_FLOAT:
		strSetValue.Format(_T("%.2f"), (float)m_fSetValue);
		break;
	case CProcessPara::VALUETYPE_DOUBLE:
		strSetValue.Format(_T("%.2lf"),(double) m_fSetValue);
		break;
	default:
		break;
	}
	return strSetValue;
}

int CProcessPara::SetParaValue(float fParaValue)
{
	//unsigned long *p = (unsigned long *)&m_ParaValue;
	//InterlockedExchange(p, fParaValue);

	m_ParaValue = fParaValue;
	return 0;
}

void CProcessPara::SetPreSetValue(float fSetValue)
{
	this->m_fSetValue = fSetValue;
}

int CProcessPara::GetReadAddrIndex()
{
	return _ttoi(m_strReadAddrIndex);
}


int CProcessPara::GetReadAddrByteIndex()
{
	float temp = _ttof(m_strReadAddrIndex);
	temp = temp * 10;
	int addIndex = temp / 10; //取十位为字节位置

	return addIndex;
}


//获取bit位在字节里面的偏移//
int CProcessPara::GetReadBitOffSet()
{
	float temp = _ttof(m_strReadAddrIndex);
	
	temp = temp * 10;
	int addrIndex = (int)temp;
	int offset = addrIndex % 10; //获取BIT的位置

	if (offset>=8)
	{
		offset = 0;
	}
	return offset;
}




int CProcessPara::GetWriteAddrByteIndex()
{
	float temp = _ttof(m_strWriteAddrIndex);
	temp = temp * 10;
	int addIndex = temp / 10; //取十位为字节位置

	return addIndex;
}
int CProcessPara::GetWriteBitOffSet()
{
	float temp = _ttof(m_strWriteAddrIndex);

	temp = temp * 10;
	int addrIndex = (int)temp;
	int offset = addrIndex % 10; //获取BIT的位置

	if (offset >= 8)
	{
		offset = 0;
	}
	return offset;
}



//把存储的字符串类型转化为枚举类型表示的数值//
int CProcessPara::GetAddrTypeInEmType()
{
	if (m_strAddressType == _T("MX"))
	{
		return ADDR_TYPE_BIT;
	}
	else if (m_strAddressType == _T("MB"))
	{
		return ADDR_TYPE_BYTE;
	}
	else if (m_strAddressType == _T("MW"))
	{
		return ADDR_TYPE_WORD;
	}
	else if (m_strAddressType == _T("MD"))
	{
		return ADDR_TYPE_DWORD;
	}

	return ADDR_TYPE_WORD; //默认为双字节类型//
}






TiXmlElement* CProcessPara::GetParaInfoXmlNode()
{

	TiXmlElement* InfoNode = new TiXmlElement("InfoNode");


	InfoNode->LinkEndChild(CreateInfoNode("tbName", "tbProcessPara"));

	InfoNode->LinkEndChild(CreateInfoNode("Id", this->m_Id));

	InfoNode->LinkEndChild(CreateInfoNode("ProductionLineId", this->m_ProductionLineId));
	InfoNode->LinkEndChild(CreateInfoNode("ProcessModuleId", this->m_ProcessModuleId));

	InfoNode->LinkEndChild(CreateInfoNode("CreatedDateTime", m_strCreatedDateTime));
	
	InfoNode->LinkEndChild(CreateInfoNode("LastUpdatedDateTime", m_strLastUpdatedDateTime));
	InfoNode->LinkEndChild(CreateInfoNode("ProductionLineName", m_strProductionLineName));
	InfoNode->LinkEndChild(CreateInfoNode("ProcessModuleName", m_strProcessModuleName));
	InfoNode->LinkEndChild(CreateInfoNode("m_strPlcName", m_strPlcName));
	InfoNode->LinkEndChild(CreateInfoNode("ParaValue", m_ParaValue));
	InfoNode->LinkEndChild(CreateInfoNode("SetValue", m_fSetValue));
	InfoNode->LinkEndChild(CreateInfoNode("ParaName", m_strParaName));
	InfoNode->LinkEndChild(CreateInfoNode("IsConfig", m_IsConfig));
	InfoNode->LinkEndChild(CreateInfoNode("IsRecord", m_IsRecord));

	InfoNode->LinkEndChild(CreateInfoNode("IsVisible", m_IsVisible));
	InfoNode->LinkEndChild(CreateInfoNode("PlcId", m_PlcId));
	InfoNode->LinkEndChild(CreateInfoNode("ReadAddrIndex", m_strReadAddrIndex));
	InfoNode->LinkEndChild(CreateInfoNode("AddressType", m_strAddressType));

	InfoNode->LinkEndChild(CreateInfoNode("WriteAddrIndex", m_strWriteAddrIndex));
	InfoNode->LinkEndChild(CreateInfoNode("Unit", m_strUnit));


	return InfoNode;
}





