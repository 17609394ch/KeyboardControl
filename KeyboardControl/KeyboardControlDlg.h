
// KeyboardControlDlg.h: 头文件
//

#pragma once


#include"kvaser.h"
// CKeyboardControlDlg 对话框
class CKeyboardControlDlg : public CDialogEx
{
// 构造
public:
	CKeyboardControlDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_KEYBOARDCONTROL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedInitkvaser();


public:
	void ControlMode(UINT mode);
	bool isInitKvaser;

	Kvaser* m_kvaser;
	afx_msg void OnBnClickedEnd();

	double vd;
	double wd;
	UINT SELECT_MODE;
	CButton Close_Button;
	CButton Start_Init;
};
