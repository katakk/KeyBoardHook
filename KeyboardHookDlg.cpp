// KeyboardHookDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "KeyboardHook.h"
#include "KeyboardHookDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CKeyboardHookDlg ダイアログ



CKeyboardHookDlg::CKeyboardHookDlg(CWnd* pParent /*=NULL*/)
: CDialog(CKeyboardHookDlg::IDD, pParent)
{
	m_hHook = NULL;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CKeyboardHookDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_button);
}

BEGIN_MESSAGE_MAP(CKeyboardHookDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
END_MESSAGE_MAP()


// CKeyboardHookDlg メッセージ ハンドラ

BOOL CKeyboardHookDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定

	// TODO: 初期化をここに追加します。
	m_button.SetBitmap(LoadBitmap(AfxGetApp()->m_hInstance, (LPCTSTR)IDB_BITMAP1 ));
	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}


// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。

void CKeyboardHookDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// クライアントの四角形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンの描画
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR CKeyboardHookDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CKeyboardHookDlg::OnBnClickedOk()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	OnOK();
}

#ifdef DEBUG
#    pragma comment(lib, "./Debug/KeyboardHookDll.lib")
#else
#    pragma comment(lib, "./Release/KeyboardHookDll.lib")
#endif

LRESULT __declspec(dllimport) CALLBACK MyKeyboardProc(int, WPARAM, LPARAM);
HHOOK __declspec(dllimport) CALLBACK SetHook( HWND hwnd, UINT mes );
void __declspec(dllimport) CALLBACK UnHook();

void CKeyboardHookDlg::OnBnClickedButton1()
{
	if(m_hHook != NULL) {
		UnHook();
		m_hHook = NULL;
		m_button.SetBitmap(LoadBitmap(AfxGetApp()->m_hInstance, (LPCTSTR)IDB_BITMAP1 ));
		SetWindowText(_T("UnHooked"));
	} else {
		m_hHook = SetHook(AfxGetMainWnd()->GetSafeHwnd(), 0 );
///*
//#if (_WIN32_WINNT >= 0x0400)
//		m_hHook = SetWindowsHookEx( WH_KEYBOARD_LL, MyKeyboardProc, GetModuleHandle(_T("KeyboardHookDll.dll")), 0); /* 低レベルHook */
//#else
//		m_hHook = SetWindowsHookEx( WH_KEYBOARD, MyKeyboardProc, GetModuleHandle(_T("KeyboardHookDll.dll")), 0);
//#endif
//		*/
		m_button.SetBitmap(LoadBitmap(AfxGetApp()->m_hInstance, (LPCTSTR)IDB_BITMAP2 ));
		SetWindowText(_T("Hooked"));
	}
}

BOOL CKeyboardHookDlg::DestroyWindow()
{
	UnHook();
	return CDialog::DestroyWindow();
}
