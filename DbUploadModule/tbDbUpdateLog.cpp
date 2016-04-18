// tbDbUpdateLog.h : CtbDbUpdateLog 类的实现



// CtbDbUpdateLog 实现

// 代码生成在 2016年4月12日 星期二, 16:15

#include "stdafx.h"
#include "tbDbUpdateLog.h"
IMPLEMENT_DYNAMIC(CtbDbUpdateLog, CRecordset)

CtbDbUpdateLog::CtbDbUpdateLog(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_Id = 0;
	m_ud_TbName = "";
	m_ud_id = 0;
	m_ud_OperType = "";
	m_ud_Datetime;
	m_nFields = 5;
	m_nDefaultType = dynaset;
}
//#error 安全问题：连接字符串可能包含密码。
// 此连接字符串中可能包含明文密码和/或其他重要
// 信息。请在查看完此连接字符串并找到所有与安全
// 有关的问题后移除 #error。可能需要将此密码存
// 储为其他格式或使用其他的用户身份验证。
CString CtbDbUpdateLog::GetDefaultConnect()
{
	return _T("DSN=xfcj_SQLSERVER;UID=sa;PWD=123456;APP=Microsoft\x00ae Visual Studio\x00ae 2013;WSID=ZHOUYU-PC");
}

CString CtbDbUpdateLog::GetDefaultSQL()
{
	return _T("[dbo].[tbDbUpdateLog]");
}

void CtbDbUpdateLog::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() 和 RFX_Int() 这类宏依赖的是
// 成员变量的类型，而不是数据库字段的类型。
// ODBC 尝试自动将列值转换为所请求的类型
	RFX_Long(pFX, _T("[Id]"), m_Id);
	RFX_Text(pFX, _T("[ud_TbName]"), m_ud_TbName);
	RFX_Long(pFX, _T("[ud_id]"), m_ud_id);
	RFX_Text(pFX, _T("[ud_OperType]"), m_ud_OperType);
	RFX_Date(pFX, _T("[ud_Datetime]"), m_ud_Datetime);

}
/////////////////////////////////////////////////////////////////////////////
// CtbDbUpdateLog 诊断

#ifdef _DEBUG
void CtbDbUpdateLog::AssertValid() const
{
	CRecordset::AssertValid();
}

void CtbDbUpdateLog::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


