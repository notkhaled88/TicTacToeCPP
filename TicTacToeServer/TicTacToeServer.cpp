#include "../TicTacToe/Server.h"
using namespace TicTacToe;
int main()
{
    Server _server;
    _server.init();
    //main loop of  the server after init game
    while (true)
    {
        _server.ReciveRequest(Player::player1);
    }
    return 0;
}