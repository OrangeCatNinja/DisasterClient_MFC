
// DisasterClient_MFCDlg.h: 头文件
//

#pragma once
#include "GameMapCity.h"

class GameMapCity;

namespace GameLogic
{
namespace GameMap
{


// CDisasterClientMFCDlg 对话框
class CDisasterClientMFCDlg : public CDialogEx
{
// 构造
public:
	CDisasterClientMFCDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DISASTERCLIENT_MFC_DIALOG };
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

private:
	bool InitMap();

private:
	void CreateCity(const SCityInfo& cityInfo);
	void DrawCityLine(CPaintDC& dc);

private:
	//处理http应答报文的方法
	bool OnRespInit(const std::string& response);

private:
	std::unordered_map<WORD, GameMapCity*> m_mapCityInfo;
};

}
}