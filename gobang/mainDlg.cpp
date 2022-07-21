/*
	����������������
	ʵ���ļ�(���л��������ڴ��ڵ�ʵ���ļ������Է����ȥ)
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
	����������������Ĺ��캯��.����:
		nParent	������ָ��
	��������IDB_**������Դ��ͼ�ж����BMP��Դ
*/
CMyDlg::CMyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyDlg::IDD, pParent)
{
	CBitmap b,c,d,e,f,c_l,d_l;
	CSize x;

	//��������DC
	b.LoadBitmap(IDB_QP);
	x.cx =446 ;
	x.cy =446; 
	qp.CreateCompatibleDC(NULL);
	qp.SelectObject(&b);
	qp.SetSize(x);
	b.DeleteObject(); 

	//���غ���DC
	c.LoadBitmap(IDB_QZH);
	x.cx = 27 ;
	x.cy =27 ;
	qzh.CreateCompatibleDC(NULL);
	qzh.SelectObject(&c);
	qzh.SetSize(x);
	c.DeleteObject(); 
	//���غ���DC(��ԲȦ)
	c_l.LoadBitmap(IDB_QZHL);
	x.cx = 27 ;
	x.cy =27 ;
	qzhl.CreateCompatibleDC(NULL);
	qzhl.SelectObject(&c_l);
	qzhl.SetSize(x);
	c_l.DeleteObject(); 

	//���ذ���DC
	d.LoadBitmap(IDB_QZB);
	x.cx = 27 ;
	x.cy =27; 
	qzb.CreateCompatibleDC(NULL);
	qzb.SelectObject(&d);
	qzb.SetSize(x);
	d.DeleteObject(); 
	//���ذ���DC(��ԲȦ)
	d_l.LoadBitmap(IDB_QZBL);
	x.cx = 27 ;
	x.cy =27; 
	qzbl.CreateCompatibleDC(NULL);
	qzbl.SelectObject(&d_l);
	qzbl.SetSize(x);
	d_l.DeleteObject(); 

	//��������DC
	e.LoadBitmap(IDB_MASK);
	x.cx = 27 ;
	x.cy =27; 
	mask.CreateCompatibleDC(NULL);
	mask.SelectObject(&e);
	mask.SetSize(x);
	d.DeleteObject();

	//���غ���DC
	f.LoadBitmap(IDB_DEAD);
	x.cx=27;
	x.cy=27;
	dead.CreateCompatibleDC(NULL);
	dead.SelectObject(&f);
	dead.SetSize(x);
	f.DeleteObject();
   
	//{{AFX_DATA_INIT(CMyDlg)
	//}}AFX_DATA_INIT
	//����ͼ��
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

//��Ϣѭ��
BEGIN_MESSAGE_MAP(CMyDlg, CDialog)
	//{{AFX_MSG_MAP(CMyDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnNewGame)	//����BUTTON1ʱ,����OnNewGame�¼�
	ON_WM_LBUTTONDOWN()						//�����������¼�
	ON_BN_CLICKED(IDC_BUTTON2, OnOption)	//����BUTTON2ʱ,����OnOption�¼�
	ON_BN_CLICKED(IDC_BUTTON3, OnBack)	//����BUTTON3ʱ,����OnBack�¼�
	ON_BN_CLICKED(IDC_BUTTON8, OnExit)	//����BUTTON8ʱ,����OnExit�¼�
	ON_BN_CLICKED(IDC_BUTTON7, OnAbout)	//����BUTTON7ʱ,����OnAbout�¼�
	ON_BN_CLICKED(IDC_BUTTON4, OnSave)
	ON_BN_CLICKED(IDC_BUTTON5, OnLoad)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/*
	��ʼ������
*/
BOOL CMyDlg::OnInitDialog()
{
	//���ø���ĳ�ʼ������
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
	//BOOL IsIconic(HWND hWnd);˵ �����жϴ����Ƿ�����С��
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
	����"����Ϸ"�����ťʱ
*/
void CMyDlg::OnNewGame() 
{
	twzq.NewGame();

	//���λ��������ť
	CMyDlg::m_back.EnableWindow(twzq.getbackble()); 
}


void CMyDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnMouseMove(nFlags, point);
}

/*
	����������ʱ
*/
void CMyDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	int x1,y1;

	//����������һ����һ�е���(��������-7/29)
	x1=(int)(point.x-7)/29 ;
	y1=(int)(point.y-7)/29 ;

	//�������������ĵط�����
	twzq.downzi(x1,y1);

	//�ж��Ƿ�����һ��Ӯ��
	if (twzq.twinner.winner==1)
	{
		CMyDlg::MessageBox("�����ʤ!" );
		//�ػ�����,��������
		twzq.draw();
	}
	if (twzq.twinner.winner==2)
	{
		CMyDlg::MessageBox("�����ʤ!" );
		//�ػ�����,��������
		twzq.draw();
	}

	//���û��������ť��״̬
	CMyDlg::m_back.EnableWindow(twzq.getbackble()); 
	//���ø���ĺ���
	CDialog::OnLButtonDown(nFlags, point);
}

