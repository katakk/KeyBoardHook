// KeyboardHookDlg.h : ヘッダー ファイル
//

#pragma once
#include "afxwin.h"


// CKeyboardHookDlg ダイアログ
class CKeyboardHookDlg : public CDialog
{
// コンストラクション
public:
	HHOOK m_hHook;
	CKeyboardHookDlg(CWnd* pParent = NULL);	// 標準コンストラクタ

// ダイアログ データ
	enum { IDD = IDD_KEYBOARDHOOK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート


// 実装
protected:
	HICON m_hIcon;

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
	virtual BOOL DestroyWindow();
	CButton m_button;
	afx_msg void OnClose();
};
