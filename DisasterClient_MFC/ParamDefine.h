#pragma once

namespace Param
{
	enum class EnGameType
	{
		enServer,//������ģʽ
		enSingle//����ģʽ
	};

	struct GlobalParam
	{
		EnGameType gameType;
	};
}
