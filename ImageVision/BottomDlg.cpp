// BottomDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ImageVision.h"
#include "BottomDlg.h"
#include "afxdialogex.h"
#include "Tools.h"

// CBottomDlg 对话框
CBottomDlg* BottomDlg = NULL;
IMPLEMENT_DYNAMIC(CBottomDlg, CDialogEx)



CBottomDlg::CBottomDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBottomDlg::IDD, pParent)
{
	BottomDlg = this;
	isRunTrain = false;
	isCap = false;
}

CBottomDlg::~CBottomDlg()
{
}

void CBottomDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CBottomDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SEL_BROI, &CBottomDlg::OnBnClickedButtonSelBroi)
	ON_BN_CLICKED(IDC_BUTTON_SHOW_BROI, &CBottomDlg::OnBnClickedButtonShowBroi)
	ON_BN_CLICKED(IDC_BUTTON_BSHOW_TSAVEMODEL, &CBottomDlg::OnBnClickedButtonBshowTsavemodel)
//	ON_BN_CLICKED(IDC_BUTTON_BSELALL, &CBottomDlg::OnBnClickedButtonBselall)
	ON_BN_CLICKED(IDC_BUTTON_BTRAINMODEL, &CBottomDlg::OnBnClickedButtonBtrainmodel)
	ON_BN_CLICKED(IDC_BUTTON_BCAP, &CBottomDlg::OnBnClickedButtonBcap)
	ON_BN_CLICKED(IDC_BUTTON_TEST, &CBottomDlg::OnBnClickedButtonTest)
	ON_BN_CLICKED(IDC_BUTTON_LOAD2, &CBottomDlg::OnBnClickedButtonLoad2)
	ON_BN_CLICKED(IDC_BUTTON_TESTT2, &CBottomDlg::OnBnClickedButtonTestt2)
	ON_BN_CLICKED(IDC_BUTTON_COMFIRMPARA2, &CBottomDlg::OnBnClickedButtonComfirmpara2)
	ON_BN_CLICKED(IDC_BUTTON_BSHOW_FOLDER, &CBottomDlg::OnBnClickedButtonBshowFolder)
	ON_BN_CLICKED(IDC_BUTTON_SEL_BNOROIRECT, &CBottomDlg::OnBnClickedButtonSelBnoroirect)
	ON_BN_CLICKED(IDC_BUTTON_SEL_BNOROICIRCLE, &CBottomDlg::OnBnClickedButtonSelBnoroicircle)
	ON_BN_CLICKED(IDC_BUTTON_SEL_BNOROICLEAR, &CBottomDlg::OnBnClickedButtonSelBnoroiclear)
	ON_BN_CLICKED(IDC_BUTTON_SEL_BNOROISHOW, &CBottomDlg::OnBnClickedButtonSelBnoroishow)
END_MESSAGE_MAP()


// CBottomDlg 消息处理程序


void CBottomDlg::OnBnClickedButtonSelBroi()
{
	// TODO:  在此添加控件通知处理程序代码
	if (NO_RECT != g.Controller.ROI_rect) { AfxMessageBox(show_roi_msg(g.Controller.ROI_rect)); return; }
	HTuple  Exception;
	HException::InstallHHandler(&CPPExpDefaultExceptionHandler);
	set_check("~give_error");
	try
	{
		g.Controller.ROI_rect = BROI_RECT;
		double row, col, row2, col2;
		Hobject ROI;
		Halcon::set_color(g.show_image.get_disp_hd1(), "green");
		set_draw(g.show_image.get_disp_hd1(), "margin");
		draw_rectangle1(g.show_image.get_disp_hd1(), &row, &col, &row2, &col2);
		gen_rectangle1(&ROI, row, col, row2, col2);
		disp_obj(ROI, g.show_image.get_disp_hd1());
		g.ini.BROI_x = col;
		g.ini.BROI_y = row;
		g.ini.BROI_w = col2;
		g.ini.BROI_h = row2;
		g.ini.SaveParaFile(PARA_IMAGE);
		g.Controller.ROI_rect = NO_RECT;
	}
	catch (HException &HDevExpDefaultException) 
	{
		HDevExpDefaultException.ToHTuple(&Exception);
		write_string(36000, Exception);
		set_check("~give_error");
		g.Controller.ROI_rect = NO_RECT;
		AfxMessageBox(L"设定搜索范围失败！");
	}
}


