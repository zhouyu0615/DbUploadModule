
// DbUploadModuleDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DbUploadModule.h"
#include "DbUploadModuleDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDbUploadModuleDlg 对话框



CDbUploadModuleDlg::CDbUploadModuleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDbUploadModuleDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	
	m_pdataP = CDataProvider::getInstance();
	
	m_pdataP->InitDataProvider();

}

void CDbUploadModuleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_UpdateList);
}

BEGIN_MESSAGE_MAP(CDbUploadModuleDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_BtnStart, &CDbUploadModuleDlg::OnBnClickedBtnstart)
END_MESSAGE_MAP()


// CDbUploadModuleDlg 消息处理程序

BOOL CDbUploadModuleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	ShowWindow(SW_MINIMIZE);

	// TODO:  在此添加额外的初始化代码


	ListOnPaint();


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDbUploadModuleDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDbUploadModuleDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CDbUploadModuleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDbUploadModuleDlg::ListOnPaint()
{
	//设置列表控件风格//
	CRect rect1;
	m_UpdateList.GetWindowRect(&rect1);
	m_UpdateList.SetExtendedStyle(m_UpdateList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LBS_OWNERDRAWVARIABLE | LVS_EX_GRIDLINES);

	//清空列表//
	m_UpdateList.DeleteAllItems();
	int nCount = m_UpdateList.GetItemCount();
	for (int i = nCount - 1; i >= 0; i--)
		m_UpdateList.DeleteColumn(i);




	//初始化列表区//
	m_UpdateList.InsertColumn(0, _T(""), LVCFMT_CENTER, 0, -1);       //列标编辑//
	m_UpdateList.InsertColumn(1, _T("序号"), LVCFMT_CENTER, rect1.Width() / 10 * 1, -1);
	m_UpdateList.InsertColumn(2, _T("表名"), LVCFMT_CENTER, rect1.Width() / 10*2, -1);
	m_UpdateList.InsertColumn(3, _T("行ID"), LVCFMT_CENTER, rect1.Width() / 10 * 2, -1);
	m_UpdateList.InsertColumn(4, _T("更改类型"), LVCFMT_CENTER, rect1.Width() / 10 * 2, -1);
	m_UpdateList.InsertColumn(5, _T("更改时间"), LVCFMT_CENTER, rect1.Width() / 10 * 3, -1);


	int temp = 0;
	LV_ITEM litem;
	litem.mask = LVIF_TEXT;
	litem.iSubItem = 0;
	litem.pszText = _T("");

	temp = m_pdataP->m_vDbUpdateLog.size();
	for (int i = 0; i < temp; i++)
	{
		litem.iItem = i;
		m_UpdateList.InsertItem(&litem);

		CString str;
		str.Format(_T("%d"), i + 1);

		m_UpdateList.SetItemText(i, 1, str); //序号
		m_UpdateList.SetItemText(i, 2, m_pdataP->m_vDbUpdateLog[i].m_strUdTbName);

		str.Format(_T("%d"), m_pdataP->m_vDbUpdateLog[i].m_lUdId);
		m_UpdateList.SetItemText(i, 3, str);
		m_UpdateList.SetItemText(i, 4, m_pdataP->m_vDbUpdateLog[i].m_strUdOperType);

		str= m_pdataP->m_vDbUpdateLog[i].m_UdDatetime.Format("%Y-%m-%d %H:%M:%S");
		m_UpdateList.SetItemText(i, 5, str);
		
	}

}



void CDbUploadModuleDlg::OnBnClickedBtnstart()
{
	m_xmlTest.CreateXmlUpdateFile();
	//m_xmlTest.xmlTest();
}
