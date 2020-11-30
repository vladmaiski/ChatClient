//---------------------------------------------------------------------------

#ifndef MainFormH
#define MainFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
#include <iostream>
#include <string>
#include <winsock2.h>
#include <ctime>
#include <vector>

#pragma comment(lib, "ws2_32.lib")

#define _WINSOCK_DEPRECATED_NO_WARNINGS

const int PACKET_TYPE_LENGHT = 5;
const int MAX_MESSAGE_SIZE = 1000;
const int MAX_USER_INPUT_SIZE = 3000;


const char *MSG_PCKT = "/000/";
const char *LOG_PCKT = "/111/";
const char *DISCONNECT_PCKT = "/222/";
const char *REG_PCKT = "/333/";
const char* USER_REGISTRED_PCKT = "/444/";
const char* USER_NOT_REGISTRED_PCKT = "/555/";
const char* NOT_LOGGED_PCKT = "/666/";
const char* LOGGED_PCKT = "/777/";
const char* USER_INFO_PCKT = "/888/";

SOCKET serverSock = NULL;

std::string userName;

void printMsg(std::string msg);
void printMsg(std::string msg);
void sendMsg(const char *packetType, std::string msg);
std::string makePacket(const char *packetType, std::string msg);
void sendPacket(SOCKET server, std::string packet);
std::string sysStrToStd(String str);
bool connectToServer();
DWORD WINAPI clientHandler(LPVOID lpParam);
void printMsg(std::string msg, bool flag);
void greetUser(String name);
void disconnect();
std::string sysStrToStd(String str);
bool checkInputSize(std::string input, int size);
bool checkUserInput(std::string input, int size);
void createHandlerThreat();
void packetHandle(char* _msg);


class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TButton *Button1;
	TEdit *MsgBox;
	TMemo *ChatBox;
	TLabel *Label1;
	TListBox *ListBox1;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall MsgBoxKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall MsgBoxChange(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
