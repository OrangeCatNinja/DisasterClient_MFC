
// DisasterClient_MFCDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "DisasterClient_MFC.h"
#include "DisasterClient_MFCDlg.h"
#include "afxdialogex.h"

#include "ParamsManager.h"
#include "NetWorkManager.h"

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


// CDisasterClientMFCDlg 对话框


namespace GameLogic
{
	namespace GameMap
	{
	CDisasterClientMFCDlg::CDisasterClientMFCDlg(CWnd* pParent /*=nullptr*/)
		: CDialogEx(IDD_DISASTERCLIENT_MFC_DIALOG, pParent)
	{
		m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	}

	void CDisasterClientMFCDlg::DoDataExchange(CDataExchange* pDX)
	{
		CDialogEx::DoDataExchange(pDX);
	}

	BEGIN_MESSAGE_MAP(CDisasterClientMFCDlg, CDialogEx)
		ON_WM_SYSCOMMAND()
		ON_WM_PAINT()
		ON_WM_QUERYDRAGICON()
	END_MESSAGE_MAP()


	// CDisasterClientMFCDlg 消息处理程序

	BOOL CDisasterClientMFCDlg::OnInitDialog()
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

		ShowWindow(SW_MAXIMIZE);

		// TODO: 在此添加额外的初始化代码
		NetWork::SHttpRequestMessage message;
		GETNETWORK()->SendMessage(message);

		if (!InitMap())
			return FALSE;

		return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
	}

	void CDisasterClientMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

	void CDisasterClientMFCDlg::OnPaint()
	{
		CPaintDC dc(this); // 用于绘制的设备上下文
		if (IsIconic())
		{
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

		//绘制各城市之间的连线
		DrawCityLine(dc);
	}

	//当用户拖动最小化窗口时系统调用此函数取得光标
	//显示。
	HCURSOR CDisasterClientMFCDlg::OnQueryDragIcon()
	{
		return static_cast<HCURSOR>(m_hIcon);
	}

	bool CDisasterClientMFCDlg::InitMap()
	{
		const Param::MapParam& mapParam = Param::CParamsManager::GetInstance().GetMapParam();

		auto itr = mapParam.begin();
		for (; itr != mapParam.end(); ++itr)
		{
			CreateCity(itr->second);
		}

		return true;
	}

	void CDisasterClientMFCDlg::CreateCity(const SCityInfo& cityInfo)
	{
		GameMapCity* city = new GameMapCity(cityInfo);
		m_mapCityInfo.insert(std::pair<WORD, GameMapCity*>(cityInfo.m_id, city));

		city->Create(NULL, _T("Game Map City"), WS_CHILD | WS_VISIBLE,
			CRect(CPoint(cityInfo.m_position.x, cityInfo.m_position.y), GameMapCity::szDefault),
			this, IDC_CITYBUTTON);

		city->ShowWindow(SW_SHOWNORMAL);
	}

	void CDisasterClientMFCDlg::DrawCityLine(CPaintDC& dc)
	{
		std::unordered_set<WORD> citySet;
		CPen pen(PS_SOLID, 5, RGB(0, 0, 0));
		dc.SelectObject(pen);

		for (auto& city : m_mapCityInfo)
		{
			if (citySet.find(city.first) != citySet.end())
				continue;

			citySet.insert(city.first);
			const CPoint selfPs = city.second->GetCenterPos();
			const auto& adjoinVec = city.second->GetAdjoinCity();
			for (auto& adjoinCity : adjoinVec)
			{
				const GameMapCity* pAdCity = m_mapCityInfo.find(adjoinCity) != m_mapCityInfo.end() ?
					m_mapCityInfo[adjoinCity] : NULL;
				
				if(!pAdCity)
					continue;

				const CPoint adPs = pAdCity->GetCenterPos();

				dc.MoveTo(selfPs);
				dc.LineTo(adPs);
			}
		}
	}

}
}