// KeyboardHookDll.cpp : DLL �̏��������[�`���ł��B
//

#include "stdafx.h"
#include "KeyboardHookDll.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//	����!
//
//		���� DLL �� MFC DLL �ɑ΂��ē��I�Ƀ����N�����ꍇ�A
//		MFC ���ŌĂяo����邱�� DLL ����G�N�X�|�[�g���ꂽ
//		�ǂ̊֐����֐��̍ŏ��ɒǉ������ AFX_MANAGE_STATE 
//		�}�N�����܂�ł��Ȃ���΂Ȃ�܂���B
//
//		��:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �ʏ�֐��̖{�̂͂��̈ʒu�ɂ���܂�
//		}
//
//		���̃}�N�����e�֐��Ɋ܂܂�Ă��邱�ƁAMFC ����
//		�ǂ̌Ăяo�����D�悷�邱�Ƃ͔��ɏd�v�ł��B
//		����͊֐����̍ŏ��̃X�e�[�g�����g�łȂ���΂�
//		��Ȃ����Ƃ��Ӗ����܂��A�R���X�g���N�^�� MFC 
//		DLL ���ւ̌Ăяo�����s���\��������̂ŁA�I�u
//		�W�F�N�g�ϐ��̐錾�����O�łȂ���΂Ȃ�܂���B
//
//		�ڍׂɂ��Ă� MFC �e�N�j�J�� �m�[�g 33 �����
//		58 ���Q�Ƃ��Ă��������B
//

// CKeyboardHookDllApp

BEGIN_MESSAGE_MAP(CKeyboardHookDllApp, CWinApp)
END_MESSAGE_MAP()


// CKeyboardHookDllApp �R���X�g���N�V����

CKeyboardHookDllApp::CKeyboardHookDllApp()
{
	// TODO: ���̈ʒu�ɍ\�z�p�R�[�h��ǉ����Ă��������B
	// ������ InitInstance ���̏d�v�ȏ��������������ׂċL�q���Ă��������B
}


// �B��� CKeyboardHookDllApp �I�u�W�F�N�g�ł��B

CKeyboardHookDllApp theApp;


// CKeyboardHookDllApp ������

BOOL CKeyboardHookDllApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

#pragma data_seg( ".HookData" )
HHOOK hHook;      // �t�b�N���ʗp�̃n���h��
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
        WH_KEYBOARD_LL,           // �t�b�N�̎��
        MyKeyboardProc,          // �����p�֐�
		theApp.m_hInstance,      // �t�b�N����C���X�^���X
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
