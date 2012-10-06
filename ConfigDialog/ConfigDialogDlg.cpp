
// ConfigDialogDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ConfigDialog.h"
#include "ConfigDialogDlg.h"
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


// CConfigDialogDlg �Ի���




CConfigDialogDlg::CConfigDialogDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CConfigDialogDlg::IDD, pParent)
	, input_prompt(0)
	, dy_adjust_frequency(0)
	, input_style(0)
	, embed_languagebar(0)
	, next_page(0)
	{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//��ʼ����Ա����
	this->dy_adjust_frequency=0;
	this->embed_languagebar=0;
	this->input_prompt=0;
	this->input_style=0;
	this->next_page=0;

	sec_input_prompt= L"input prompt";
	sec_dy_adjust_frequency=L"dynamic adjust frequency";
	sec_input_style=L"input style";
	sec_embed_languagebar=L"embed languagebar";
	sec_next_page=L"next page";

	key_input_prompt=L"input_prompt";
	key_dy_adjust_frequency=L"dy_adjust_frequency";
	key_input_style=L"input_style";
	key_embed_languagebar=L"embed_languagebar";
	key_next_page=L"next_page";
}

void CConfigDialogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CConfigDialogDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RADIO1, &CConfigDialogDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CConfigDialogDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CConfigDialogDlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &CConfigDialogDlg::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_RADIO5, &CConfigDialogDlg::OnBnClickedRadio5)
	ON_BN_CLICKED(IDC_RADIO6, &CConfigDialogDlg::OnBnClickedRadio6)
	ON_BN_CLICKED(IDC_RADIO7, &CConfigDialogDlg::OnBnClickedRadio7)
	ON_BN_CLICKED(IDC_RADIO8, &CConfigDialogDlg::OnBnClickedRadio8)
	ON_BN_CLICKED(IDC_RADIO9, &CConfigDialogDlg::OnBnClickedRadio9)
	ON_BN_CLICKED(IDOK, &CConfigDialogDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CHECK1, &CConfigDialogDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CConfigDialogDlg::OnBnClickedCheck2)
END_MESSAGE_MAP()


// CConfigDialogDlg ��Ϣ�������

BOOL CConfigDialogDlg::OnInitDialog()
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	this->readconfig(); //��ʼ���Ի����е�radio button ��״̬

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CConfigDialogDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CConfigDialogDlg::OnPaint()
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
HCURSOR CConfigDialogDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//������ʾ  ���ָ�
void CConfigDialogDlg::OnBnClickedRadio1()
	{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->input_prompt=1;
	}

//������ʾ  ��ʾ�ָ�
void CConfigDialogDlg::OnBnClickedRadio2()
	{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->input_prompt=2;
	}

//������ʾ �����ѡ��
void CConfigDialogDlg::OnBnClickedRadio3()
	{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->input_prompt=3;
	}

//������Ƶ ��
void CConfigDialogDlg::OnBnClickedRadio4()
	{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->dy_adjust_frequency=1;
	}

//������Ƶ  ��
void CConfigDialogDlg::OnBnClickedRadio5()
	{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->dy_adjust_frequency=2;
	}

//������ ��������
void CConfigDialogDlg::OnBnClickedRadio6()
	{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->input_style=1;
	}

//������ ���ո�����
void CConfigDialogDlg::OnBnClickedRadio7()
	{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->input_style=2;
	}

//Ƕ��������   ��
void CConfigDialogDlg::OnBnClickedRadio8()
	{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->embed_languagebar=1;
	}

//Ƕ��������  ��
void CConfigDialogDlg::OnBnClickedRadio9()
	{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->embed_languagebar=2;
	}


