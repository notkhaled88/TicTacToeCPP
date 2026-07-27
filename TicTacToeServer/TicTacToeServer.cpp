#include "../TicTacToe/Server.h"
#include <thread>
#include <chrono>
using namespace TicTacToe;
int main()
{
    Server _server;
    _server.init();
    //main loop of  the server after init game
    while (true)
    {
        _server.ReciveRequest(Player::player1);
        _server.ReciveRequest(Player::player2);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    return 0;
}