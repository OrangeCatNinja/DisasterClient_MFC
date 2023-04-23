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

	bool SendMessage(const SHttpRequestMessage& message) override;
private:
	SOCKET m_scoket;
};

}
