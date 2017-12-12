// TopCamDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ImageVision.h"
#include "TopCamDlg.h"
#include "afxdialogex.h"
#include "Tools.h"
#include <iostream>
using namespace std;
// CTopCamDlg 对话框

IMPLEMENT_DYNAMIC(CTopCamDlg, CDialogEx)

CTopCamDlg::CTopCamDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTopCamDlg::IDD, pParent)
{
	isTrain = false;
	isCap = false;
}

CTopCamDlg::~CTopCamDlg()
{
}

void CTopCamDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTopCamDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CTopCamDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_SEL_TROI, &CTopCamDlg::OnBnClickedButtonSelTroi)
	ON_BN_CLICKED(IDC_BUTTON_SHOW_TROI, &CTopCamDlg::OnBnClickedButtonShowTroi)
	ON_BN_CLICKED(IDC_BUTTON_SHOW_TSAVEMODEL, &CTopCamDlg::OnBnClickedButtonShowTsavemodel)
	ON_CBN_SELCHANGE(IDC_COMBO_MODELSEL, &CTopCamDlg::OnSelchangeComboModelsel)
	ON_BN_CLICKED(IDC_BUTTON_SHOW_MODEL, &CTopCamDlg::OnBnClickedButtonShowModel)
	ON_BN_CLICKED(IDC_BUTTON_TRAINMODEL, &CTopCamDlg::OnBnClickedButtonTrainmodel)
//	ON_BN_CLICKED(IDC_BUTTON_SELALL, &CTopCamDlg::OnBnClickedButtonSelall)
	ON_BN_CLICKED(IDC_BUTTON_CAP, &CTopCamDlg::OnBnClickedButtonCap)
	ON_BN_CLICKED(IDC_BUTTON_TESTT, &CTopCamDlg::OnBnClickedButtonTestt)
	ON_BN_CLICKED(IDC_BUTTON_COMFIRMPARA, &CTopCamDlg::OnBnClickedButtonComfirmpara)
	ON_BN_CLICKED(IDC_BUTTON_LOAD, &CTopCamDlg::OnBnClickedButtonLoad)
	ON_BN_CLICKED(IDC_BUTTON_SEL_TDROI1, &CTopCamDlg::OnBnClickedButtonSelTdroi1)
	ON_BN_CLICKED(IDC_BUTTON_SHOW_TDROI1, &CTopCamDlg::OnBnClickedButtonShowTdroi1)
	ON_BN_CLICKED(IDC_BUTTON_TDTEST1, &CTopCamDlg::OnBnClickedButtonTdtest1)
	ON_BN_CLICKED(IDC_BUTTON_SEL_TDROI2, &CTopCamDlg::OnBnClickedButtonSelTdroi2)
	ON_BN_CLICKED(IDC_BUTTON_SHOW_TDROI2, &CTopCamDlg::OnBnClickedButtonShowTdroi2)
	ON_BN_CLICKED(IDC_BUTTON_TDTEST2, &CTopCamDlg::OnBnClickedButtonTdtest2)
	ON_BN_CLICKED(IDC_BUTTON_TAREACOMF, &CTopCamDlg::OnBnClickedButtonTareacomf)
	ON_BN_CLICKED(IDC_BUTTON_SHOW_TFOLDER, &CTopCamDlg::OnBnClickedButtonShowTfolder)
	ON_BN_CLICKED(IDC_BUTTON_SEL_TNOROIRECT, &CTopCamDlg::OnBnClickedButtonSelTnoroirect)
	ON_BN_CLICKED(IDC_BUTTON_SEL_TNOROICIRCLE, &CTopCamDlg::OnBnClickedButtonSelTnoroicircle)
	ON_BN_CLICKED(IDC_BUTTON_SEL_TNOROICLEAR, &CTopCamDlg::OnBnClickedButtonSelTnoroiclear)
	ON_BN_CLICKED(IDC_BUTTON_SEL_TNOROISHOW, &CTopCamDlg::OnBnClickedButtonSelTnoroishow)
END_MESSAGE_MAP()


// CTopCamDlg 消息处理程序


