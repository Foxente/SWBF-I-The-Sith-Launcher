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

#pragma hdrstop

#include "API.h"

#pragma package(smart_init)

//Get GameData folder's path
UnicodeString GetGameDataPath ()
 {
  return ExtractFilePath (Application -> ExeName) + "GameData\\";
 }

//Get LauncherData folder's path
UnicodeString GetLauncherDataPath ()
 {
  return ExtractFilePath (Application -> ExeName) + "LauncherData\\";
 }

//Get file name without extension
UnicodeString GetOnlyFileName (UnicodeString FilePath)
 {
  return StringReplace (ExtractFileName (FilePath), ExtractFileExt (FilePath), "", TReplaceFlags ());
 }

//If ident doesnt exists that will writed this value in new ident
void WriteNewStringToIniFile (TMemIniFile *IniFile, UnicodeString Section, UnicodeString Ident, UnicodeString Value)
 {
  Value = IniFile -> ReadString (Section, Ident, Value);
  IniFile -> WriteString (Section, Ident, Value);
 }

//If file doesn't exists that will be error shown and the application terminate
void RequiredFileExists (UnicodeString FilePath)
 {
  if (!FileExists (FilePath))
   {
	ShowErrorM ("File '" + FilePath + "' doesn't exsists!");
    Application -> Terminate ();
   }
 }

//Set form position to screen center
void SetFormToScreenCenter (TForm* Form)
 {
  Form -> Left = (Screen -> Width - Form -> Width) / 2;
  Form -> Top = (Screen -> Height - Form -> Height) / 2;
 }

//Show error message
void ShowErrorM (UnicodeString Error)
 {
  Application -> MessageBox (Error.c_str (), UnicodeString ("ERROR").c_str (), MB_OK);
 }
