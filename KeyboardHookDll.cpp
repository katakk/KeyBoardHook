// KeyboardHookDll.cpp : DLL の初期化ルーチンです。
//

#include "stdafx.h"
#include "KeyboardHookDll.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//	メモ!
//
//		この DLL が MFC DLL に対して動的にリンクされる場合、
//		MFC 内で呼び出されるこの DLL からエクスポートされた
//		どの関数も関数の最初に追加される AFX_MANAGE_STATE 
//		マクロを含んでいなければなりません。
//
//		例:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 通常関数の本体はこの位置にあります
//		}
//
//		このマクロが各関数に含まれていること、MFC 内の
//		どの呼び出しより優先することは非常に重要です。
//		これは関数内の最初のステートメントでなければな
//		らないことを意味します、コンストラクタが MFC 
//		DLL 内への呼び出しを行う可能性があるので、オブ
//		ジェクト変数の宣言よりも前でなければなりません。
//
//		詳細については MFC テクニカル ノート 33 および
//		58 を参照してください。
//

// CKeyboardHookDllApp

BEGIN_MESSAGE_MAP(CKeyboardHookDllApp, CWinApp)
END_MESSAGE_MAP()


// CKeyboardHookDllApp コンストラクション

CKeyboardHookDllApp::CKeyboardHookDllApp()
{
	// TODO: この位置に構築用コードを追加してください。
	// ここに InitInstance 中の重要な初期化処理をすべて記述してください。
}


// 唯一の CKeyboardHookDllApp オブジェクトです。

CKeyboardHookDllApp theApp;


// CKeyboardHookDllApp 初期化

BOOL CKeyboardHookDllApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

#pragma data_seg( ".HookData" )
HHOOK hHook;      // フック識別用のハンドル
static HWND g_hwnd = NULL;
static UINT g_message = -1;
#pragma data_seg()

LRESULT CALLBACK MyKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode < 0 || nCode != HC_ACTION)
		return CallNextHookEx(hHook, nCode, wParam, lParam);

	LPKBDLLHOOKSTRUCT pKey = (LPKBDLLHOOKSTRUCT) lParam;

	LPCTSTR event[5] = { _T(""), _T("KD"), _T("KU"), _T("SD"), _T("SU") };

	int i = 0;
	if(wParam == WM_KEYDOWN) i = 1;
	if(wParam == WM_KEYUP) i = 2;
	if(wParam == WM_SYSKEYDOWN) i = 3;
	if(wParam == WM_SYSKEYUP) i = 4;

#define VK_BROWSER_BACK        0xA6
#define VK_BROWSER_FORWARD     0xA7
#define VK_BROWSER_REFRESH     0xA8
#define VK_BROWSER_STOP        0xA9
#define VK_BROWSER_SEARCH      0xAA
#define VK_BROWSER_FAVORITES   0xAB
#define VK_BROWSER_HOME        0xAC

#define VK_VOLUME_MUTE         0xAD
#define VK_VOLUME_DOWN         0xAE
#define VK_VOLUME_UP           0xAF
#define VK_MEDIA_NEXT_TRACK    0xB0
#define VK_MEDIA_PREV_TRACK    0xB1
#define VK_MEDIA_STOP          0xB2
#define VK_MEDIA_PLAY_PAUSE    0xB3
#define VK_LAUNCH_MAIL         0xB4
#define VK_LAUNCH_MEDIA_SELECT 0xB5
#define VK_LAUNCH_APP1         0xB6
#define VK_LAUNCH_APP2         0xB7

	switch( pKey->vkCode)
	{
		case 0x14: return TRUE; //CAPS;
		case 0xf2: return TRUE; //Kana;
		case 0xB1: pKey->vkCode = 0x24; pKey->scanCode = 0x47; break;
		case 0xB0: pKey->vkCode = 0x23; pKey->scanCode = 0x4f; break;
		case 0xB2: pKey->vkCode = 0x21; pKey->scanCode = 0x49; break;
		case 0xB3: pKey->vkCode = 0x22; pKey->scanCode = 0x51; break;
	}

//	SendMessage( g_hwnd, g_message, wParam, lParam );
	CString str;
	str.Format(_T("%s [%x %x], %x, f:%x, e:%x"),
		event[i],
		pKey->vkCode, pKey->scanCode,
		pKey->time,  pKey->flags, pKey->dwExtraInfo );
//	AfxMessageBox(str);
SetWindowText(g_hwnd, str);
		return CallNextHookEx(hHook, nCode, wParam, lParam);

//	return TRUE;
}


void CALLBACK UnHook( )
{
	UnhookWindowsHookEx(hHook);
	hHook = NULL;
}

HHOOK CALLBACK SetHook( HWND hwnd, UINT mes )
{
    if ( hHook != NULL )
		UnHook();

    hHook = SetWindowsHookEx(
        WH_KEYBOARD_LL,           // フックの種類
        MyKeyboardProc,          // 処理用関数
		theApp.m_hInstance,      // フックするインスタンス
        NULL );

    g_hwnd = hwnd;
    g_message = mes;

    if ( hHook == NULL )
    {
        TRACE("EORROR hook install\n");
        return 0;
    }
    return hHook;
}
