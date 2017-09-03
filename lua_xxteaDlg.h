
// lua_xxteaDlg.h : 头文件
//

#pragma once
#include <vector>

// Clua_xxteaDlg 对话框
class Clua_xxteaDlg : public CDialogEx
{
// 构造
public:
	Clua_xxteaDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_LUA_XXTEA_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	typedef std::vector<CString> LuaFileVector;
// 实现
protected:
	HICON m_hIcon;

	//原始文件绝对路径
	LuaFileVector vFilePathList;

	// 生成的消息映射函数
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
