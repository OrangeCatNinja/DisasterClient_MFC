#pragma once
#include "NetWorkBase.h"

namespace NetWork
{

class NativeNetWork :
	public NetWorkBase
{
public:
	void InitNetWork() override;

	void Disconnect() override;

	bool SendToServer(const SHttpRequestMessage& message, OnResponseHandle onHandle) override;
private:
	SOCKET m_scoket;
};

}
