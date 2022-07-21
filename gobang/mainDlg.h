/*
	智能五子棋主界面
	头文件
*/


#if !defined(AFX_7DLG_H__DE4ED715_0414_4E98_A342_87D74F1CB23D__INCLUDED_)
#define AFX_7DLG_H__DE4ED715_0414_4E98_A342_87D74F1CB23D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "CDC2.h"
/////////////////////////////////////////////////////////////////////////////
// CMyDlg dialog
#include "RoundButton1.h"		//圆形按钮
#include "wzq.h"
#include "Dlgoption.h"
#include "fstream.h"
class CMyDlg : public CDialog
{
// Construction
public:
	CMyDlg(CWnd* pParent = NULL);	// standard constructor
protected:
	void loadfile();
	void setini(CString keyS ,CString AppS ,CString StrS );
	CString getini(CString keyS ,CString AppS, CString def );

	CDC2 qp;			//棋盘DC
	CDC2 qzh;			//黑子DC
	CDC2 qzhl;			//黑子DC(带圆圈)
	CDC2 qzb;			//白子DC
	CDC2 qzbl;			//黑子DC(带圆圈)
	CDC2 mask;			//掩码DC
	CDC2 dead;			//红子DC
	wzq twzq;			//五子棋的主要功能类
	CString runpath;
// Dialog Data
	//{{AFX_DATA(CMyDlg)
	enum { IDD = IDD_MAINDLG };
	CRoundButton	m_exit;
	CRoundButton	m_about;
	CRoundButton	m_back;
	CRoundButton	m_option;
	CRoundButton	m_new;
	CRoundButton	m_save;
	CRoundButton	m_load;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	// Generated message map functions
	//{{AFX_MSG(CMyDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnNewGame();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnOption();
	afx_msg void OnBack();
	afx_msg void OnExit();
	afx_msg void OnAbout();
	afx_msg void OnSave();
	afx_msg void OnLoad();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_7DLG_H__DE4ED715_0414_4E98_A342_87D74F1CB23D__INCLUDED_)