void CBottomDlg::OnBnClickedButtonShowBroi()
{
	// TODO:  在此添加控件通知处理程序代码
	if (NO_RECT != g.Controller.ROI_rect) { AfxMessageBox(show_roi_msg(g.Controller.ROI_rect)); return; }
	HTuple  Exception;
	HException::InstallHHandler(&CPPExpDefaultExceptionHandler);
	set_check("give_error");
	try
	{
		double row = g.ini.BROI_y, col = g.ini.BROI_x, col2 = g.ini.BROI_w, row2 = g.ini.BROI_h;
		Hobject ROI;
		Halcon::set_color(g.show_image.get_disp_hd1(), "red");
		set_draw(g.show_image.get_disp_hd1(), "margin");
		gen_rectangle1(&ROI, row, col, row2, col2);
		disp_obj(ROI, g.show_image.get_disp_hd1());
	}
	catch (HException &HDevExpDefaultException)
	{
		AfxMessageBox(L"error!");
		HDevExpDefaultException.ToHTuple(&Exception);
		write_string(36000, Exception);
		set_check("~give_error");;

	}
}


BOOL CBottomDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  在此添加额外的初始化
	CString str;
	str.Format(_T("%d"), static_cast<int>(g.ini.bottom_threshold));
	GetDlgItem(IDC_EDIT_THRESHOLD2)->SetWindowText(str);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CBottomDlg::OnBnClickedButtonBshowTsavemodel()
{
	// TODO:  在此添加控件通知处理程序代码
	if (WAIT_OBJECT_0 == ::WaitForSingleObject(g.evt_capture1.evt, 1)) { AfxMessageBox(L"底部相机正在拍摄中！"); return; }
	if (NO_RECT != g.Controller.ROI_rect) { AfxMessageBox(show_roi_msg(g.Controller.ROI_rect)); return; }

	win_tool wt;
	//	win_tool wt;
	CString AppPath = wt.AppPath();
	AppPath += L"\\" + g.prjini.m_Prj_Name + L"\\BottomModel";
	CreateDirectory(AppPath, NULL);

	CString FileName = g.prjini.m_Prj_Name + L"\\BottomModel\\" + wt.Get_Date_Time() + L".bmp";
	set_check("~give_error");
	write_image(g.hRawImage1, "bmp", 0, (char*)(LPCSTR)(CStringA)FileName);
	g.show_image.Dis_Obj1(g.hRawImage1);
	return;

	CComboBox* pBox = (CComboBox*)GetDlgItem(IDC_COMBO_BMODELSEL);
	int nSel = pBox->GetCurSel();
	// 根据选中项索引获取该项字符串
	CString str;
	pBox->GetLBText(nSel, str);


	HException::InstallHHandler(&CPPExpDefaultExceptionHandler);
	try{
		set_check("give_error");
		CString ImageName = AppPath + str + ".bmp";
		write_image(g.hRawImage1, "bmp", 0, (char*)(LPCSTR)(CStringA)ImageName);
		g.show_image.Dis_Obj1(g.hRawImage1);
	}
	catch (HException &HDevExpDefaultException)
	{
		set_check("~give_error");
	}
}

/**
void CBottomDlg::OnBnClickedButtonBselall()
{
	// TODO:  在此添加控件通知处理程序代码
	int  i = IDC_CHECKB1;
	int iend = IDC_CHECKB12;
	for (; i <= iend; i++)
	{
		((CButton*)GetDlgItem(i))->SetCheck(1);
	}
}
*/


void CBottomDlg::OnBnClickedButtonBtrainmodel()
{
	// TODO:  在此添加控件通知处理程序代码
	if (SYSRUNNING == (SYSRUNNING & g.Controller.SysState) || SYSBOTTOMTRAIN == (SYSBOTTOMTRAIN & g.Controller.SysState))
	{
		AfxMessageBox(L"系统正在运行中或者正在训练中！");
		return;
	}

	RunTrain();
	return;

	int l_selsetcheck = 0;
	const int start_index = IDC_CHECKB1;
	const int end_index = IDC_CHECKB12;
	int l_mask = 1;
	for (int i = 1; i <= (1 + end_index - start_index); i++)
	{
		if (((CButton*)GetDlgItem(start_index + i - 1))->GetCheck())
		{
			l_selsetcheck |= l_mask;
		}
		l_mask = l_mask << 1;
	}
	g.ini.m_BottomModel = l_selsetcheck;
	g.ini.SaveParaFile(PARA_IMAGE);
	RunTrain();
	
}


