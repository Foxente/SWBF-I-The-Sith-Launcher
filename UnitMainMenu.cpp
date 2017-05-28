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

#include "UnitMainMenu.h"
#include "API.h"
#include "UnitAboutLauncher.h"

#include "UnitSettings.h"
#include "UnitAddonsControl.h"

#pragma package(smart_init)
#pragma link "sBitBtn"
#pragma link "sLabel"
#pragma resource "*.dfm"

TFormMainMenu *FormMainMenu;

__fastcall TFormMainMenu::TFormMainMenu (TComponent* Owner) : TForm (Owner)
 {
 }

void __fastcall TFormMainMenu::FormClose (TObject *Sender, TCloseAction &Action)
 {
  Application -> Terminate ();
 }

void __fastcall TFormMainMenu::sBitBtnSettingsClick (TObject *Sender)
 {
  if (!IsBattlefrontRunning ())
   {
    SetFormToScreenCenter (FormSettings);
    FormSettings -> ShowModal ();
   }
 }

void __fastcall TFormMainMenu::sBitBtnPlayClick (TObject *Sender)
 {
  if (!IsBattlefrontRunning ())
   {
    //Patching .exe for changing game version
    TFileStream *Stream = new TFileStream (GetBattlefrontExePath (), fmOpenReadWrite | fmShareDenyWrite);
    Stream -> Position = 0x2AF12C;
    AnsiString NewVersion = SettingsFile -> ReadString ("Multiplayer", "Current_version", "1.3");
    Stream -> Write (&NewVersion [1], NewVersion.Length () + 1);
    Stream -> Free ();
    //Launch the game
    UnicodeString cmdline = "";
    if (SettingsFile -> ReadString ("Game_launch", "Window_mode", "false") == "true") cmdline += " /win";
    if (SettingsFile -> ReadString ("Game_launch", "Skip_logos", "false") == "true") cmdline += " /nointro";
    if (SettingsFile -> ReadString ("Game_launch", "Skip_startup_music", "false") == "true") cmdline += " /nostartupmusic";
    if (SettingsFile -> ReadString ("Game_launch", "Skip_menu_background", "false") == "true") cmdline += " /nomovies";
    if (SettingsFile -> ReadString ("Game_launch", "Audio_buffer_enable", "false") == "true") cmdline += " /audiomixbuffer " + SettingsFile -> ReadString ("Game_launch", "Audio_buffer_ms", "200");
    if (SettingsFile -> ReadString ("Game_launch", "Audio_rate_enable", "false") == "true") cmdline += " /audiosamplerate " + SettingsFile -> ReadString ("Game_launch", "Audio_rate", "11000");
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    memset (&pi, 0, sizeof (pi));
    memset (&si, 0, sizeof (si));
    si.cb = sizeof (si);
    CreateProcess (GetBattlefrontExePath ().w_str (), cmdline.w_str (),  0, 0, true, 0, 0, GetGameDataPath ().w_str (), &si, &pi);
    //Patching hosts file for Internet multiplayer game
    if (SettingsFile -> ReadString ("Multiplayer", "Use_user_host", "true") == "true")
     {
      TStringList *oldDomens = new TStringList ();
      oldDomens -> Delimiter = ' ';
      oldDomens -> DelimitedText = "swbfrontpc.ms4.gamespy.com swbfrontpc.available.gamespy.com available.gamespy.com master.gamespy.com swbfrontpc.master.gamespy.com key.gamespy.com peerchat.gamespy.com gpsp.gamespy.com gpcm.gamespy.com natneg1.gamespy.com swbfront2pc.ms4.gamespy.com swbfront2pc.ms5.gamespy.com swbfront2pc.ms6.gamespy.com swbfront2pc.available.gamespy.com swbfront2pc.master.gamespy.com natneg2.gamespy.com swbfront2pc.gamestats.gamespy.com gamestats.gamespy.com swbfrontps2.ms10.gamespy.com swbfrontps2.available.gamespy.com swbfrontps2.master.gamespy.com swbfront2ps2.ms4.gamespy.com swbfront2ps2.available.gamespy.com swbfront2ps2.master.gamespy.com";
      TStringList *hosts = new TStringList ();
      hosts -> LoadFromFile (GetHostsFilePath ());
      //Get start and end positions for cyclic pass
      int StartPos = hosts -> IndexOf ("#Star Wars Battlefront Multiplayer Servers");
      int EndPos;
      if (StartPos == -1)
       {
        StartPos = hosts -> Count - 1;
        EndPos = 0;
       } else
       {
        EndPos = StartPos;
        StartPos = EndPos + oldDomens -> Count;
        if (StartPos > hosts -> Count - 1) StartPos = hosts -> Count - 1;
       }
      //Cyclic pass for deleting exists swbf domens
      for (int i = StartPos; i >= EndPos; i--)
        {
         for (int j = 0; j <= oldDomens -> Count - 1; j++)
           {
            if ((hosts -> Strings [i].Pos (oldDomens -> Strings [j]) > 0) || (hosts -> Strings [i] == "#Star Wars Battlefront Multiplayer Servers"))
             {
              hosts -> Delete (i);
              break;
             }
           }
        }
      //Cyclic pass for adding redirects for old swbf domens
      hosts -> Add ("#Star Wars Battlefront Multiplayer Servers");
      for (int i = 0; i <= oldDomens -> Count - 1; i++)
        {
         hosts -> Add (SettingsFile -> ReadString ("Multiplayer", "Host", "162.248.92.172") + " " + oldDomens -> Strings [i]);
        }
      hosts -> SaveToFile (GetHostsFilePath ());
      hosts -> Free ();
      oldDomens -> Free ();
     }
   }
 }

void __fastcall TFormMainMenu::sBitBtnSetAdditionalMapClick (TObject *Sender)
 {
  if (!IsBattlefrontRunning ())
   {
    SetFormToScreenCenter (FormAddonsControl);
    FormAddonsControl -> ShowModal ();
   }
 }

void __fastcall TFormMainMenu::sBitBtnAboutLauncherClick (TObject *Sender)
 {
  SetFormToScreenCenter (FormAboutLauncher);
  FormAboutLauncher -> ShowModal ();
 }
