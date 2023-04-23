#pragma once

namespace NetWork
{
	using OnResponseHandle = std::function<bool(const std::string&)>;

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
		std::string m_method;
	};

	struct SHttpRequestHead
	{
		std::unordered_map<std::string, std::string> m_headMap;
	};

	struct SHttpRequestBody
	{
		std::string m_strMethod;

	};

	struct SHttpRequestMessage
	{
		SHttpRequestLine m_reqLine;
		SHttpRequestHead m_reqHead;
		SHttpRequestBody m_reqBody;
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
	
	virtual void Disconnect() = 0;

	virtual bool SendToServer(const SHttpRequestMessage& message, OnResponseHandle onHandle) = 0;

public:
	static const std::string m_sServerAddr;
	static const int m_sPort;
};

}
