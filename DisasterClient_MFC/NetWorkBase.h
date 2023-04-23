#pragma once

namespace NetWork
{
	extern const std::stringstream strRequestLine;

	extern const std::stringstream strResponseLine;

	extern const std::unordered_set<std::string> setMethod;

	enum RequestBodyType
	{
		enJson = 0,
		enImage = 1
	};

	struct SHttpRequestLine
	{

	};

	struct SHttpRequestHead
	{

	};

	struct SHttpRequestBody
	{
		std::string m_strMethod;

	};

	struct SHttpRequestMessage
	{
		SHttpRequestBody m_bodyData;
	};

	struct SHttpResponseMessage
	{

	};

class NetWorkBase
{
public:
	NetWorkBase() = default;
	virtual ~NetWorkBase() = default;

	virtual void InitNetWork() = 0;
	bool SendMessage(const SHttpRequestMessage& message);

public:
	static const std::string m_sServerAddr;
	static const int m_sPort;
};

}
