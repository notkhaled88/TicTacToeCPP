#pragma once
#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include "Models.h"
#include "TicTacToeGame.h"
// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

// #pragma comment (lib, "Mswsock.lib")
namespace TicTacToe {

	class __declspec(dllexport) Server {
	public:
		enum EnumResult init();
		enum EnumResult ReciveRequest(enum Player player);
		bool GetThreadState(enum Player player);
	private:
		SOCKET _serverSocket  = INVALID_SOCKET;
		SOCKET _player1Socket = INVALID_SOCKET;
		SOCKET _player2Socket = INVALID_SOCKET;
		TicTacToeGame _game;
		enum GameState _gameState = GameState::gameInit;
		enum EnumResult getPlayers();
		addrinfo* resolveServerAddress();
		int getDataLen(const char* data);
		Player _currentPlayer = Player::player1;
		void startThread(enum Player);
		void endThread(enum Player);
		bool _threadPlayer1Running = false;
		bool _threadPlayer2Running = false;

	};
}