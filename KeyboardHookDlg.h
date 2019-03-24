#pragma once
#include "afxwin.h"

class CKeyboardHookDlg : public CDialog
{
public:
	HHOOK m_hHook;
	CKeyboardHookDlg(CWnd* pParent = NULL);	// 標準コンストラクタ
	enum { IDD = IDD_KEYBOARDHOOK_DIALOG };
	afx_msg void OnBnClickedButton1();
	afx_msg void OnClose();
	virtual BOOL DestroyWindow();
	CButton m_button;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート
	HICON m_hIcon;
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
};
