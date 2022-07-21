// mfcHelloWorld.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "mfcHelloWorld.h"
#include "mfcHelloWorldDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMfcHelloWorldApp

BEGIN_MESSAGE_MAP(CMfcHelloWorldApp, CWinApp)
	//{{AFX_MSG_MAP(CMfcHelloWorldApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMfcHelloWorldApp construction

CMfcHelloWorldApp::CMfcHelloWorldApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMfcHelloWorldApp object

CMfcHelloWorldApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMfcHelloWorldApp initialization

BOOL CMfcHelloWorldApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CMfcHelloWorldDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
