
// lua_xxteaDlg.cpp : ʵ���ļ�
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


// Clua_xxteaDlg �Ի���



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


// Clua_xxteaDlg ��Ϣ�������

BOOL Clua_xxteaDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	//CFont *m_Font;
	//m_Font = new CFont;
	//m_Font->CreateFont(25, 10, 0, 0, 100,
	//	FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
	//	CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_SWISS, _T("����"));
	//CEdit *m_Edit = (CEdit *)GetDlgItem(IDC_STATIC);
	//m_Edit->SetFont(m_Font, FALSE);
	//GetDlgItem(IDC_STATIC)->SetFont(m_Font);

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void Clua_xxteaDlg::OnPaint()
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
HCURSOR Clua_xxteaDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




//����·��
void Clua_xxteaDlg::OnBnClickedButton1()
{
	//����·��
	WCHAR szDir[MAX_PATH];
	BROWSEINFO bi;
	ITEMIDLIST *pidl;
	CString path;

	bi.hwndOwner = this->m_hWnd;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = szDir;
	bi.lpszTitle = L"��ѡ��Ŀ¼";
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

//���·��
void Clua_xxteaDlg::OnBnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	WCHAR szDir[MAX_PATH];
	BROWSEINFO bi;
	ITEMIDLIST *pidl;
	CString path;

	bi.hwndOwner = this->m_hWnd;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = szDir;
	bi.lpszTitle = L"��ѡ��Ŀ¼";
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




//�ļ���ȡ�������ڴ棬ʹ�����ͷ�
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

//д�ļ����ͷ�
void WriteFile(CString sPath, unsigned char *buf,  size_t file_len)
{
	CFile file;
	try
	{
		file.Open(sPath, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);
		//CArchive ar(&file, CArchive::store);//���ݴ򿪵��ļ��������ļ����л�����
		//Serialize(ar); //д�ļ�����
		//ar.Write(buf, NUM);
		////������رն���
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
	BOOL isNotEmpty = finder.FindFile(findPath);//���ļ��У���ʼ���� 
	while (isNotEmpty)
	{
		filename.Empty();
		extraName.Empty();
		isNotEmpty = finder.FindNextFile();//�����ļ� 
		filename = finder.GetFilePath();//��ȡ�ļ���·�����������ļ��У��������ļ� 
		if (finder.IsDots())
		{
			continue;
		}else if (!(finder.IsDirectory()))
		{
			//�����lua�ļ�������ļ��б� 
			extraName = GetSuffix(filename);
			if (extraName == "lua" || extraName == "LUA")
			{
				vFilePathList.push_back(filename);//��һ���ļ�·���������� 
			}
		}
		else
		{
			//�ݹ�����û��ļ��У��������û��ļ��� 
			if (!(finder.IsDots() || finder.IsHidden() || finder.IsSystem() || finder.IsTemporary() || finder.IsReadOnly()))
			{
				vFilePathList.push_back(filename + _T("\\"));//��һ���ļ�·���������� 
				GetFilePath(filename + _T("/"));

			}
		}
	}
}


//�������ͷ�
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
	// TODO:  ���ܴ���

	//�ж������
	CString filePath;
	CString str;

	CString key;
	GetDlgItem(IDC_EDIT3)->GetWindowText(key);
	if (key.IsEmpty())
	{
		OnAddContentEdit(CString("1"), CString("key����Ϊ��"));
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
		OnAddContentEdit(CString("1"),CString("����·�����Ϸ�"));
		return;
	}

	CString output;
	GetDlgItem(IDC_EDIT5)->GetWindowText(output);
	if (output.IsEmpty())
	{
		OnAddContentEdit(CString("1"), CString("���·�����Ϸ�"));
		return;
	}

	//�ļ�����
	GetFilePath(input);

	if (vFilePathList.size() == 0)
	{

		OnAddContentEdit(CString("1"), CString("û�пɴ�����ļ�"));
	}
	
	std::vector<CString>::iterator iter;
	for (iter = vFilePathList.begin(); iter != vFilePathList.end(); iter++)
	{
		filePath = CString("");
		filePath = *iter;


		CString reFilePath = filePath;
		reFilePath.Replace(input, output);
		//�ļ��У�����
		if (GetFileAttributes(filePath) == FILE_ATTRIBUTE_DIRECTORY)
		{
			::CreateDirectory(reFilePath, NULL);//����Ŀ¼,���еĻ���Ӱ��   
		}
		else //�ļ������ܲ�д�ļ�
		{
			size_t file_len;
			char *buf = FileRead(filePath, &file_len);
			unsigned char *enRet = NULL;
			size_t enRetLen;
			enRet = lua_SignAndXXTEA::lua_SignAndEncrypt(buf, file_len, Pkey, strlen(Pkey), Psinged, strlen(Psinged), &enRetLen);
			WriteFile(reFilePath, enRet, enRetLen);
			delete buf;

		}
		OnAddContentEdit(CString("�����ļ��ɹ�"), filePath);
		
	}
	OnAddContentEdit(CString("2"), CString("-------------------------------------------------------------------------------------------"));
	return;
}




void Clua_xxteaDlg::OnBnClickedOk2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//�ж������
	CString filePath;
	CString str;

	CString key;
	GetDlgItem(IDC_EDIT3)->GetWindowText(key);
	if (key.IsEmpty())
	{
		OnAddContentEdit(CString("1"), CString("key����Ϊ��"));
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
		OnAddContentEdit(CString("1"), CString("����·�����Ϸ�"));
		return;
	}

	CString output;
	GetDlgItem(IDC_EDIT5)->GetWindowText(output);
	if (output.IsEmpty())
	{
		OnAddContentEdit(CString("1"), CString("���·�����Ϸ�"));
		return;
	}

	//�ļ�����
	GetFilePath(input);

	if (vFilePathList.size() == 0)
	{

		OnAddContentEdit(CString("1"), CString("û�пɴ�����ļ�"));
	}

	std::vector<CString>::iterator iter;
	for (iter = vFilePathList.begin(); iter != vFilePathList.end(); iter++)
	{
		filePath = CString("");
		filePath = *iter;


		CString reFilePath = filePath;
		reFilePath.Replace(input, output);
		//�ļ��У�����
		if (GetFileAttributes(filePath) == FILE_ATTRIBUTE_DIRECTORY)
		{
			::CreateDirectory(reFilePath, NULL);//����Ŀ¼,���еĻ���Ӱ��   
		}
		else //�ļ������ܲ�д�ļ�
		{
			size_t file_len;
			char *buf = FileRead(filePath, &file_len);
			unsigned char *enRet = NULL;
			size_t enRetLen;
			enRet = lua_SignAndXXTEA::lua_SignAndDecrypt(buf, file_len, Pkey, strlen(Pkey), Psinged, strlen(Psinged), &enRetLen);
			WriteFile(reFilePath, enRet, enRetLen);
			delete buf;
		}
		OnAddContentEdit(CString("�����ļ��ɹ�"), filePath);

	}
	OnAddContentEdit(CString("2"), CString("------------------------------------------------------------------------------------------------"));
	return;
}


void Clua_xxteaDlg::OnBnClickedDecrypt()
{
	// TODO:  ���ܴ���
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


	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
