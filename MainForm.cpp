//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainForm.h"
#include "LogInForm.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------

const int PACKET_TYPE_LENGHT = 5;
const int MAX_MESSAGE_SIZE = 1000;
const int MAX_USER_INPUT_SIZE = 3000;
const char *SERVER_IP  = "127.0.0.1";
const int SERVER_PORT  = 1111;
const int MAX_LINE_LEN = 55;

const char *MSG_PCKT = "/000/";
const char *LOG_PCKT = "/111/";
const char *DISCONNECT_PCKT = "/222/";
const char *REG_PCKT = "/333/";
const char* USER_REGISTRED_PCKT = "/444/";
const char* USER_NOT_REGISTRED_PCKT = "/555/";
const char* NOT_LOGGED_PCKT = "/666/";
const char* LOGGED_PCKT = "/777/";
const char* USER_INFO_PCKT = "/888/";
const char* PRIVATE_MSG = "/999/";

SOCKET serverSock;

std::string userName;

std::vector<std::string> usersOnline;

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

void showUserList()
{
	Form1->ListBox1->Items->Clear();
	Form1->ListBox1->Items->Add("Users Online:");
	for(std::string userName: usersOnline)
	{
		Form1->ListBox1->Items->Add(userName.c_str());
	}
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
		usersOnline.clear();

		std::string currentUserName;
		for(int i = 0; i < msg.size(); i++)
		{
			if(msg[i] == ':')
			{
				usersOnline.push_back(currentUserName);
				currentUserName = "";
				continue;
			}
			currentUserName += msg[i];
		}
		showUserList();
	}

	if(!packetType.compare(PRIVATE_MSG))
	{
		printPrivateMsg(std::string(msg), true, "");
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
		sec = "0" + sec;

	if(min.size() == 1)
		min = "0" + min;

	if(hour.size() == 1)
		hour = "0" + hour;

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
	servAddr.sin_addr.s_addr = inet_addr(SERVER_IP);//TODO
	servAddr.sin_port = htons(SERVER_PORT);
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

void printMsg(std::string msg, bool isClientMessage)
{
	std::string debug(msg);
	std::string user = "(you)";
	if (isClientMessage) {
		user = "";
	}
	msg = getTimeStr() + user + " " + msg;
	std::vector<std::string> words = divByWords(msg, MAX_LINE_LEN);
	for(int i = 0; i < words.size(); i++)
	{
	   Form1->ChatBox->Lines->Add(words[i].c_str());
	}

}

void printPrivateMsg(std::string msg, bool isClientMessage, std::string recieverName)
{
	Form1->ChatBox->Text += ("\r\n-------PRIVATE-------");
	if(!isClientMessage)
			Form1->ChatBox->Text += ("\r\nCHAT WITH: " + recieverName).c_str();
	printMsg(msg, isClientMessage);
	Form1->ChatBox->Text += ("\r\n-------------------------");
}

bool checkMsg(std::string msg, int size)
{
	if(msg == "" || msg.length() > size)
		return false;
	return true;
}

void __fastcall TForm1::SendButtonClick(TObject *Sender)
{
	String msg = MsgBox->Text.Trim();
	std::string stdMsg = sysStrToStd(msg);
	const int MAX_SIZE = 1000;
	if(checkMsg(stdMsg, MAX_SIZE))
	{

		std::string currentUser(userName);

		std::string selectedUserName;


		if(ListBox1->ItemIndex > 0
		&& (selectedUserName =
		sysStrToStd(ListBox1->Items->Strings[ListBox1->ItemIndex])).compare(currentUser))
		{
			printPrivateMsg(std::string(stdMsg), false, selectedUserName);
			stdMsg = selectedUserName + ":" + stdMsg;
			sendMsg(PRIVATE_MSG, stdMsg);
		} else
		{
			sendMsg(MSG_PCKT, stdMsg);
			printMsg(std::string(stdMsg), false);
		}

		SendMessage(ChatBox->Handle, WM_VSCROLL, SB_BOTTOM, 0);

		MsgBox->Clear();
	} else
	{
		ShowMessage("Your message is too long(no more than " + AnsiString(MAX_SIZE) + " characters)");
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
	if(!connectToServer())
	{
		Application->MessageBox(_T("Server unavailable"), _T("Application error"));
		exit(0);
	}

	Form1->ChatBox->Text = ("");
	Form1->ChatBox->WantReturns = false;
	Form1->ChatBox->WordWrap = false;

}
//---------------------------------------------------------------------------

void greetUser(std::string name)
{
	Form1->ChatBox->Text += ("Hello " + name).c_str();
}

void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
	if(serverSock != NULL)
		disconnect();
}
//---------------------------------------------------------------------------

std::vector<std::string>divByWords(std::string msg, const int MAX_LINE_LEN)
{
	int i = 0;
	std::vector<std::string>msgToLines;

	int offset = 0;
	while (offset < msg.length()) {
		int currLength = 0;
		int lastSpace = 0;
		while (currLength < MAX_LINE_LEN && i < msg.length()) {
            if (msg[i] == ' ' || msg[i] == ',' || msg[i] == '.'
                || msg[i] == ':' || msg[i] == ';' || msg[i] == '!'
                || msg[i] == '?') {
				lastSpace = i;
			}
			currLength++;
			i++;
        }
		if (lastSpace && currLength == MAX_LINE_LEN && i != msg.length()) {
			msgToLines.push_back(msg.substr(offset, lastSpace - offset + 1));
			i = lastSpace + 1;
			offset = lastSpace + 1;
			lastSpace = 0;
        }
        else {
			if (msg.length() - MAX_LINE_LEN > 0 && msg.length() - offset >
				MAX_LINE_LEN)
			{
				msgToLines.push_back(msg.substr(offset, MAX_LINE_LEN));
            }
			else
			{
				msgToLines.push_back(msg.substr(offset, msg.length() - offset));
			}
			offset += MAX_LINE_LEN;
		}
    }
	return msgToLines;
}

void __fastcall TForm1::MsgBoxKeyPress(TObject *Sender, System::WideChar &Key)
{
	if(Key == VK_RETURN)
	{
		Key = 0;
		Form1->SendButtonClick(Sender);
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

void __fastcall TForm1::FormShow(TObject *Sender)
{
    Form1->Enabled = false;
	Form2->Show();
}
//---------------------------------------------------------------------------



void __fastcall TForm1::ListBox1Click(TObject *Sender)
{
	const std::string TO_TEXT("to: ");
	const std::string TO_ALL("All");

	std::string selectedUserName;

	if(ListBox1->ItemIndex > 0
	&& (selectedUserName =
	sysStrToStd(ListBox1->Items->Strings[ListBox1->ItemIndex])).compare(userName))
	{
		MsgToLabel->Caption = (TO_TEXT + selectedUserName).c_str();
	} else
	{
		MsgToLabel->Caption = (TO_TEXT + TO_ALL).c_str();
	}
}
//---------------------------------------------------------------------------
