#pragma once
#include <iostream>;
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
namespace TicTacToc {
	class Server {
	public:
		void init();
		void Send(char* msg);
	private:
		SOCKET _serverSocket = INVALID_SOCKET;
	};
}