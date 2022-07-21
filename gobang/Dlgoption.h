/*
	设置界面，设置以下两个参数：
		模式选择：
			人先机后、
			机先人后
			两个对弈
		智能等级
			低、中、高

*/
#if !defined(AFX_DLGOPTION_H__F90FDCA6_784E_4E0C_9441_0DE3485B0010__INCLUDED_)
#define AFX_DLGOPTION_H__F90FDCA6_784E_4E0C_9441_0DE3485B0010__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlgoption.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgoption dialog

class CDlgoption : public CDialog
{
// Construction
public:
	CDlgoption(CWnd* pParent = NULL); 
	void setoption(int model,int aitype);
	int getmodel();
	int getai();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();	//初始化
	virtual void OnOK();			//保存设置类中

	// Generated message map functions
	DECLARE_MESSAGE_MAP()

private:
	int model;			//保存模式变量
	int aitype;			//保存智能等级的变量
	enum { IDD = IDD_OPTIONDLG };
		// NOTE: the ClassWizard will add data members here
};

#endif // !defined(AFX_DLGOPTION_H__F90FDCA6_784E_4E0C_9441_0DE3485B0010__INCLUDED_)
