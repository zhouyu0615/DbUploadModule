
// DbUploadModuleDlg.h : 头文件
//

#pragma once

#include "DataProvider.h"
#include "SettingDlg.h"
#include "afxcmn.h"

#include "XmlTransform.h"

// CDbUploadModuleDlg 对话框
class CDbUploadModuleDlg : public CDialogEx
{
// 构造
public:
	CDbUploadModuleDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_DBUPLOADMODULE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
