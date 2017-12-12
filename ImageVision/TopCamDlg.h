#pragma once


// CTopCamDlg 对话框

class CTopCamDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTopCamDlg)

public:
	CTopCamDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTopCamDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_TOPCAM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButtonSelTroi();
	afx_msg void OnBnClickedButtonShowTroi();
	afx_msg void OnBnClickedButtonShowTsavemodel();
//	afx_msg void OnBnClickedButtonSelall();
	afx_msg void OnSelchangeComboModelsel();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonShowModel();
	afx_msg void OnBnClickedButtonTrainmodel();
private:
	bool RunTrain();
	CWinThread *pRunTrain;
	bool isTrain;
	static UINT RunTrainThread(LPVOID lp);
	bool train();
	vector<CString> get_train_img_path();
	bool train_img(vector<CString> str);


	CWinThread *pCap;
	bool isCap;
	static UINT RunCapThread(LPVOID);
	
public:
	afx_msg void OnBnClickedButtonCap();
	afx_msg void OnBnClickedButtonTestt();
	afx_msg void OnBnClickedButtonComfirmpara();
	afx_msg void OnBnClickedButtonLoad();
	afx_msg void OnBnClickedButtonSelTdroi1();
	afx_msg void OnBnClickedButtonShowTdroi1();
	afx_msg void OnBnClickedButtonTdtest1();
	afx_msg void OnBnClickedButtonSelTdroi2();
	afx_msg void OnBnClickedButtonShowTdroi2();
	afx_msg void OnBnClickedButtonTdtest2();
	
	afx_msg void OnBnClickedButtonTareacomf();
	afx_msg void OnBnClickedButtonShowTfolder();
	afx_msg void OnBnClickedButtonSelTnoroirect();
	afx_msg void OnBnClickedButtonSelTnoroicircle();
	afx_msg void OnBnClickedButtonSelTnoroiclear();
	afx_msg void OnBnClickedButtonSelTnoroishow();
};
