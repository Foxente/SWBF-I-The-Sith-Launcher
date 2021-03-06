﻿/*
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
USEFORM ("UnitAddonsControl.cpp", FormAddonsControl);
USEFORM ("UnitScreenZoom.cpp", FormScreenZoom);
USEFORM ("UnitGlobalProcess.cpp", FormGlobalProcess);
USEFORM ("UnitAboutLauncher.cpp", FormAboutLauncher);
USEFORM ("UnitSelectMapMode.cpp", FormSelectMapMode);

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
    Application -> CreateForm (__classid (TFormAddonsControl), &FormAddonsControl);
    Application -> CreateForm (__classid (TFormScreenZoom), &FormScreenZoom);
    Application -> CreateForm (__classid (TFormGlobalProcess), &FormGlobalProcess);
    Application -> CreateForm (__classid (TFormAboutLauncher), &FormAboutLauncher);
    Application -> CreateForm (__classid (TFormSelectMapMode), &FormSelectMapMode);
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
