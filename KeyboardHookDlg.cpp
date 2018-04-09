// KeyboardHookDlg.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "KeyboardHook.h"
#include "KeyboardHookDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CKeyboardHookDlg �_�C�A���O



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


// CKeyboardHookDlg ���b�Z�[�W �n���h��

BOOL CKeyboardHookDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���̃_�C�A���O�̃A�C�R����ݒ肵�܂��B�A�v���P�[�V�����̃��C�� �E�B���h�E���_�C�A���O�łȂ��ꍇ�A
	//  Framework �́A���̐ݒ�������I�ɍs���܂��B
	SetIcon(m_hIcon, TRUE);			// �傫���A�C�R���̐ݒ�
	SetIcon(m_hIcon, FALSE);		// �������A�C�R���̐ݒ�

	// TODO: �������������ɒǉ����܂��B
	m_button.SetBitmap(LoadBitmap(AfxGetApp()->m_hInstance, (LPCTSTR)IDB_BITMAP1 ));
	return TRUE;  // �t�H�[�J�X���R���g���[���ɐݒ肵���ꍇ�������ATRUE ��Ԃ��܂��B
}


// �_�C�A���O�ɍŏ����{�^����ǉ�����ꍇ�A�A�C�R����`�悷�邽�߂�
//  ���̃R�[�h���K�v�ł��B�h�L�������g/�r���[ ���f�����g�� MFC �A�v���P�[�V�����̏ꍇ�A
//  ����́AFramework �ɂ���Ď����I�ɐݒ肳��܂��B

void CKeyboardHookDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �`��̃f�o�C�X �R���e�L�X�g

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// �N���C�A���g�̎l�p�`�̈���̒���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �A�C�R���̕`��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���[�U�[���ŏ��������E�B���h�E���h���b�O���Ă���Ƃ��ɕ\������J�[�\�����擾���邽�߂ɁA
//  �V�X�e�������̊֐����Ăяo���܂��B
HCURSOR CKeyboardHookDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CKeyboardHookDlg::OnBnClickedOk()
{
	// TODO : �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
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
//		m_hHook = SetWindowsHookEx( WH_KEYBOARD_LL, MyKeyboardProc, GetModuleHandle(_T("KeyboardHookDll.dll")), 0); /* �჌�x��Hook */
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
