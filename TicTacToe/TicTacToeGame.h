#pragma once
#include "Models.h"
#include <iostream>
using namespace TicTacToc;
namespace TicTacToe {
#define GameArraySize 3
	class __declspec(dllexport) TicTacToeGame {
	public:
		EnumResult Set(int x, int y, TicTacToeElem value);
		char* Print();
		TicTacToeElem GetWinner();
	private:
		TicTacToeElem _game[GameArraySize][GameArraySize];
		char transform(TicTacToeElem elem);
	};
}