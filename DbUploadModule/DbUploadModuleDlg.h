
// DbUploadModuleDlg.h : ͷ�ļ�
//

#pragma once

#include "DataProvider.h"
#include "SettingDlg.h"
#include "afxcmn.h"

#include "XmlTransform.h"

// CDbUploadModuleDlg �Ի���
class CDbUploadModuleDlg : public CDialogEx
{
// ����
public:
	CDbUploadModuleDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DBUPLOADMODULE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnstart();


	void ListOnPaint();

private:
	CSettingDlg m_setDlg;

	CDataProvider*  m_pdataP;
public:
	CListCtrl m_UpdateList;

	CXmlTransform m_xmlTest;
};
