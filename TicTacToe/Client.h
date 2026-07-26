#pragma once
#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include "Models.h"
#include <thread>
#include <chrono>

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

// #pragma comment (lib, "Mswsock.lib")

namespace TicTacToe {
	class __declspec(dllexport) Client {
	public:
		EnumResult init();
		enum EnumResult SendRequest(Requests request, char* data)
		{
			msg _msg = preparemsg(data);
			_msg.str[0] = (char)request;
			send(_serverSocket, _msg.str, _msg.len, 0);
			char buffer[BufferLength];
			recv(_serverSocket, buffer, BufferLength, 0);
			//todo
		}
	private:
		SOCKET _serverSocket = INVALID_SOCKET;
	};
}