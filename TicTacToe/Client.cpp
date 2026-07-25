#include "Client.h"

using namespace TicTacToc;

void Client::init() {
    std::this_thread::sleep_for(std::chrono::milliseconds(10000));
    struct addrinfo* result = NULL, hints;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    int iResult = getaddrinfo("127.0.0.1", Port, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed: %d\n", iResult);
        WSACleanup();
        return;
    }
    _serverSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

    if (_serverSocket == INVALID_SOCKET)
    {
        printf("Error at socket(): %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return;
    }
    iResult = connect(_serverSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        closesocket(_serverSocket);
        _serverSocket = INVALID_SOCKET;
    }
    freeaddrinfo(result);

    if (_serverSocket == INVALID_SOCKET) {
        printf("Unable to connect to server!\n");
        WSACleanup();
        return;
    }
    const char* sendbuf = "this is a test";
    char recvbuf[BufferLength];

    // Send an initial buffer
    iResult = send(_serverSocket, sendbuf, (int)strlen(sendbuf), 0);
    if (iResult == SOCKET_ERROR) {
        printf("send failed: %d\n", WSAGetLastError());
        closesocket(_serverSocket);
        WSACleanup();
        return;
    }

}