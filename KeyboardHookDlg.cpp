// KeyboardHookDlg.cpp : ŽÀ‘•ƒtƒ@ƒCƒ‹
#include "stdafx.h"
#include "KeyboardHook.h"
#include "KeyboardHookDlg.h"
#include "KeyboardHookDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#ifdef DEBUG
#    pragma comment(lib, "./Debug/KeyboardHookDll.lib")
#else
#    pragma comment(lib, "./Release/KeyboardHookDll.lib")
#endif

LRESULT __declspec(dllimport) CALLBACK MyKeyboardProc(int, WPARAM, LPARAM);
HHOOK __declspec(dllimport) CALLBACK SetHook( HWND hwnd, UINT mes );
void __declspec(dllimport) CALLBACK UnHook();
int __declspec(dllimport) CALLBACK ToggleEnable();


CKeyboardHookDlg::CKeyboardHookDlg(CWnd* pParent /*=NULL*/)
: CDialog(CKeyboardHookDlg::IDD, pParent)
{
	m_hHook = NULL;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CKeyboardHookDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_button);
}

BEGIN_MESSAGE_MAP(CKeyboardHookDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_CLOSE()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
END_MESSAGE_MAP()

BOOL CKeyboardHookDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);
	m_button.SetBitmap(LoadBitmap(AfxGetApp()->m_hInstance, (LPCTSTR)IDB_UNHOOK ));
	m_hHook = SetHook(AfxGetMainWnd()->GetSafeHwnd(), 0 );
	return TRUE;
}

void CKeyboardHookDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this);
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CKeyboardHookDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL CKeyboardHookDlg::DestroyWindow()
{
	UnHook();
	return CDialog::DestroyWindow();
}

void CKeyboardHookDlg::OnOK()
{
	m_button.SetBitmap(LoadBitmap(AfxGetApp()->m_hInstance,
		(LPCTSTR)
			(ToggleEnable() ? IDB_HOOK : IDB_UNHOOK )));
	//CDialog::OnOK();
}

void CKeyboardHookDlg::OnCancel()
{
	//CDialog::OnCancel();
}

void CKeyboardHookDlg::OnClose()
{
//	UnHook();
	DestroyWindow();
	CDialog::OnClose();
};
void CKeyboardHookDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
//	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CKeyboardHookDlg::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
//	CDialog::OnKeyUp(nChar, nRepCnt, nFlags);
}
