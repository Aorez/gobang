/*
	���ý��棬������������������
		ģʽѡ��
			���Ȼ���
			�����˺�
			��������
		���ܵȼ�
			�͡��С���

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
	virtual BOOL OnInitDialog();	//��ʼ��
	virtual void OnOK();			//������������

	// Generated message map functions
	DECLARE_MESSAGE_MAP()

private:
	int model;			//����ģʽ����
	int aitype;			//�������ܵȼ��ı���
	enum { IDD = IDD_OPTIONDLG };
		// NOTE: the ClassWizard will add data members here
};

#endif // !defined(AFX_DLGOPTION_H__F90FDCA6_784E_4E0C_9441_0DE3485B0010__INCLUDED_)
