
#include "../TicTacToe/Client.h"
using namespace TicTacToe;
int main()
{
    Client _client;
    _client.init();
    char* buffer;
    int bufferLen = BufferLength;
    while (true)
    {
        buffer = _client.SendRequest(Requests::CheckWinner, "\0");
        for (int i = 1; i < BufferLength; i++)
        {
            if (buffer[i] == '\0')
            {
                printf("\n");
                break;
            }
            printf("%c", buffer[i]);
        }
        delete[] buffer;
    }
    return 0;
}