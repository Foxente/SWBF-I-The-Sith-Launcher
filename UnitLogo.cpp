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

#pragma package(smart_init)
#pragma link "sSkinManager"
#pragma link "acImage"
#pragma resource "*.dfm"

TFormLogo *FormLogo;
TMemIniFile *SettingsFile = new TMemIniFile (GetLauncherDataPath () + "Settings.ini");

__fastcall TFormLogo::TFormLogo (TComponent* Owner) : TForm (Owner)
 {
 }

void __fastcall TFormLogo::FormShow (TObject *Sender)
 {
  //Position to center
  SetFormToScreenCenter (FormLogo);
  //Generate new Settings.ini if doesnt exists
  WriteNewStringToIniFile (SettingsFile, "Game_launch", "Window_mode", "false");
  WriteNewStringToIniFile (SettingsFile, "Game_launch", "Skip_logos", "false");
  WriteNewStringToIniFile (SettingsFile, "Game_launch", "Skip_startup_music", "false");
  WriteNewStringToIniFile (SettingsFile, "Game_launch", "Skip_menu_background", "false");
  WriteNewStringToIniFile (SettingsFile, "Game_launch", "Audio_buffer_enable", "false");
  WriteNewStringToIniFile (SettingsFile, "Game_launch", "Audio_buffer_ms", "200");
  WriteNewStringToIniFile (SettingsFile, "Game_launch", "Audio_rate_enable", "false");
  WriteNewStringToIniFile (SettingsFile, "Game_launch", "Audio_rate", "11000");
  WriteNewStringToIniFile (SettingsFile, "Language", "Name", "English");
  WriteNewStringToIniFile (SettingsFile, "Multiplayer", "Use_user_host", "true");
  WriteNewStringToIniFile (SettingsFile, "Multiplayer", "Host", "162.248.92.172");
  WriteNewStringToIniFile (SettingsFile, "Multiplayer", "Current_version", "1.3");
  if (SettingsFile -> ReadString ("Multiplayer", "Current_version", "1.3").Length () != 3)
   {
	SettingsFile -> WriteString ("Multiplayer", "Current_version", "1.3");
	//ShowMessage
   }
  SettingsFile -> UpdateFile ();
 }
