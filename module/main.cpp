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
#include "Class.h"
#include <compare>
#include <stdio.h>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>


int main() {

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "wsaStartup failed" << std::endl;
        exit(1);
    }

    if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
        std::cerr << "version 2.2 unavailable" << std::endl;
        WSACleanup();
        exit(2);
    }

    WSACleanup();

    return 0;
}

