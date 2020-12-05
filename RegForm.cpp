//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainForm.h"
#include "RegForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;
//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
	: TForm(Owner)
{
}

//---------------------------------------------------------------------------


void __fastcall TForm3::Button1Click(TObject *Sender)
{   if(checkUserInput(sysStrToStd(NicknameField->Text), NICKNAME_LENGTH))
	{
		if(checkUserInput(sysStrToStd(PasswordField->Text), PASSWORD_LENGTH))
		{
			std::string res = sysStrToStd(NicknameField->Text) + ":" + sysStrToStd(PasswordField->Text);
			sendMsg(REG_PCKT, res);
			char* packetType = (char*)calloc(PACKET_TYPE_LENGHT, sizeof(char));
			recv(serverSock, packetType, PACKET_TYPE_LENGHT, NULL);
			std::string packet(packetType);
			if(!packet.compare(USER_REGISTRED_PCKT))
			{
				ShowMessage("You register your account!");
				Form3->Close();
			} else
			{
				ShowMessage("Account with such name already exist");
			}
		} else
		{
			ShowMessage("Incorrect password(no more than " + AnsiString(PASSWORD_LENGTH) + " characters).");
			return;
		}
	} else
	{
		ShowMessage("Incorrect nickname(no more than " + AnsiString(NICKNAME_LENGTH) + " characters)");
		return;
	}


}
//---------------------------------------------------------------------------


void __fastcall TForm3::FormCreate(TObject *Sender)
{
	PasswordField ->PasswordChar = '*';
}

void __fastcall TForm3::FormKeyPress(TObject *Sender, System::WideChar &Key)
{
	if(Key == VK_RETURN)
	{
		Key = 0;
		Form3->Button1Click(Sender);
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Label3MouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y)
{
	PasswordField->PasswordChar = 0;
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Label3MouseLeave(TObject *Sender)
{
	PasswordField ->PasswordChar = '*';
}
//---------------------------------------------------------------------------

