#include "Server.h"; 
using namespace TicTacToc;


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

enum EnumResult Server::startGame()
{
    if (_gameState == GameState::gameReady || _gameState == GameState::GameIsPlaying)
    {
        _gameState = GameState::GameIsPlaying;
        SendCommand(Player::player1, Commands::Test, "Hello World!");
        ReciveCommand(Player::player1);
    }
    return Succeed;
}

addrinfo* Server::resolveServerAddress()
{
    WSADATA wsaData;
    int iResult;
    struct addrinfo* result = NULL;
    struct addrinfo hints;

    int iSendResult;
    char recvbuf[BufferLength];
    int recvbuflen = BufferLength;

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

    printf("Connection successful!");
    _gameState = GameState::gameReady;
    
    startGame();
    return EnumResult::Succeed;

}

enum EnumResult Server::SendCommand(enum Player player, enum Commands command, const char* data)
{

    SOCKET tempSocket;
    tempSocket = player == player1 ? _player1Socket : _player2Socket;
    int len = getDataLen(data);
    char* msg = new char[len + 1];
    *(msg) = command;
    for (int i = 0; i < len; i++)
    {
        *(msg + i + 1) = *(data + i);
    }

    send(tempSocket, msg, len + 1, 0);

    delete[] msg;

    return EnumResult::Succeed;
}
enum EnumResult Server::ReciveCommand(enum Player player)
{
    SOCKET tempSocket;
    tempSocket = player == player1 ? _player1Socket : _player2Socket;
    char* buffer = new char[BufferLength];
    recv(tempSocket, buffer, BufferLength, 0);
    printf(buffer);
    delete[] buffer;
    return EnumResult::Succeed;

}

#pragma endregion