/*
	����"ѡ��"�����ťʱ
*/
void CMyDlg::OnOption() 
{
	CDlgoption option;
	//���ó�ʼ��ֵ
	option.setoption(twzq.Model,twzq.AItype ) ;
	CString temp;

	if (option.DoModal()==IDOK)		//��ʾ���ڲ������û�����
	{
		//���û���ѡ����ڱ�����
		twzq.AItype=option.getai();
		twzq.Model=option.getmodel();
		
		//�������ģʽ���ѡ�INI�ļ���
		temp.Format("%i",twzq.Model) ; 
		setini("wuzi","model",temp);
		//�������ܵȼ����ѡ�INI�ļ���
		temp.Format("%i",twzq.AItype);  
		setini("wuzi","ai",temp);

		//��ʼ����Ϸ
		twzq.NewGame(); 
	}
}

/*
	����"����"�����ťʱ
*/
void CMyDlg::OnBack() 
{
	//���û��庯��
	twzq.goback();

	//�ж��Ƿ񻹿����ڻ���
	CMyDlg::m_back.EnableWindow(twzq.getbackble()); 
}

/*
	����"����"�����ťʱ
*/
void CMyDlg::OnAbout() 
{
	CAboutDlg aboutme;
	aboutme.DoModal(); 	
}

/*
	����"�˳�"�����ťʱ
*/
void CMyDlg::OnExit() 
{
	CMyDlg::OnOK(); 
}

/*
	���������ļ�
*/
void CMyDlg::loadfile()
{
	CString a=getini("wuzi","ai","1");	//�����ܵȼ��������
	twzq.AItype=atoi(a);				//ת��ΪINT

	a=getini("wuzi","model","1");		//������ģʽ�������
	twzq.Model=atoi(a);					//ת��ΪINT
}

/*
	����INI�ļ�,����API������д��������
		keyS	��������INI�ļ�����[]���
		AppS	������
		StrS	����ֵ

	WritePrivateProfileString����INI�ļ��е�ָ��Ŀ¼д������
*/
void CMyDlg::setini(CString keyS ,CString AppS ,CString StrS )
{
	CString file=CMyDlg::runpath+"wuzi.ini";
	::WritePrivateProfileString(keyS, AppS, StrS, file);
}

