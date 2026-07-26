
#include "../TicTacToe/Client.h"
using namespace TicTacToe;
int main()
{
    Client _client;
    _client.init();
    while (true)
    {
        _client.SendRequest(Requests::CheckWinner, "\0");
    }
    return 0;
}