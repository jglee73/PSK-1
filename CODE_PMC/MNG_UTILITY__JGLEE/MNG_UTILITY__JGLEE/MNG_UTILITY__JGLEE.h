// MNG_UTILITY__JGLEE.h : MNG_UTILITY__JGLEE DLL�� �⺻ ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CMNG_UTILITY__JGLEEApp
// �� Ŭ������ ������ ������ MNG_UTILITY__JGLEE.cpp�� �����Ͻʽÿ�.
//

class CMNG_UTILITY__JGLEEApp : public CWinApp
{
public:
	CMNG_UTILITY__JGLEEApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
