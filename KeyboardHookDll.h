// KeyboardHookDll.h : KeyboardHookDll.DLL �̃��C�� �w�b�_�[ �t�@�C��
//

#pragma once

#ifndef __AFXWIN_H__
	#error ���̃t�@�C���� PCH �Ɋ܂ޑO�ɁA'stdafx.h' ���܂߂Ă��������B
#endif

#include "resource.h"		// ���C�� �V���{��


// CKeyboardHookDllApp
// ���̃N���X�̎����Ɋւ��Ă� KeyboardHookDll.cpp ���Q�Ƃ��Ă��������B
//

class CKeyboardHookDllApp : public CWinApp
{
public:
	CKeyboardHookDllApp();

// �I�[�o�[���C�h
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
