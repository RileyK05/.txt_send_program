#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <string> 
#include <conio.h>
#include <fstream>
#include <algorithm>
#include <math.h>
#include <vector>
#include <chrono>
#include <thread>
#include <compare>
#include <stdio.h>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>


int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize Winsock" << std::endl;
        return -1;
    }

    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Error creating socket: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return -1;
    }

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;


    if (InetPton(AF_INET, L"server ip address"/*Replace whats in quotes with the ip4 address of the server*/, &(serverAddress.sin_addr)) != 1) {
        std::cerr << "Invalid IP address" << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return -1;
    }

    serverAddress.sin_port = htons(8080);

    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
        std::cerr << "Error binding socket: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return -1;
    }


    if (listen(serverSocket, 5) == SOCKET_ERROR) {
        std::cerr << "Error listening for connections: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return -1;
    }

    std::cout << "Server listening on port 8080..." << std::endl;

    sockaddr_in clientAddress;
    int clientAddrSize = sizeof(clientAddress);
    SOCKET clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddrSize);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Error accepting connection: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return -1;
    }

    WCHAR ipString[INET6_ADDRSTRLEN];
    InetNtopW(AF_INET, &clientAddress.sin_addr, ipString, ARRAYSIZE(ipString));
    wprintf(L"Connection accepted from %s\n", ipString);

    // Now you can send and receive data using clientSocket

    int fileSize;
    int receivedSize = recv(clientSocket, reinterpret_cast<char*>(&fileSize), sizeof(fileSize), 0);

    if (receivedSize <= 0) {
        std::cerr << "Error receiving file size. Bytes received: " << receivedSize << " Error: " << WSAGetLastError() << std::endl;
        closesocket(clientSocket);
        closesocket(serverSocket);
        WSACleanup();
        return -1;
    }
    else {
        std::cout << "No data lost in reception.\n";
    }


    fileSize = ntohl(fileSize);

    std::cout << "Received file size: " << fileSize << " bytes, rec size int: " << receivedSize << std::endl;


    if (fileSize <= 0) {
        std::cerr << "Invalid file size" << std::endl;
        closesocket(clientSocket);
        closesocket(serverSocket);
        WSACleanup();
        return -1;
    }

    std::ofstream outputFile("receivedTextfile.txt", std::ios::binary | std::ios::trunc);
    int totalBytesReceived = 0;


    const int maxBufferSize = 4096;
    char buffer[maxBufferSize];

    while (totalBytesReceived < fileSize) {
        int bytesToReceive = std::min(fileSize - totalBytesReceived, maxBufferSize);
        int bytesReceived = recv(clientSocket, buffer, bytesToReceive, 0);

        std::cout << "Current Buffer: " << bytesReceived << std::endl;

        if (bytesReceived <= 0) {
            std::cerr << "Error receiving file. Bytes received: " << totalBytesReceived << " Error: " << WSAGetLastError() << std::endl;
            break;
        }

        outputFile.write(buffer, bytesReceived);
        totalBytesReceived += bytesReceived;
        std::cout << "Bytes received: " << totalBytesReceived << " / " << fileSize << "\r" << std::flush;
    }

    outputFile.close();

    if (totalBytesReceived == fileSize) {
        std::cout << "\nFile received successfully" << std::endl;


        std::ifstream receivedFile("receivedTextfile.txt", std::ios::binary);
        if (receivedFile.is_open()) {
            std::cout << "\nReceived content:\n";
            std::cout << receivedFile.rdbuf() << std::endl;
            receivedFile.close();
        }
        else {
            std::cerr << "Error opening received file" << std::endl;
        }
    }
    else {
        std::cerr << "\nFile reception incomplete, error " << WSAGetLastError() << std::endl;
    }


    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();

    return 0;
}
