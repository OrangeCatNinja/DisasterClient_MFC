#pragma once
#include "NetWorkBase.h"

#define GETNETWORK()	NetWork::NetWorkManager::GetInstance().GetNetWork()

class NetWorkBase;

namespace NetWork
{
	enum NetWorkType
	{
		enNative = 0,//原生实现的网络
		enBoost,//boost库实现的网络
		enLibhv,//Libhv库实现的网络
		enCurl//Curl库实现的网络
	};

class NetWorkManager
{
public:
	static NetWorkManager& GetInstance();

	NetWorkBase* CreateNetWork(NetWorkType type);

	NetWorkBase* GetNetWork() { return m_pNetWork; }

	//void SendMessage(const SHttpRequestMessage& messge);

private:
	NetWorkManager();
	~NetWorkManager() = default;

private:
	NetWorkBase* m_pNetWork;
	bool m_bCreate;
};

}
