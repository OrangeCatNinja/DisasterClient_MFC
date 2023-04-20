#pragma once
#include <afxwin.h>
#include "pch.h"

namespace GameLogic
{

namespace GameMap
{
	enum class EnCityType
	{
		enFriend,
		enEnemy,
		enNeutral
	};

	struct SCityInfo
	{
		WORD m_id;
		EnCityType m_cityType;
		CPoint m_position;
		CString m_strCityName;
		std::vector<WORD> m_pAdjoinCity;
	};

	class GameMapCity :
		public CWnd
	{
	public:
		//GameMapCity();
		GameMapCity(const SCityInfo& info);
		//GameMapCity(const GameMapCity& mapCity);
		virtual ~GameMapCity();

		static int nCityImageWidth;
		static int nCityImageHight;
		static int nCityNameHight;
		static CSize szDefault;
		static COLORREF colFriendText;
		static COLORREF colEnemyText;
		static COLORREF colNeutralText;

		const CPoint GetCenterPos() const;
		const std::vector<WORD>& GetAdjoinCity() const;

		afx_msg void OnRButtonDown(UINT, CPoint);

	protected:
		afx_msg void OnPaint();

		DECLARE_MESSAGE_MAP();

	private:
		void SetImage(EnCityType type);

	private:
		SCityInfo m_cityInfo;
		CImage m_image;
		COLORREF m_textColor;
		CString m_strImagePath;
	};
}
}

