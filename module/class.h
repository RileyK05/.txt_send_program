#pragma once
#define WIN32_LEAN_AND_MEAN
#include <string>
#include <iostream>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <winsock2.h>
#include <ws2tcpip.h>


typedef u_short sa_family_t;

class SockAddr {
public:
    unsigned short saFamily; // address family, AF_xxx
    char saData[14];         // 14 bytes of protocol address
};

class AddrInfo {
public:
    int aiFlags;        // AI_PASSIVE, AI_CANONNAME, etc.
    int aiFamily;       // AF_INET, AF_INET6, AF_UNSPEC
    int aiSockType;     // SOCK_STREAM, SOCK_DGRAM
    int aiProtocol;     // use 0 for "any"
    size_t aiAddrlen;   // size of aiAddr in bytes
    SockAddr* aiAddr;   // struct sockaddr_in or _in6
    char* aiCanonName;  // full canonical hostname
    AddrInfo* aiNext;   // linked list, next node
};

class InAddr {
public:
    uint32_t sAddr;     // Internet address (IPv4 address), a 32-bit integer (4 bytes)
};

class SockAddrIn {
public:
    int sinFamily;  // Address family, AF_INET
    int sinPort;    // Port number
    InAddr sinAddr;    // Internet address
    unsigned char sinZero[8];   // Same size as struct sockaddr
};

class In6Addr {
public:
    unsigned char s6Addr[16];   // IPv6 address
};

class SockAddrIn6 {
public:
    uint16_t sin6Family;    //address family, AF_INET6
    uint16_t sin6Port;   //port number, Network Byte Order
    uint32_t sin6FlowInfo;  //IPv6 flow information

    In6Addr sin6Addr; // IPv6 address
    uint32_t sin6CopeId; // Scope ID
};


class SockAddrStorage {
public:
    sa_family_t ssFamily; // address family
    char __ss_pad1[4];    // padding
    int64_t __ss_align;   // alignment
    char __ss_pad2[4];    // more padding
};
