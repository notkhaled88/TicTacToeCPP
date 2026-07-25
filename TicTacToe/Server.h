#pragma once
#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include "Models.h"

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

// #pragma comment (lib, "Mswsock.lib")
namespace TicTacToc {

	class Server {
	public:
		enum EnumResult init();
		enum EnumResult SendCommand(enum Player player, enum Commands command, const char* Data);
		enum EnumResult ReciveCommand(enum Player player);
	private:
		SOCKET _serverSocket  = INVALID_SOCKET;
		SOCKET _player1Socket = INVALID_SOCKET;
		SOCKET _player2Socket = INVALID_SOCKET;
		enum GameState _gameState = GameState::gameInit;
		enum EnumResult getPlayers();
		enum EnumResult startGame();
		addrinfo* resolveServerAddress();
		int getDataLen(const char* data);

	};
}