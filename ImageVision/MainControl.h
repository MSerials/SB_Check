#pragma once
#include "afxwin.h"


// CMainControl 对话框

class CMainControl : public CDialogEx
{
	DECLARE_DYNAMIC(CMainControl)

public:
	CMainControl(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMainControl();

// 对话框数据
	enum { IDD = IDD_DIALOG_MAINCONTROL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_ComBoxSel;
	virtual BOOL OnInitDialog();
	BOOL initPort(char *str);
//	afx_msg void OnClose();
	afx_msg void OnBnClickedButtonIomotion();
	afx_msg void OnBnClickedButtonImgset();
	afx_msg void OnBnClickedButtonToOrigin();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void BnClickedButtonToOrigin();
private:
	bool RunOrigin();
	CWinThread * pRunOrigin;
	bool isOrigin;
	static UINT pRunOriginThread(LPVOID lp);

	bool RunDelayInit();
	CWinThread * pRunDelayInit;
	bool isDelayInit;
	static UINT pDelayInit(LPVOID lp);

	bool isPortOK;
	int _counter;
	bool _isToOrigin;
public:
	afx_msg void OnSelchangeCombselprj();
	afx_msg void OnBnClickedButtonAddprj();
	afx_msg void OnBnClickedButtonSaveip();
	afx_msg LRESULT SocketCommand(WPARAM wParam, LPARAM lParam);
};
