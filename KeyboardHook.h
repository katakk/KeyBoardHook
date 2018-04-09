// KeyboardHook.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです。
//

#pragma once

#ifndef __AFXWIN_H__
	#error このファイルを PCH に含める前に、'stdafx.h' を含めてください。
#endif

#include "resource.h"		// メイン シンボル


// CKeyboardHookApp:
// このクラスの実装については、KeyboardHook.cpp を参照してください。
//

class CKeyboardHookApp : public CWinApp
{
public:
	CKeyboardHookApp();

// オーバーライド
	public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CKeyboardHookApp theApp;
