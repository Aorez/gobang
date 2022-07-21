/*
	设置模式和智能等级的窗口，实现文件
	说明：
		数据保存在一个名为wuzi.ini的配置文件中，并没有在这里保存。在CMyDlg::OnButton2() 中实现数据的读取。
*/

#include "stdafx.h"
#include "CMyApp.h"
#include "Dlgoption.h"		//保存头文件

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/*
构造函数
*/
CDlgoption::CDlgoption(CWnd* pParent):CDialog(CDlgoption::IDD, pParent)
{

	//{{AFX_DATA_INIT(CDlgoption)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

}


/*
输入数据获取和校对,MFC生成，并没有做什么特殊处理
*/
void CDlgoption::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgoption)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


/*
定义消息循环,没有定义特殊的消息循环
*/
BEGIN_MESSAGE_MAP(CDlgoption, CDialog)
	//{{AFX_MSG_MAP(CDlgoption)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/*
将用户选择的数据写到类中
*/
void CDlgoption::setoption(int model,int aitype)
{
	//CDlgoption::aitype是类CDlgoption的数据成员
	CDlgoption::aitype=aitype;
	CDlgoption::model=model;
}
	

/*
窗口初始化,使用到的API函数说明

    函数原型：BOOL CheckRadioButtoh（HWNDhDlg， intnlDFirstButton， intnlDLastBUtton， intnlDCheckButton）；

    参数：

    hDlg：指向包含单选按钮的对话框的句柄。

    nlDFirstButton：指定组中第1个单选按钮的标识符。

    nlDLastButton：指定组中最后一个单选按组的标识符。

    nlDCheckButton：指出要选中的那个单选按钮的标识符。
*/
BOOL CDlgoption::OnInitDialog() 
{
	CDialog::OnInitDialog();		//调用父类的窗口初始化函数
	
	//设置使用模式
	if (CDlgoption::model==0) 
		CDlgoption::CheckRadioButton(IDC_RADIO1, IDC_RADIO3,IDC_RADIO1);		//人先机后
	else if (CDlgoption::model==1)	
		CDlgoption::CheckRadioButton(IDC_RADIO1, IDC_RADIO3,IDC_RADIO2);		//机先人后
	else if (CDlgoption::model==2)		
		CDlgoption::CheckRadioButton(IDC_RADIO1, IDC_RADIO3,IDC_RADIO3);		//两人对弈

	//设置智能等级
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
	取使用模式
*/
int CDlgoption::getmodel()
{
	return CDlgoption::model; 
}

/*
	取智能等级
*/
int CDlgoption::getai()
{
	return CDlgoption::aitype; 
}


/*
	当用户按下确定按钮时

	GetCheckedRadioButton：对话框标准函数
    函数原型：int GetCheckedRadioButton(int nIDFirstButton, int nIDLastButton)

    参数：
	    nlDFirstButton：指定组中第1个单选按钮的标识符。
	    nlDLastButton：指定组中最后一个单选按组的标识符。
	返回值：
		被选中的单选按钮的ID

*/
void CDlgoption::OnOK() 
{
	int tem;

	//读当前用户选择的智能等级
	tem=CDlgoption::GetCheckedRadioButton (IDC_RADIO4,IDC_RADIO6);
	if (tem==IDC_RADIO4)
		CDlgoption::aitype=0; 
	else if(tem==IDC_RADIO5)
		CDlgoption::aitype=1;
	else if(tem=IDC_RADIO6)
		CDlgoption::aitype=2;
	else
		CDlgoption::aitype=1;		//处理异常时的情况,可不要

	//读当前用户选择的使用模式
	tem=CDlgoption::GetCheckedRadioButton (IDC_RADIO1,IDC_RADIO3);
	if (tem==IDC_RADIO1)
		CDlgoption::model=0;
	else if(tem==IDC_RADIO2)
		CDlgoption::model=1;
	else if(tem=IDC_RADIO3)
		CDlgoption::model=2;
	else 
		CDlgoption::model=0;		//处理异常时的情况，可以不要

	//调用父类ONOK函数
	CDialog::OnOK();
}
