#pragma once
#include <vector>
#include <map>

#include "tbDbUpdateLog.h";
#include "CDbUpdateLog.h"
#include "tbProcessPara.h"
#include "ProcessPara.h"


class CDataProvider
{
private:
	CDataProvider();
	~CDataProvider();
	CDataProvider(const CDataProvider&);
	CDataProvider& operator = (const CDataProvider&);


	static CDataProvider* Instance ;
	
public:

	static CDataProvider* getInstance();

	void InitDataProvider();

	void ReadUdLogFromDb();
	void ReadProParaFormDb();

	int ExecutionSQL(const CString& strSql);
	 

	std::vector<CdbUpdateLog> m_vDbUpdateLog;
	std::map<int,CProcessPara> m_MpProcessPara;



};

