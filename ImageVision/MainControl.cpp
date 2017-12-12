// MainControl.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ImageVision.h"
#include "MainControl.h"
#include "afxdialogex.h"
#include "MotionCtrl.h"
#include "ImgControl.h"
#include "Tools.h"


// CMainControl �Ի���

IMPLEMENT_DYNAMIC(CMainControl, CDialogEx)

CMainControl::CMainControl(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMainControl::IDD, pParent)
{
	isOrigin = false;
	isDelayInit = false;
	int _counter = 0;
	bool _isToOrigin = false;
}

CMainControl::~CMainControl()
{
}

void CMainControl::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBSELPRJ, m_ComBoxSel);
}


BEGIN_MESSAGE_MAP(CMainControl, CDialogEx)
//	ON_WM_CLOSE()
	ON_MESSAGE(WMMSG_SOCKET_COMMAND, &CMainControl::SocketCommand)
	ON_BN_CLICKED(IDC_BUTTON_IOMOTION, &CMainControl::OnBnClickedButtonIomotion)
	ON_BN_CLICKED(IDC_BUTTON_IMGSET, &CMainControl::OnBnClickedButtonImgset)
	ON_BN_CLICKED(IDC_BUTTON_TO_ORIGIN, &CMainControl::OnBnClickedButtonToOrigin)
	ON_WM_TIMER()
	ON_CBN_SELCHANGE(IDC_COMBSELPRJ, &CMainControl::OnSelchangeCombselprj)
	ON_BN_CLICKED(IDC_BUTTON_ADDPRJ, &CMainControl::OnBnClickedButtonAddprj)
	ON_BN_CLICKED(IDC_BUTTON_SAVEIP, &CMainControl::OnBnClickedButtonSaveip)
END_MESSAGE_MAP()


// CMainControl ��Ϣ�������


BOOL CMainControl::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	CComboBox* pBox = (CComboBox*)GetDlgItem(IDC_COMBSELPRJ);// ->AddString(L"1");
	win_tool wt;
	vector<CString> prj = wt.SplitCString(g.prjini.m_Prj_Vector, L",");
	for (size_t i = 0; i < prj.size(); i++)
	{
		pBox->AddString(prj[i]);
	}
	pBox->SetCurSel(g.prjini.m_Prj_index);


	CString l_string;
	l_string.Format(_T("%d"), g.ini.m_trigger_delay_time);
	GetDlgItem(IDC_EDIT_DELAYFORGET)->SetWindowText(l_string);
	g.ini.m_trigger_delay_time = _ttoi(l_string);
	if (g.ini.m_trigger_delay_time < 1000)
	{
		g.ini.m_trigger_delay_time = 1000;
		GetDlgItem(IDC_EDIT_DELAYFORGET)->SetWindowText(L"1000");
		g.ini.SaveParaFile(PARA_ALL);
	}
	

	SetTimer(ORIGIN, 600, NULL);
	CMainControl * t = this;
	g.MainCtrl = t->m_hWnd;

//	RunDelayInit();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE

	CIPAddressCtrl* ipadd = (CIPAddressCtrl*)GetDlgItem(IDC_IPADDRESS);
	CIPAddressCtrl* ipmask = (CIPAddressCtrl*)GetDlgItem(IDC_IPADDRESSMASK);
	DWORD dwIP = inet_addr((char*)(LPCSTR)(CStringA)g.ini.SerIP);
	BYTE   *pIP = (BYTE*)&dwIP;
	ipadd->SetAddress(*pIP, *(pIP + 1), *(pIP + 2), *(pIP + 3));

	dwIP = inet_addr((char*)(LPCSTR)(CStringA)g.ini.IPMask);
	pIP = (BYTE*)&dwIP;
	ipmask->SetAddress(*pIP, *(pIP + 1), *(pIP + 2), *(pIP + 3));


}


