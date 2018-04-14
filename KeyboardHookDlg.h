// KeyboardHookDlg.h : �w�b�_�[ �t�@�C��
//

#pragma once
#include "afxwin.h"


// CKeyboardHookDlg �_�C�A���O
class CKeyboardHookDlg : public CDialog
{
// �R���X�g���N�V����
public:
	HHOOK m_hHook;
	CKeyboardHookDlg(CWnd* pParent = NULL);	// �W���R���X�g���N�^

// �_�C�A���O �f�[�^
	enum { IDD = IDD_KEYBOARDHOOK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �T�|�[�g


// ����
protected:
	HICON m_hIcon;

	// �������ꂽ�A���b�Z�[�W���蓖�Ċ֐�
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
