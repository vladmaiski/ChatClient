//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "RegForm.h"
#include "LogInForm.h"
#include "MainForm.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------

bool closeMain = true;

__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{

}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button1Click(TObject *Sender)
{
	if(!checkUserInput(sysStrToStd(LoginField->Text),
	 PASS_NICKNAME_LENGTH) && !checkUserInput(sysStrToStd(PasswordField->Text), PASS_NICKNAME_LENGTH))
	{
		ShowMessage("Incorrect input.");
		return;
	}

	std::string toSend = sysStrToStd(LoginField->Text) + ":" + sysStrToStd(PasswordField->Text);
	sendMsg(LOG_PCKT, toSend.c_str());

	char* msg = (char*)calloc(PACKET_TYPE_LENGHT + 1, sizeof(char));
	recv(serverSock, msg, PACKET_TYPE_LENGHT, NULL);
	std::string packetType(msg);

	if (!packetType.compare(LOGGED_PCKT))
	{

		Form1 -> Enabled = true;
		closeMain = false;

		Form2 -> Close();

		String name = LoginField->Text;

		userName = sysStrToStd(name);

		greetUser(userName);
		createHandlerThreat();
	}
	else if(!packetType.compare(NOT_LOGGED_PCKT))
    {
		Application->MessageBox(_T("Incorrect login or password"), _T("Application error"));
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Label3MouseMove(TObject *Sender, TShiftState Shift, int X,
		  int Y)
{
	PasswordField->PasswordChar = 0;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Label3MouseLeave(TObject *Sender)
{
	PasswordField ->PasswordChar = '*';
}
//---------------------------------------------------------------------------


void __fastcall TForm2::Button2Click(TObject *Sender)
{
	Form3->ShowModal();
}


void __fastcall TForm2::FormCreate(TObject *Sender)
{
	PasswordField ->PasswordChar = '*';
}
//---------------------------------------------------------------------------

void __fastcall TForm2::FormClose(TObject *Sender, TCloseAction &Action)
{
	if(closeMain)
	{
		Form1->Close();
	}
}
void __fastcall TForm2::EnterKeyPress(TObject *Sender, System::WideChar &Key)
{
	if(Key == VK_RETURN)
	{
		Key = 0;
		Form2->Button1Click(Sender);
	}
}
//---------------------------------------------------------------------------
