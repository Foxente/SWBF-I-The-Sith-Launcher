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

#ifndef APIH
#define APIH

#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>

#include <IniFiles.hpp>

class TAPIdata : public TForm
 {
  __published:
  private:
  public:
	__fastcall TAPIdata (TComponent* Owner);
 };

extern PACKAGE TAPIdata *APIdata;

//Api data
extern PACKAGE TMemIniFile *SettingsFile;
extern PACKAGE TMemIniFile *LanguageFile;
extern PACKAGE UnicodeString LanguageStrings [100];

//Consts
extern PACKAGE UnicodeString Author;

//Api methods
UnicodeString GetGameDataPath ();
UnicodeString GetLauncherDataPath ();
UnicodeString GetOnlyFileName (UnicodeString FilePath);
UnicodeString WriteNewStringToIniFile (TMemIniFile *IniFile, UnicodeString Section, UnicodeString Ident, UnicodeString Value);
void RequiredFileExists (UnicodeString FilePath);
void ApplyLanguageFromFile (UnicodeString FilePath);
void SetFormToScreenCenter (TForm* Form);
void ShowErrorM (UnicodeString Error);

#endif