BOOL CMainControl::initPort(char *str)
{
	port.EnableSerialMessage(TRUE, FALSE, FALSE, FALSE, FALSE, FALSE);
	if (port.InitPort(this, str))
	{
		port.StartMonitoring();
		//port.WriteToPort("gcp\r\n", strlen("gcp\r\n")); Sleep(100); 
		char command[256] = { 0 };
		strcpy_s(command, "sem 2");
		for (int i = 0; i<2; i++) port.WriteToPort(command, strlen(command)); Sleep(200);
		strcpy_s(command, "set 300");
		port.WriteToPort(command,strlen(command));
#ifdef _TEST
		printf("init port ok!\n");
#endif
		port.Close();
		return TRUE;
	}
	else
	{
		AfxMessageBox(L"������������ں�ΪCOM8��COM9");
		return FALSE;
	}


}

bool CMainControl::RunDelayInit()
{
	pRunDelayInit = AfxBeginThread(pDelayInit, this, THREAD_PRIORITY_NORMAL, 0, 0, NULL);
	if (pRunDelayInit) return true;
	else
		return false;
}


UINT CMainControl::pDelayInit(LPVOID lp)
{
	CMainControl *pMC = (CMainControl*)lp;
	DWORD tick = GetTickCount();
	bool topinit = false;
	bool botinit = false;
	bool topinitsuccess = false;
	bool botinitsuccess = false;
	while (1)
	{
		int bottomcamerror = (g.Controller.SysState & BOTTOMERROR);
		int topcamerror = (g.Controller.SysState & TOPCAMERROR);
		if (topinit && botinit) break;
		if (!topcamerror && !topinit)
		{
			if (pMC->initPort("COM8"))
			{
				topinitsuccess = true;
			}
			else
				topinitsuccess = false;

			topinit = true;
		}

		if (!bottomcamerror && !botinit)
		{
			if (pMC->initPort("COM9"))
			{
				botinitsuccess = true;
			}
			else
				botinitsuccess = false;

			botinit = true;
		}
		if ((GetTickCount() - tick) > 30000) break;
		Sleep(10);
	}





	return 0;
}


void CMainControl::OnBnClickedButtonIomotion()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	
	CMotionCtrl dlg;
	dlg.DoModal();
}


void CMainControl::OnBnClickedButtonImgset()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	
	CImgControl cdlg;
	cdlg.DoModal();
	return;
}


void CMainControl::OnBnClickedButtonToOrigin()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	
	int SysState = SYSRUNNING | FST_MOTOR_NOT_ALREADY | SND_MOTOR_NOT_ALREADY | SYSEMGENCY;//Ӱ���ԭ�������
	SysState = SysState&g.Controller.SysState;
	if (SysState && (WAIT_OBJECT_0 == ::WaitForSingleObject(g.evt_procedure.evt, 8))) return; //���������Ҳ���ܻ�ԭ�㣻
	if (g.mc.CylHaveProduct()) { AfxMessageBox(L"��������������!"); return; }
	if (IDYES != MessageBox(L"ȷ��", L"ϵͳ��ԭ��", MB_YESNO | MB_ICONQUESTION)) return;
	g.evt_procedure.evt.ResetEvent();
	g.evtEmgencyStop.ResetEvent();
	g.mc.Stop(FIRST_MOTOR);
	g.mc.Stop(SECOND_MOTOR);
	RunOrigin();
}

void CMainControl::BnClickedButtonToOrigin()
{
	int SysState = SYSRUNNING | FST_MOTOR_NOT_ALREADY | SND_MOTOR_NOT_ALREADY | SYSEMGENCY;//Ӱ���ԭ�������
	SysState = SysState&g.Controller.SysState;
	if (SYSRUNNING == (SYSRUNNING & SysState))return;
	else if (SysState) { AfxMessageBox(L"����������߼�ͣ��ť����"); }
	g.evt_procedure.evt.ResetEvent();
	g.evtEmgencyStop.ResetEvent();
	g.mc.Stop(FIRST_MOTOR);
	g.mc.Stop(SECOND_MOTOR);
	//if (WAIT_OBJECT_0 == ::WaitForSingleObject(g.evt_procedure.evt, 0) || SysState) return; //���������Ҳ���ܻ�ԭ�㣻
	RunOrigin();
}

