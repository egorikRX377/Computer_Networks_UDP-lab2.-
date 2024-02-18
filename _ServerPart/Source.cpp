#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <winsock2.h>
#include <Windows.h>
#include <string>
#include <process.h>

using namespace std;


void removeChar(string& str, char charToRemove)
{
    str.erase(remove(str.begin(), str.end(), charToRemove), str.end());
}


int main() 
{

    WORD wVersionRequested;
    WSADATA wsaData;
    int err;

    wVersionRequested = MAKEWORD(2, 2);
    err = WSAStartup(wVersionRequested, &wsaData);


    SOCKET s;
    s = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in ad;

    ad.sin_family = AF_INET;
    ad.sin_port = htons(1024);

    ad.sin_addr.s_addr = 0;

    bind(s, (struct sockaddr*)&ad, sizeof(ad));

    char b[200];
    int l;
    l = sizeof(ad);

    bool serverRunning = true;

    while (serverRunning)
    {
        int rv = recvfrom(s, b, sizeof(b) - 1, 0, (struct sockaddr*)&ad, &l);

        b[rv] = '\0';

        int length = strlen(b);

        if (length % 3 == 0)
        {
            string inputString(b);
            string resultString = inputString;

            for (char c : inputString)
            {
                if (isdigit(c) && ((c - '0') % 3 == 0)) 
                {
                    removeChar(resultString, c);
                }
            }

            strcpy(b, resultString.c_str());
        }

        sendto(s, b, strlen(b) + 1, 0, (struct sockaddr*)&ad, sizeof(ad));

        if (!strcmp(b, "exit")) 
        {
            serverRunning = false;
        }
    }
 
    closesocket(s);

    WSACleanup();

    return 0;
}