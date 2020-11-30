//---------------------------------------------------------------------------

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
		packetHandle(msg);
		free(msg);
	}
	return 0;
}

void packetHandle(char* _msg)
{
	std::string packet(_msg);
	std::string packetType = packet.substr(0, PACKET_TYPE_LENGHT);
	int msgLen = packet.length() - PACKET_TYPE_LENGHT;
	std::string msg = packet.substr(PACKET_TYPE_LENGHT, msgLen);

	if (!packetType.compare(MSG_PCKT))
		printMsg(std::string(msg), true);
	if(!packetType.compare(USER_INFO_PCKT))
	{
		std::vector<std::string> users;
		std::string currentUserName;
		for(int i = 0; i < msg.size(); i++)
		{
			if(msg[i] == ':')
			{
				users.push_back(currentUserName);
				Form1->ListBox1->Items->Add(currentUserName.c_str());
				currentUserName = "";
			}
			currentUserName += msg[i];
		}

	}
}

void createHandlerThreat()
{
	DWORD dwThreadId;
	HANDLE hThread = CreateThread(NULL, NULL, clientHandler, NULL, NULL, &dwThreadId);
}

std::string getTimeStr()
{
	time_t currentTime;
	struct tm *localTime;

	time( &currentTime );
	localTime = localtime( &currentTime );

	std::string hour   = std::to_string(localTime->tm_hour);
	std::string min    = std::to_string(localTime->tm_min);
	std::string sec    = std::to_string(localTime->tm_sec);

	if(sec.size() == 1)
	{
		sec = "0" + sec;
	}


	return ("[" + hour + ":" + min + ":"
		+ sec + "]");
}

bool connectToServer()
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

bool checkInputSize(std::string input, int size)
{
	if(input == "" || input.length() > size)
		return false;
	return true;
}

bool checkUserInput(std::string input, int size)
{
	if(!checkInputSize(input, size))
		return false;

	for (const char c : input) {
		if (!isalpha(c) && !isdigit(c))
			return false;
	}

	return true;
}

std::string makePacket(const char *packetType, std::string msg)
{
	msg = packetType + msg;
	return msg;
}

void sendMsg(const char *packetType, std::string msg)
{
		std::string packet = makePacket(packetType, msg);
		sendPacket(serverSock, packet);
}

void disconnect()
{
	sendMsg(DISCONNECT_PCKT, std::string(""));
}

void printMsg(std::string msg, bool flag)
{
	std::string user = "(you)";
	if (flag) {
		user = "";
	}
	Form1->ChatBox->Text += ("\r\n" + getTimeStr() + user + " " +  msg).c_str();
}

bool checkMsg(std::string msg, int size)
{
	if(msg == "" || msg.length() > size)
		return false;
	return true;
}

void __fastcall TForm1::Button1Click(TObject *Sender)
{
	String msg = MsgBox->Text.Trim();
	std::string stdMsg = sysStrToStd(msg);
	const int MAX_SIZE = 1000;
	if(checkMsg(stdMsg, MAX_SIZE))
	{
		sendMsg(MSG_PCKT, stdMsg);
		printMsg(std::string(stdMsg), false);
		MsgBox->Clear();
	} else
	{
		ShowMessage("Your message is too long(no more than " + AnsiString(MAX_SIZE) + " characters)");
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
	if(serverSock != NULL)
		disconnect();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MsgBoxKeyPress(TObject *Sender, System::WideChar &Key)
{
	if(Key == VK_RETURN)
	{
		Key = 0;
		Form1->Button1Click(Sender);
	}
}
//---------------------------------------------------------------------------



void __fastcall TForm1::MsgBoxChange(TObject *Sender)
{
	std::string msg = sysStrToStd(MsgBox->Text);

	if(msg.size() > MAX_USER_INPUT_SIZE)
	{
		MsgBox->Text = msg.substr(0, MAX_USER_INPUT_SIZE).c_str();
		MsgBox->SelStart = MsgBox->Text.Length();
		MsgBox->Perform(EM_SCROLLCARET, 0, 0);
	}

	if(msg.size() > MAX_MESSAGE_SIZE)
		Label1->Font->Color = clRed;
	else
		Label1->Font->Color = clWhite;

	Label1->Caption = AnsiString(msg.size()) + "/" +  AnsiString(MAX_MESSAGE_SIZE);
}
//---------------------------------------------------------------------------

