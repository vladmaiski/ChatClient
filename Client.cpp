//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
#include "LogInForm.cpp"

//---------------------------------------------------------------------------
USEFORM("MainForm.cpp", Form1);
USEFORM("LogInForm.cpp", Form2);
USEFORM("RegForm.cpp", Form3);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		if(TForm2::Execute())
		{
			Application->Initialize();
			Application->MainFormOnTaskBar = true;
			Application->CreateForm(__classid(TForm1), &Form1);
		Application->Run();
		}
        else
		{
            Application->MessageBox(
                _T("¬ы не можете пользоватьс€ приложением, так как не прошли авторизацию"),
                _T("«ащита приложени€")
            );
		}
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
