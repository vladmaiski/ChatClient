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
bool __fastcall TForm2::Execute()
{
	if(connectToServer())
	{
		TForm2 *frm = new TForm2(0);
		int res = frm->ShowModal();
		delete frm;
		return res == mrOk;
	} else
	{
		Application->MessageBox(_T("Server unavailable"), _T("Application error"));
		exit(3);
	}

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
	if (true)//!packetType.compare(LOGGED_PCKT))
	{
		String name = Edit1->Text;
		userName = sysStrToStd(name);

		createHandlerThreat();
		greetUser(name);
		ModalResult = mrOk;
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
	//disconnect();
}
//---------------------------------------------------------------------------