void CTopCamDlg::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	int res = -1; //防止下面不执行的时候res会出现一个随机值
	HException::InstallHHandler(&CPPExpDefaultExceptionHandler);
	try{
		set_check("give_error");

		_Params p;
		p.threshold_get_prod = g.ini.top_threshold;
		p.MatchScore = g.ini.top_match_score;
		p.TrainScore = g.ini.top_train_score;
		p.ROI_row1 = g.ini.TROI_y;
		p.ROI_col1 = g.ini.TROI_x;
		p.ROI_row2 = g.ini.TROI_h;
		p.ROI_col2 = g.ini.TROI_w;

		res = g.img_deal.Front_Deal(g.hRawImage, g.show_image.get_disp_hd(), p);


	}
	catch (HException &HDevExpDefaultException)
	{
		set_check("~give_error");
	}

	return;



}


void CTopCamDlg::OnBnClickedButtonSelTroi()
{
	// TODO:  在此添加控件通知处理程序代码
	 	if (NO_RECT != g.Controller.ROI_rect) { AfxMessageBox(show_roi_msg(g.Controller.ROI_rect)); return; }
	 		HTuple  Exception;
	 		HException::InstallHHandler(&CPPExpDefaultExceptionHandler);
	 		set_check("~give_error");
	 		try
	 		{
	 			g.Controller.ROI_rect = TROI_RECT;
	 			double row, col, row2, col2;
	 			Hobject ROI;
	 			Halcon::set_color(g.show_image.get_disp_hd(),"green");
	 			set_draw(g.show_image.get_disp_hd(), "margin");
	 			draw_rectangle1(g.show_image.get_disp_hd(), &row, &col, &row2, &col2);
	 			gen_rectangle1(&ROI, row, col,row2, col2);
	 			disp_obj(ROI, g.show_image.get_disp_hd());
	 			g.ini.TROI_x = col;
	 			g.ini.TROI_y = row;
	 			g.ini.TROI_w = col2;
	 			g.ini.TROI_h = row2;
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


void CTopCamDlg::OnBnClickedButtonShowTroi()
{
	// TODO:  在此添加控件通知处理程序代码
	
#if 1
	if (NO_RECT != g.Controller.ROI_rect) { AfxMessageBox(show_roi_msg(g.Controller.ROI_rect)); return; }
	HTuple  Exception;
	HException::InstallHHandler(&CPPExpDefaultExceptionHandler);
	set_check("give_error");
	try
	{ 
		double row = g.ini.TROI_y, col = g.ini.TROI_x, col2 = g.ini.TROI_w, row2 = g.ini.TROI_h;
		Hobject ROI;
		Halcon::set_color(g.show_image.get_disp_hd(), "red");
		set_draw(g.show_image.get_disp_hd(), "margin");
		gen_rectangle1(&ROI, row, col, row2, col2);
		disp_obj(ROI, g.show_image.get_disp_hd());
	}
	catch (HException &HDevExpDefaultException)
	{
		HDevExpDefaultException.ToHTuple(&Exception);
		write_string(36000, Exception);
		set_check("~give_error");;
	}
#endif

}

void CTopCamDlg::OnBnClickedButtonShowTsavemodel()
{
	// TODO:  在此添加控件通知处理程序代码
	if (WAIT_OBJECT_0 == ::WaitForSingleObject(g.evt_capture.evt, 1)) { AfxMessageBox(L"相机正在拍摄中！"); return; }
	if (NO_RECT != g.Controller.ROI_rect) { AfxMessageBox(show_roi_msg(g.Controller.ROI_rect)); return; }

	win_tool wt;
	//	win_tool wt;
	CString AppPath = wt.AppPath();
	AppPath += L"\\" + g.prjini.m_Prj_Name + L"\\TopModel";
	CreateDirectory(AppPath, NULL);
	CString FileName = g.prjini.m_Prj_Name + L"\\TopModel\\" + wt.Get_Date_Time() + L".bmp";
	set_check("~give_error");
	write_image(g.hRawImage, "bmp", 0, (char*)(LPCSTR)(CStringA)FileName);
	g.show_image.Dis_Obj(g.hRawImage);
	return;

	CComboBox* pBox = (CComboBox*)GetDlgItem(IDC_COMBO_MODELSEL);
	int nSel = pBox->GetCurSel();
	// 根据选中项索引获取该项字符串
	CString str;
	pBox->GetLBText(nSel, str);
	


	HException::InstallHHandler(&CPPExpDefaultExceptionHandler);
	try{
		set_check("~give_error");
		CString ImageName = AppPath + str + ".bmp";
		write_image(g.hRawImage, "bmp", 0, (char*)(LPCSTR)(CStringA)ImageName);
		g.show_image.Dis_Obj(g.hRawImage);
	}
	catch (HException &HDevExpDefaultException)
	{
		set_check("~give_error");
	}


}


void CTopCamDlg::OnSelchangeComboModelsel()
{
	// TODO:  在此添加控件通知处理程序代码
	CComboBox* pBox = (CComboBox*)GetDlgItem(IDC_COMBO_MODELSEL);
	int nSel = pBox->GetCurSel();
	// 根据选中项索引获取该项字符串
	CString str;
	pBox->GetLBText(nSel, str);
	nSel = _ttoi(str);

}


BOOL CTopCamDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CString str;
	str.Format(_T("%d"), (int)g.ini.top_threshold);
	GetDlgItem(IDC_EDIT_THRESHOLD)->SetWindowText(str);
	str.Format(_T("%d"), (int)g.ini.top_area1);
	GetDlgItem(IDC_EDIT_TAREA1)->SetWindowText(str);
	str.Format(_T("%d"), (int)g.ini.top_area2);
	GetDlgItem(IDC_EDIT_TAREA2)->SetWindowText(str);
	str.Format(_T("%d"), (int)g.ini.top_area_uplimit);
	GetDlgItem(IDC_EDIT_TAREAUPLIMIT)->SetWindowText(str);
	str.Format(_T("%d"), (int)g.ini.top_area_downlimit);
	GetDlgItem(IDC_EDIT_TAREADOWNLIMIT)->SetWindowText(str);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CTopCamDlg::OnBnClickedButtonShowModel()
{
	win_tool wt;
	CString fileName = wt.Get_Date_Time();
	CString AppPath = wt.AppPath();
	AppPath = AppPath + L"\\" + g.prjini.m_Prj_Name + L"\\" + L"ScaledImage";
	CreateDirectory(AppPath, NULL);
	CString str = AppPath + L"\\" + fileName + L".bmp";

#ifdef _HALCON
	HException::InstallHHandler(&CPPExpDefaultExceptionHandler);
	try{
		set_check("give_error");
		Halcon::Hobject ScaledImage;
		Halcon::HTuple Width, Height, iniWidth((double)g.ini.m_topwScaleTo);
		get_image_size(g.hRawImage, &Width, &Height);
		if (g.ini.m_TopRatio <= 0)
		{
			double w = Width[0].D();
			double h = Height[0].D();
			double Ratio = h / w;
			Height = (int)(Ratio*(double)g.ini.m_topwScaleTo);
		}
		Width = (int)g.ini.m_topwScaleTo;
		zoom_image_size(g.hRawImage, &ScaledImage, Width, Height, "weighted");
		Halcon::write_image(ScaledImage, "bmp", NULL, (char*)(LPCSTR)(CStringA)str);
		g.show_image.Dis_Obj(ScaledImage);
	}
	catch (HException &CPPExpDefaultExceptionHandler)
	{
		set_check("~give_error");
		TRACE(CPPExpDefaultExceptionHandler);
		AfxMessageBox(L"没有图片，保存失败");	
	}
#endif
	// TODO:  在此添加控件通知处理程序代码
}


void CTopCamDlg::OnBnClickedButtonTrainmodel()
{
	// TODO:  在此添加控件通知处理程序代码
	//GetDlgItem(IDC_BUTTON_TRAINMODEL)->
	
	if (SYSRUNNING == (SYSRUNNING & g.Controller.SysState) || SYSTOPTRAIN == (SYSTOPTRAIN & g.Controller.SysState))
	{
		AfxMessageBox(L"系统正在运行中或者正在训练中！");
		return;
	}

	RunTrain();
	return;

	int l_selsetcheck = 0;
	const int start_index = IDC_CHECK1;
	const int end_index = IDC_CHECK12;
	int l_mask = 1;
	for (int i = 1; i <= (1 + end_index - start_index); i++)
	{
		if (((CButton*)GetDlgItem(start_index + i - 1))->GetCheck())
		{
			l_selsetcheck |= l_mask;
		}
		l_mask = l_mask << 1;
	}
	g.ini.m_TopModel = l_selsetcheck;
	g.ini.SaveParaFile(PARA_IMAGE);
	
}


bool CTopCamDlg::RunTrain()
{
	if (isTrain) return false;
	pRunTrain = AfxBeginThread(RunTrainThread, this, THREAD_PRIORITY_ABOVE_NORMAL, 0, 0, NULL);
	if (!pRunTrain) return false;
	return true;
}

UINT CTopCamDlg::RunTrainThread(LPVOID lp)
{
	CTopCamDlg* pDlg = (CTopCamDlg*)lp;
	pDlg->isTrain = true;
	g.Controller.SysState  |= SYSTOPTRAIN;
	if (pDlg->train())
	{
		g.Controller.SysState &= ~SYSLOADDATAERROR;
		g.Controller.SysState &= ~SYSTOPTRAIN;//让系统无法进行训练，如果在运行的时候
	}
	else
	{
		g.Controller.SysState &= ~SYSTOPTRAIN;//让系统无法进行训练，如果在运行的时候
		g.Controller.SysState |= SYSLOADDATAERROR;
		AfxMessageBox(L"第一个训练错误\r\n1.确保画了搜索框\r\n2.确保有图片并且大小一致\r\n3.勾选了模板序列？\r\n4.确保参数正确");
	}
	pDlg->isTrain = false;
	return 0;
}



vector<CString> CTopCamDlg::get_train_img_path()
{
	vector<CString> str;
	win_tool wt;
	CString AppPath = wt.AppPath();
	AppPath += L"\\" + g.prjini.m_Prj_Name + L"\\TopModel\\";

	int l_selsetcheck  = g.ini.m_TopModel;
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



bool CTopCamDlg::train_img(vector<CString> str)
{
	vector<std::string> imgpath;
	for (size_t i = 0; i < str.size(); i++)
	{
		imgpath.push_back((std::string)(CStringA)str[i]);
	}


#ifdef _HALCON
	_Params p;
	p.threshold_get_prod = g.ini.top_threshold;
	p.MatchScore = g.ini.top_match_score;
	p.TrainScore = g.ini.top_train_score;
		vector<Hobject> ROIS;
		Halcon::Hobject ROI;
		p.ROI_row1 = g.ini.TROI_y;
		p.ROI_col1 = g.ini.TROI_x;
		p.ROI_row2 = g.ini.TROI_h;
		p.ROI_col2 = g.ini.TROI_w;
		set_check("give_error");
		HException::InstallHHandler(&CPPExpDefaultExceptionHandler);
		try{
			return g.img_deal.Front_Train(imgpath, g.show_image.get_disp_hd(), p);
		}
	
		catch (HException &HDevExpDefaultException)
		{
			set_check("~give_error");
			return false;
		}

#endif
	
	return true;
}

bool CTopCamDlg::train()
{
	std::vector<CString> images;
	win_tool::CSelectFolderDlg DirPath;
	DirPath.ProcPicDir(g.prjini.m_Prj_Name + L"\\TopModel", images);
	return train_img(images);
	//return train_img(get_train_img_path());
}




void CTopCamDlg::OnBnClickedButtonCap()
{
	// TODO:  在此添加控件通知处理程序代码
	if (isCap)
	{
		GetDlgItem(IDC_BUTTON_CAP)->SetWindowText(L"合成中");
		return;
	}
	pCap = AfxBeginThread(RunCapThread, this, THREAD_PRIORITY_NORMAL, 0, 0, NULL);
	return;


#ifdef _TEST
	//g.mc.MoveToOrigin(FIRST_MOTOR, g.ini.m_FstMtr.MaxSpeed, g.ini.m_FstMtr.Tacc);

#else
	if (FST_MOTOR_NOT_ALREADY == (FST_MOTOR_NOT_ALREADY&g.Controller.SysState))
	{
		AfxMessageBox(L"第二轴电机没有复位！");
	}
#endif
	if (WAIT_OBJECT_0 == ::WaitForSingleObject(g.evt_capture.evt, 0) || g.mc.isRunning(FIRST_MOTOR))
	{
		GetDlgItem(IDC_BUTTON_CAP)->SetWindowText(L"合成中");
		Sleep(500);
		return;
	}


}


UINT CTopCamDlg::RunCapThread(LPVOID lp)
{
	CTopCamDlg *pDlg = (CTopCamDlg*)lp;
	pDlg->isCap = true;

	if (WAIT_OBJECT_0 == ::WaitForSingleObject(g.evt_capture.evt, 0) || g.mc.isRunning(FIRST_MOTOR))
	{
		pDlg->GetDlgItem(IDC_BUTTON_CAP)->SetWindowText(L"合成中");
		Sleep(500);
		pDlg->GetDlgItem(IDC_BUTTON_CAP)->SetWindowText(L"采集图片");
		goto endfun;
	}

	g.mc.MoveToOrigin(FIRST_MOTOR, g.ini.m_FstMtr.MaxSpeed, g.ini.m_FstMtr.Tacc);
	if (!g.mc.Wait(FIRST_MOTOR, 10000))
	{
		goto endfun;
	}
	g.mc.Stop(FIRST_MOTOR);
	Sleep(200);
	g.mc.MoveToDes(FIRST_MOTOR, g.ini.m_FstMtr.InitSpeed, g.ini.m_FstMtr.MaxSpeed, g.ini.m_FstMtr.Tacc, g.ini.m_FstMtr.Waves);
	g.evt_capture.SetEvent();	
	for (; g.evt_capture.EventState();){ Sleep(20); }
	g.show_image.Dis_Obj(g.hRawImage);

	endfun:
	pDlg->isCap = false;
	pDlg->GetDlgItem(IDC_BUTTON_CAP)->SetWindowText(L"采集图片");
	return 0;
}

void CTopCamDlg::OnBnClickedButtonLoad()
{
	// TODO:  在此添加控件通知处理程序代码
	CFileDialog fileDlg(TRUE, (LPCTSTR)"BMP", L"", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"All Files (*.*)|*.*|位图文件 (*.bmp)|*.bmp||");	//打开读取文件对话框
	if (fileDlg.DoModal() != IDOK) return;
	read_image(&g.hRawImage, (char*)(LPCSTR)CStringA(fileDlg.GetPathName()));
	g.show_image.Dis_Obj(g.hRawImage);
}


void CTopCamDlg::OnBnClickedButtonTestt()
{
	// TODO:  在此添加控件通知处理程序代码
	CString str;
	GetDlgItem(IDC_EDIT_THRESHOLD)->GetWindowText(str);
	int _threshold = _ttoi(str);
#ifdef _HALCON
	set_check("~give_error");
	
	Halcon::Hobject obj,org;
	Halcon::bit_not(g.hRawImage,&org);
	Halcon::threshold(org, &obj, _threshold, 255);
	Halcon::set_draw(g.show_image.get_disp_hd(),"fill");
	Halcon::clear_window(g.show_image.get_disp_hd());
	g.show_image.Dis_Obj(obj);
	Halcon::set_draw(g.show_image.get_disp_hd(), "margin");
	set_check("give_error");
#endif
	//g.ini.top_threshold = 
}


void CTopCamDlg::OnBnClickedButtonComfirmpara()
{
	// TODO:  在此添加控件通知处理程序代码
	CString str;
	GetDlgItem(IDC_EDIT_THRESHOLD)->GetWindowText(str);
	g.ini.top_threshold = static_cast<float>(_ttoi(str));
	g.ini.SaveParaFile(PARA_ALL);
}




void CTopCamDlg::OnBnClickedButtonSelTdroi1()
{
	// TODO:  在此添加控件通知处理程序代码
	if (NO_RECT != g.Controller.ROI_rect) { AfxMessageBox(show_roi_msg(g.Controller.ROI_rect)); return; }
	HTuple  Exception;
	HException::InstallHHandler(&CPPExpDefaultExceptionHandler);
	set_check("~give_error");
	try
	{
		g.Controller.ROI_rect = TDROI_RECT1;
		double row, col, row2, col2;
		Hobject ROI;
		Halcon::set_color(g.show_image.get_disp_hd(), "yellow");
		set_draw(g.show_image.get_disp_hd(), "margin");
		draw_rectangle1(g.show_image.get_disp_hd(), &row, &col, &row2, &col2);
		gen_rectangle1(&ROI, row, col, row2, col2);
		disp_obj(ROI, g.show_image.get_disp_hd());
		g.ini.TDROI1.x = col;
		g.ini.TDROI1.y = row;
		g.ini.TDROI1.w = col2;
		g.ini.TDROI1.h = row2;
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


void CTopCamDlg::OnBnClickedButtonShowTdroi1()
{
	// TODO:  在此添加控件通知处理程序代码
	if (NO_RECT != g.Controller.ROI_rect) { AfxMessageBox(show_roi_msg(g.Controller.ROI_rect)); return; }
	HTuple  Exception;
	HException::InstallHHandler(&CPPExpDefaultExceptionHandler);
	set_check("give_error");
	try
	{
		double row = g.ini.TDROI1.y, col = g.ini.TDROI1.x, col2 = g.ini.TDROI1.w, row2 = g.ini.TDROI1.h;
		Hobject ROI;
		Halcon::set_color(g.show_image.get_disp_hd(), "blue");
		set_draw(g.show_image.get_disp_hd(), "fill");
		gen_rectangle1(&ROI, row, col, row2, col2);
		disp_obj(ROI, g.show_image.get_disp_hd());
	}
	catch (HException &HDevExpDefaultException)
	{
		HDevExpDefaultException.ToHTuple(&Exception);
		write_string(36000, Exception);
		set_check("~give_error");;
	}
}


void CTopCamDlg::OnBnClickedButtonTdtest1()
{
	// TODO:  在此添加控件通知处理程序代码
	HTuple  Exception;
	HException::InstallHHandler(&CPPExpDefaultExceptionHandler);
	CString str;
	GetDlgItem(IDC_EDIT_TAREA1)->GetWindowText(str);
	g.ini.top_area1 = _ttof(str);
	g.ini.SaveParaFile(PARA_IMAGE);
	set_check("give_error");
	try
	{
		Halcon::HTuple winHandle = g.show_image.get_disp_hd();
		_Params p;
		p.ROI_col1 = g.ini.TDROI1.x; p.ROI_col2 = g.ini.TDROI1.w; p.ROI_row1 = g.ini.TDROI1.y; p.ROI_row2 = g.ini.TDROI1.h;
		p.AreaUpLimt = g.ini.top_area_uplimit;
		p.AreaDownLimit = g.ini.top_area_downlimit;
		p.threshold_get_prod = g.ini.top_threshold;
		Halcon::clear_window(winHandle);
		Halcon::disp_obj(g.hRawImage, winHandle);
		Halcon::HTuple img_area = g.img_deal.CheckHole(g.hRawImage, winHandle, p);
		if (img_area[0].D() > g.ini.top_area1)
		{
			set_color(winHandle, "green");
			set_tposition(winHandle, 120, 1);
			write_string(winHandle, "堵孔良好, 面积为: ");
			write_string(winHandle, img_area);
		}
		else
		{
			set_color(winHandle, "red");
			set_tposition(winHandle, 120, 1);
			write_string(winHandle, "堵孔异常, 面积为: ");
			write_string(winHandle, img_area);	
		}
	}
	catch (HException &HDevExpDefaultException)
	{
		HDevExpDefaultException.ToHTuple(&Exception);
		write_string(36000, Exception);
		set_check("~give_error");;
	}
}


void CTopCamDlg::OnBnClickedButtonSelTdroi2()
{
	// TODO:  在此添加控件通知处理程序代码
	if (NO_RECT != g.Controller.ROI_rect) { AfxMessageBox(show_roi_msg(g.Controller.ROI_rect)); return; }
	HTuple  Exception;
	HException::InstallHHandler(&CPPExpDefaultExceptionHandler);
	set_check("~give_error");
	try
	{
		g.Controller.ROI_rect = TDROI_RECT2;
		double row, col, row2, col2;
		Hobject ROI;
		Halcon::set_color(g.show_image.get_disp_hd(), "purple");
		set_draw(g.show_image.get_disp_hd(), "margin");
		draw_rectangle1(g.show_image.get_disp_hd(), &row, &col, &row2, &col2);
		gen_rectangle1(&ROI, row, col, row2, col2);
		disp_obj(ROI, g.show_image.get_disp_hd());
		g.ini.TDROI2.x = col;
		g.ini.TDROI2.y = row;
		g.ini.TDROI2.w = col2;
		g.ini.TDROI2.h = row2;
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


void CTopCamDlg::OnBnClickedButtonShowTdroi2()
{
	// TODO:  在此添加控件通知处理程序代码
	if (NO_RECT != g.Controller.ROI_rect) { AfxMessageBox(show_roi_msg(g.Controller.ROI_rect)); return; }
	HTuple  Exception;
	HException::InstallHHandler(&CPPExpDefaultExceptionHandler);
	set_check("give_error");
	try
	{
		double row = g.ini.TDROI2.y, col = g.ini.TDROI2.x, col2 = g.ini.TDROI2.w, row2 = g.ini.TDROI2.h;
		Hobject ROI;
		Halcon::set_color(g.show_image.get_disp_hd(), "gray");
		set_draw(g.show_image.get_disp_hd(), "fill");
		gen_rectangle1(&ROI, row, col, row2, col2);
		disp_obj(ROI, g.show_image.get_disp_hd());
	}
	catch (HException &HDevExpDefaultException)
	{
		HDevExpDefaultException.ToHTuple(&Exception);
		write_string(36000, Exception);
		set_check("~give_error");;
	}
}


void CTopCamDlg::OnBnClickedButtonTdtest2()
{
	// TODO:  在此添加控件通知处理程序代码
	HTuple  Exception;
	HException::InstallHHandler(&CPPExpDefaultExceptionHandler);
	CString str;
	GetDlgItem(IDC_EDIT_TAREA2)->GetWindowText(str);
	g.ini.top_area2 = _ttof(str);
	g.ini.SaveParaFile(PARA_IMAGE);
	set_check("give_error");
	try
	{
		Halcon::HTuple winHandle = g.show_image.get_disp_hd();
		_Params p;
		p.ROI_col1 = g.ini.TDROI2.x; p.ROI_col2 = g.ini.TDROI2.w; p.ROI_row1 = g.ini.TDROI2.y; p.ROI_row2 = g.ini.TDROI2.h;
		p.AreaUpLimt = g.ini.top_area_uplimit;
		p.AreaDownLimit = g.ini.top_area_downlimit;
		p.threshold_get_prod = g.ini.top_threshold;
		Halcon::clear_window(winHandle);
		Halcon::disp_obj(g.hRawImage, winHandle);
		Halcon::HTuple img_area = g.img_deal.CheckHole(g.hRawImage, winHandle, p);
		if (img_area[0].D() > g.ini.top_area2)
		{
			set_color(winHandle, "green");
			set_tposition(winHandle, 120, 1);
			write_string(winHandle, "堵孔良好, 面积为: ");
			write_string(winHandle, img_area);
		}
		else
		{
			set_color(winHandle, "red");
			set_tposition(winHandle, 120, 1);
			write_string(winHandle, "堵孔异常, 面积为: ");
			write_string(winHandle, img_area);
		}
	}
	catch (HException &HDevExpDefaultException)
	{
		HDevExpDefaultException.ToHTuple(&Exception);
		write_string(36000, Exception);
		set_check("~give_error");;
	}
}




void CTopCamDlg::OnBnClickedButtonTareacomf()
{
	// TODO:  在此添加控件通知处理程序代码
	CString upstr,downstr;
	GetDlgItem(IDC_EDIT_TAREADOWNLIMIT)->GetWindowText(upstr);
	g.ini.top_area_downlimit = _ttof(upstr);
	GetDlgItem(IDC_EDIT_TAREAUPLIMIT)->GetWindowText(downstr);
	g.ini.top_area_uplimit = _ttof(downstr);

	if (g.ini.top_area_uplimit < g.ini.top_area_downlimit)
	{
		GetDlgItem(IDC_EDIT_TAREADOWNLIMIT)->SetWindowText(downstr);
		GetDlgItem(IDC_EDIT_TAREAUPLIMIT)->SetWindowText(upstr);

		*(int*)&g.ini.top_area_downlimit ^= *(int*)&g.ini.top_area_uplimit;
		*(int*)&g.ini.top_area_uplimit ^= *(int*)&g.ini.top_area_downlimit;
		*(int*)&g.ini.top_area_downlimit ^= *(int*)&g.ini.top_area_uplimit;
	}
	g.ini.SaveParaFile(PARA_IMAGE);
}


void CTopCamDlg::OnBnClickedButtonShowTfolder()
{
	// TODO:  在此添加控件通知处理程序代码
	win_tool wt;
	CString path = wt.AppPath() + L"\\" + g.prjini.m_Prj_Name + L"\\TopModel";
	ShellExecute(NULL,L"open",_T("explorer.exe"),path,NULL,SW_SHOW);
}


void CTopCamDlg::OnBnClickedButtonSelTnoroirect()
{
	// TODO:  在此添加控件通知处理程序代码
	if (NO_RECT != g.Controller.ROI_rect) { AfxMessageBox(show_roi_msg(g.Controller.ROI_rect)); return; }
	HTuple  Exception;
	HException::InstallHHandler(&CPPExpDefaultExceptionHandler);
	set_check("~give_error");
	try
	{
		g.Controller.ROI_rect = TNROI_RECT;
		double row, col, row2, col2;
		Hobject ROI;
		Halcon::set_color(g.show_image.get_disp_hd(), "green");
		set_draw(g.show_image.get_disp_hd(), "fill");
		draw_rectangle1(g.show_image.get_disp_hd(), &row, &col, &row2, &col2);
		gen_rectangle1(&ROI, row, col, row2, col2);
		g.img_deal.unionTNoROI(ROI);//向已有的
		disp_obj(g.img_deal.GetTNoROI(), g.show_image.get_disp_hd());
		g.img_deal.write_top_nroi(g.prjini.m_Prj_Name);//保存region
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


void CTopCamDlg::OnBnClickedButtonSelTnoroicircle()
{
	// TODO:  在此添加控件通知处理程序代码
	if (NO_RECT != g.Controller.ROI_rect) { AfxMessageBox(show_roi_msg(g.Controller.ROI_rect)); return; }
	HTuple  Exception;
	HException::InstallHHandler(&CPPExpDefaultExceptionHandler);
	set_check("~give_error");
	try
	{
		g.Controller.ROI_rect = TNROI_RECT;
		double row, col, phi, radius1, radius2;
		Hobject ROI;
		Halcon::set_color(g.show_image.get_disp_hd(), "green");
		set_draw(g.show_image.get_disp_hd(), "fill");
		draw_ellipse(g.show_image.get_disp_hd(), &row, &col, &phi, &radius1,&radius2);
		gen_ellipse(&ROI, row, col, phi, radius1, radius2);
		g.img_deal.unionTNoROI(ROI);//向已有的
		disp_obj(g.img_deal.GetTNoROI(), g.show_image.get_disp_hd());
		g.img_deal.write_top_nroi(g.prjini.m_Prj_Name);//保存region
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


void CTopCamDlg::OnBnClickedButtonSelTnoroiclear()
{
	// TODO:  在此添加控件通知处理程序代码
	if (NO_RECT != g.Controller.ROI_rect) { AfxMessageBox(show_roi_msg(g.Controller.ROI_rect)); return; }
	HTuple  Exception;
	HException::InstallHHandler(&CPPExpDefaultExceptionHandler);
	set_check("~give_error");
	try
	{
		g.img_deal.clearTNROI();
		disp_obj(g.hRawImage, g.show_image.get_disp_hd());
		disp_obj(g.img_deal.GetTNoROI(), g.show_image.get_disp_hd());
		g.img_deal.write_top_nroi(g.prjini.m_Prj_Name);//保存region
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


void CTopCamDlg::OnBnClickedButtonSelTnoroishow()
{
	// TODO:  在此添加控件通知处理程序代码
	set_check("~give_error");
	disp_obj(g.hRawImage, g.show_image.get_disp_hd());
	disp_obj(g.img_deal.GetTNoROI(), g.show_image.get_disp_hd());
	set_check("give_error");
}
