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
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{

}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button1Click(TObject *Sender)
{
	if(!checkUserInput(sysStrToStd(Edit1->Text),
	 PASS_NICKNAME_LENGTH) && !checkUserInput(sysStrToStd(Edit2->Text), PASS_NICKNAME_LENGTH))
	{
		ShowMessage("Incorrect input.");
		return;
	}

	std::string toSend = sysStrToStd(Edit1->Text) + ":" + sysStrToStd(Edit2->Text);
	sendMsg(LOG_PCKT, toSend.c_str());

	char* msg = (char*)calloc(PACKET_TYPE_LENGHT + 1, sizeof(char));
	recv(serverSock, msg, PACKET_TYPE_LENGHT, NULL);
	std::string packetType(msg);

	if (!packetType.compare(LOGGED_PCKT))
	{

		Form1 -> Enabled = true;
		Form2 -> Hide();

		String name = Edit1->Text;

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
	Edit2->PasswordChar = 0;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Label3MouseLeave(TObject *Sender)
{
	Edit2 ->PasswordChar = '*';
}
//---------------------------------------------------------------------------


void __fastcall TForm2::Button2Click(TObject *Sender)
{
	Form3->ShowModal();
}


void __fastcall TForm2::FormCreate(TObject *Sender)
{
	Edit2 ->PasswordChar = '*';
}
//---------------------------------------------------------------------------

void __fastcall TForm2::FormClose(TObject *Sender, TCloseAction &Action)
{
	Form1->Close();
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