void CMainControl::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//ʵ����һ�����¿�ʼ��ť2������и�λ�Ĺ���
	
	if (ORIGIN == nIDEvent)
	{
		CString str;
		str.Format(_T("%d"),g.backNo);
		GetDlgItem(IDC_EDIT_CHECKED)->SetWindowText(str);
		str.Format(_T("%d"), g.NGCounter);
		GetDlgItem(IDC_EDIT_NG)->SetWindowText(str);
		bool NewBit = g.mc.Read_Input(IN_START);
		if (3 < _counter && !_isToOrigin)
		{
			//if ((OldBit != NewBit) && (NewBit))
				_isToOrigin = true;
				BnClickedButtonToOrigin();
		}
		if (NewBit)
		{
			_counter++;
		}
		else
		{
			_isToOrigin = false;
			_counter = 0;
		}		
	}
	CDialogEx::OnTimer(nIDEvent);
}


bool CMainControl::RunOrigin()
{
	if (isOrigin) return false;
	pRunOrigin = AfxBeginThread(pRunOriginThread, this, THREAD_PRIORITY_HIGHEST, 0, 0, NULL);
	return true;
}

UINT CMainControl::pRunOriginThread(LPVOID lp)
{
	CMainControl * pApp = (CMainControl*)lp;
	pApp->isOrigin = true;
	int res = g.mc.SysToOrigin();
	res &= ~TOPCAMERROR;
	res &= ~BOTTOMERROR;
	res &= ~SYSLOADDATAERROR;
	g.Controller.SysState &= ~SYSLOADDATAERROR;
	if (res)
	{
		g.Controller.SysState |= SYSNEEDORIGIN;
		AfxMessageBox(L"ԭ�㸴λ����:"+g.ErrorString(res));
	}		
	else
	{
		g.mc.clear_index_data();
		g.mc.clear_running_state();
#ifdef _�߼�һ
		g.mc.MoveToDes(FIRST_MOTOR, g.ini.m_FstMtr.InitSpeed, g.ini.m_FstMtr.MaxSpeed, g.ini.m_FstMtr.Tacc, g.ini.m_FstMtr.Waves);
#else
		g.mc.MoveToDes(FIRST_MOTOR, 100, g.ini.m_FstMtr.MaxSpeed, g.ini.m_FstMtr.Tacc, g.ini.m_FstMtr.Waves);
#endif

		if (!g.mc.Wait(FIRST_MOTOR, 20000)){ g.Controller.SysState |= SYSNEEDORIGIN; goto endf; }

		if (g.mc.Get_Position(FIRST_MOTOR) != g.ini.m_FstMtr.Waves) { g.Controller.SysState |= SYSNEEDORIGIN; goto endf; }
		g.Controller.SysState &= ~SYSNEEDORIGIN;
		g.Controller.SysState &= ~SYSERROR;
		g.evt_procedure.SetEvent();
		g.evtEmgencyStop.ResetEvent();
	}

endf:
	Sleep(1);
	pApp->isOrigin = false;
	return 0;
}

void CMainControl::OnSelchangeCombselprj()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	win_tool wt;
	CComboBox* pBox = (CComboBox*)GetDlgItem(IDC_COMBSELPRJ);
	int nSel = pBox->GetCurSel();
	// ����ѡ����������ȡ�����ַ���
	CString str;
	pBox->GetLBText(nSel, str);
	//bug 1
	g.prjini.m_Prj_index = nSel;
	g.prjini.m_Prj_Name = str;
	CString AppPath;
	::GetModuleFileName(GetModuleHandle(NULL), AppPath.GetBuffer(300), 300);
	AppPath.ReleaseBuffer();
	CString PrjPath = AppPath.Left(AppPath.ReverseFind('\\'));
	AppPath = PrjPath + L"\\" + L"Configuration";

	g.prjini.SaveParaFile(PARA_ALL);
	PrjPath += L"\\" + g.prjini.m_Prj_Name;
	g.ini.SetIniDir(PrjPath, false);
	if (0 == g.ini.SetIniFile(L"PrgParameter.ini"))
	{
		g.ini.InitData();
		g.ini.SaveParaFile(PARA_ALL);
		g.Controller.SysState |= SYSNEEDORIGIN;
	}
	g.ini.LoadParaFile(PARA_ALL);

	if (!g.img_deal.read_params(g.prjini.m_Prj_Name))
	{
		g.Controller.SysState |= SYSNEEDORIGIN;
		AfxMessageBox(L"δ���뵽���ݣ��������ƴ�����Ķ���ѡ�����ѵ��ͼƬ�͵ײ�ѡ����ѵ��ͼƬ��");
	}
}


