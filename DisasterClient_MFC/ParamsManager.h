#pragma once
#include "pch.h"
#include "GameMapCity.h"

namespace Param
{

using MapParam = std::unordered_map<WORD, GameLogic::GameMap::SCityInfo>;

class CParamsManager
{
public:
	static CParamsManager& GetInstance();

	bool InitParam();

	CString GetImageResourcePath();

	const MapParam& GetMapParam();

private:
	CParamsManager();
	~CParamsManager() = default;

private:
	MapParam m_mapParam;
	//MapParamManager m_mapParamManager;
};
}


