#ifndef Unit2H
#define Unit2H

#pragma package(smart_init)

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <string>
#include <winsock2.h>

class ClientHandler
{
private:
	static void serverListener();
public:
	static SOCKET connection;
	static void createListenerThread();
	static void sendToAllMessage(std::string clientBuffer);
	static bool connect();
};

#endif
