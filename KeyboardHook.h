// KeyboardHook.h : PROJECT_NAME �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C���ł��B
//

#pragma once

#ifndef __AFXWIN_H__
	#error ���̃t�@�C���� PCH �Ɋ܂߂�O�ɁA'stdafx.h' ���܂߂Ă��������B
#endif

#include "resource.h"		// ���C�� �V���{��


// CKeyboardHookApp:
// ���̃N���X�̎����ɂ��ẮAKeyboardHook.cpp ���Q�Ƃ��Ă��������B
//

class CKeyboardHookApp : public CWinApp
{
public:
	CKeyboardHookApp();

// �I�[�o�[���C�h
	public:
	virtual BOOL InitInstance();

// ����

	DECLARE_MESSAGE_MAP()
};

extern CKeyboardHookApp theApp;
