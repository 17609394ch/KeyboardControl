
// KeyboardControlDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "KeyboardControl.h"
#include "KeyboardControlDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CKeyboardControlDlg 对话框



CKeyboardControlDlg::CKeyboardControlDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_KEYBOARDCONTROL_DIALOG, pParent),
	SELECT_MODE(0),
	vd(0.1),
	wd(0.1),
	isInitKvaser(false),
	m_kvaser(new Kvaser())
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON_APP);
}

void CKeyboardControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, BUTTON_End, Close_Button);
	DDX_Control(pDX, BUTTON_InitKvaser, Start_Init);
}

BEGIN_MESSAGE_MAP(CKeyboardControlDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(BUTTON_InitKvaser, &CKeyboardControlDlg::OnBnClickedInitkvaser)
	ON_BN_CLICKED(BUTTON_End, &CKeyboardControlDlg::OnBnClickedEnd)
END_MESSAGE_MAP()


// CKeyboardControlDlg 消息处理程序

BOOL CKeyboardControlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	Close_Button.SetWindowTextW(L"未初始化Kvaser");

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CKeyboardControlDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CKeyboardControlDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CKeyboardControlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL CKeyboardControlDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYUP)

	{
		// 响应keyup消息
		//MessageBox(_T("有键被按下"));
		//判断具体键
		switch (pMsg->wParam)
		{
		case 81:
			vd += 0.05;
			if (vd>=0.3)
			{
				vd = 0.3;
			}
			ControlMode(SELECT_MODE);
			return TRUE;
			break;
		case 65:
			vd -= 0.1;
			if (vd <= -0.3)
			{
				vd = -0.3;
			}
			ControlMode(SELECT_MODE);
			return TRUE;
			break;
		case 87:
			wd += 0.1;
			if (wd >= 0.3)
			{
				wd = 0.3;
			}
			ControlMode(SELECT_MODE);
			return TRUE;
			break;
		case 83:
			wd -= 0.1;
			if (wd <= -0.3)
			{
				wd = -0.3;
			}

			ControlMode(SELECT_MODE);
			return TRUE;
			break;

		case VK_UP://按下上键
			SELECT_MODE = 1;
			ControlMode(SELECT_MODE);
			return TRUE;
			break;

		case VK_DOWN://按下下键
			SELECT_MODE = 2;
			ControlMode(SELECT_MODE);
			return TRUE;
			break;

		case VK_LEFT://按下左键
			SELECT_MODE = 3;
			ControlMode(SELECT_MODE);
			return TRUE;
			break;

		case VK_RIGHT://按下右键
			SELECT_MODE = 4;
			ControlMode(SELECT_MODE);
			return TRUE;
			break;

		case 32://按下空格
			SELECT_MODE = 0;
			vd = 0.1;
			wd = 0.0;
			ControlMode(SELECT_MODE);
			return TRUE;
			break;

		default:
			return TRUE;
			break;
		}
	}


	return CDialogEx::PreTranslateMessage(pMsg);
}

void CKeyboardControlDlg::ControlMode(UINT mode)
{
	double wheelRadius = 0.315 / 2;
	switch (mode)
	{
	case 0:  //按下上键
		m_kvaser->speedMode(1, 0);
		m_kvaser->speedMode(2, 0);
		break;
	case 1:  //按下上键
		m_kvaser->speedMode(1, vd * 32 * 4096 / 2 / PI / wheelRadius);
		m_kvaser->speedMode(2, vd * 32 * 4096 / 2 / PI / wheelRadius);
		break;
	case 2:  //按下下键
		m_kvaser->speedMode(1, -vd * 32 * 4096 / 2 / PI / wheelRadius);
		m_kvaser->speedMode(2, -vd * 32 * 4096 / 2 / PI / wheelRadius);
		break;
	case 3:  //按下左键
		m_kvaser->speedMode(1, -wd * 32 * 4096 / 2 / PI / wheelRadius);
		m_kvaser->speedMode(2, wd * 32 * 4096 / 2 / PI / wheelRadius);
		break;
	case 4:  //按下右键
		m_kvaser->speedMode(1, wd * 32 * 4096 / 2 / PI / wheelRadius);
		m_kvaser->speedMode(2, -wd * 32 * 4096 / 2 / PI / wheelRadius);
		break;
	default:
		break;
	}
}

void CKeyboardControlDlg::OnBnClickedInitkvaser()
{
	// TODO: 在此添加控件通知处理程序代码
	if (isInitKvaser)
	{
		return;
	}
	isInitKvaser = true;

	m_kvaser->canInit(0);//初始化电机

	m_kvaser->connectMotor(1);//连接电机
	m_kvaser->connectMotor(2);

	m_kvaser->motorEnable(1);//使能电机
	m_kvaser->motorEnable(2);

	m_kvaser->modeChoose(1, m_kvaser->SPEED_MODE);//速度模式
	m_kvaser->modeChoose(2, m_kvaser->SPEED_MODE);


	Close_Button.SetWindowTextW(L"退出");
	Start_Init.SetWindowTextW(L"已经初始化Kvaser");



}


void CKeyboardControlDlg::OnBnClickedEnd()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!isInitKvaser)
	{
		UINT i = MessageBox(TEXT("确认要退出程序吗？"), TEXT("温馨提示"), MB_YESNO | MB_ICONQUESTION);
		if (i == IDNO)
		{
			return;
		}

		CDialogEx::OnOK();
		return;
	}
	isInitKvaser = false;

	m_kvaser->motorDisable(1);//关闭电机
	m_kvaser->motorDisable(2);
	m_kvaser->canRelease();//释放电机

	delete m_kvaser;

	CDialogEx::OnOK();
}
