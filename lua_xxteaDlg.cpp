
// lua_xxteaDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "lua_xxtea.h"
#include "lua_xxteaDlg.h"
#include "afxdialogex.h"
#include "lua_signAndxxtea.h"
#include <vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Clua_xxteaDlg 对话框



Clua_xxteaDlg::Clua_xxteaDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Clua_xxteaDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Clua_xxteaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Clua_xxteaDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &Clua_xxteaDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &Clua_xxteaDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDOK, &Clua_xxteaDlg::OnBnClickedEncrypt)
	ON_BN_CLICKED(IDCANCEL, &Clua_xxteaDlg::OnBnClickedDecrypt)
	ON_BN_CLICKED(IDOK2, &Clua_xxteaDlg::OnBnClickedOk2)
	ON_BN_CLICKED(IDC_BUTTON3, &Clua_xxteaDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// Clua_xxteaDlg 消息处理程序

BOOL Clua_xxteaDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	//CFont *m_Font;
	//m_Font = new CFont;
	//m_Font->CreateFont(25, 10, 0, 0, 100,
	//	FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
	//	CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_SWISS, _T("宋体"));
	//CEdit *m_Edit = (CEdit *)GetDlgItem(IDC_STATIC);
	//m_Edit->SetFont(m_Font, FALSE);
	//GetDlgItem(IDC_STATIC)->SetFont(m_Font);

	// TODO:  在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Clua_xxteaDlg::OnPaint()
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
HCURSOR Clua_xxteaDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




//输入路径
void Clua_xxteaDlg::OnBnClickedButton1()
{
	//设置路径
	WCHAR szDir[MAX_PATH];
	BROWSEINFO bi;
	ITEMIDLIST *pidl;
	CString path;

	bi.hwndOwner = this->m_hWnd;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = szDir;
	bi.lpszTitle = L"请选择目录";
	bi.ulFlags = BIF_RETURNONLYFSDIRS;
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;

	pidl = SHBrowseForFolder(&bi);
	if (pidl == NULL)
		return;

	if (SHGetPathFromIDList(pidl, szDir))
	{
		path.Format(L"%s", szDir);
	}
	CWnd::SetDlgItemTextW(IDC_EDIT4, path);

}

//输出路径
void Clua_xxteaDlg::OnBnClickedButton2()
{
	// TODO:  在此添加控件通知处理程序代码
	WCHAR szDir[MAX_PATH];
	BROWSEINFO bi;
	ITEMIDLIST *pidl;
	CString path;

	bi.hwndOwner = this->m_hWnd;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = szDir;
	bi.lpszTitle = L"请选择目录";
	bi.ulFlags = BIF_RETURNONLYFSDIRS;
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;

	pidl = SHBrowseForFolder(&bi);
	if (pidl == NULL)
		return;

	if (SHGetPathFromIDList(pidl, szDir))
	{
		path.Format(L"%s", szDir);
	}
	CWnd::SetDlgItemTextW(IDC_EDIT5, path);
}




//文件读取，申请内存，使用完释放
char * FileRead(CString sPath, size_t *file_len)
{
	CFile file;
	char * buf = nullptr;
	try
	{
		FILE *pFile = nullptr;        //pFile = fopen(sPath.c_str(), "r+t"); 
		char *filePath = new char[sPath.GetLength()];
		for (int i = 0; i <= sPath.GetLength(); i++)
		{
			*(filePath + i) = sPath.GetAt(i);

			*(filePath + sPath.GetLength()) = NULL;
		}

		fopen_s(&pFile, filePath, "rb");

		if (pFile)
		{
			fseek(pFile, 0, SEEK_END);
			int nFileLen = ftell(pFile);
			buf = new char[nFileLen];
			fseek(pFile, 0, SEEK_SET);
			fread(buf, sizeof(char), nFileLen, pFile);
			fclose(pFile);
			*file_len = nFileLen;
			return buf;

		}
	}
	catch (CFileException *e)
	{
		file.Abort();
		e->Delete();
	}
}

//写文件并释放
void WriteFile(CString sPath, unsigned char *buf,  size_t file_len)
{
	CFile file;
	try
	{
		file.Open(sPath, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);
		//CArchive ar(&file, CArchive::store);//根据打开的文件，创建文件串行化对象
		//Serialize(ar); //写文件内容
		//ar.Write(buf, NUM);
		////结束后关闭对象
		//ar.Close();
		file.SeekToBegin();
		file.Write(buf, file_len);//CString m_data
		//file.Flush();
		file.Close();
		free(buf);
	}
	catch (CFileException *e)
	{
		file.Abort();
		e->Delete();
	}
}


CString GetSuffix(CString strFileName)
{
	return strFileName.Right(strFileName.GetLength() - strFileName.ReverseFind('.') - 1);
}

void Clua_xxteaDlg::GetFilePath(CString strDir)
{
	CFileFind finder;

	CString filename;
	CString extraName;
	CString findPath;
	findPath = strDir + _T("\\*.*");
	BOOL isNotEmpty = finder.FindFile(findPath);//从文件夹，开始遍历 
	while (isNotEmpty)
	{
		filename.Empty();
		extraName.Empty();
		isNotEmpty = finder.FindNextFile();//查找文件 
		filename = finder.GetFilePath();//获取文件的路径，可能是文件夹，可能是文件 
		if (finder.IsDots())
		{
			continue;
		}else if (!(finder.IsDirectory()))
		{
			//如果是lua文件则加入文件列表 
			extraName = GetSuffix(filename);
			if (extraName == "lua" || extraName == "LUA")
			{
				vFilePathList.push_back(filename);//将一个文件路径加入容器 
			}
		}
		else
		{
			//递归遍历用户文件夹，跳过非用户文件夹 
			if (!(finder.IsDots() || finder.IsHidden() || finder.IsSystem() || finder.IsTemporary() || finder.IsReadOnly()))
			{
				vFilePathList.push_back(filename + _T("\\"));//将一个文件路径加入容器 
				GetFilePath(filename + _T("/"));

			}
		}
	}
}


//用完请释放
char *CStringToChar(CString sPath)
{
	char *filePath = new char[sPath.GetLength()];
	for (int i = 0; i <= sPath.GetLength(); i++)
	{
		*(filePath + i) = sPath.GetAt(i);

		*(filePath + sPath.GetLength()) = NULL;
	}
	return filePath;
}



void Clua_xxteaDlg::OnAddContentEdit(CString title, CString content)
{
	CString str;
	if (title == "1")
	{
		str = CString("*******") + content;
		((CEdit*)GetDlgItem(IDC_EDIT1))->SetSel(GetDlgItem(IDC_EDIT1)->GetWindowTextLength(), GetDlgItem(IDC_EDIT1)->GetWindowTextLength());
		((CEdit*)GetDlgItem(IDC_EDIT1))->ReplaceSel(str + L"\r\n");
	}
	else if (title == "2")
	{
		str = content;
		((CEdit*)GetDlgItem(IDC_EDIT1))->SetSel(GetDlgItem(IDC_EDIT1)->GetWindowTextLength(), GetDlgItem(IDC_EDIT1)->GetWindowTextLength());
		((CEdit*)GetDlgItem(IDC_EDIT1))->ReplaceSel(str + L"\r\n");
	}
	else
	{
		str = title + "  ---->  " + content;
		((CEdit*)GetDlgItem(IDC_EDIT1))->SetSel(GetDlgItem(IDC_EDIT1)->GetWindowTextLength(), GetDlgItem(IDC_EDIT1)->GetWindowTextLength());
		((CEdit*)GetDlgItem(IDC_EDIT1))->ReplaceSel(str + L"\r\n");
	}
}

void Clua_xxteaDlg::OnBnClickedEncrypt()
{
	// TODO:  加密处理

	//判断输入框
	CString filePath;
	CString str;

	CString key;
	GetDlgItem(IDC_EDIT3)->GetWindowText(key);
	if (key.IsEmpty())
	{
		OnAddContentEdit(CString("1"), CString("key不能为空"));
		return;
	}
	char *Pkey = CStringToChar(key);

	CString singed;
	GetDlgItem(IDC_EDIT2)->GetWindowText(singed);
	char *Psinged = CStringToChar(singed);

	CString input;
	GetDlgItem(IDC_EDIT4)->GetWindowText(input);
	if (input.IsEmpty())
	{
		OnAddContentEdit(CString("1"),CString("输入路径不合法"));
		return;
	}

	CString output;
	GetDlgItem(IDC_EDIT5)->GetWindowText(output);
	if (output.IsEmpty())
	{
		OnAddContentEdit(CString("1"), CString("输出路径不合法"));
		return;
	}

	//文件查找
	GetFilePath(input);

	if (vFilePathList.size() == 0)
	{

		OnAddContentEdit(CString("1"), CString("没有可处理的文件"));
	}
	
	std::vector<CString>::iterator iter;
	for (iter = vFilePathList.begin(); iter != vFilePathList.end(); iter++)
	{
		filePath = CString("");
		filePath = *iter;


		CString reFilePath = filePath;
		reFilePath.Replace(input, output);
		//文件夹，创建
		if (GetFileAttributes(filePath) == FILE_ATTRIBUTE_DIRECTORY)
		{
			::CreateDirectory(reFilePath, NULL);//创建目录,已有的话不影响   
		}
		else //文件，加密并写文件
		{
			size_t file_len;
			char *buf = FileRead(filePath, &file_len);
			unsigned char *enRet = NULL;
			size_t enRetLen;
			enRet = lua_SignAndXXTEA::lua_SignAndEncrypt(buf, file_len, Pkey, strlen(Pkey), Psinged, strlen(Psinged), &enRetLen);
			WriteFile(reFilePath, enRet, enRetLen);
			delete buf;

		}
		OnAddContentEdit(CString("加密文件成功"), filePath);
		
	}
	OnAddContentEdit(CString("2"), CString("-------------------------------------------------------------------------------------------"));
	return;
}




void Clua_xxteaDlg::OnBnClickedOk2()
{
	// TODO:  在此添加控件通知处理程序代码
	//判断输入框
	CString filePath;
	CString str;

	CString key;
	GetDlgItem(IDC_EDIT3)->GetWindowText(key);
	if (key.IsEmpty())
	{
		OnAddContentEdit(CString("1"), CString("key不能为空"));
		return;
	}
	char *Pkey = CStringToChar(key);

	CString singed;
	GetDlgItem(IDC_EDIT2)->GetWindowText(singed);
	char *Psinged = CStringToChar(singed);

	CString input;
	GetDlgItem(IDC_EDIT4)->GetWindowText(input);
	if (input.IsEmpty())
	{
		OnAddContentEdit(CString("1"), CString("输入路径不合法"));
		return;
	}

	CString output;
	GetDlgItem(IDC_EDIT5)->GetWindowText(output);
	if (output.IsEmpty())
	{
		OnAddContentEdit(CString("1"), CString("输出路径不合法"));
		return;
	}

	//文件查找
	GetFilePath(input);

	if (vFilePathList.size() == 0)
	{

		OnAddContentEdit(CString("1"), CString("没有可处理的文件"));
	}

	std::vector<CString>::iterator iter;
	for (iter = vFilePathList.begin(); iter != vFilePathList.end(); iter++)
	{
		filePath = CString("");
		filePath = *iter;


		CString reFilePath = filePath;
		reFilePath.Replace(input, output);
		//文件夹，创建
		if (GetFileAttributes(filePath) == FILE_ATTRIBUTE_DIRECTORY)
		{
			::CreateDirectory(reFilePath, NULL);//创建目录,已有的话不影响   
		}
		else //文件，加密并写文件
		{
			size_t file_len;
			char *buf = FileRead(filePath, &file_len);
			unsigned char *enRet = NULL;
			size_t enRetLen;
			enRet = lua_SignAndXXTEA::lua_SignAndDecrypt(buf, file_len, Pkey, strlen(Pkey), Psinged, strlen(Psinged), &enRetLen);
			WriteFile(reFilePath, enRet, enRetLen);
			delete buf;
		}
		OnAddContentEdit(CString("解密文件成功"), filePath);

	}
	OnAddContentEdit(CString("2"), CString("------------------------------------------------------------------------------------------------"));
	return;
}


void Clua_xxteaDlg::OnBnClickedDecrypt()
{
	// TODO:  解密处理
	CDialogEx::OnCancel();
}


void Clua_xxteaDlg::OnBnClickedButton3()
{
	CString input;
	GetDlgItem(IDC_EDIT4)->GetWindowText(input);
	CString output;
	GetDlgItem(IDC_EDIT5)->GetWindowText(output);

	CString tmp;
	tmp = input;
	input = output;
	output = tmp;
	GetDlgItem(IDC_EDIT4)->SetWindowTextW(input);
	GetDlgItem(IDC_EDIT5)->SetWindowTextW(output);


	// TODO:  在此添加控件通知处理程序代码
}
