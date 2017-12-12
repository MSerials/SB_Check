//工具

//
#include "stdafx.h"
#include <windows.h> //不适合64位程序
#include <tlhelp32.h>


#ifndef __TOOLS__
#define __TOOLS__


class win_tool
{
public:
	win_tool(){};
	virtual ~win_tool(){};
	int GetProcessIDByName(PWSTR pname)
	{
		HANDLE SnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		SHFILEINFO shSmall;
		BOOL Status = FALSE;
		PROCESSENTRY32 ProcessInfo;//声明进程信息变量
		DWORD pid = 0;
		if (SnapShot == NULL)
		{
			return -1;
		}


		ProcessInfo.dwSize = sizeof(ProcessInfo);//设置ProcessInfo的大小
		//返回系统中第一个进程的信息
		Status = Process32First(SnapShot, &ProcessInfo);

		while (Status)
		{
			//获取进程文件信息
			SHGetFileInfo(ProcessInfo.szExeFile, 0, &shSmall,
				sizeof(shSmall), SHGFI_ICON | SHGFI_SMALLICON);
			//在列表控件中添加映像名称
			if (StrStrI(ProcessInfo.szExeFile, pname) != NULL)
			{
				pid = ProcessInfo.th32ProcessID;
				break;
			}
			//获取下一个进程的信息
			Status = Process32Next(SnapShot, &ProcessInfo);

		}
		return pid;
	}

	CString AppPath()
	{
		CString AppPath;
		::GetModuleFileName(GetModuleHandle(NULL), AppPath.GetBuffer(300), 300);
		AppPath.ReleaseBuffer();
		AppPath = AppPath.Left(AppPath.ReverseFind('\\'));
		return AppPath;
	}


	CString Get_Date()
	{
		SYSTEMTIME st;
		CString strDate;
		GetLocalTime(&st);
		strDate.Format(_T("%4d-%d-%d"), st.wYear, st.wMonth, st.wDay);
		return strDate;	
	}

	CString Get_Time()
	{
		SYSTEMTIME st;
		CString strTime;
		GetLocalTime(&st);
		strTime.Format(_T("%d-%d-%d"), st.wHour, st.wMinute, st.wSecond);
		return  strTime;	
	}

	CString Get_Date_Time()
	{
		CString str;
		SYSTEMTIME st;
		CString strDate, strTime;
		GetLocalTime(&st);
		strDate.Format(_T("%4d-%d-%d_"), st.wYear, st.wMonth, st.wDay);
		strTime.Format(_T("%d-%d-%d"), st.wHour, st.wMinute, st.wSecond);
		str = strDate + strTime;
		return str;
	}

	vector<CString> SplitCString(CString strSource, CString ch)
	{
		vector <CString> vecString;
		int iPos = 0;
		CString strTmp;
		strTmp = strSource.Tokenize(ch, iPos);
		while (strTmp.Trim() != _T(""))
		{
			vecString.push_back(strTmp);
			strTmp = strSource.Tokenize(ch, iPos);
		}
		return vecString;
	}


	class CSelectFolderDlg
	{
	public:
		//创建一个选择文件夹的对话框，返回所选路径  
		static CString Show()
		{
			TCHAR           szFolderPath[MAX_PATH] = { 0 };
			CString         strFolderPath = TEXT("");

			BROWSEINFO      sInfo;
			::ZeroMemory(&sInfo, sizeof(BROWSEINFO));
			sInfo.pidlRoot = 0;
			sInfo.lpszTitle = _T("请选择一个文件夹：");
			sInfo.ulFlags = BIF_DONTGOBELOWDOMAIN | BIF_NEWDIALOGSTYLE | BIF_EDITBOX | BIF_RETURNONLYFSDIRS;
			sInfo.lpfn = NULL;

			// 显示文件夹选择对话框  
			LPITEMIDLIST lpidlBrowse = ::SHBrowseForFolder(&sInfo);
			if (lpidlBrowse != NULL)
			{
				// 取得文件夹名  
				if (::SHGetPathFromIDList(lpidlBrowse, szFolderPath))
				{
					strFolderPath = szFolderPath;
				}
			}
			if (lpidlBrowse != NULL)
			{
				::CoTaskMemFree(lpidlBrowse);
			}

			return strFolderPath;

		}

		bool ProcPicDir(CString strPicDir, vector<CString>& strPath)
		{
			strPath.clear();
			CFileFind fileFinder;

			if (strPicDir.Right(1) == TEXT("\\"))
			{
				int nPos = strPicDir.ReverseFind(TEXT('\\'));
				strPicDir = strPicDir.Left(nPos);
			}

			CString strPicFile = TEXT("");
			strPicFile.Format(TEXT("%s\\%s"), strPicDir, TEXT("*.*"));

			BOOL bWorking = fileFinder.FindFile(strPicFile);
			while (bWorking)
			{
				bWorking = fileFinder.FindNextFile();
				if (fileFinder.IsDots())
				{
					continue;
				}

				CString strFilePath = fileFinder.GetFilePath();
				//		if (fileFinder.IsDirectory())
				//		{
				//继续遍历目录
				//			ProcPicDir(strFilePath);
				//		}
				//		else
				//		{
				int nPos = strFilePath.ReverseFind(TEXT('.'));
				CString strExt = strFilePath.Right(strFilePath.GetLength() - nPos - 1);
				if (strExt.CompareNoCase(TEXT("jpg")) == 0 ||
					strExt.CompareNoCase(TEXT("jpeg")) == 0 ||
					strExt.CompareNoCase(TEXT("bmp")) == 0)
				{
					//处理图片
					//...
					strPath.push_back(strFilePath);
				}
			}
			fileFinder.Close();
			return true;
		}

	};





};


#endif