// tbDbUpdateLog.h : CtbDbUpdateLog ���ʵ��



// CtbDbUpdateLog ʵ��

// ���������� 2016��4��12�� ���ڶ�, 16:15

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
//#error ��ȫ���⣺�����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
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
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Long(pFX, _T("[Id]"), m_Id);
	RFX_Text(pFX, _T("[ud_TbName]"), m_ud_TbName);
	RFX_Long(pFX, _T("[ud_id]"), m_ud_id);
	RFX_Text(pFX, _T("[ud_OperType]"), m_ud_OperType);
	RFX_Date(pFX, _T("[ud_Datetime]"), m_ud_Datetime);

}
/////////////////////////////////////////////////////////////////////////////
// CtbDbUpdateLog ���

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


