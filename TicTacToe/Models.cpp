#include "Models.h"
using namespace TicTacToe;
namespace TicTacToe {
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