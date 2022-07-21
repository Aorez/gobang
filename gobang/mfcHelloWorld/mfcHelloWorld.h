// mfcHelloWorld.h : main header file for the MFCHELLOWORLD application
//

#if !defined(AFX_MFCHELLOWORLD_H__D8348351_3A9C_4FC7_994C_AF028DD6E47F__INCLUDED_)
#define AFX_MFCHELLOWORLD_H__D8348351_3A9C_4FC7_994C_AF028DD6E47F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMfcHelloWorldApp:
// See mfcHelloWorld.cpp for the implementation of this class
//

class CMfcHelloWorldApp : public CWinApp
{
public:
	CMfcHelloWorldApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMfcHelloWorldApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMfcHelloWorldApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCHELLOWORLD_H__D8348351_3A9C_4FC7_994C_AF028DD6E47F__INCLUDED_)
