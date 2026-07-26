
#include "../TicTacToe/Client.h"
using namespace TicTacToe;

int main()
{
    Client _client;
    _client.init();
    char* buffer;
    int bufferLen = BufferLength;
    //main loop of the client
    while (true)
    {
        buffer = _client.SendRequest(Requests::CheckWinner, "\0");
        if ((EnumResult)buffer[0] == EnumResult::Succeed)
        {
            if ((TicTacToeElem)buffer[1] != TicTacToeElem::None)
            {
                printf("game ended. we have a winner!!\n");
                break;
            }
        }
        else
        {
            printf("request failed!\n");
            break;
        }
        delete[] buffer;


        buffer = _client.SendRequest(Requests::GetGame, "\0");
        if ((EnumResult)buffer[0] == EnumResult::Succeed)
        {
            for (int i = 1; i < BufferLength; i++)
            {
                if (buffer[i] == '\0')
                {
                    printf("\n");
                    break;
                }
                printf("%c", buffer[i]);
            }            
        }
        else
        {
            printf("request failed!\n");
            break;
        }
        delete[] buffer;

        buffer = _client.SendRequest(Requests::IsItMyTurn, "\0");
        if ((EnumResult)buffer[0] == EnumResult::NotAllowed)
        {
            delete[] buffer;
            continue;
        }
        delete[] buffer;
        int x;
        int y; 
        printf("enter your next game? in format >xy");
        scanf("%d%d", &x, &y);
        todo



    }
    delete[] buffer;
    return 0;
}