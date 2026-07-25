#include "../TicTacToe/Server.h"
#include "../TicTacToe/Client.h"
#include <thread>
using namespace TicTacToc;
int main()
{
    /*
    Server _server;
    Client _player1;
    Client _player2;

    std::thread serverThread(&Server::init, &_server);
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    std::thread player1Thread(&Client::init, &_player1);
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    std::thread player2Thread(&Client::init, &_player2);
    std::this_thread::sleep_for(std::chrono::milliseconds(10000));
    return 0;
    */

    Server _server;
    _server.init();
}