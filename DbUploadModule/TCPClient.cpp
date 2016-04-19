#include "stdafx.h"
#include "TCPClient.h"

#define  SINGLE_SEND_MAX_LENGTH 4096

CTCPClient::CTCPClient()
{
	Init();
}

CTCPClient::CTCPClient(const CString& IpAddr, int port, const CString& filePath, const CString& fileName)
	:m_strDestIPAddr(IpAddr), m_nPort(port), m_FilePath(filePath), m_FileName(fileName)
{
	Init();
}

CTCPClient::~CTCPClient()
{
	//�ͷ�Socket��Դ
	WSACleanup();
}


void CTCPClient::Init()
{
	InitSocket();
	m_sendCompeletePercent = 0;
}

void CTCPClient::CreatePollThread()
{
	m_pWorkThread = new CThread(this);
	m_pWorkThread->SetThreadPriority(THREAD_PRIORITY_NORMAL);

}

void CTCPClient::StartPollThread()
{
	m_pWorkThread->Start();
	m_pWorkThread->SetThreadName(m_strDestIPAddr);
}
void CTCPClient::ResumePollThread()
{
	m_pWorkThread->Resume();
}
void CTCPClient::SuspendPollThread()
{
	m_pWorkThread->Suspend();
}


int CTCPClient::InitSocket()
{
	// ��ʼ��socket dll 
	WSADATA wd;
	if (WSAStartup(MAKEWORD(2, 1), &wd)!= 0)
	{
		TRACE("Init socket dll error!");
		return -1;
	}
	return 0;
}


void CTCPClient::Run()
{
	OpenSocket();
	if (Connect())
	{
		SendFile();
	}
	CloseSocket();
}


bool CTCPClient::OpenSocket()
{
	m_Socket = socket(AF_INET, SOCK_STREAM, 0);
	if (SOCKET_ERROR == m_Socket)
	{
		TRACE("Create Socket Error!");
		return false;
	}
	return true;
}

//���أ�TRUE--�������ӳɹ���FALSE--��������ʧ��
bool CTCPClient::Connect()
{
	struct sockaddr_in addr;
	int nErr;
	char cAnsiRemoteHost[255];

	addr.sin_family = AF_INET;
	addr.sin_port = htons(m_nPort);
	//�˴�Ҫ��˫�ֽ�ת���ɵ��ֽ�
	ZeroMemory(cAnsiRemoteHost, 255);
	WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, m_strDestIPAddr, wcslen(m_strDestIPAddr), cAnsiRemoteHost, wcslen(m_strRemoteHost), NULL, NULL);
	addr.sin_addr.S_un.S_addr = inet_addr(cAnsiRemoteHost);

	//�������ӳ�ʱʱ��//
	DWORD TimeOut = 600;
	setsockopt(m_Socket, SOL_SOCKET, SO_SNDTIMEO, (char *)&TimeOut, sizeof(TimeOut));

	nErr = connect(m_Socket, (struct sockaddr*)&addr, sizeof(addr));
	if (nErr == SOCKET_ERROR)
	{
		TRACE("����ʧ��\n");
		m_bIsconnected = FALSE;
		return FALSE;
	}
	//����ͨѶģʽΪ�첽ģʽ
	DWORD dwUl = 1;
	ioctlsocket(m_Socket, FIONBIO, &dwUl);
	TRACE("���ӳɹ�\n");
	m_bIsconnected = TRUE;

	return TRUE;
}


int CTCPClient::SendFile()
{
	CString  filePathName = m_FilePath + _T("/")+ m_FileName;

	FILE *fp = NULL;
	fp=fopen((LPSTR)(LPCTSTR)filePathName, "rb");
	
	if (fp==NULL)
	{
		TRACE("�ļ���ʧ��\n");
		return -1;
	}

	//�����ļ���//
	int len = SendData((LPSTR)(LPCTSTR)m_FileName, m_FileName.GetLength());
	if (len==m_FileName.GetLength())
	{
		TRACE("�ļ������ͳɹ�\n");
	}
	fseek(fp, 0, SEEK_END); //�ļ�ָ��ָ��ĩβ
	size_t fileSize = ftell(fp);//�õ��ļ���С
	fseek(fp, 0, SEEK_SET);//�ļ�ָ���Ƶ��ļ�ͷ//

	size_t sendLen = 0;	
	char fileBuff[SINGLE_SEND_MAX_LENGTH];
	while (sendLen<fileSize)
	{   
		size_t nRead=fread(fileBuff, sizeof(char), SINGLE_SEND_MAX_LENGTH, fp);
		size_t nSend=SendData(fileBuff, nRead);
		if ((nRead==nSend)&&(nRead!=0))
		{
			sendLen += nSend;
			m_sendCompeletePercent = sendLen * 100 / fileSize;
		}
		else
		{
			TRACE("����ʧ��\n");
			break;
		}
		memset(fileBuff, 0, SINGLE_SEND_MAX_LENGTH);
	}
	fclose(fp);
	return 0;
}

int CTCPClient::SendData(const char *p_SendBuff, int BuffLen)
{
	int nBytes = 0;
	nBytes = send(m_Socket, p_SendBuff, BuffLen, 0);
	if (nBytes == SOCKET_ERROR)
	{
		int nErrorCode = WSAGetLastError();
		TRACE("��������ʧ��:%d",nErrorCode);
		//�ر�Socket
		CloseSocket();
		m_bIsconnected = FALSE;
		return -1;
	}
	m_bIsconnected = TRUE;
	return nBytes;
}

bool CTCPClient::CloseSocket()
{
	//�ر�Socket���ͷ���Դ
	int nErr = closesocket(m_Socket);
	if (nErr == SOCKET_ERROR)
	{
		return FALSE;
	}
	m_bIsconnected = FALSE;
	return TRUE;
}

int CTCPClient::GetSendCompletePercent()
{
	
	return m_sendCompeletePercent;
}