// ��ȡ�����ļ���ʼ���Ի���
void CConfigDialogDlg::readconfig(void)
	{

	wchar_t strBuff[256];
	//CString strFilePath=L"C:\\Users\\wtp\\Desktop\\config.ini";
	CString strFilePath;
	HWND   hWnd=*AfxGetMainWnd();
	
	GetCurrentDirectory(256,strBuff);  //��ȡ��ǰ·��
	strFilePath.Format(_T("%s//config.ini"),strBuff);
	
	this->dy_adjust_frequency=::GetPrivateProfileIntW(sec_dy_adjust_frequency,key_dy_adjust_frequency,0,strFilePath);
	switch(this->dy_adjust_frequency)
		{
	case 1:
		::CheckRadioButton(hWnd,IDC_RADIO4,IDC_RADIO5,IDC_RADIO4);
		break;
	case 2:
		::CheckRadioButton(hWnd,IDC_RADIO4,IDC_RADIO5,IDC_RADIO5);
		break;
	default:
		break;
		}
	
	this->embed_languagebar=::GetPrivateProfileIntW(sec_embed_languagebar,key_embed_languagebar,0,strFilePath);
	switch(this->embed_languagebar)
		{
	case 1:
		::CheckRadioButton(hWnd,IDC_RADIO8,IDC_RADIO9,IDC_RADIO8);
		break;
	case 2:
		::CheckRadioButton(hWnd,IDC_RADIO8,IDC_RADIO9,IDC_RADIO9);
	default:
		break;
		}

	this->input_prompt=::GetPrivateProfileIntW(sec_input_prompt,key_input_prompt,0,strFilePath);
	switch(this->input_prompt)
		{
	case 1:
		::CheckRadioButton(hWnd,IDC_RADIO1,IDC_RADIO3,IDC_RADIO1);
		break;
	case 2:
		::CheckRadioButton(hWnd,IDC_RADIO1,IDC_RADIO3,IDC_RADIO2);
		break;
	case 3:
		::CheckRadioButton(hWnd,IDC_RADIO1,IDC_RADIO3,IDC_RADIO3);
		break;
	default:
		break;
		}

	this->input_style=::GetPrivateProfileIntW( sec_input_style,key_input_style,0,strFilePath);
	switch(this->input_style)
		{
	case 1:
		::CheckRadioButton(hWnd,IDC_RADIO6,IDC_RADIO7,IDC_RADIO6);
		break;
	case 2:
		::CheckRadioButton(hWnd,IDC_RADIO6,IDC_RADIO7,IDC_RADIO7);
		break;
	default:
		break;
		}

	this->next_page=::GetPrivateProfileIntW(sec_next_page,key_next_page,0,strFilePath);
	switch(this->next_page)
		{
	case 1:
		((CButton*)GetDlgItem(IDC_CHECK1))->SetCheck(true);
		break;
	case 2:
		((CButton*)GetDlgItem(IDC_CHECK2))->SetCheck(true);
		break;
	case 3:
		((CButton*)GetDlgItem(IDC_CHECK1))->SetCheck(true);
		((CButton*)GetDlgItem(IDC_CHECK2))->SetCheck(true);
		break;
	default:
		break;
		}
	}


// �����Ի������ݲ����������ļ�
void CConfigDialogDlg::writeconfig(void)
	{

	CString val_input_prompt;
	CString val_dy_adjust_frequency;
	CString val_input_style;
	CString val_embed_languagebar;
	CString val_next_page;
	
	wchar_t strBuff[256];
	//CString strFilePath=L"C:\\Users\\wtp\\Desktop\\config.ini";
	CString strFilePath;
	
	GetCurrentDirectory(256,strBuff);  //��ȡ��ǰ·��
	strFilePath.Format(_T("%s//config.ini"),strBuff);

	val_input_prompt.Format(_T("%d"),this->input_prompt);
	::WritePrivateProfileString(sec_input_prompt,key_input_prompt,val_input_prompt,strFilePath);  //д��ini�ļ�����Ӧ�ֶ�

	val_dy_adjust_frequency.Format(_T("%d"),this->dy_adjust_frequency);
	::WritePrivateProfileString(sec_dy_adjust_frequency,key_dy_adjust_frequency,val_dy_adjust_frequency,strFilePath);

	val_input_style.Format(_T("%d"),this->input_style);
	::WritePrivateProfileString(sec_input_style,key_input_style,val_input_style,strFilePath); 

	val_embed_languagebar.Format(_T("%d"),this->embed_languagebar);
	::WritePrivateProfileString(sec_embed_languagebar,key_embed_languagebar,val_embed_languagebar,strFilePath); 

	val_next_page.Format(_T("%d"),this->next_page);
	::WritePrivateProfileString(sec_next_page,key_next_page,val_next_page,strFilePath); 

}

void CConfigDialogDlg::OnBnClickedOk()
	{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->writeconfig();
	CDialogEx::OnOK();
	}


void CConfigDialogDlg::OnBnClickedCheck1()
	{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(this->next_page==0||this->next_page==2)
		this->next_page+=1;
	else if(this->next_page==1||this->next_page==3)
		this->next_page-=1;
	}


void CConfigDialogDlg::OnBnClickedCheck2()
	{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(this->next_page==0||this->next_page==1)
		this->next_page+=2;
	else if(this->next_page==2||this->next_page==3)
		this->next_page-=2;
	}
