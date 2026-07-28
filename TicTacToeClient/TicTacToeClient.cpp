
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
        system("cls");
        
        //print game
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
        
        // check a winner
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

        //check if it is my turn

        buffer = _client.SendRequest(Requests::IsItMyTurn, "\0");
        if ((EnumResult)buffer[0] == EnumResult::NotAllowed)
        {
            delete[] buffer;
            printf("not yet your turn! please wait for other player\n");
            continue;
        }
        delete[] buffer;
        int x;
        int y; 
        printf("enter your next game? in format >xy\n");
        scanf_s("%d%d", &x, &y);
        char* data = new char[3];
        data[0] = x + 1; //add one to avoid string terminator
        data[1] = y + 1; //add one to avoid string terminator
        data[2] = '\0';
        buffer = _client.SendRequest(Requests::SetValue, data);
        delete[] data;
        if ((EnumResult)buffer[0] == EnumResult::NotAllowed)
        {
            printf("you are not allowed to play this move. please try again!\n");
        }
        delete[] buffer;
    }
    delete[] buffer;
    return 0;
}