
// �ֱʹ���.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// C�ֱʹ���App:
// �йش����ʵ�֣������ �ֱʹ���.cpp
//

class C�ֱʹ���App : public CWinApp
{
public:
	C�ֱʹ���App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern C�ֱʹ���App theApp;