#pragma once
namespace TicTacToc {
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