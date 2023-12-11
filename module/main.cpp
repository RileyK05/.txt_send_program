
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
    // Initialize Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize Winsock" << std::endl;
        return -1;
    }

    // Create a socket
    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Error creating socket" << std::endl;
        WSACleanup();
        return -1;
    }

    // Set up the server address and port
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;

    // Use inet_pton to convert the IP address to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &(serverAddress.sin_addr)) != 1) {
        std::cerr << "Invalid IP address" << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return -1;
    }

    serverAddress.sin_port = htons(8080);  // Use the same port as the server

    // Connect to the server
    if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
        std::cerr << "Error connecting to server" << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return -1;
    }

    std::cout << "Connected to the server" << std::endl;

    // Now you can send and receive data using clientSocket

    // Close the socket
    closesocket(clientSocket);
    WSACleanup();

    return 0;
}
