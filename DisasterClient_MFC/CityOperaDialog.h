#pragma once
#include "GameMapCity.h"

// CityOperaDialog 对话框

class CityOperaDialog : public CDialog
{
	DECLARE_DYNAMIC(CityOperaDialog)

public:
	CityOperaDialog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CityOperaDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CITY_OPERA1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

	GameLogic::GameMap::SCityInfo* m_pCurCityInfo;
};
