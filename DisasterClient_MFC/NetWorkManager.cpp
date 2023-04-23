#include "pch.h"
#include "NetWorkManager.h"
#include "NativeNetWork.h"

namespace NetWork
{

	NetWorkManager::NetWorkManager()
		: m_pNetWork(NULL)
		, m_bCreate(false)
	{

	}

	NetWorkManager & NetWorkManager::GetInstance()
	{
		static NetWorkManager networkFactory;
		return networkFactory;
	}

	NetWorkBase * NetWorkManager::CreateNetWork(NetWorkType type)
	{
		if (!m_bCreate && m_pNetWork)
		{
			delete m_pNetWork;
			m_pNetWork = NULL;
		}

		switch (type)
		{
		case NetWork::enNative:
			m_pNetWork = new NativeNetWork();
			break;
		case NetWork::enBoost:
			break;
		case NetWork::enLibhv:
			break;
		case NetWork::enCurl:
			break;
		default:
			break;
		}

		m_bCreate = true;

		return nullptr;
	}

}
