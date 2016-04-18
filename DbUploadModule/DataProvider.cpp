#include "stdafx.h"
#include "DataProvider.h"


CRITICAL_SECTION Cs;
CDataProvider::CDataProvider()
{
	
}


CDataProvider::~CDataProvider()
{
	delete Instance;
	DeleteCriticalSection(&Cs);
}


void CDataProvider::InitDataProvider()
{
	
	ReadUdLogFromDb();
	ReadProParaFormDb();

}

CDataProvider* CDataProvider::Instance = NULL;
CDataProvider* CDataProvider::getInstance()
{
	InitializeCriticalSection(&Cs);
	if (Instance == NULL)
	{
		EnterCriticalSection(&Cs);
		if (Instance == NULL)
		{
			Instance = new CDataProvider();
		}
		LeaveCriticalSection(&Cs);
	}

	return Instance;
}



int CDataProvider::ExecutionSQL(const CString& strSql)
{
	CtbDbUpdateLog tbLog;
	try{
		if (tbLog.Open(CRecordset::dynaset)){
			tbLog.m_pDatabase->ExecuteSQL(strSql);
		}
		else{
			AfxMessageBox(_T("打开数据库失败！"));
			tbLog.Close();
			return 1;
		}
	}
	catch (CDBException *e){
		e->ReportError();
	}
	tbLog.Close();

	return 0;
}

void CDataProvider::ReadUdLogFromDb()
{

	CString strsql;
	strsql.Format(_T("select * from tbDbUpdateLog order by Id"));

	CtbDbUpdateLog tbLog;
	try{
		if (tbLog.IsOpen())
			tbLog.Close();
		if (!tbLog.Open(CRecordset::dynaset, strsql)){
			AfxMessageBox(_T("打开数据库失败！"));
			return;
		}
	}
	catch (CDBException *e){
		e->ReportError();
	}

	if (tbLog.IsBOF())
	{
		return;
	}

	m_vDbUpdateLog.clear();
	tbLog.MoveFirst();
	while (!tbLog.IsEOF()){
		CdbUpdateLog  tempLog(tbLog);
		m_vDbUpdateLog.push_back(tempLog);
		tbLog.MoveNext();
	}

	tbLog.Close();
}


void CDataProvider::ReadProParaFormDb()
{
	CString strsql;
	strsql.Format(_T("select * from tbProcessPara order by Id"));

	CtbProcessPara tbProPara;
	try{
		if (tbProPara.IsOpen())
			tbProPara.Close();
		if (!tbProPara.Open(CRecordset::dynaset, strsql)){
			AfxMessageBox(_T("打开数据库失败！"));
			return;
		}
	}
	catch (CDBException *e){
		e->ReportError();
	}

	if (tbProPara.IsBOF())
	{
		return;
	}

	m_MpProcessPara.clear();
	tbProPara.MoveFirst();
	while (!tbProPara.IsEOF()){
		CProcessPara  tempPara(tbProPara);
		m_MpProcessPara[tempPara.m_Id] = tempPara;
		tbProPara.MoveNext();
	}

	tbProPara.Close();

}





