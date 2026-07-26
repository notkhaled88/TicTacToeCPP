#pragma once
namespace TicTacToe {
	#define BufferLength 512 //Buffer Size
	#define Port "27015" //Port Number
	#define MaxDataLen 10000

	enum __declspec(dllexport) Requests
	{
		GetGame,
		SetValue,
		CheckWinner
	};
	enum __declspec(dllexport) Player
	{
		player1,
		player2
	};
	enum __declspec(dllexport) GameState
	{
		gameInit,
		gameReady,
		GameIsPlaying,
		gameFailed,
		gameFinished
	};

	enum __declspec(dllexport) EnumResult
	{
		Failed,
		Succeed,
		Retry
	};
	enum __declspec(dllexport) TicTacToeElem
	{
		X,
		O,
		None
	};
	struct __declspec(dllexport) msg
	{
		char* str;
		int len;
	};
	msg preparemsg(const char* rawmsg)
	{
		int len = 0;
		msg _msg;
		while (rawmsg[len] != '\0')
		{
			len++;
		}
		_msg.len = len + 2; 
		_msg.str = new char[_msg.len];
		for (int i = 1; i < _msg.len; i++)
		{
			_msg.str[i] = rawmsg[i - 1];
		}
		return _msg;
	}
}