#include "pch.h"
#include "ParamsManager.h"

namespace Param
{
	CParamsManager & CParamsManager::GetInstance()
	{
		static CParamsManager paramsManager;
		return paramsManager;
	}

	bool CParamsManager::InitParam()
	{
		m_mapParam = std::unordered_map<WORD, GameLogic::GameMap::SCityInfo>{
			std::pair<WORD, GameLogic::GameMap::SCityInfo>(1,{1,GameLogic::GameMap::EnCityType::enFriend, CPoint(50,50), L"白银港", {2,3}}),
			std::pair<WORD, GameLogic::GameMap::SCityInfo>(2,{2,GameLogic::GameMap::EnCityType::enFriend, CPoint(650, 150), L"北境草原", {1, 3}}),
			std::pair<WORD, GameLogic::GameMap::SCityInfo>(3,{3,GameLogic::GameMap::EnCityType::enEnemy, CPoint(550,700), L"陨星城", {1,4}}),
			std::pair<WORD, GameLogic::GameMap::SCityInfo>(4,{4,GameLogic::GameMap::EnCityType::enNeutral, CPoint(500,500), L"雷鸣城", {3}}),
		};
		return true;
	}

	CString CParamsManager::GetImageResourcePath()
	{
		TCHAR szPath[MAX_PATH];
		GetModuleFileName(NULL, szPath, MAX_PATH);
		CString strPath(szPath);
		int nPos = strPath.ReverseFind('\\');
		if (nPos > 0)
		{
			strPath = strPath.Left(nPos);
		}
		strPath += L"\\Resource\\Picture\\";
		return strPath;
	}

	const MapParam & CParamsManager::GetMapParam()
	{
		return m_mapParam;
	}

	CParamsManager::CParamsManager()
	{

	}
}
