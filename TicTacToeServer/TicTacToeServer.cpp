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
        if (!_server.GetThreadState(Player::player1))
        {
            //_server.ReciveRequest(Player::player1);
            std::thread(&Server::ReciveRequest, &_server, Player::player1).detach();
        }
        if (!_server.GetThreadState(Player::player2))
        {
            //_server.ReciveRequest(Player::player2);
            std::thread(&Server::ReciveRequest, &_server, Player::player2).detach();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(RenderTimeInMs));
    }
    return 0;
}