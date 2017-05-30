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

#include "UnitLogo.h"
#include "API.h"

#include "UnitMainMenu.h"

#pragma package(smart_init)
#pragma link "sSkinManager"
#pragma link "acImage"
#pragma resource "*.dfm"

TFormLogo *FormLogo;

__fastcall TFormLogo::TFormLogo (TComponent* Owner) : TForm (Owner)
 {
 }

void __fastcall TFormLogo::FormShow (TObject *Sender)
 {
  //Position to center
  SetFormToScreenCenter (FormLogo);
  //Create some directories
  CreateDir (GetAddOnPath ());
  CreateDir (GetLauncherDataPath () + "Languages\\English\\");
  //Load language file or create if doesn't exists
  ApplyLanguageFromFile (GetLauncherDataPath () + "Languages\\" + SettingsFile -> ReadString ("Language", "Name", "English") + "\\Language.ini");
  Caption = ReplaceStringMask (LanguageStrings [0], "name", Author);
 }

void __fastcall TFormLogo::TimerNextFormTimer (TObject *Sender)
 {
  //Go to the next form
  TimerNextForm -> Enabled = false;
  SetFormToScreenCenter (FormMainMenu);
  UnvisibleForm (FormLogo);
  Caption = LanguageStrings [2];
  FormMainMenu -> ShowModal ();
 }
