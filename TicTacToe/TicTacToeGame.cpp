#include "TicTacToeGame.h";
using namespace TicTacToc;
EnumResult TicTacToe::TicTacToeGame::Set(int x, int y, TicTacToeElem value)
{
	if (x > GameArraySize - 1 || y > GameArraySize - 1)
	{
		printf("the indexs (%d , %d) is out of limit\n", x, y);
		return EnumResult::Retry;
	}
	if (_game[x][y] == TicTacToeElem::X || _game[x][y] == TicTacToeElem::O)
	{
		printf("this is not allowed this element (%d , %d) is already played with %c\n",x, y, TicTacToeGame::transform(_game[x][y]));
		return EnumResult::Retry;
	}
	_game[x][y] = value;
	printf("setting value to the array (%d , %d) to the value %c\n", x, y, TicTacToeGame::transform(value));
	return EnumResult::Succeed;
}

char* TicTacToe::TicTacToeGame::Print()
{
	char str[256];

	snprintf(str, sizeof(str),
		" |0|1|2|\n"
		"--------\n"
		"0|%c|%c|%c|\n"
		"--------\n"
		"1|%c|%c|%c|\n"
		"--------\n"
		"2|%c|%c|%c|\n"
		"--------\n",
		TicTacToeGame::transform(_game[0][0]), TicTacToeGame::transform(_game[0][1]), TicTacToeGame::transform(_game[0][2]),
		TicTacToeGame::transform(_game[1][0]), TicTacToeGame::transform(_game[1][1]), TicTacToeGame::transform(_game[1][2]),
		TicTacToeGame::transform(_game[2][0]), TicTacToeGame::transform(_game[2][1]), TicTacToeGame::transform(_game[2][2])
	);

	printf("%s", str);
	return str;
}

TicTacToeElem TicTacToe::TicTacToeGame::GetWinner()
{
	for (int i = 0; i < GameArraySize; i++)
	{
		//check horizontal
		if (TicTacToeGame::transform(_game[i][0]) != ' ')
		{
			if (_game[i][0] == _game[i][1] && _game[i][0] == _game[i][2])
			{
				return _game[i][0];
			}
		}
		//check vertical
		if (TicTacToeGame::transform(_game[0][i]) != ' ')
		{
			if (_game[0][i] == _game[1][i] && _game[0][i] == _game[2][i])
			{
				return _game[0][i];
			}
		}
	}
	//check diagonal
	if (TicTacToeGame::transform(_game[1][1]) != ' ')
	{
		if ((_game[1][1] == _game[0][0] && _game[1][1] == _game[2][2]) || (_game[1][1] == _game[0][2] && _game[1][1] == _game[2][0]))
		{
			return _game[1][1];
		}
	}
	return TicTacToeElem::None;

}

char TicTacToe::TicTacToeGame::transform(TicTacToeElem elem) {
	switch (elem) {
	case TicTacToeElem::X:
		return 'X';
	case TicTacToeElem::O:
		return 'O';
	default:
		return ' ';
	}
}