bool CBottomDlg::RunTrain()
{
	if (isRunTrain) return false;
	pRunTrain = AfxBeginThread(RunTrainThread, this, THREAD_PRIORITY_ABOVE_NORMAL, 0, 0, NULL);
	return true;
}

UINT CBottomDlg::RunTrainThread(LPVOID lp)
{
	CBottomDlg* pDlg = (CBottomDlg*)lp;
	pDlg->isRunTrain = true;
	g.Controller.SysState |= SYSBOTTOMTRAIN;
	if (pDlg->train())
	{
		g.Controller.SysState &= ~SYSBOTTOMTRAIN;//让系统无法进行训练，如果在运行的时候
		g.Controller.SysState &= ~SYSLOADDATAERROR;
//		g.img_deal.write_bottom_params(g.prjini.m_Prj_Name);

	}
	else
	{
		g.Controller.SysState &= ~SYSBOTTOMTRAIN;//让系统无法进行训练，如果在运行的时候
		g.Controller.SysState |= SYSLOADDATAERROR;
		AfxMessageBox(L"第二个训练错误\r\n1.确保画了搜索框\r\n2.确保有图片并且大小一致\r\n3.勾选了模板序列？\r\n4.确保参数正确");
	}
	pDlg->isRunTrain = false;
	return 0;
}



vector<CString> CBottomDlg::get_train_img_path()
{
	vector<CString> str;
	win_tool wt;
	CString AppPath = wt.AppPath();
	AppPath += L"\\" + g.prjini.m_Prj_Name + L"\\BottomModel\\";

	int l_selsetcheck = g.ini.m_BottomModel;
	int l_mask = 1;
	for (int i = 1; i <= _MODEL_MAX; i++)
	{
		if (l_selsetcheck&l_mask)
		{
			CString l_serial, path;
			l_serial.Format(_T("%d.bmp"), i);
			path = AppPath + l_serial;
			str.push_back(path);
		}
		l_mask = l_mask << 1;
	}
	return str;
}



bool CBottomDlg::train_img(vector<CString> str)
{
	vector<std::string> imgpath;
	for (size_t i = 0; i < str.size(); i++)
	{
		imgpath.push_back((std::string)(CStringA)str[i]);
	}


#ifdef _HALCON
	_Params p;
	p.threshold_get_prod = g.ini.bottom_threshold;
	p.MatchScore = g.ini.bottom_match_score;
	p.TrainScore = g.ini.bottom_train_score;
	p.ROI_row1 = g.ini.BROI_y;
	p.ROI_col1 = g.ini.BROI_x;
	p.ROI_row2 = g.ini.BROI_h;
	p.ROI_col2 = g.ini.BROI_w;
	set_check("give_error");
	HException::InstallHHandler(&CPPExpDefaultExceptionHandler);
	try{
		return g.img_deal.Back_Train(imgpath, g.show_image.get_disp_hd1(), p);
	}

	catch (HException &HDevExpDefaultException)
	{
		set_check("~give_error");
		return false;
	}

#endif

	return true;
}

bool CBottomDlg::train()
{
	std::vector<CString> images;
	win_tool::CSelectFolderDlg DirPath;
	DirPath.ProcPicDir(g.prjini.m_Prj_Name + L"\\BottomModel", images);
	return train_img(images);
	//return train_img(get_train_img_path());
}




void CBottomDlg::OnBnClickedButtonTest()
{
	// TODO:  在此添加控件通知处理程序代码
	int res = -1; //防止下面不执行的时候res会出现一个随机值
	HException::InstallHHandler(&CPPExpDefaultExceptionHandler);
	try{
		set_check("give_error");

		_Params p;
		p.threshold_get_prod = g.ini.bottom_threshold;
		p.MatchScore = g.ini.bottom_match_score;
		p.TrainScore = g.ini.bottom_train_score;
		p.ROI_row1 = g.ini.BROI_y;
		p.ROI_col1 = g.ini.BROI_x;
		p.ROI_row2 = g.ini.BROI_h;
		p.ROI_col2 = g.ini.BROI_w;
		res = g.img_deal.Back_Deal(g.hRawImage1, g.show_image.get_disp_hd1(), p);
	}
	catch (HException &HDevExpDefaultException)
	{
		set_check("~give_error");
	}
	//AfxMessageBox(L"ok!!!");

}

