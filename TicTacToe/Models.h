#pragma once
namespace TicTacToc {
	#define BufferLength 512 //Buffer Size
	#define Port "27015" //Port Number
	#define MaxDataLen 10000

	enum Commands
	{
		Render,
		Test
	};
	enum Player
	{
		player1,
		player2
	};
	enum GameState
	{
		gameInit,
		gameReady,
		GameIsPlaying,
		gameFailed,
		gameFinished
	};

	enum EnumResult
	{
		Failed,
		Succeed,
		Retry
	};

}