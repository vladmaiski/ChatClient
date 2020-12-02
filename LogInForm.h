//---------------------------------------------------------------------------

#ifndef LogInFormH
#define LogInFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>

//---------------------------------------------------------------------------

const int PASS_NICKNAME_LENGTH = 30;

class TForm2 : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TLabel *Label2;
	TEdit *Edit1;
	TEdit *Edit2;
	TButton *Button1;
	TLabel *Label3;
	TButton *Button2;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Label3MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall Label3MouseLeave(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall EnterKeyPress(TObject *Sender, System::WideChar &Key);

private:	// User declarations
public:		// User declarations
	__fastcall TForm2(TComponent* Owner);
	static bool __fastcall Execute();
};

//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