void CMainControl::OnBnClickedButtonAddprj()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	win_tool  wt;
	CString str;
	GetDlgItem(IDC_EDIT_ADDPRJ)->GetWindowText(str);
	if (-1 != str.ReverseFind(','))
	{
		AfxMessageBox(L"���ܰ������·���: ,");
		return;
	}
	if (str.IsEmpty()) return;

	vector<CString> s = wt.SplitCString(g.prjini.m_Prj_Vector, L",");
	for (size_t i = 0; i < s.size(); i++)
	{
		if (!str.Compare(s[i]))
		{
			AfxMessageBox(L"�������б�������");
			return;
		}
	}
	g.prjini.m_Prj_Name = str;

	CString NewPrj = L"," + str;
	g.prjini.m_Prj_Vector += NewPrj;
	g.prjini.m_Prj_index = (int)s.size(); //�պõ����һ����Ŀ����
	g.prjini.SaveParaFile(PARA_ALL);

	CString AppPath;
	::GetModuleFileName(GetModuleHandle(NULL), AppPath.GetBuffer(300), 300);
	AppPath.ReleaseBuffer();
	CString PrjPath = AppPath.Left(AppPath.ReverseFind('\\'));
	AppPath = PrjPath + L"\\" + L"Configuration";

	PrjPath += L"\\" + g.prjini.m_Prj_Name;
	g.ini.SetIniDir(PrjPath, false);
	if (0 == g.ini.SetIniFile(L"PrgParameter.ini"))
	{
		g.ini.InitData();
		g.ini.SaveParaFile(PARA_ALL);
		g.Controller.SysState |= SYSNEEDORIGIN;
	}
	g.ini.LoadParaFile(PARA_ALL);
	CComboBox* pBox = (CComboBox*)GetDlgItem(IDC_COMBSELPRJ);
	pBox->AddString(str);
	vector<CString> prj = wt.SplitCString(g.prjini.m_Prj_Vector, L",");
	pBox->SetCurSel(g.prjini.m_Prj_index);

	if (!g.img_deal.read_params(g.prjini.m_Prj_Name))
	{
		g.Controller.SysState |= SYSNEEDORIGIN;
		AfxMessageBox(L"δ���뵽���ݣ��������ƴ�����Ķ���ѡ�����ѵ��ͼƬ�͵ײ�ѡ����ѵ��ͼƬ��");
	}
}


void CMainControl::OnBnClickedButtonSaveip()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString l_string;
	GetDlgItem(IDC_EDIT_DELAYFORGET)->GetWindowText(l_string);
	g.ini.m_trigger_delay_time = _ttoi(l_string);
	if (g.ini.m_trigger_delay_time < 1000)
	{
		g.ini.m_trigger_delay_time = 1000;
		GetDlgItem(IDC_EDIT_DELAYFORGET)->SetWindowText(L"1000");
	}
	g.ini.SaveParaFile(PARA_ALL);
	return;

	CIPAddressCtrl* ipadd = (CIPAddressCtrl*)GetDlgItem(IDC_IPADDRESS);
	BYTE   *pIP;
	CString   csIP;
	DWORD   dwIP;
	ipadd->GetAddress(dwIP);
	pIP = (unsigned   char*)&dwIP;
	csIP.Format(_T("%d.%d.%d.%d"), *(pIP + 3), *(pIP + 2), *(pIP + 1), *pIP);
	g.ini.SerIP = csIP;
	CIPAddressCtrl* ipmask = (CIPAddressCtrl*)GetDlgItem(IDC_IPADDRESSMASK);
	ipmask->GetAddress(dwIP);
	pIP = (unsigned   char*)&dwIP;
	csIP.Format(_T("%d.%d.%d.%d"), *(pIP + 3), *(pIP + 2), *(pIP + 1), *pIP);
	g.ini.IPMask = csIP;
	g.ini.SaveParaFile(PARA_ALL);
}


