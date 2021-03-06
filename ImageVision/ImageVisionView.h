// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// (“Fluent UI”)。该示例仅供参考，
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。  
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。  
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问  
// http://go.microsoft.com/fwlink/?LinkId=238214。
//
// 版权所有(C) Microsoft Corporation
// 保留所有权利。

// ImageVisionView.h : CImageVisionView 类的接口
//

#pragma once


class CImageVisionView : public CView
{
protected: // 仅从序列化创建
	CImageVisionView();
	DECLARE_DYNCREATE(CImageVisionView)

// 特性
public:
	CImageVisionDoc* GetDocument() const;

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

	// 操作
public:


// 实现
public:
	virtual ~CImageVisionView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnButtonChangeef();
	afx_msg void OnButtonLoadimg();
	afx_msg void OnButtonSnap();
	afx_msg void OnButtonSaveimg();
	afx_msg void OnButtonTop();
	afx_msg void OnButtonBottom();
	afx_msg void OnButtonTrain();
	afx_msg LRESULT ReceiveParaMessage(WPARAM wParam, LPARAM lParam);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnButtonShowResult();



	CRectTracker  m_RectTracker;
	//bool RunCaptureThread();
	//static UINT CaptrueThread(LPVOID lParam);
	//CWinThread* pCaputreThread;

	bool RunDetectionThread();
	static UINT DetectionThread(LPVOID lParam);
	CWinThread* pDetectionThread;

	bool RunIOThread();
	static UINT IOThread(LPVOID lParam);
	CWinThread* pIOThread;

	void get_mfc_roi();
	bool ProcPicDir(CString strPicDir, vector<CString>& strPath);

	
	LONG64 Tick;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void Detection_Trigger();
	void RunCature();
	void CaptureAndDection();
	void StopCapture();
	float ImgResult();
	void Draw();
#ifdef _HALCON
	void Draw(const Hobject &hobject);
#endif
	afx_msg void OnButtonTestDlg();
	afx_msg void OnButtonClear();
	afx_msg void OnButtonTestpic();
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnButtonTestgroup();
	bool MatEqual(cv::Mat& img1, cv::Mat& img2);
//	afx_msg void showStitching();
//	afx_msg void OnButtonReadpics();
	afx_msg void OnButtonRpics();
	afx_msg void OnButtonStitch();
};

#ifndef _DEBUG  // ImageVisionView.cpp 中的调试版本
inline CImageVisionDoc* CImageVisionView::GetDocument() const
   { return reinterpret_cast<CImageVisionDoc*>(m_pDocument); }
#endif

