//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <RegForm.h>
#include "LogInForm.h"
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
	TForm2 *frm = new TForm2(0);
	int res = frm->ShowModal();
	delete frm;
	return res == mrOk;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button1Click(TObject *Sender)
{
	if(Edit1->Text == "" || Edit2->Text == "")
	{
		ShowMessage("Incorrect input.");
		return;
	}
	if (Edit1->Text == "1" && Edit2->Text == "1")
    {
		ModalResult = mrOk;
	}
	else
    {
		Application->MessageBox(_T("Application error"), _T("Incorrect login or password"));
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

