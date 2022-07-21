/*
	智能五子棋主界面
	实现文件(其中还包括关于窗口的实现文件，可以分离出去)
*/


#include "stdafx.h"
#include "CMyApp.h"
#include "mainDlg.h"
#include "dim.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/*
	智能五子棋主界面的构造函数.参数:
		nParent	父窗口指针
	函数中以IDB_**是在资源视图中定义的BMP资源
*/
CMyDlg::CMyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyDlg::IDD, pParent)
{
	CBitmap b,c,d,e,f,c_l,d_l;
	CSize x;

	//加载棋盘DC
	b.LoadBitmap(IDB_QP);
	x.cx =446 ;
	x.cy =446; 
	qp.CreateCompatibleDC(NULL);
	qp.SelectObject(&b);
	qp.SetSize(x);
	b.DeleteObject(); 

	//加载黑子DC
	c.LoadBitmap(IDB_QZH);
	x.cx = 27 ;
	x.cy =27 ;
	qzh.CreateCompatibleDC(NULL);
	qzh.SelectObject(&c);
	qzh.SetSize(x);
	c.DeleteObject(); 
	//加载黑子DC(带圆圈)
	c_l.LoadBitmap(IDB_QZHL);
	x.cx = 27 ;
	x.cy =27 ;
	qzhl.CreateCompatibleDC(NULL);
	qzhl.SelectObject(&c_l);
	qzhl.SetSize(x);
	c_l.DeleteObject(); 

	//加载白子DC
	d.LoadBitmap(IDB_QZB);
	x.cx = 27 ;
	x.cy =27; 
	qzb.CreateCompatibleDC(NULL);
	qzb.SelectObject(&d);
	qzb.SetSize(x);
	d.DeleteObject(); 
	//加载白子DC(带圆圈)
	d_l.LoadBitmap(IDB_QZBL);
	x.cx = 27 ;
	x.cy =27; 
	qzbl.CreateCompatibleDC(NULL);
	qzbl.SelectObject(&d_l);
	qzbl.SetSize(x);
	d_l.DeleteObject(); 

	//加载掩码DC
	e.LoadBitmap(IDB_MASK);
	x.cx = 27 ;
	x.cy =27; 
	mask.CreateCompatibleDC(NULL);
	mask.SelectObject(&e);
	mask.SetSize(x);
	d.DeleteObject();

	//加载红子DC
	f.LoadBitmap(IDB_DEAD);
	x.cx=27;
	x.cy=27;
	dead.CreateCompatibleDC(NULL);
	dead.SelectObject(&f);
	dead.SetSize(x);
	f.DeleteObject();
   
	//{{AFX_DATA_INIT(CMyDlg)
	//}}AFX_DATA_INIT
	//加载图标
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

}

void CMyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyDlg)
	DDX_Control(pDX, IDC_BUTTON8, m_exit);
	DDX_Control(pDX, IDC_BUTTON7, m_about);
	DDX_Control(pDX, IDC_BUTTON3, m_back);
	DDX_Control(pDX, IDC_BUTTON2, m_option);
	DDX_Control(pDX, IDC_BUTTON1, m_new);
	DDX_Control(pDX, IDC_BUTTON4, m_save);
	DDX_Control(pDX, IDC_BUTTON5, m_load);
	//}}AFX_DATA_MAP
}

//消息循环
BEGIN_MESSAGE_MAP(CMyDlg, CDialog)
	//{{AFX_MSG_MAP(CMyDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnNewGame)	//按下BUTTON1时,触发OnNewGame事件
	ON_WM_LBUTTONDOWN()						//鼠标左键按下事件
	ON_BN_CLICKED(IDC_BUTTON2, OnOption)	//按下BUTTON2时,触发OnOption事件
	ON_BN_CLICKED(IDC_BUTTON3, OnBack)	//按下BUTTON3时,触发OnBack事件
	ON_BN_CLICKED(IDC_BUTTON8, OnExit)	//按下BUTTON8时,触发OnExit事件
	ON_BN_CLICKED(IDC_BUTTON7, OnAbout)	//按下BUTTON7时,触发OnAbout事件
	ON_BN_CLICKED(IDC_BUTTON4, OnSave)
	ON_BN_CLICKED(IDC_BUTTON5, OnLoad)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/*
	初始化函数
*/
BOOL CMyDlg::OnInitDialog()
{
	//调用父类的初始化函数
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);		// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	CString sModFileName;
	GetModuleFileName(NULL, sModFileName.GetBuffer(MAX_PATH), MAX_PATH);
	sModFileName.ReleaseBuffer();

	sModFileName.MakeReverse();
	runpath = sModFileName.Right(sModFileName.GetLength() - sModFileName.Find('\\'));
	runpath.MakeReverse();
	sModFileName.MakeReverse();

	loadfile();
	twzq.SetDc(&qp,&qzh,&qzb,&mask,&dead,this->GetDC(),&qzhl,&qzbl);  
	twzq.NewGame(); 

	CMyDlg::m_back.EnableWindow(twzq.getbackble()); 
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMyDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMyDlg::OnPaint() 
{
	//BOOL IsIconic(HWND hWnd);说 明：判断窗口是否已最小化
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);

	}
	else
	{	
		CDialog::OnPaint();
		CSize x;
		x=qp.GetSize();
		twzq.draw(); 
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMyDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;

}

