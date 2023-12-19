/*



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

    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Error creating socket" << std::endl;
        WSACleanup();
        return -1;
    }

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;

    if (inet_pton(AF_INET, "server ip address" //Replace whats in quotes with the ip4 address of the server//, &(serverAddress.sin_addr)) != 1) {
        std::cerr << "Invalid IP address" << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return -1;
    }

    serverAddress.sin_port = htons(8080);

    if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
        std::cerr << "Error connecting to server" << WSAGetLastError() << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return -1;
    }

    std::cout << "Connected to the server" << std::endl;

    std::ifstream inputFile("sendThis.txt", std::ios::binary); 

    if (!inputFile.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return -1;
    }

    inputFile.seekg(0, std::ios::end);
    int fileSize = static_cast<int>(inputFile.tellg());
    inputFile.seekg(0, std::ios::beg);

    if (fileSize <= 0) {
        std::cerr << "File size is zero or negative" << std::endl;
        inputFile.close();
        closesocket(clientSocket);
        WSACleanup();
        return -1;
    }

    fileSize = htonl(fileSize);

    if (send(clientSocket, reinterpret_cast<char*>(&fileSize), sizeof(fileSize), 0) == SOCKET_ERROR) {
        std::cerr << "Error sending file size" << std::endl;
        inputFile.close();
        closesocket(clientSocket);
        WSACleanup();
        return -1;
    }

    const int maxBufferSize = 4096;
    char buffer[maxBufferSize];

    int bytesRead;
    while ((bytesRead = inputFile.readsome(buffer, maxBufferSize)) > 0) {
        if (send(clientSocket, buffer, bytesRead, 0) == SOCKET_ERROR) {
            std::cerr << "Error sending file content" << std::endl;
            inputFile.close();
            closesocket(clientSocket);
            WSACleanup();
            return -1;
        }
    }

    std::cout << "File sent successfully" << std::endl;

    closesocket(clientSocket);
    WSACleanup();

    return 0;
}



*/