//---------------------------------------------------------------------------

#ifndef MainFormH
#define MainFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
//---------------------------------------------------------------------------
#include <iostream>
#include <string>
#include <winsock2.h>
#include <ctime>
#include <vector>

#pragma comment(lib, "ws2_32.lib")

#define _WINSOCK_DEPRECATED_NO_WARNINGS

extern const int PACKET_TYPE_LENGHT;
extern const int MAX_MESSAGE_SIZE;
extern const int MAX_USER_INPUT_SIZE;
extern const char *SERVER_IP;
extern const int SERVER_PORT;
extern const int MAX_LINE_LEN;

extern const char *MSG_PCKT;
extern const char *LOG_PCKT;
extern const char *DISCONNECT_PCKT;
extern const char *REG_PCKT;
extern const char* USER_REGISTRED_PCKT;
extern const char* USER_NOT_REGISTRED_PCKT;
extern const char* NOT_LOGGED_PCKT;
extern const char* LOGGED_PCKT;
extern const char* USER_INFO_PCKT;
extern const char* PRIVATE_MSG;

extern SOCKET serverSock;

extern std::string userName;

extern std::vector<std::string> usersOnline;

void printMsg(std::string msg);
void printMsg(std::string msg);
void sendMsg(const char *packetType, std::string msg);
std::string makePacket(const char *packetType, std::string msg);
void sendPacket(SOCKET server, std::string packet);
std::string sysStrToStd(String str);
bool connectToServer();
DWORD WINAPI clientHandler(LPVOID lpParam);
void printMsg(std::string msg, bool flag);
void greetUser(std::string name);
void disconnect();
std::string sysStrToStd(String str);
bool checkInputSize(std::string input, int size);
bool checkUserInput(std::string input, int size);
void createHandlerThreat();
void packetHandle(char* _msg);
void printPrivateMsg(std::string msg, bool isClientMessage, std::string recieverName);
std::vector<std::string>divByWords(std::string msg, const int MAX_LINE_LEN);


class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TButton *SendButton;
	TLabel *Label1;
	TListBox *ListBox1;
	TEdit *MsgBox;
	TRichEdit *ChatBox;
	TLabel *MsgToLabel;
	TLabel *DevInf;
	void __fastcall SendButtonClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall MsgBoxKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall MsgBoxChange(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall ListBox1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