/*
	按下"新游戏"这个按钮时
*/
void CMyDlg::OnNewGame() 
{
	twzq.NewGame();

	//屏蔽悔棋这个按钮
	CMyDlg::m_back.EnableWindow(twzq.getbackble()); 
}


void CMyDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnMouseMove(nFlags, point);
}

/*
	鼠标左键单击时
*/
void CMyDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	int x1,y1;

	//计算在在哪一行哪一列单击(绝对坐标-7/29)
	x1=(int)(point.x-7)/29 ;
	y1=(int)(point.y-7)/29 ;

	//在鼠标左键单击的地方落子
	twzq.downzi(x1,y1);

	//判断是否又哪一方赢了
	if (twzq.twinner.winner==1)
	{
		CMyDlg::MessageBox("白棋获胜!" );
		//重画棋盘,画出红子
		twzq.draw();
	}
	if (twzq.twinner.winner==2)
	{
		CMyDlg::MessageBox("黑棋获胜!" );
		//重画棋盘,画出红子
		twzq.draw();
	}

	//设置悔棋这个按钮的状态
	CMyDlg::m_back.EnableWindow(twzq.getbackble()); 
	//调用父类的函数
	CDialog::OnLButtonDown(nFlags, point);
}

/*
	按下"选项"这个按钮时
*/
void CMyDlg::OnOption() 
{
	CDlgoption option;
	//设置初始数值
	option.setoption(twzq.Model,twzq.AItype ) ;
	CString temp;

	if (option.DoModal()==IDOK)		//显示窗口并接收用户操作
	{
		//将用户的选项保存在变量中
		twzq.AItype=option.getai();
		twzq.Model=option.getmodel();
		
		//保存操作模式这个选项到INI文件中
		temp.Format("%i",twzq.Model) ; 
		setini("wuzi","model",temp);
		//保存智能等级这个选项到INI文件中
		temp.Format("%i",twzq.AItype);  
		setini("wuzi","ai",temp);

		//开始新游戏
		twzq.NewGame(); 
	}
}

/*
	按下"悔棋"这个按钮时
*/
void CMyDlg::OnBack() 
{
	//调用悔棋函数
	twzq.goback();

	//判断是否还可以在悔棋
	CMyDlg::m_back.EnableWindow(twzq.getbackble()); 
}

/*
	按下"关于"这个按钮时
*/
void CMyDlg::OnAbout() 
{
	CAboutDlg aboutme;
	aboutme.DoModal(); 	
}

/*
	按下"退出"这个按钮时
*/
void CMyDlg::OnExit() 
{
	CMyDlg::OnOK(); 
}

/*
	加载配置文件
*/
void CMyDlg::loadfile()
{
	CString a=getini("wuzi","ai","1");	//读智能等级这个参数
	twzq.AItype=atoi(a);				//转换为INT

	a=getini("wuzi","model","1");		//读操作模式这个参数
	twzq.Model=atoi(a);					//转换为INT
}

/*
	设置INI文件,调用API函数读写。参数：
		keyS	段名。在INI文件中用[]标记
		AppS	变量名
		StrS	变量值

	WritePrivateProfileString：先INI文件中的指定目录写入数据
*/
void CMyDlg::setini(CString keyS ,CString AppS ,CString StrS )
{
	CString file=CMyDlg::runpath+"wuzi.ini";
	::WritePrivateProfileString(keyS, AppS, StrS, file);
}

/*
	读取INI文件。参数
		keyS	段名。在INI文件中用[]标记
		AppS	变量名
		StrS	变量默认值

*/
CString CMyDlg::getini(CString keyS ,CString AppS, CString def )
{
	char b[255];
	CString c;
	CString file=CMyDlg::runpath+"wuzi.ini";
	GetPrivateProfileString(keyS, AppS, def, b, 255, file);
	c.Format("%s",b);
	return c;  
}

