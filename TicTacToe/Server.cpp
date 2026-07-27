#include "Server.h"

using namespace TicTacToe;


#pragma region Private


enum EnumResult Server::getPlayers()
{
    if (Server::_player1Socket != INVALID_SOCKET && Server::_player2Socket != INVALID_SOCKET)
    {
        return EnumResult::Succeed;
    }
    if (listen(_serverSocket, SOMAXCONN) == SOCKET_ERROR)
    {
        return EnumResult::Failed;
    }
    SOCKET tempSocket = accept(_serverSocket, NULL, NULL);
    if (tempSocket == INVALID_SOCKET)
    {
        return EnumResult::Failed;
    }
    else if (_player1Socket == INVALID_SOCKET)
    {
        _player1Socket = tempSocket;
        return EnumResult::Retry;
    }
    else
    {
        _player2Socket = tempSocket;
        return EnumResult::Succeed;
    }

}


addrinfo* Server::resolveServerAddress()
{
    WSADATA wsaData;
    int iResult;
    struct addrinfo* result = NULL;
    struct addrinfo hints;


    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData); //The WSAStartup function is called to initiate use of WS2_32.dll.

    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return nullptr;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET; //IPv4
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the server address and port
    iResult = getaddrinfo(NULL, Port, &hints, &result); //this method return fill result which return the first available socket matched the address family, socket type, and protocol specified in the hints parameter. 
    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return nullptr;
    }
    return result;
}

int Server::getDataLen(const char* data) {
    int i = 0;
    while (i < MaxDataLen)
    {
        if (*(data + i) == 0)
        {
            i++;
            return i;
        }
        i++;
    }
    throw "getDataLen: Invalid data size";
}
#pragma endregion

#pragma region Public

enum EnumResult Server::init() {
    printf("init started \n");
    addrinfo* serverAdressInfo = resolveServerAddress();
    if (serverAdressInfo == nullptr)
    {
        return EnumResult::Failed;
    }
    _serverSocket = socket(serverAdressInfo->ai_family, serverAdressInfo->ai_socktype, serverAdressInfo->ai_protocol);
    if (_serverSocket == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(serverAdressInfo);
        WSACleanup();
        return EnumResult::Failed;
    }

    if (bind(_serverSocket, serverAdressInfo->ai_addr, (int)serverAdressInfo->ai_addrlen) == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(serverAdressInfo);
        closesocket(_serverSocket);
        WSACleanup();
        return EnumResult::Failed;
    }

    freeaddrinfo(serverAdressInfo);

    printf("waiting for 2 player!\n");

    enum EnumResult tempRes;
    while (_player1Socket == INVALID_SOCKET || _player2Socket == INVALID_SOCKET)
    {
        tempRes = getPlayers();
        if (tempRes == EnumResult::Failed)
        {
            printf("listen failed with error: %d\n", WSAGetLastError());
            closesocket(_serverSocket); //todo need to check and clean client socket too
            WSACleanup();
            return EnumResult::Failed;
        }

    }

    closesocket(_serverSocket);

    printf("Connection successful!\n");
    _gameState = GameState::gameReady;
    
    return EnumResult::Succeed;

}

enum EnumResult Server::ReciveRequest(enum Player player)
{
    SOCKET tempSocket;
    tempSocket = player == player1 ? _player1Socket : _player2Socket;
    int playerNumber = player == player1 ? 1 : 2;
    char* buffer = new char[BufferLength];
    int res = recv(tempSocket, buffer, BufferLength, 0);
    msg _msg;
    if (res <= 0)
    {
        printf("ReciveRequest Error Error number %d\n", res);
        delete[] buffer;
        _msg = preparemsg("\0");
        _msg.str[0] = (char)EnumResult::Failed;
        send(tempSocket, _msg.str, _msg.len, 0);
        return EnumResult::Failed;
    }
    switch ((Requests)buffer[0])
    {

    case Requests::GetGame: {
        printf("ReciveRequest-GetGame player %d\n", playerNumber);
            _msg = preparemsg(_game.Print());
            _msg.str[0] = EnumResult::Succeed;
            break;
        }
    case Requests::CheckWinner: {
            printf("ReciveRequest-CheckWinner player %d\n", playerNumber);
            TicTacToeElem winner = _game.GetWinner();
            char charWinner[2] = { (char)winner, '\0'};
            _msg = preparemsg(("", charWinner));
            _msg.str[0] = EnumResult::Succeed;
            break;
        }
    case Requests::SetValue: {
        printf("ReciveRequest-SetValue player %d\n", playerNumber);
        if (player != _currentPlayer)
        {
            _msg = preparemsg("\0");
            _msg.str[0] = NotAllowed;
            break;
        }
        else
        {
            TicTacToeElem elem = player == player1 ? TicTacToeElem::X : TicTacToeElem::O;
            int x = (int)buffer[1];
            int y = (int)buffer[2];
            EnumResult res = _game.Set(x-1, y-1, elem); //return to original value because the client add 1 before sending to the server
            _msg = preparemsg("\0");
            _msg.str[0] = res;
            if (res == EnumResult::Succeed)
            {
                _currentPlayer = _currentPlayer == player1 ? player2 : player1;
            }
            break;
        }
        }
    case Requests::IsItMyTurn: {
        printf("ReciveRequest-IsItMyTurn player %d\n", playerNumber);
        _msg = preparemsg("\0");
        _msg.str[0] = player == _currentPlayer ? EnumResult::Allowed : EnumResult::NotAllowed;
        break;
    }
    default: {

        printf("ReciveRequest-default player %d\n", playerNumber);
            _msg = preparemsg("\0");
            _msg.str[0] = (char)EnumResult::Failed;
            return EnumResult::Failed;
        }
    }
    send(tempSocket, _msg.str, _msg.len, 0);
    delete[] _msg.str;
    delete[] buffer;
    return EnumResult::Succeed;

}

#pragma endregion