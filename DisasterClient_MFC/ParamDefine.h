#pragma once

namespace Param
{
	enum class EnGameType
	{
		enServer,//服务器模式
		enSingle//单机模式
	};

	struct GlobalParam
	{
		EnGameType gameType;
	};
}