/*
	��ȡINI�ļ�������
		keyS	��������INI�ļ�����[]���
		AppS	������
		StrS	����Ĭ��ֵ

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
	����"����"�����ťʱ,��Ҫ��������ݰ���:
			int		nturn;		//��ʾ��ǰ���ӵ�˳��(ֻ����ʹ��ģʽΪ2(���˶���ʱ����Ч)
								//1-������,2-������,0-��֪��˭��)
			int		AItype;		//���ܵȼ�:0��Ԥ��6�� 1��Ԥ��10�� 2��Ԥ��16��
			int		Model;		//ģʽ0��->�� 1��->�� 2����
			char map[15][15];				//�������̵�ͼ(0-ĳ���,1-����,2-����)
											//��ʾ������ĳһ��������Ƿ��Ѿ��¹���
			//���²������ڱ���������ʷ��¼
			int nowd2;						//��ʾ��ǰ�Ѿ����˶����ӵļ�����
			wzsave wzs[225];				//��Ӧ���̵�15��*15��

	��Щ����ȫ������ͨ��twzq.****�ĸ�ʽ����д���磺
		������˳�����������������������д��
			twzq.nturn=1;
*/
void CMyDlg::OnSave() 
{
	CString ls_fileName;

	/*��ʾ�����ļ��Ի���
	CFileDialog(BOOL bOpenFileDialog,  TRUE for FileOpen, FALSE for FileSaveAs
		LPCTSTR lpszDefExt = NULL,	 Ĭ����չ��
		LPCTSTR lpszFileName = NULL, Ĭ���ļ�����
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,�򿪷�ʽ
		LPCTSTR lpszFilter = NULL,	�ɹ�ѡ����ļ����ͺ���Ӧ����չ��,�ļ�����֮����|�ָ�,��β��||�ָ�
		CWnd* pParentWnd = NULL);
	*/

	CFileDialog lcf_open(false,"wzq",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
			"wzq files(*.wzq)||",NULL);
	if (lcf_open.DoModal()==IDOK){

		/*���ݱ������ļ���,��д�ļ���Ҫʹ�õ�����ļ���ofstream,ʹ�õ���ز���Ϊ:
			open����			���ļ�����д,д����ʱ��Ҫ����ļ��Ƿ���������
			close����			д��ر��ļ�
			>>����				�ļ������
		  �����Ҫ��ʾ��ʾ��Ϣ����ʹ��AfxMessageBox����
		*/
		AfxMessageBox("���湦����δʵ��");
	}	

}

/*
	����"����"�����ťʱ,��Ҫд�����ݰ���
			int		nturn;		//��ʾ��ǰ���ӵ�˳��(ֻ����ʹ��ģʽΪ2(���˶���ʱ����Ч)
								//1-������,2-������,0-��֪��˭��)
			int		AItype;		//���ܵȼ�:0��Ԥ��6�� 1��Ԥ��10�� 2��Ԥ��16��
			int		Model;		//ģʽ0��->�� 1��->�� 2����
			char map[15][15];				//�������̵�ͼ(0-ĳ���,1-����,2-����)
											//��ʾ������ĳһ��������Ƿ��Ѿ��¹���
			//���²������ڱ���������ʷ��¼
			int nowd2;						//��ʾ��ǰ�Ѿ����˶����ӵļ�����
			wzsave wzs[225];				//��Ӧ���̵�15��*15��

	��Щ����ȫ������ͨ��twzq.****�ĸ�ʽ����д���磺
		������˳�����������������������д��
			twzq.nturn=1;
*/
void CMyDlg::OnLoad() 
{
	CString ls_fileName;

	/*��ʾ���ļ��Ի���
	CFileDialog(BOOL bOpenFileDialog,  TRUE for FileOpen, FALSE for FileSaveAs
		LPCTSTR lpszDefExt = NULL,	 Ĭ����չ��
		LPCTSTR lpszFileName = NULL, Ĭ���ļ�����
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,�򿪷�ʽ
		LPCTSTR lpszFilter = NULL,	�ɹ�ѡ����ļ����ͺ���Ӧ����չ��,�ļ�����֮����|�ָ�,��β��||�ָ�
		CWnd* pParentWnd = NULL);
	*/

	CFileDialog lcf_open(true,"wzq",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
			"wzq files(*.wzq)||",NULL);
	if (lcf_open.DoModal()==IDOK){

		//ȡ�ļ�����
		ls_fileName = lcf_open.GetPathName();
		//��ʼһ������Ϸ
		twzq.NewGame();


		/*�ӱ�����ļ��ж�����,���ļ���Ҫʹ�õ������ļ���ifstream,ʹ�õ���ز���Ϊ:
			open����			���ļ�����д,д����ʱ��Ҫ����ļ��Ƿ���������
			close����			д��ر��ļ�
			getline����			���ļ��ж���һ������
			>>����				���ļ��ж�����
		  �����Ҫ��ʾ��ʾ��Ϣ����ʹ��AfxMessageBox����
		*/
		AfxMessageBox("���ع�����δʵ��,����ʼһ������Ϸ");

	}	

	//���û��尴ť��״̬
	CMyDlg::m_back.EnableWindow(twzq.getbackble()); 
	//�ػ���Ļ
	twzq.draw();
}