void CBottomDlg::OnBnClickedButtonBcap()
{
	// TODO:  在此添加控件通知处理程序代码

	if (isCap)
	{
		GetDlgItem(IDC_BUTTON_BCAP)->SetWindowText(L"合成中");
		return;
	}
	pCap = AfxBeginThread(RunCapThread, this, THREAD_PRIORITY_NORMAL, 0, 0, NULL);
	return;


}

UINT CBottomDlg::RunCapThread(LPVOID lp)
{
	CBottomDlg *pDlg = (CBottomDlg*)lp;
	pDlg->isCap = true;

	if (WAIT_OBJECT_0 == ::WaitForSingleObject(g.evt_capture1.evt, 0) || g.mc.isRunning(SECOND_MOTOR))
	{
		pDlg->GetDlgItem(IDC_BUTTON_BCAP)->SetWindowText(L"合成中");
		Sleep(500);
		pDlg->GetDlgItem(IDC_BUTTON_BCAP)->SetWindowText(L"采集图片");
		goto endfun1;
	}

	g.mc.MoveToOrigin(SECOND_MOTOR, g.ini.m_SndMtr.MaxSpeed, g.ini.m_SndMtr.Tacc);
	if (!g.mc.Wait(SECOND_MOTOR, 10000))
	{
		goto endfun1;
	}
	g.mc.Stop(SECOND_MOTOR);
	Sleep(200);
	g.mc.MoveToDes(SECOND_MOTOR, g.ini.m_SndMtr.InitSpeed, g.ini.m_SndMtr.MaxSpeed, g.ini.m_SndMtr.Tacc, g.ini.m_SndMtr.Waves);
	g.evt_capture1.SetEvent();
	for (; g.evt_capture1.EventState();){ Sleep(20); }
	g.show_image.Dis_Obj1(g.hRawImage1);
endfun1:
	pDlg->isCap = false;
	pDlg->GetDlgItem(IDC_BUTTON_BCAP)->SetWindowText(L"采集图片");
	return 0;
}

void CBottomDlg::OnBnClickedButtonLoad2()
{
	// TODO:  在此添加控件通知处理程序代码
	CFileDialog fileDlg(TRUE, (LPCTSTR)"BMP", L"", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"All Files (*.*)|*.*|位图文件 (*.bmp)|*.bmp||");	//打开读取文件对话框
	if (fileDlg.DoModal() != IDOK) return;
	read_image(&g.hRawImage1, (char*)(LPCSTR)CStringA(fileDlg.GetPathName()));
	g.show_image.Dis_Obj1(g.hRawImage1);
}


void CBottomDlg::OnBnClickedButtonTestt2()
{
	// TODO:  在此添加控件通知处理程序代码
	CString str;
	GetDlgItem(IDC_EDIT_THRESHOLD2)->GetWindowText(str);
	int _threshold = _ttoi(str);
#ifdef _HALCON
	set_check("~give_error");
	Halcon::Hobject obj, org;
	Halcon::bit_not(g.hRawImage1, &org);
	Halcon::threshold(org, &obj, _threshold, 255);
	Halcon::set_draw(g.show_image.get_disp_hd1(), "fill");
	Halcon::clear_window(g.show_image.get_disp_hd1());
	g.show_image.Dis_Obj1(obj);
	Halcon::set_draw(g.show_image.get_disp_hd1(), "margin");
	set_check("give_error");
#endif
}


void CBottomDlg::OnBnClickedButtonComfirmpara2()
{
	// TODO:  在此添加控件通知处理程序代码
	CString str;
	GetDlgItem(IDC_EDIT_THRESHOLD2)->GetWindowText(str);
	g.ini.bottom_threshold = static_cast<float>(_ttoi(str));
	g.ini.SaveParaFile(PARA_ALL);
}


void CBottomDlg::OnBnClickedButtonBshowFolder()
{
	// TODO:  在此添加控件通知处理程序代码
	win_tool wt;
	CString path = wt.AppPath() + L"\\" + g.prjini.m_Prj_Name + L"\\BottomModel";
	ShellExecute(NULL, L"open", _T("explorer.exe"), path, NULL, SW_SHOW);
}


