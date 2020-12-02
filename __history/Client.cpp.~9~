//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
#include "LogInForm.h"
#include "RegForm.h"

//---------------------------------------------------------------------------
//USEFORM("RegForm.cpp", Form3);
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
USEFORM("RegForm.cpp", Form3);
USEFORM("MainForm.cpp", Form1);
USEFORM("LogInForm.cpp", Form2);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		TStyleManager::TrySetStyle("Tablet Dark");
		Application->CreateForm(__classid(TForm1), &Form1);
		Application->CreateForm(__classid(TForm3), &Form3);
		if(TForm2::Execute())
		{
			Application->Initialize();
			Application->MainFormOnTaskBar = true;
			Application->Run();
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
