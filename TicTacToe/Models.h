#pragma once
namespace TicTacToc {
	#define BufferLength 512 //Buffer Size
	#define Port "27015" //Port Number
	#define MaxDataLen 10000

	enum __declspec(dllexport) Commands
	{
		Render,
		Test
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
	enum TicTacToeElem
	{
		X,
		O,
		None
	};
}