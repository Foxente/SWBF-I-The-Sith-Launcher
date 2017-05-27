/*
╔══╦╗╔╗╔╦══╗╔══╗╔══╗  ╔══╦══╦════╦╗╔╗  ╔╗─╔══╦╗╔╦╗─╔╦══╦╗╔╦═══╦═══╗
║╔═╣║║║║║╔╗║║╔═╝╚╗╔╝  ║╔═╩╗╔╩═╗╔═╣║║║  ║║─║╔╗║║║║╚═╝║╔═╣║║║╔══╣╔═╗║
║╚═╣║║║║║╚╝╚╣╚═╗─║║   ║╚═╗║║──║║─║╚╝║  ║║─║╚╝║║║║╔╗─║║─║╚╝║╚══╣╚═╝║
╚═╗║║║║║║╔═╗║╔═╝─║║   ╚═╗║║║──║║─║╔╗║  ║║─║╔╗║║║║║╚╗║║─║╔╗║╔══╣╔╗╔╝
╔═╝║╚╝╚╝║╚═╝║║──╔╝╚╗  ╔═╝╠╝╚╗─║║─║║║║  ║╚═╣║║║╚╝║║─║║╚═╣║║║╚══╣║║║
╚══╩═╝╚═╩═══╩╝──╚══╝  ╚══╩══╝─╚╝─╚╝╚╝  ╚══╩╝╚╩══╩╝─╚╩══╩╝╚╩═══╩╝╚╝
Created by FOXente (Aradam)
License GPL-3.0
*/

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>

USEFORM ("API.cpp", APIdata);
USEFORM ("UnitLogo.cpp", FormLogo);
USEFORM ("UnitMainMenu.cpp", FormMainMenu);
USEFORM ("UnitSettings.cpp", FormSettings);

int WINAPI _tWinMain (HINSTANCE, HINSTANCE, LPTSTR, int)
 {
  try
   {
	Application -> Initialize ();
	Application -> MainFormOnTaskBar = true;
	Application -> CreateForm (__classid (TFormLogo), &FormLogo);
	Application -> CreateForm (__classid (TAPIdata), &APIdata);
	Application -> CreateForm (__classid (TFormMainMenu), &FormMainMenu);
	Application -> CreateForm (__classid (TFormSettings), &FormSettings);
	Application -> Run ();
   }
  catch (Exception &exception)
   {
	Application -> ShowException (&exception);
   }
  catch (...)
   {
	try
	 {
	  throw Exception ("");
	 }
	catch (Exception &exception)
	 {
	  Application -> ShowException (&exception);
	 }
   }
  return 0;
}
