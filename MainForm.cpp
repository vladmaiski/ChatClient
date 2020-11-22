﻿//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainForm.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------


__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{

}

DWORD WINAPI clientHandler(LPVOID lpParam)
{
	char *msg;
	char msgLen[5] = {};
	while(true)
	{
		recv(serverSock, msgLen, 4, NULL);
		int length = std::stoi(msgLen);
		msg = (char *) calloc(length + 1, sizeof(char));
		recv(serverSock, msg, length, NULL);
		printMsg(std::string(msg));
		free(msg);
	}
	return 0;
}

std::string getTimeStr()
{
	time_t currentTime;
	struct tm *localTime;

	time( &currentTime );                   // Get the current time
	localTime = localtime( &currentTime );  // Convert the current time to the local time

	int hour   = localTime->tm_hour;
	int min    = localTime->tm_min;
	int sec    = localTime->tm_sec;

	return ("[" + std::to_string(hour) + ":" + std::to_string(min) + ":"
		+ std::to_string(sec) + "]");
}

bool connectToServer(const char *adress)
{
	WSADATA wsaData;
    WORD DLLVersion = MAKEWORD(2, 1);
    if (WSAStartup(DLLVersion, &wsaData) != 0) {
		std::cout << "Error" << std::endl;
		exit(1);
    }

	SOCKADDR_IN servAddr;
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servAddr.sin_port = htons(1111);
    servAddr.sin_family = AF_INET;

	serverSock = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(serverSock, (SOCKADDR*)&servAddr, sizeof(servAddr)) != 0) {
		return false;
	} else {
		DWORD dwThreadId;
		HANDLE hThread = CreateThread(NULL, NULL, clientHandler, NULL, NULL, &dwThreadId);
	}
	return true;
}

std::string sysStrToStd(String str)
{
	std::string stdMsg = "";
	for(int i = 1; i <= str.Length(); i++)
	{
		stdMsg += (char) str[i];
	}
	return(stdMsg);
}

void sendPacket(SOCKET server, std::string packet)
{
	std::string msg = std::to_string(packet.length());
	send(server, msg.c_str(), 4, NULL);
	send(server, packet.c_str(), packet.length(), NULL);
}

std::string makePacket(const char *packetType, std::string msg)
{
	msg = packetType + msg;
	return msg;
}

void sendMsg(const char *packetType, std::string msg)
{
	if(msg.length() > 100)
	{
		//TODO Error
	}else
	{
		std::string packet = makePacket(packetType, msg);
		sendPacket(serverSock, packet);
		Sleep(10);
	}
}

void disconnect()
{
	sendMsg(DISCONNECT_PCKT, std::string(""));
}

void printMsg(std::string msg)
{
	//Form1->ChatBox->Lines->Add();
	Form1->ChatBox->Text += ("\r\n" + getTimeStr() + " " +  msg).c_str();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
	String msg = MsgBox->Text.Trim();
	if(msg != "")
	{
		std::string stdMsg = sysStrToStd(msg);
		sendMsg(MSG_PCKT, stdMsg);
		printMsg(std::string(stdMsg));
		MsgBox->Clear();
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
	Form1->ChatBox->Text = ("");
	Form1->ChatBox->WantReturns = false;
	Form1->ChatBox->WordWrap = false;

}
//---------------------------------------------------------------------------

void greetUser(String name)
{
	Form1->ChatBox->Text = ("Hello " + name).c_str();
}

void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
	disconnect();
}
//---------------------------------------------------------------------------

