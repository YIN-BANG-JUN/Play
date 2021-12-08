
// PlayDlg.h: 头文件

#pragma once

#define DIALOG_HIGH 600		//窗口高度
#define DIALOG_WIDE	900		//窗口宽度

#define MAP_ROW		4		//行
#define MAP_LIST	4		//列
#define IMG_SIZE	17		//最大图片数

struct bounDary				//空白图片位置
{
	int x;
	int y;
};

// CPlayDlg 对话框
class CPlayDlg : public CDialogEx
{
// 构造
public:
	CPlayDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PLAY_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CComboBox* m_list;								//CComboBox控件变量
	CString    m_str;								//关卡接收字符串
	UINT       m_Uint;								//关卡标识
	CRect      m_rect;								//背景区矩形坐标
	int        m_add;								//关卡步数

	afx_msg void OnBnClickedButton1();				//开始游戏
	afx_msg void OnBnClickedButton2();				//结束游戏
	afx_msg void OnBnClickedButton3();				//重置游戏
	virtual BOOL PreTranslateMessage(MSG* pMsg);	//移动图片

	void initMap(int lovel);						//初始化贴图数组
	void initImg(int lovel);						//初始化贴图
	void showImg(int kd);							//显示图片
	bool boundary(bounDary point);					//判断移动边界值是否合法
	int showCoordinate(bounDary point);				//返回交换图片位置坐标
	void coorDinate(int index, bounDary point);		//交换图片
	void showStr(int lovel);						//将步数输出到编辑对话框
	bool judgeClearance();							//判断图片是否全部移动到位
	

	int    randd[IMG_SIZE - 1];						//图片随机数
	int	   m_map[MAP_ROW][MAP_LIST];				//贴图数组

	CImage m_img1[IMG_SIZE - 7];					//图片数组
	CImage m_img2[IMG_SIZE - 7];					//图片数组
	CImage m_img3[IMG_SIZE];						//图片数组

	CDC m_memdc;									//设备上下文
	CBitmap m_bitmap;								//图片类
	BITMAP m_bmInfo;								//图片类
	bounDary point;									//白图坐标
	bool begain;									//开始或结束游戏标识
	
};
