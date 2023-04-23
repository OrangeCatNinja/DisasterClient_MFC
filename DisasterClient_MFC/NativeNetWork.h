#pragma once
#include "NetWorkBase.h"

namespace NetWork
{

class NativeNetWork :
	public NetWorkBase
{
public:
	void InitNetWork() override;

private:
	SOCKET m_scoket;
};

}
