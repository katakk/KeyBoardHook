#include "stdafx.h"
#include "KeyboardHook.h"
#include "KeyboardHookDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CKeyboardHookApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

CKeyboardHookApp::CKeyboardHookApp()
{
}
CKeyboardHookApp theApp;

BOOL CKeyboardHookApp::InitInstance()
{
	InitCommonControls();
	CWinApp::InitInstance();
	AfxEnableControlContainer();
	CKeyboardHookDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	return FALSE;
}
