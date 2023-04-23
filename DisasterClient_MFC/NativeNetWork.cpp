#include <sstream>

#include "pch.h"
#include "NativeNetWork.h"

namespace NetWork
{
	const std::unordered_set<std::string> setMethod{
		"GET","POST"
	};

	void NativeNetWork::InitNetWork()
	{
		m_scoket = socket(AF_INET, SOCK_STREAM, 0);
		if (m_scoket == -1)
		{
			ERROR("failed to create socket");
		}

		sockaddr_in server_addr;
		std::memset(&server_addr, 0, sizeof(server_addr));
		server_addr.sin_family = AF_INET;
		server_addr.sin_addr.S_un.S_addr = inet_addr(m_sServerAddr.c_str());
		server_addr.sin_port = htons(m_sPort);

		if (connect(m_scoket, reinterpret_cast<sockaddr*>(&server_addr), sizeof(server_addr)))
		{
			ERROR("Failed to connect to server");
		}
	}

	void NativeNetWork::Disconnect()
	{
		closesocket(m_scoket);
	}

	bool NativeNetWork::SendMessage(const SHttpRequestMessage & message)
	{
		std::stringstream ss;

		//请求行
		ss << message.m_reqLine.m_method << " " << m_sServerAddr << " HTTP/1.1\r\n";

		//请求头
		for (const auto& head : message.m_reqHead.m_headMap)
		{
			ss << head.first << ": " << head.second << "\r\n";
		}

		//空白行
		ss << L"\r\n";

		//请求体

		std::string request = ss.str();
		if (send(m_scoket, request.c_str(), request.length(), 0) == -1)
		{
			ERROR("Failed send message");
		}

		const int nBufferSize = 5 * 1024 * 1024;
		char buffer[nBufferSize];
		std::string response;
		int recv_len;

		while ((recv_len = recv(m_scoket, buffer, nBufferSize - 1, 0)) > 0)
		{
			buffer[recv_len] = '\0';
			response += buffer;
		}
		if (recv_len == -1)
		{
			ERROR("Failed recv message");
		}
	}
}