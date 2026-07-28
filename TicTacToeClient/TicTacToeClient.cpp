
#include "../TicTacToe/Client.h"
using namespace TicTacToe;

bool printGame(Client &_client)
{
    system("cls");
    char* buffer;
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
        return false;
    }
    delete[] buffer;
    return true;
}

void waitTillIsItMyTurn(Client& _client)
{
    char* buffer = nullptr;
    bool isWarnningPrinted = false;
    EnumResult state = EnumResult::NotAllowed;
    while (state == EnumResult::NotAllowed)
    {
        buffer = _client.SendRequest(Requests::IsItMyTurn, "\0");
        state = (EnumResult)buffer[0];
        if (!isWarnningPrinted)
        {
            printf("not yet your turn! please wait for other player\n");
            isWarnningPrinted = true;
        }
        delete[] buffer;
        std::this_thread::sleep_for(std::chrono::milliseconds(RenderTimeInMs));
    }

}

int main()
{
    Client _client;
    _client.init();
    char* buffer = nullptr;
    //main loop of the client
    while (true)
    {        
        //print game
        if (!printGame(_client))
        {
            break;
        }
        
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
        waitTillIsItMyTurn(_client);
        
        int x;
        int y; 
        //print the actual state of the game before waiting for input!
        if (!printGame(_client))
        {
            break;
        }
        printf("enter your next game? with space between number for example:x y\n");
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