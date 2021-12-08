
// PlayDlg.cpp: 实现文件

#include "pch.h"
#include "framework.h"
#include "Play.h"
#include "PlayDlg.h"
#include "afxdialogex.h"
#include <time.h>

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
public:

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


// CPlayDlg 对话框

CPlayDlg::CPlayDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PLAY_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	//初始化成员变量
	m_list = nullptr;

	m_Uint = 0;
	m_map[0][0] = NULL;

	m_bmInfo;
	begain = false;

	point.x = 0;
	point.y = 0;

	randd[0] = 0;
	m_add = 0;
}

void CPlayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPlayDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CPlayDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CPlayDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CPlayDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CPlayDlg 消息处理程序

BOOL CPlayDlg::OnInitDialog()
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

	//设置关卡初始值
	m_list = (CComboBox*)GetDlgItem(IDC_COMBO1);
	m_list->AddString(_T("1"));
	m_list->AddString(_T("2"));
	m_list->AddString(_T("3"));
	m_list->SetCurSel(0);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CPlayDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CPlayDlg::OnPaint()
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
		//1.加载背景图片
		CPaintDC dc(this);						//设备上下文
		CDC memdc;								//设备上下文
		CImage img;								//图片类
		CBitmap bitmap;							//图片类
		BITMAP bmInfo;							//图片类
		GetClientRect(m_rect);					//获取客户区大小

		img.Load(_T("x64/Release/res/1.png"));					//载入图片
		bitmap.Attach(img.Detach());				//获得图片
		bitmap.GetBitmap(&bmInfo);					//选中图片
		memdc.CreateCompatibleDC(&dc);				//转换兼容设备上下文
		memdc.SelectObject(bitmap);					//选中兼容设备上下文
		dc.StretchBlt(0, 0, m_rect.Width(), m_rect.Height(), &memdc, 0, 0, bmInfo.bmWidth, bmInfo.bmHeight, SRCCOPY);	//指定区域填充图片
		bitmap.Detach();							//分离类和窗口
		memdc.DeleteDC();							//释放设备上下文
		bitmap.DeleteObject();						//释放图片

		//2.画边框线
		CBrush* brush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
		CBrush* cb = dc.SelectObject(brush);
		dc.Rectangle(DIALOG_WIDE - 250, DIALOG_HIGH - 600, DIALOG_WIDE, DIALOG_HIGH);

		//3.指定位置输出文字
		CFont font;
		font.CreatePointFont(300, _T("楷体"));
		CFont* fot = dc.SelectObject(&font);
		dc.SetTextColor(RGB(255, 0, 0));
		CString str(_T("拼图游戏"));
		dc.TextOut(DIALOG_WIDE - 200, DIALOG_HIGH - 590, str, str.GetLength());

		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CPlayDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//开始游戏
void CPlayDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	//1.选择关卡,开始游戏
	CComboBox* lis = (CComboBox*)GetDlgItem(IDC_COMBO1);
	int n = lis->GetCurSel();
	lis->GetLBText(n, m_str);
	MessageBox(m_str);
	m_Uint = n + 1;

	//good();					//通关关卡设置

	initMap(m_Uint);		//初始化贴图数组
	initImg(m_Uint);		//初始化贴图
	showImg(m_Uint);		//显示图片

	begain = true;

	randd[0] = 0;
	m_add = 0;
	showStr(m_add);
}

//结束游戏
void CPlayDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码

	//结束游戏,关闭窗口
	EndDialog(0);
}

//重置游戏
void CPlayDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	m_add = 0;
	if (begain == true) {
		if (m_Uint == 1)
		{
			initMap(1);		//初始化贴图数组
			initImg(1);		//初始化贴图
			showImg(1);		//显示图片

			randd[0] = 0;
			showStr(m_add);
		}
		else if (m_Uint == 2)
		{
			initMap(2);		//初始化贴图数组
			initImg(2);		//初始化贴图
			showImg(2);		//显示图片

			randd[0] = 0;
			showStr(m_add);
		}
		else
		{
			initMap(3);		//初始化贴图数组
			initImg(3);		//初始化贴图
			showImg(3);		//显示图片

			randd[0] = 0;
			showStr(m_add);
		}
	}
}

