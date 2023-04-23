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
}