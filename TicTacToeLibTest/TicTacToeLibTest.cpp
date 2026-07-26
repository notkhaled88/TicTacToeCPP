// TicTacToeLibTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include "../TicTacToe/Server.h"
#include "../TicTacToe/Client.h"
using namespace TicTacToe;

void testGameClass()
{
    TicTacToeGame game;
    game.Set(10, 10, TicTacToeElem::X);
    game.Set(1, 1, TicTacToeElem::X);
    game.Set(1, 1, TicTacToeElem::X);
    game.Set(1, 0, TicTacToeElem::O);
    if (game.GetWinner() == TicTacToeElem::None)
    {
        printf("no winner!\n");
    }
    game.Print();
    game.Set(0, 0, TicTacToeElem::X);
    game.Set(2, 2, TicTacToeElem::X);
    game.Print();
    if (game.GetWinner() != TicTacToeElem::None)
    {
        printf("we have a winner!!!\n");
    }

    game.Print();
}
void testServerClientCommunication() {
    
    Server _server;
    Client _player1;
    Client _player2;

    std::thread serverThread(&Server::init, &_server);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::thread player1Thread(&Client::init, &_player1);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::thread player2Thread(&Client::init, &_player2);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    serverThread.join(); //wait until init finshed
    while (true)
    {
        std::thread threadRecieveRequest(&Server::ReciveRequest, &_server, Player::player1);
        _player1.SendRequest(Requests::GetGame, "\0");

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        threadRecieveRequest.join();

    }
    
}

int main()
{
    testServerClientCommunication();
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
