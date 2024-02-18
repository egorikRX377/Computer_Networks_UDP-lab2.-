#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <winsock2.h>
#include <Windows.h>
#include <conio.h>
#include <string>


using namespace std;


int main()
{
	char buf[100], b[100];

	WORD wVersionRequested;
	WSADATA wsaData;
	wVersionRequested = MAKEWORD(2, 2);
	int err;
	err = WSAStartup(wVersionRequested, &wsaData);

	if (err)
	{
		return 0;
	}

	SOCKET s;
	s = socket(AF_INET, SOCK_DGRAM, 0);

	struct sockaddr_in add;
	add.sin_family = AF_INET;
	add.sin_port = htons(1024);

	add.sin_addr.s_addr = inet_addr("127.0.0.1");

	int t;
	t = sizeof(add);

	cout << "Enter the string please: ";
	cin >> buf;

	sendto(s, buf, strlen(buf) + 1, 0, (struct sockaddr*)&add, t);

	int rv = recvfrom(s, b, sizeof(b), 0, (struct sockaddr*)&add, &t);

	cout << b << endl;

	closesocket(s);

	WSACleanup();

	return 0;
}