LRESULT CMainControl::SocketCommand(WPARAM wParam, LPARAM lParam)
{
#if 0
	if (SELECTPRJ == wParam)
	{
		if (0 == lParam) return 0;
		g.evt_procedure.ResetEvent();
		int sel = lParam - 1; //��Ҫ��1
		win_tool wt;
		CString prjtotal = g.prjini.m_Prj_Vector;
		std::vector<CString> totalprj = wt.SplitCString(prjtotal, L",");
		if ((size_t)lParam > totalprj.size())
		{
			return 0;
		}
		CComboBox* pBox = (CComboBox*)GetDlgItem(IDC_COMBSELPRJ);
		CString str;
		pBox->GetLBText(sel, str);
		pBox->SetCurSel(sel);

		//bug 1
		g.prjini.m_Prj_index = sel;
		g.prjini.m_Prj_Name = str;
		CString AppPath;
		::GetModuleFileName(GetModuleHandle(NULL), AppPath.GetBuffer(300), 300);
		AppPath.ReleaseBuffer();
		CString PrjPath = AppPath.Left(AppPath.ReverseFind('\\'));
		AppPath = PrjPath + L"\\" + L"Configuration";

		g.prjini.SaveParaFile(PARA_ALL);
		PrjPath += L"\\" + g.prjini.m_Prj_Name;
		g.ini.SetIniDir(PrjPath, false);
		if (0 == g.ini.SetIniFile(L"PrgParameter.ini"))
		{
			g.ini.InitData();
			g.ini.SaveParaFile(PARA_ALL);
			g.Controller.SysState |= SYSNEEDORIGIN;
		}
		g.ini.LoadParaFile(PARA_ALL);
		if (!g.img_deal.read_params(g.prjini.m_Prj_Name))
		{
			g.Controller.SysState |= SYSNEEDORIGIN;
			AfxMessageBox(L"δ���뵽���ݣ��������ƴ�����Ķ���ѡ�����ѵ��ͼƬ�͵ײ�ѡ����ѵ��ͼƬ��");
		}
		else
		{
			RunOrigin();
			g.CurrentPrj = lParam;
		}
	}
#endif
	if (SELECTPRJBYNAME == lParam)
	{
		win_tool wt;
		CString prjtotal = g.prjini.m_Prj_Vector;
		std::vector<CString> totalprj = wt.SplitCString(prjtotal, L",");
		int sel = -1;
		for (size_t i = 0; i < totalprj.size(); i++)
		{
			if (0 == totalprj[i].Compare(g.CurrentPrjName))
			{
				sel = i;
			}
		}
		if (-1 == sel)
		{
			g.CurrentPrjName = "PROJECT_NO_EXIST";
			return 0;
		}

		CComboBox* pBox = (CComboBox*)GetDlgItem(IDC_COMBSELPRJ);
		CString str;
		pBox->GetLBText(sel, str);
		pBox->SetCurSel(sel);

		//bug 1
		g.prjini.m_Prj_index = sel;
		g.prjini.m_Prj_Name = str;
		CString AppPath;
		::GetModuleFileName(GetModuleHandle(NULL), AppPath.GetBuffer(300), 300);
		AppPath.ReleaseBuffer();
		CString PrjPath = AppPath.Left(AppPath.ReverseFind('\\'));
		AppPath = PrjPath + L"\\" + L"Configuration";

		g.prjini.SaveParaFile(PARA_ALL);
		PrjPath += L"\\" + g.prjini.m_Prj_Name;
		g.ini.SetIniDir(PrjPath, false);
		if (0 == g.ini.SetIniFile(L"PrgParameter.ini"))
		{
			g.ini.InitData();
			g.ini.SaveParaFile(PARA_ALL);
			g.Controller.SysState |= SYSNEEDORIGIN;
		}
		g.ini.LoadParaFile(PARA_ALL);
		//EnterCriticalSection(&g.cs);
		if (!g.img_deal.read_params(g.prjini.m_Prj_Name))
		{
			g.Controller.SysState |= SYSNEEDORIGIN;
			g.CurrentPrjName = "PROJECT_ERROR";
			AfxMessageBox(L"δ���뵽���ݣ��������ƴ�����Ķ���ѡ�����ѵ��ͼƬ�͵ײ�ѡ����ѵ��ͼƬ��");
		}
		else
		{
			RunOrigin();
			g.CurrentPrjName = str;
			g.CurrentPrj = sel;
			g.backNo = g.NGCounter = 0;
		}
		//LeaveCriticalSection(&g.cs);
	}
	return 0;
}