//初始化贴图数组
void CPlayDlg::initMap(int lovel)
{
	srand((unsigned int)time(0));

	//获取贴图数组随机数
	if (lovel == 1 || lovel == 2) {
		randd[0] = rand() % 9 + 1;
		for (int i = 0; i < IMG_SIZE - 8; i++)
		{
		ST: randd[i] = rand() % 9 + 1;
			for (int j = 0; j < i; j++)
			{
				if (randd[i] == randd[j])
				{
					goto ST;
				}
			}
		}
	}
	else
	{
		randd[0] = rand() % 16 + 1;
		for (int i = 0; i < 16; i++)
		{
		SP: randd[i] = rand() % 16 + 1;
			for (int j = 0; j < i; j++)
			{
				if (randd[i] == randd[j])
				{
					goto SP;
				}
			}
		}
	}

	//贴图数组赋值
	if (lovel == 1 || lovel == 2)
	{
		int n = 0;
		for (int i = 0; i < MAP_ROW - 1; i++)
		{
			for (int j = 0; j < MAP_LIST - 1; j++)
			{
				m_map[i][j] = randd[n++];
			}
		}
	}
	else
	{
		int n = 0;
		for (int i = 0; i < MAP_ROW; i++)
		{
			for (int j = 0; j < MAP_LIST; j++)
			{
				m_map[i][j] = randd[n++];
			}
		}
	}

	//确定空白图片位置
	if (lovel == 1 || lovel == 2)
	{
		for (int i = 0; i < MAP_ROW - 1; i++)
		{
			for (int j = 0; j < MAP_LIST - 1; j++)
			{
				if (m_map[i][j] == 9)
				{
					point.x = i;
					point.y = j;
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < MAP_ROW; i++)
		{
			for (int j = 0; j < MAP_LIST; j++)
			{
				if (m_map[i][j] == 16)
				{
					point.x = i;
					point.y = j;
				}
			}
		}
	}
}

//初始化贴图
void CPlayDlg::initImg(int lovel)
{
	switch (lovel)
	{
	case 1:
		if (m_img1[0] == NULL)
		{
			m_img1[0].Load(_T("x64/Release/res/res2/A1.png"));	//载入图片
			m_img1[1].Load(_T("x64/Release/res/res3/1.png"));	//载入图片
			m_img1[2].Load(_T("x64/Release/res/res3/2.png"));	//载入图片
			m_img1[3].Load(_T("x64/Release/res/res3/3.png"));	//载入图片
			m_img1[4].Load(_T("x64/Release/res/res3/4.png"));	//载入图片
			m_img1[5].Load(_T("x64/Release/res/res3/5.png"));	//载入图片
			m_img1[6].Load(_T("x64/Release/res/res3/6.png"));	//载入图片
			m_img1[7].Load(_T("x64/Release/res/res3/7.png"));	//载入图片
			m_img1[8].Load(_T("x64/Release/res/res3/8.png"));	//载入图片
			m_img1[9].Load(_T("x64/Release/res/res3/9.png"));	//载入图片

		}
		break;
	case 2:
		if (m_img2[0] == NULL)
		{
			m_img2[0].Load(_T("x64/Release/res/res2/A2.png"));	//载入图片
			m_img2[1].Load(_T("x64/Release/res/res4/1.png"));	//载入图片
			m_img2[2].Load(_T("x64/Release/res/res4/2.png"));	//载入图片
			m_img2[3].Load(_T("x64/Release/res/res4/3.png"));	//载入图片
			m_img2[4].Load(_T("x64/Release/res/res4/4.png"));	//载入图片
			m_img2[5].Load(_T("x64/Release/res/res4/5.png"));	//载入图片
			m_img2[6].Load(_T("x64/Release/res/res4/6.png"));	//载入图片
			m_img2[7].Load(_T("x64/Release/res/res4/7.png"));	//载入图片
			m_img2[8].Load(_T("x64/Release/res/res4/8.png"));	//载入图片
			m_img2[9].Load(_T("x64/Release/res/res4/9.png"));	//载入图片

		}
		break;
	case 3:
		if (m_img3[0] == NULL)
		{
			m_img3[0].Load(_T("x64/Release/res/res2/A3.png"));	//载入图片
			m_img3[1].Load(_T("x64/Release/res/res5/1.png"));	//载入图片
			m_img3[2].Load(_T("x64/Release/res/res5/2.png"));	//载入图片
			m_img3[3].Load(_T("x64/Release/res/res5/3.png"));	//载入图片
			m_img3[4].Load(_T("x64/Release/res/res5/4.png"));	//载入图片
			m_img3[5].Load(_T("x64/Release/res/res5/5.png"));	//载入图片
			m_img3[6].Load(_T("x64/Release/res/res5/6.png"));	//载入图片
			m_img3[7].Load(_T("x64/Release/res/res5/7.png"));	//载入图片
			m_img3[8].Load(_T("x64/Release/res/res5/8.png"));	//载入图片
			m_img3[9].Load(_T("x64/Release/res/res5/9.png"));	//载入图片
			m_img3[10].Load(_T("x64/Release/res/res5/10.png"));	//载入图片
			m_img3[11].Load(_T("x64/Release/res/res5/11.png"));	//载入图片
			m_img3[12].Load(_T("x64/Release/res/res5/12.png"));	//载入图片
			m_img3[13].Load(_T("x64/Release/res/res5/13.png"));	//载入图片
			m_img3[14].Load(_T("x64/Release/res/res5/14.png"));	//载入图片
			m_img3[15].Load(_T("x64/Release/res/res5/15.png"));	//载入图片
			m_img3[16].Load(_T("x64/Release/res/res5/16.png"));	//载入图片

		}
		break;
	}
}

//显示图片
void CPlayDlg::showImg(int kd)
{
	CClientDC dc(this);						//设备上下文
	if (kd == 1)
	{
		for (int i = 0; i < MAP_ROW - 1; i++)
		{
			for (int j = 0; j < MAP_LIST - 1; j++)
			{
				m_bitmap.Attach(m_img1[m_map[i][j]].Detach());					//获得图片
				m_bitmap.GetBitmap(&m_bmInfo);									//选中图片
				m_memdc.CreateCompatibleDC(&dc);								//转换兼容设备上下文
				m_memdc.SelectObject(m_bitmap);									//选中兼容设备上下文
				dc.StretchBlt(i * 200, j * 200, i + 200, j + 200, &m_memdc, 0, 0, m_bmInfo.bmWidth, m_bmInfo.bmHeight, SRCCOPY);	//指定区域填充图片
				m_bitmap.Detach();											//分离类和窗口
				m_memdc.DeleteDC();											//释放设备上下文
				m_bitmap.DeleteObject();									//释放图片
			}
		}
		m_bitmap.Attach(m_img1[0].Detach());								//获得图片
		m_bitmap.GetBitmap(&m_bmInfo);									//选中图片
		m_memdc.CreateCompatibleDC(&dc);									//转换兼容设备上下文
		m_memdc.SelectObject(m_bitmap);									//选中兼容设备上下文
		dc.StretchBlt(680, 380, m_rect.Width() - 700, m_rect.Height() - 400, &m_memdc, 0, 0, m_bmInfo.bmWidth, m_bmInfo.bmHeight, SRCCOPY);	//指定区域填充图片
		m_bitmap.Detach();												//分离类和窗口
		m_memdc.DeleteDC();												//释放设备上下文
		m_bitmap.DeleteObject();										//释放图片
	}
	else if (kd == 2)
	{
		for (int i = 0; i < MAP_ROW - 1; i++)
		{
			for (int j = 0; j < MAP_LIST - 1; j++)
			{
				m_bitmap.Attach(m_img2[m_map[i][j]].Detach());					//获得图片
				m_bitmap.GetBitmap(&m_bmInfo);									//选中图片
				m_memdc.CreateCompatibleDC(&dc);								//转换兼容设备上下文
				m_memdc.SelectObject(m_bitmap);									//选中兼容设备上下文
				dc.StretchBlt(i * 200, j * 200, i + 200, j + 200, &m_memdc, 0, 0, m_bmInfo.bmWidth, m_bmInfo.bmHeight, SRCCOPY);	//指定区域填充图片
				m_bitmap.Detach();											//分离类和窗口
				m_memdc.DeleteDC();											//释放设备上下文
				m_bitmap.DeleteObject();									//释放图片
			}
		}
		m_bitmap.Attach(m_img2[0].Detach());								//获得图片
		m_bitmap.GetBitmap(&m_bmInfo);									//选中图片
		m_memdc.CreateCompatibleDC(&dc);									//转换兼容设备上下文
		m_memdc.SelectObject(m_bitmap);									//选中兼容设备上下文
		dc.StretchBlt(680, 380, m_rect.Width() - 700, m_rect.Height() - 400, &m_memdc, 0, 0, m_bmInfo.bmWidth, m_bmInfo.bmHeight, SRCCOPY);	//指定区域填充图片
		m_bitmap.Detach();												//分离类和窗口
		m_memdc.DeleteDC();												//释放设备上下文
		m_bitmap.DeleteObject();										//释放图片
	}
	else if (kd == 3)
	{
		for (int i = 0; i < MAP_ROW; i++)
		{
			for (int j = 0; j < MAP_LIST; j++)
			{
				m_bitmap.Attach(m_img3[m_map[i][j]].Detach());					//获得图片
				m_bitmap.GetBitmap(&m_bmInfo);									//选中图片
				m_memdc.CreateCompatibleDC(&dc);								//转换兼容设备上下文
				m_memdc.SelectObject(m_bitmap);									//选中兼容设备上下文
				dc.StretchBlt(i * 150, j * 150, i + 150, j + 150, &m_memdc, 0, 0, m_bmInfo.bmWidth, m_bmInfo.bmHeight, SRCCOPY);	//指定区域填充图片
				m_bitmap.Detach();											//分离类和窗口
				m_memdc.DeleteDC();											//释放设备上下文
				m_bitmap.DeleteObject();									//释放图片
			}
		}
		m_bitmap.Attach(m_img3[0].Detach());								//获得图片
		m_bitmap.GetBitmap(&m_bmInfo);									//选中图片
		m_memdc.CreateCompatibleDC(&dc);									//转换兼容设备上下文
		m_memdc.SelectObject(m_bitmap);									//选中兼容设备上下文
		dc.StretchBlt(680, 380, m_rect.Width() - 700, m_rect.Height() - 400, &m_memdc, 0, 0, m_bmInfo.bmWidth, m_bmInfo.bmHeight, SRCCOPY);	//指定区域填充图片
		m_bitmap.Detach();												//分离类和窗口
		m_memdc.DeleteDC();												//释放设备上下文
		m_bitmap.DeleteObject();										//释放图片
	}
}

//判断移动边界值是否合法
bool CPlayDlg::boundary(bounDary point)
{
	int x = point.x;
	int y = point.y;
	if (m_Uint == 1 || m_Uint == 2)
	{
		if ((x >= 0 && x <= 2) && (y >= 0 && y <= 2))
		{
			return true;
		}
	}
	else if (m_Uint == 3)
	{
		if ((x >= 0 && x <= 3) && (y >= 0 && y <= 3))
		{
			return true;
		}
	}
	return false;
}

//返回交换图片位置坐标
int CPlayDlg::showCoordinate(bounDary point)
{
	return m_map[point.x][point.y];
}

//交换图片
void CPlayDlg::coorDinate(int index, bounDary point)
{
	CClientDC dc(this);						//设备上下文
	CDC memdc;								//设备上下文
	CImage img1;								//图片类
	CBitmap bitmap;							//图片类
	BITMAP bmInfo;							//图片类

	initImg(m_Uint);

	if (m_Uint == 1)
	{
		img1 = m_img1[index];
		bitmap.Attach(img1.Detach());						//获得图片
		bitmap.GetBitmap(&bmInfo);									//选中图片
		memdc.CreateCompatibleDC(&dc);								//转换兼容设备上下文
		memdc.SelectObject(bitmap);									//选中兼容设备上下文
		dc.StretchBlt(point.x * 200, point.y * 200, point.x + 200, point.y + 200, &memdc, 0, 0, bmInfo.bmWidth, bmInfo.bmHeight, SRCCOPY);	//指定区域填充图片
		bitmap.Detach();											//分离类和窗口
		memdc.DeleteDC();											//释放设备上下文
		bitmap.DeleteObject();									//释放图片
	}
	else if (m_Uint == 2)
	{
		img1 = m_img2[index];
		bitmap.Attach(img1.Detach());						//获得图片
		bitmap.GetBitmap(&bmInfo);									//选中图片
		memdc.CreateCompatibleDC(&dc);								//转换兼容设备上下文
		memdc.SelectObject(bitmap);									//选中兼容设备上下文
		dc.StretchBlt(point.x * 200, point.y * 200, point.x + 200, point.y + 200, &memdc, 0, 0, bmInfo.bmWidth, bmInfo.bmHeight, SRCCOPY);	//指定区域填充图片
		bitmap.Detach();											//分离类和窗口
		memdc.DeleteDC();											//释放设备上下文
		bitmap.DeleteObject();									//释放图片
	}
	else
	{
		img1 = m_img3[index];
		bitmap.Attach(img1.Detach());						//获得图片
		bitmap.GetBitmap(&bmInfo);									//选中图片
		memdc.CreateCompatibleDC(&dc);								//转换兼容设备上下文
		memdc.SelectObject(bitmap);									//选中兼容设备上下文
		dc.StretchBlt(point.x * 150, point.y * 150, point.x + 150, point.y + 150, &memdc, 0, 0, bmInfo.bmWidth, bmInfo.bmHeight, SRCCOPY);	//指定区域填充图片
		bitmap.Detach();											//分离类和窗口
		memdc.DeleteDC();											//释放设备上下文
		bitmap.DeleteObject();									//释放图片
	}
}

//将步数输出到编辑对话框
void CPlayDlg::showStr(int lovel)
{
	CString    str;									//步数输出字符
	str.Format(_T("%d"), lovel);
	GetDlgItem(IDC_EDIT1)->SetWindowText(str);
}

//判断图片是否全部移动到位
bool CPlayDlg::judgeClearance()
{
	if (m_Uint == 1 || m_Uint == 2)
	{
		if (m_map[0][0] == 1 && m_map[0][1] == 4 && m_map[0][2] == 7 &&
			m_map[1][0] == 2 && m_map[1][1] == 5 && m_map[1][2] == 8 &&
			m_map[2][0] == 3 && m_map[2][1] == 6 && m_map[2][2] == 9)
		{
			return true;
		}
	}
	else
	{
		if (m_map[0][0] == 1 && m_map[0][1] == 5 && m_map[0][2] == 9 && m_map[0][3] == 13 &&
			m_map[1][0] == 2 && m_map[1][1] == 6 && m_map[1][2] == 10 && m_map[1][3] == 14 &&
			m_map[2][0] == 3 && m_map[2][1] == 7 && m_map[2][2] == 12 && m_map[2][3] == 15 &&
			m_map[3][0] == 4 && m_map[3][1] == 8 && m_map[3][2] == 11 && m_map[3][3] == 16)
		{
			return true;
		}
	}
	return false;
}

//移动图片
BOOL CPlayDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	bounDary pointxy;									//白图坐标
	int		   Iint;									//图片标识
	Iint = 0;
	pointxy = point;

	if (pMsg->message == WM_KEYDOWN && begain == true)
	{

		switch (pMsg->wParam) {

		case VK_UP:  //up
			pointxy.y--;
			if (boundary(pointxy))
			{
				Iint = showCoordinate(pointxy);
				coorDinate(Iint, point);
				if (m_Uint == 1 || m_Uint == 2)
				{
					coorDinate(9, pointxy);
					m_add++;
					showStr(m_add);
				}
				else
				{
					coorDinate(16, pointxy);
					m_add++;
					showStr(m_add);
				}
				//MessageBox(_T("上"));
				if (m_Uint == 1 || m_Uint == 2)
				{
					m_map[pointxy.x][pointxy.y] = 9;
					m_map[point.x][point.y] = Iint;
					point = pointxy;
				}
				else
				{
					m_map[pointxy.x][pointxy.y] = 16;
					m_map[point.x][point.y] = Iint;
					point = pointxy;
				}
			}
			break;


		case VK_DOWN:  //down
			pointxy.y++;
			if (boundary(pointxy))
			{
				Iint = showCoordinate(pointxy);
				coorDinate(Iint, point);
				if (m_Uint == 1 || m_Uint == 2)
				{
					coorDinate(9, pointxy);
					m_add++;
					showStr(m_add);
				}
				else
				{
					coorDinate(16, pointxy);
					m_add++;
					showStr(m_add);
				}
				//MessageBox(_T("下"));
				if (m_Uint == 1 || m_Uint == 2)
				{
					m_map[pointxy.x][pointxy.y] = 9;
					m_map[point.x][point.y] = Iint;
					point = pointxy;
				}
				else
				{
					m_map[pointxy.x][pointxy.y] = 16;
					m_map[point.x][point.y] = Iint;
					point = pointxy;
				}
			}
			break;


		case VK_LEFT:  //left
			pointxy.x--;
			if (boundary(pointxy))
			{
				Iint = showCoordinate(pointxy);
				coorDinate(Iint, point);
				if (m_Uint == 1 || m_Uint == 2)
				{
					coorDinate(9, pointxy);
					m_add++;
					showStr(m_add);
				}
				else
				{
					coorDinate(16, pointxy);
					m_add++;
					showStr(m_add);
				}
				//MessageBox(_T("左"));
				if (m_Uint == 1 || m_Uint == 2)
				{
					m_map[pointxy.x][pointxy.y] = 9;
					m_map[point.x][point.y] = Iint;
					point = pointxy;
				}
				else
				{
					m_map[pointxy.x][pointxy.y] = 16;
					m_map[point.x][point.y] = Iint;
					point = pointxy;
				}
			}
			break;


		case VK_RIGHT:  //right
			pointxy.x++;
			if (boundary(pointxy))
			{
				Iint = showCoordinate(pointxy);
				coorDinate(Iint, point);
				if (m_Uint == 1 || m_Uint == 2)
				{
					coorDinate(9, pointxy);
					m_add++;
					showStr(m_add);
				}
				else
				{
					coorDinate(16, pointxy);
					m_add++;
					showStr(m_add);
				}
				//MessageBox(_T("右"));
				if (m_Uint == 1 || m_Uint == 2)
				{
					m_map[pointxy.x][pointxy.y] = 9;
					m_map[point.x][point.y] = Iint;
					point = pointxy;
				}
				else
				{
					m_map[pointxy.x][pointxy.y] = 16;
					m_map[point.x][point.y] = Iint;
					point = pointxy;
				}
			}
			break;
		}
		if (judgeClearance())
		{
			MessageBox(_T("恭喜您当前关卡拼图成功! 重置当前关卡或重新选择关卡开始游戏!"));
			begain = false;
		}
		return true;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}