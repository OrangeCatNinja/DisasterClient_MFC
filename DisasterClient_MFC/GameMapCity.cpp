#include "pch.h"
#include "GameMapCity.h"
#include "ParamsManager.h"

namespace GameLogic
{

namespace GameMap
{
	int GameMapCity::nCityImageWidth = 150;
	int GameMapCity::nCityImageHight = 150;
	int GameMapCity::nCityNameHight = 30;
	CSize GameMapCity::szDefault = CSize(nCityImageWidth, nCityImageHight + nCityNameHight);//默认控件尺寸
	COLORREF GameMapCity::colFriendText = RGB(0, 255, 0);//友方城市-绿色
	COLORREF GameMapCity::colEnemyText = RGB(255, 0, 0);//敌方城市-红色
	COLORREF GameMapCity::colNeutralText = RGB(255, 255, 0);//中立城市-黄色

	BEGIN_MESSAGE_MAP(GameMapCity, CWnd)
		ON_WM_PAINT()
		ON_WM_RBUTTONDOWN()
	END_MESSAGE_MAP()

	GameMapCity::GameMapCity(const SCityInfo& info)
	{
		m_cityInfo = info;

		SetImage(info.m_cityType);
	}

	GameMapCity::~GameMapCity()
	{
	}

	const CPoint GameMapCity::GetCenterPos() const
	{
		CPoint ps(m_cityInfo.m_position);
		ps.x += nCityImageWidth / 2;
		ps.y += (nCityImageHight + nCityNameHight) / 2;

		return ps;
	}

	const std::vector<WORD>& GameMapCity::GetAdjoinCity() const
	{
		return m_cityInfo.m_pAdjoinCity;
	}

	void GameMapCity::OnRButtonDown(UINT, CPoint)
	{
		AfxMessageBox(_T("Clicked!"));
	}

	void GameMapCity::OnPaint()
	{
		CPaintDC dc(this);

		//绘制图片
		if (!m_strImagePath.IsEmpty())
		{
			CRect rectImage(CPoint(0, 0), CSize(nCityImageWidth, nCityImageHight));
			m_image.Draw(dc, rectImage);
		}

		//绘制文本
		if (!m_cityInfo.m_strCityName.IsEmpty())
		{
			CRect rectText(CPoint(0, nCityImageHight), CSize(nCityImageWidth, nCityNameHight));
			dc.SetTextColor(m_textColor);
			dc.TextOutW(rectText.left, rectText.top, m_cityInfo.m_strCityName);
		}
	}

	void GameMapCity::SetImage(EnCityType type)
	{
		m_strImagePath = Param::CParamsManager::GetInstance().GetImageResourcePath();
		if (EnCityType::enFriend == type)
		{
			m_strImagePath += "Friend.png";
			m_textColor = colFriendText;
		}
		else if (EnCityType::enEnemy == type)
		{
			m_strImagePath += "Enemy.png";
			m_textColor = colEnemyText;
		}
		else if (EnCityType::enNeutral == type)
		{
			m_strImagePath += "Neutrality.png";
			m_textColor = colNeutralText;
		}
		else
		{
			m_strImagePath = L"";
			m_textColor = 0;
		}
		m_image.Load(m_strImagePath);
	}

}

}