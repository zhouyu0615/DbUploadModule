#pragma once
#include "tbDbUpdateLog.h"

class CdbUpdateLog
{
	
public:
	CdbUpdateLog();
	~CdbUpdateLog();

	CdbUpdateLog(const CtbDbUpdateLog& tbLog);

public:
	long	 m_lId;
	CString	 m_strUdTbName;
	long	 m_lUdId;
	CString	 m_strUdOperType;
	CTime	 m_UdDatetime;


public:

};

