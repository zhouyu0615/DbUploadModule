
// DbUploadModuleDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DbUploadModule.h"
#include "DbUploadModuleDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CDbUploadModuleDlg �Ի���



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


// CDbUploadModuleDlg ��Ϣ�������

BOOL CDbUploadModuleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	ShowWindow(SW_MINIMIZE);

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������


	ListOnPaint();


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CDbUploadModuleDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CDbUploadModuleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDbUploadModuleDlg::ListOnPaint()
{
	//�����б�ؼ����//
	CRect rect1;
	m_UpdateList.GetWindowRect(&rect1);
	m_UpdateList.SetExtendedStyle(m_UpdateList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LBS_OWNERDRAWVARIABLE | LVS_EX_GRIDLINES);

	//����б�//
	m_UpdateList.DeleteAllItems();
	int nCount = m_UpdateList.GetItemCount();
	for (int i = nCount - 1; i >= 0; i--)
		m_UpdateList.DeleteColumn(i);




	//��ʼ���б���//
	m_UpdateList.InsertColumn(0, _T(""), LVCFMT_CENTER, 0, -1);       //�б�༭//
	m_UpdateList.InsertColumn(1, _T("���"), LVCFMT_CENTER, rect1.Width() / 10 * 1, -1);
	m_UpdateList.InsertColumn(2, _T("����"), LVCFMT_CENTER, rect1.Width() / 10*2, -1);
	m_UpdateList.InsertColumn(3, _T("��ID"), LVCFMT_CENTER, rect1.Width() / 10 * 2, -1);
	m_UpdateList.InsertColumn(4, _T("��������"), LVCFMT_CENTER, rect1.Width() / 10 * 2, -1);
	m_UpdateList.InsertColumn(5, _T("����ʱ��"), LVCFMT_CENTER, rect1.Width() / 10 * 3, -1);


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

		m_UpdateList.SetItemText(i, 1, str); //���
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