void CBottomDlg::OnBnClickedButtonSelBnoroirect()
{
	// TODO:  在此添加控件通知处理程序代码
	// TODO:  在此添加控件通知处理程序代码
	if (NO_RECT != g.Controller.ROI_rect) { AfxMessageBox(show_roi_msg(g.Controller.ROI_rect)); return; }
	HTuple  Exception;
	HException::InstallHHandler(&CPPExpDefaultExceptionHandler);
	set_check("~give_error");
	try
	{
		g.Controller.ROI_rect = BNROI_RECT;
		double row, col, row2, col2;
		Hobject ROI;
		Halcon::set_color(g.show_image.get_disp_hd1(), "green");
		set_draw(g.show_image.get_disp_hd1(), "fill");
		draw_rectangle1(g.show_image.get_disp_hd1(), &row, &col, &row2, &col2);
		gen_rectangle1(&ROI, row, col, row2, col2);
		g.img_deal.unionBNoROI(ROI);//向已有的
		disp_obj(g.img_deal.GetBNoROI(), g.show_image.get_disp_hd1());
		g.img_deal.write_bottom_nroi(g.prjini.m_Prj_Name);//保存region
		g.Controller.ROI_rect = NO_RECT;
	}
	catch (HException &HDevExpDefaultException)
	{
		HDevExpDefaultException.ToHTuple(&Exception);
		write_string(36000, Exception);
		set_check("~give_error");
		g.Controller.ROI_rect = NO_RECT;
		AfxMessageBox(L"设定搜索范围失败！");
	}
}


void CBottomDlg::OnBnClickedButtonSelBnoroicircle()
{
	// TODO:  在此添加控件通知处理程序代码
	if (NO_RECT != g.Controller.ROI_rect) { AfxMessageBox(show_roi_msg(g.Controller.ROI_rect)); return; }
	HTuple  Exception;
	HException::InstallHHandler(&CPPExpDefaultExceptionHandler);
	set_check("~give_error");
	try
	{
		g.Controller.ROI_rect = BNROI_RECT;
		double row, col, phi, radius1, radius2;
		Hobject ROI;
		Halcon::set_color(g.show_image.get_disp_hd1(), "green");
		set_draw(g.show_image.get_disp_hd1(), "fill");
		draw_ellipse(g.show_image.get_disp_hd1(), &row, &col, &phi, &radius1, &radius2);
		gen_ellipse(&ROI, row, col, phi, radius1, radius2);
		g.img_deal.unionBNoROI(ROI);//向已有的
		disp_obj(g.img_deal.GetBNoROI(), g.show_image.get_disp_hd1());
		g.img_deal.write_bottom_nroi(g.prjini.m_Prj_Name);//保存region
		g.Controller.ROI_rect = NO_RECT;
	}
	catch (HException &HDevExpDefaultException)
	{
		HDevExpDefaultException.ToHTuple(&Exception);
		write_string(36000, Exception);
		set_check("~give_error");
		g.Controller.ROI_rect = NO_RECT;
		AfxMessageBox(L"设定搜索范围失败！");
	}
}


void CBottomDlg::OnBnClickedButtonSelBnoroiclear()
{
	// TODO:  在此添加控件通知处理程序代码
	if (NO_RECT != g.Controller.ROI_rect) { AfxMessageBox(show_roi_msg(g.Controller.ROI_rect)); return; }
	HTuple  Exception;
	HException::InstallHHandler(&CPPExpDefaultExceptionHandler);
	set_check("~give_error");
	try
	{
		g.img_deal.clearBNROI();
		disp_obj(g.hRawImage1, g.show_image.get_disp_hd1());
		disp_obj(g.img_deal.GetBNoROI(), g.show_image.get_disp_hd1());
		g.img_deal.write_bottom_nroi(g.prjini.m_Prj_Name);//保存region
	}
	catch (HException &HDevExpDefaultException)
	{
		HDevExpDefaultException.ToHTuple(&Exception);
		write_string(36000, Exception);
		set_check("~give_error");
		g.Controller.ROI_rect = NO_RECT;
		AfxMessageBox(L"设定搜索范围失败！");
	}
}


void CBottomDlg::OnBnClickedButtonSelBnoroishow()
{
	// TODO:  在此添加控件通知处理程序代码
	set_check("~give_error");
	disp_obj(g.hRawImage1, g.show_image.get_disp_hd1());
	disp_obj(g.img_deal.GetBNoROI(), g.show_image.get_disp_hd1());
	set_check("give_error");
}
