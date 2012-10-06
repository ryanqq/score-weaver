
// ConfigDialogDlg.h : ͷ�ļ�
//

#pragma once


// CConfigDialogDlg �Ի���
class CConfigDialogDlg : public CDialogEx
{
// ����
public:
	CConfigDialogDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CONFIGDIALOG_DIALOG };

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
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedRadio5();
	afx_msg void OnBnClickedRadio6();
	afx_msg void OnBnClickedRadio7();
	afx_msg void OnBnClickedRadio8();
	afx_msg void OnBnClickedRadio9();
	// ��ȡ�����ļ���ʼ���Ի���
	void readconfig(void);
	// �����Ի������ݲ����������ļ�
	void writeconfig(void);
private:
	// ������ʾ��ֵΪ1��ʾ����ʾ��ֵΪ2��ʾ��ʾ�ָ���ֵΪ3��ʾ�����ѡ�֣���ʼֵΪ0.
	int input_prompt;
	// ��̬������Ƶ��ֵΪ1��ʾ�ǣ�ֵΪ2��ʾ�񣬳�ʼֵΪ0��
	int dy_adjust_frequency;
	// ������ֵΪ1��ʾ�������֣�ֵΪ2��ʾ���ո���֣���ʼֵΪ0��
	int input_style;
	// ״̬��Ƕ����������ֵΪ1��ʾ�ǣ�ֵΪ2��ʾ�񣬳�ʼֵΪ0��
	int embed_languagebar;

	CString sec_input_prompt;
	CString sec_dy_adjust_frequency;
	CString sec_input_style;
	CString sec_embed_languagebar;
	CString sec_next_page;

	CString key_input_prompt;
	CString key_dy_adjust_frequency;
	CString key_input_style;
	CString key_embed_languagebar;
	CString key_next_page;

public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
private:
	// ��ҳ��ֵΪ1ʱ��ʾ���ӺŵȺŽ��з�ҳ��ֵΪ2�Ǳ�ʾ�����ž�Ž��з�ҳ��ֵΪ3ʱ��ʾ2�߶����ԡ�
	int next_page;
	};
