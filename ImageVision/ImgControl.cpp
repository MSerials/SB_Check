// ImgControl.cpp : 实现文件
//

#include "stdafx.h"
#include "ImageVision.h"
#include "ImgControl.h"
#include "afxdialogex.h"


// CImgControl 对话框

IMPLEMENT_DYNAMIC(CImgControl, CDialogEx)

CImgControl::CImgControl(CWnd* pParent /*=NULL*/)
	: CDialogEx(CImgControl::IDD, pParent)
{

}

CImgControl::~CImgControl()
{
}

void CImgControl::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CImgControl, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_UI, &CImgControl::OnBnClickedButtonUi)
	ON_BN_CLICKED(IDC_BUTTON_CAMSAVE, &CImgControl::OnBnClickedButtonCamsave)
	ON_BN_CLICKED(IDC_BUTTON_CAMSAVE2, &CImgControl::OnBnClickedButtonCamsave2)
END_MESSAGE_MAP()


// CImgControl 消息处理程序




void CImgControl::OnBnClickedButtonUi()
{
	// TODO:  在此添加控件通知处理程序代码
}


void CImgControl::OnBnClickedButtonCamsave()
{
	// TODO:  在此添加控件通知处理程序代码
	CString str;











	int SysState = (g.Controller.SysState & TOPCAMERROR);
	//初始化成功的相机才能调整参数
	GetDlgItem(IDC_EDIT_DELAYSNAP)->GetWindowText(str);
	g.ini.m_FstCam.delaysnap = _ttoi(str);

	GetDlgItem(IDC_EDIT_GAIN)->GetWindowText(str);
	g.ini.m_FstCam.gain = _ttoi(str);

	GetDlgItem(IDC_EDIT_EXPLOSURE)->GetWindowText(str);
	g.ini.m_FstCam.explosure = _ttoi(str);

	g.ini.SaveParaFile(PARA_IMAGE);

	if (port.InitPort(this, "COM8"))
	{
	//	port.StartMonitoring();
		port.WriteToPort("gcp\r\n", strlen("gcp\r\n")); Sleep(10);
		port.WriteToPort("sem 2\r\n", strlen("sem 2\r\n")); Sleep(10);
		str.Format(_T("set %d\r\n"), g.ini.m_FstCam.explosure);
		char *s = (char*)(LPCSTR)(CStringA)str;
		port.WriteToPort(s, strlen(s));
		//str.Format(_T("ssg 0 %d\r"), g.ini.m_SndCam.explosure);
		port.Close();
	}

}


void CImgControl::OnBnClickedButtonCamsave2()
{
	// TODO:  在此添加控件通知处理程序代码
	CString str;
	int SysState = (g.Controller.SysState & BOTTOMERROR);
	//初始化成功的相机才能调整参数
	
		GetDlgItem(IDC_EDIT_DELAYSNAP2)->GetWindowText(str);
		g.ini.m_SndCam.delaysnap = _ttoi(str);
		
		GetDlgItem(IDC_EDIT_GAIN2)->GetWindowText(str);
		g.ini.m_SndCam.gain = _ttoi(str);

		GetDlgItem(IDC_EDIT_EXPLOSURE2)->GetWindowText(str);
		g.ini.m_SndCam.explosure = _ttoi(str);

		g.ini.SaveParaFile(PARA_IMAGE);
	
		if (port.InitPort(this, "COM9"))
		{
		//	port.StartMonitoring();
			port.WriteToPort("gcp\r\n", strlen("gcp\r\n")); Sleep(10);
			port.WriteToPort("sem 2\r\n", strlen("sem 2\r\n")); Sleep(10);
			str.Format(_T("set %d\r\n"), g.ini.m_SndCam.explosure);
			char *s = (char*)(LPCSTR)(CStringA)str;
			port.WriteToPort(s, strlen(s));
			//str.Format(_T("ssg 0 %d\r"), g.ini.m_SndCam.explosure);
			port.Close();
		}

}


BOOL CImgControl::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CString str;
	str.Format(_T("%d"), g.ini.m_FstCam.delaysnap);
	GetDlgItem(IDC_EDIT_DELAYSNAP)->SetWindowText(str);
	str.Format(_T("%d"), g.ini.m_SndCam.delaysnap);
	GetDlgItem(IDC_EDIT_DELAYSNAP2)->SetWindowText(str);

	str.Format(_T("%d"), g.ini.m_FstCam.explosure);
	GetDlgItem(IDC_EDIT_EXPLOSURE)->SetWindowText(str);
	str.Format(_T("%d"), g.ini.m_SndCam.explosure);
	GetDlgItem(IDC_EDIT_EXPLOSURE2)->SetWindowText(str);

	str.Format(_T("%d"), g.ini.m_FstCam.gain);
	GetDlgItem(IDC_EDIT_GAIN)->SetWindowText(str);
	str.Format(_T("%d"), g.ini.m_SndCam.gain);
	GetDlgItem(IDC_EDIT_GAIN2)->SetWindowText(str);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}
