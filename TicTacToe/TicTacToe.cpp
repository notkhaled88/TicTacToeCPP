// TicTacToe.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<thread>
#include "Server.h"
#include "Client.h"3


using namespace TicTacToc;
int main()
{
    Server _server;
    Client _player1;
    Client _player2;
    
    std::thread serverThread(&Server::init, &_server);
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    std::thread player1Thread(&Client::Connect, &_player1);
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    std::thread player2Thread(&Client::Connect, &_player2);
    std::this_thread::sleep_for(std::chrono::milliseconds(10000));
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
