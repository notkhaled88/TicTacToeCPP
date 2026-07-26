#include "Client.h"

using namespace TicTacToe;

EnumResult Client::init() {
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData); //The WSAStartup function is called to initiate use of WS2_32.dll.

    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return EnumResult::Failed;
    }

    struct addrinfo* result = NULL, hints;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    iResult = getaddrinfo("127.0.0.1", Port, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed: %d\n", iResult);
        WSACleanup();
        return EnumResult::Failed;
    }
    _serverSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

    if (_serverSocket == INVALID_SOCKET)
    {
        printf("Error at socket(): %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return EnumResult::Failed;
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
        return EnumResult::Failed;
    }
    return EnumResult::Succeed;

    /*
    // Send an initial buffer
    const char* sendbuf = "this is a test";
    char recvbuf[BufferLength];
    
    iResult = send(_serverSocket, sendbuf, (int)strlen(sendbuf), 0);
    if (iResult == SOCKET_ERROR) {
        printf("send failed: %d\n", WSAGetLastError());
        closesocket(_serverSocket);
        WSACleanup();
        return;
    }
    */

}

enum EnumResult Client::SendRequest(Requests request, const char* data){
    msg _msg = preparemsg(data);
    _msg.str[0] = (char)request;
    send(_serverSocket, _msg.str, _msg.len, 0);
    char buffer[BufferLength];
    recv(_serverSocket, buffer, BufferLength, 0);
    for (int i = 1; i < BufferLength; i++)
    {
        if (buffer[i] == '\0')
        {
            printf("\n");
            break;
        }
        printf("%c", buffer[i]);
    }
    return (EnumResult)buffer[0];
}