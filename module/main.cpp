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

    SockAddrIn sa;
    SockAddrIn6 sa6;

    inet_pton(AF_INET, "10.12.110.57", &(sa.sinAddr.sAddr));
    inet_pton(AF_INET6, "2001:db8:63b3:1::3490", &(sa6.sin6Addr.s6Addr));

    char ip4[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(sa.sinAddr), ip4, INET_ADDRSTRLEN);

    char ip6[INET6_ADDRSTRLEN]; // space to hold the IPv6 string
    inet_ntop(AF_INET6, &(sa6.sin6Addr), ip6, INET6_ADDRSTRLEN);

    std::cout << "The IPv4 address is: " << ip4 << std::endl;
    std::cout << "The IPv6 address is: " << ip6 << std::endl;


    return 0;
}

