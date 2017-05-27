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

#include "API.h"

#include "UnitLogo.h"
#include "UnitMainMenu.h"

#pragma package(smart_init)
#pragma resource "*.dfm"

TAPIdata *APIdata;

__fastcall TAPIdata::TAPIdata (TComponent* Owner) : TForm (Owner)
 {
 }

//Vars for saving main data
TMemIniFile *SettingsFile = new TMemIniFile (GetLauncherDataPath () + "Settings.ini");
TMemIniFile *LanguageFile = new TMemIniFile ("");
UnicodeString LanguageStrings [100];

//Don't change theese consts
UnicodeString Author = "FOXente (Aradam)";

//Get GameData folder's path
UnicodeString GetGameDataPath ()
 {
  return ExtractFilePath (Application -> ExeName) + "GameData/";
 }

//Get LauncherData folder's path
UnicodeString GetLauncherDataPath ()
 {
  return ExtractFilePath (Application -> ExeName) + "LauncherData/";
 }

//Get file name without extension
UnicodeString GetOnlyFileName (UnicodeString FilePath)
 {
  return StringReplace (ExtractFileName (FilePath), ExtractFileExt (FilePath), "", TReplaceFlags ());
 }

//If ident doesnt exists that will writed this value in new ident
UnicodeString WriteNewStringToIniFile (TMemIniFile *IniFile, UnicodeString Section, UnicodeString Ident, UnicodeString Value)
 {
  Value = IniFile -> ReadString (Section, Ident, Value);
  IniFile -> WriteString (Section, Ident, Value);
  return Value;
 }

//Replace string mask with replacement
UnicodeString ReplaceStringMask (UnicodeString CurrentString, UnicodeString Mask, UnicodeString Replacement)
 {
  return StringReplace (CurrentString, "%" + Mask + "%", Replacement, TReplaceFlags () << rfReplaceAll);
 }

//If file doesn't exists that will be error shown and the application terminate
void RequiredFileExists (UnicodeString FilePath)
 {
  if (!FileExists (FilePath))
   {
	ShowErrorM (ReplaceStringMask (LanguageStrings [1], "path", FilePath));
    Application -> Terminate ();
   }
 }

//Apply new program's language from file
void ApplyLanguageFromFile (UnicodeString FilePath)
 {
  //Loading
  LanguageFile = new TMemIniFile (FilePath);
  LanguageStrings [2] = WriteNewStringToIniFile (LanguageFile, "FormCaption", "Name", "SWBF I The Sith Launcher");
  LanguageStrings [0] = WriteNewStringToIniFile (LanguageFile, "FormCaption", "Logo", "Created by %name%");
  LanguageStrings [1] = WriteNewStringToIniFile (LanguageFile, "Error", "1", "File '%path%' doesn't exsists!");
  LanguageFile -> UpdateFile ();
  //Apply
  FormLogo -> Caption = LanguageStrings [2];
  FormMainMenu -> Caption = LanguageStrings [2];
 }

//Set form position to screen center
void SetFormToScreenCenter (TForm* Form)
 {
  Form -> Left = (Screen -> Width - Form -> Width) / 2;
  Form -> Top = (Screen -> Height - Form -> Height) / 2;
 }

//Unvisible form
void UnvisibleForm (TForm* Form)
 {
  Form -> Enabled = false;
  Form -> Left = -99999;
  Form -> Top = -99999;
 }

//Show error message
void ShowErrorM (UnicodeString Error)
 {
  Application -> MessageBox (Error.c_str (), UnicodeString ("ERROR").c_str (), MB_OK);
 }
