/*
	����ģʽ�����ܵȼ��Ĵ��ڣ�ʵ���ļ�
	˵����
		���ݱ�����һ����Ϊwuzi.ini�������ļ��У���û�������ﱣ�档��CMyDlg::OnButton2() ��ʵ�����ݵĶ�ȡ��
*/

#include "stdafx.h"
#include "CMyApp.h"
#include "Dlgoption.h"		//����ͷ�ļ�

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/*
���캯��
*/
CDlgoption::CDlgoption(CWnd* pParent):CDialog(CDlgoption::IDD, pParent)
{

	//{{AFX_DATA_INIT(CDlgoption)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

}


/*
�������ݻ�ȡ��У��,MFC���ɣ���û����ʲô���⴦��
*/
void CDlgoption::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgoption)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


/*
������Ϣѭ��,û�ж����������Ϣѭ��
*/
BEGIN_MESSAGE_MAP(CDlgoption, CDialog)
	//{{AFX_MSG_MAP(CDlgoption)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/*
���û�ѡ�������д������
*/
void CDlgoption::setoption(int model,int aitype)
{
	//CDlgoption::aitype����CDlgoption�����ݳ�Ա
	CDlgoption::aitype=aitype;
	CDlgoption::model=model;
}
	

/*
���ڳ�ʼ��,ʹ�õ���API����˵��

    ����ԭ�ͣ�BOOL CheckRadioButtoh��HWNDhDlg�� intnlDFirstButton�� intnlDLastBUtton�� intnlDCheckButton����

    ������

    hDlg��ָ�������ѡ��ť�ĶԻ���ľ����

    nlDFirstButton��ָ�����е�1����ѡ��ť�ı�ʶ����

    nlDLastButton��ָ���������һ����ѡ����ı�ʶ����

    nlDCheckButton��ָ��Ҫѡ�е��Ǹ���ѡ��ť�ı�ʶ����
*/
BOOL CDlgoption::OnInitDialog() 
{
	CDialog::OnInitDialog();		//���ø���Ĵ��ڳ�ʼ������
	
	//����ʹ��ģʽ
	if (CDlgoption::model==0) 
		CDlgoption::CheckRadioButton(IDC_RADIO1, IDC_RADIO3,IDC_RADIO1);		//���Ȼ���
	else if (CDlgoption::model==1)	
		CDlgoption::CheckRadioButton(IDC_RADIO1, IDC_RADIO3,IDC_RADIO2);		//�����˺�
	else if (CDlgoption::model==2)		
		CDlgoption::CheckRadioButton(IDC_RADIO1, IDC_RADIO3,IDC_RADIO3);		//���˶���

	//�������ܵȼ�
	if (CDlgoption::aitype==0) 
		CDlgoption::CheckRadioButton(IDC_RADIO4, IDC_RADIO6,IDC_RADIO4);
	else if (CDlgoption::aitype==1)
		CDlgoption::CheckRadioButton(IDC_RADIO4, IDC_RADIO6,IDC_RADIO5);
	else if (CDlgoption::aitype==2)
		CDlgoption::CheckRadioButton(IDC_RADIO4, IDC_RADIO6,IDC_RADIO6);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/*
	ȡʹ��ģʽ
*/
int CDlgoption::getmodel()
{
	return CDlgoption::model; 
}

/*
	ȡ���ܵȼ�
*/
int CDlgoption::getai()
{
	return CDlgoption::aitype; 
}


/*
	���û�����ȷ����ťʱ

	GetCheckedRadioButton���Ի����׼����
    ����ԭ�ͣ�int GetCheckedRadioButton(int nIDFirstButton, int nIDLastButton)

    ������
	    nlDFirstButton��ָ�����е�1����ѡ��ť�ı�ʶ����
	    nlDLastButton��ָ���������һ����ѡ����ı�ʶ����
	����ֵ��
		��ѡ�еĵ�ѡ��ť��ID

*/
void CDlgoption::OnOK() 
{
	int tem;

	//����ǰ�û�ѡ������ܵȼ�
	tem=CDlgoption::GetCheckedRadioButton (IDC_RADIO4,IDC_RADIO6);
	if (tem==IDC_RADIO4)
		CDlgoption::aitype=0; 
	else if(tem==IDC_RADIO5)
		CDlgoption::aitype=1;
	else if(tem=IDC_RADIO6)
		CDlgoption::aitype=2;
	else
		CDlgoption::aitype=1;		//�����쳣ʱ�����,�ɲ�Ҫ

	//����ǰ�û�ѡ���ʹ��ģʽ
	tem=CDlgoption::GetCheckedRadioButton (IDC_RADIO1,IDC_RADIO3);
	if (tem==IDC_RADIO1)
		CDlgoption::model=0;
	else if(tem==IDC_RADIO2)
		CDlgoption::model=1;
	else if(tem=IDC_RADIO3)
		CDlgoption::model=2;
	else 
		CDlgoption::model=0;		//�����쳣ʱ����������Բ�Ҫ

	//���ø���ONOK����
	CDialog::OnOK();
}
