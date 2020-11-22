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

#pragma comment(lib, "ws2_32.lib")

#define _WINSOCK_DEPRECATED_NO_WARNINGS

const char *MSG_PCKT = "/000/";
const char *REG_PCKT = "/111/";
const char *DISCONNECT_PCKT = "/222/";

SOCKET serverSock;

std::string userName;

void printMsg(std::string msg);
void printMsg(std::string msg);
void sendMsg(const char *packetType, std::string msg);
std::string makePacket(const char *packetType, std::string msg);
void sendPacket(SOCKET server, std::string packet);
std::string sysStrToStd(String str);
bool connectToServer(const char *adress);
DWORD WINAPI clientHandler(LPVOID lpParam);
void printMsg(std::string msg);
void greetUser(String name);

class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TButton *Button1;
	TEdit *MsgBox;
	TMemo *ChatBox;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
