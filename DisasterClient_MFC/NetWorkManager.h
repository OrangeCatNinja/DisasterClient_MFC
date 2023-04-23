#pragma once
#include "NetWorkBase.h"

#define GETNETWORK()	NetWork::NetWorkManager::GetInstance().GetNetWork()

class NetWorkBase;

namespace NetWork
{
	enum NetWorkType
	{
		enNative = 0,//ԭ��ʵ�ֵ�����
		enBoost,//boost��ʵ�ֵ�����
		enLibhv,//Libhv��ʵ�ֵ�����
		enCurl//Curl��ʵ�ֵ�����
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
