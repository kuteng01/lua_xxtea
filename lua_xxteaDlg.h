
// lua_xxteaDlg.h : ͷ�ļ�
//

#pragma once
#include <vector>

// Clua_xxteaDlg �Ի���
class Clua_xxteaDlg : public CDialogEx
{
// ����
public:
	Clua_xxteaDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_LUA_XXTEA_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	typedef std::vector<CString> LuaFileVector;
// ʵ��
protected:
	HICON m_hIcon;

	//ԭʼ�ļ�����·��
	LuaFileVector vFilePathList;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedEncrypt();
	afx_msg void OnBnClickedDecrypt();
	void OnAddContentEdit(CString title, CString content);
	void GetFilePath(CString strDir);
	afx_msg void OnBnClickedOk2();
	afx_msg void OnBnClickedButton3();
};
