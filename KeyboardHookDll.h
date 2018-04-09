// KeyboardHookDll.h : KeyboardHookDll.DLL のメイン ヘッダー ファイル
//

#pragma once

#ifndef __AFXWIN_H__
	#error このファイルを PCH に含む前に、'stdafx.h' を含めてください。
#endif

#include "resource.h"		// メイン シンボル


// CKeyboardHookDllApp
// このクラスの実装に関しては KeyboardHookDll.cpp を参照してください。
//

class CKeyboardHookDllApp : public CWinApp
{
public:
	CKeyboardHookDllApp();

// オーバーライド
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