/*
	按下"保存"这个按钮时,需要保存的数据包括:
			int		nturn;		//表示当前下子的顺序(只有在使用模式为2(两人对弈时才有效)
								//1-白子下,2-黑子下,0-不知道谁下)
			int		AItype;		//智能等级:0低预测6步 1中预测10步 2高预测16步
			int		Model;		//模式0人->机 1机->人 2对翌
			char map[15][15];				//储存棋盘地图(0-某点空,1-白子,2-黑子)
											//表示棋盘上某一个交叉点是否已经下过子
			//以下参数用于保存下棋历史记录
			int nowd2;						//表示当前已经下了多少子的计数器
			wzsave wzs[225];				//对应棋盘的15行*15列

	这些数据全部可以通过twzq.****的格式来读写，如：
		读下子顺序的这个变量，程序可以这项写：
			twzq.nturn=1;
*/
void CMyDlg::OnSave() 
{
	CString ls_fileName;

	/*显示保存文件对话框
	CFileDialog(BOOL bOpenFileDialog,  TRUE for FileOpen, FALSE for FileSaveAs
		LPCTSTR lpszDefExt = NULL,	 默认扩展名
		LPCTSTR lpszFileName = NULL, 默认文件名称
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,打开方式
		LPCTSTR lpszFilter = NULL,	可供选择的文件类型和相应的扩展名,文件类型之间用|分割,结尾用||分割
		CWnd* pParentWnd = NULL);
	*/

	CFileDialog lcf_open(false,"wzq",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
			"wzq files(*.wzq)||",NULL);
	if (lcf_open.DoModal()==IDOK){

		/*数据保存在文件中,读写文件需要使用到输出文件流ofstream,使用的相关操作为:
			open函数			打开文件供读写,写程序时需要检查文件是否能正常打开
			close函数			写完关闭文件
			>>操作				文件流输出
		  如果需要显示提示信息，则使用AfxMessageBox函数
		*/
		AfxMessageBox("保存功能尚未实现");
	}	

}

/*
	按下"加载"这个按钮时,需要写的数据包括
			int		nturn;		//表示当前下子的顺序(只有在使用模式为2(两人对弈时才有效)
								//1-白子下,2-黑子下,0-不知道谁下)
			int		AItype;		//智能等级:0低预测6步 1中预测10步 2高预测16步
			int		Model;		//模式0人->机 1机->人 2对翌
			char map[15][15];				//储存棋盘地图(0-某点空,1-白子,2-黑子)
											//表示棋盘上某一个交叉点是否已经下过子
			//以下参数用于保存下棋历史记录
			int nowd2;						//表示当前已经下了多少子的计数器
			wzsave wzs[225];				//对应棋盘的15行*15列

	这些数据全部可以通过twzq.****的格式来读写，如：
		读下子顺序的这个变量，程序可以这项写：
			twzq.nturn=1;
*/
void CMyDlg::OnLoad() 
{
	CString ls_fileName;

	/*显示打开文件对话框
	CFileDialog(BOOL bOpenFileDialog,  TRUE for FileOpen, FALSE for FileSaveAs
		LPCTSTR lpszDefExt = NULL,	 默认扩展名
		LPCTSTR lpszFileName = NULL, 默认文件名称
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,打开方式
		LPCTSTR lpszFilter = NULL,	可供选择的文件类型和相应的扩展名,文件类型之间用|分割,结尾用||分割
		CWnd* pParentWnd = NULL);
	*/

	CFileDialog lcf_open(true,"wzq",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
			"wzq files(*.wzq)||",NULL);
	if (lcf_open.DoModal()==IDOK){

		//取文件名称
		ls_fileName = lcf_open.GetPathName();
		//开始一个新游戏
		twzq.NewGame();


		/*从保存的文件中读数据,读文件需要使用到输入文件流ifstream,使用的相关操作为:
			open函数			打开文件供读写,写程序时需要检查文件是否能正常打开
			close函数			写完关闭文件
			getline函数			从文件中读入一行数据
			>>操作				从文件中读数据
		  如果需要显示提示信息，则使用AfxMessageBox函数
		*/
		AfxMessageBox("加载功能尚未实现,将开始一盘新游戏");

	}	

	//设置悔棋按钮的状态
	CMyDlg::m_back.EnableWindow(twzq.getbackble()); 
	//重画屏幕
	twzq.draw();
}
