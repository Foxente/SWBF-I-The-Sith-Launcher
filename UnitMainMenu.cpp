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

#include <System.hpp>
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
UnicodeString ErrorMessage;

__fastcall TFormMainMenu::TFormMainMenu (TComponent* Owner) : TForm (Owner)
 {
 }

__fastcall TErrorSearchThread::TErrorSearchThread (bool CreateSuspended) : TThread (CreateSuspended)
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
    FormSettings -> sComboBoxSelectingMessage -> ItemIndex = 0;
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
    AnsiString NewVersion = SettingsFile -> ReadString ("Multiplayer", "Current_version", "1.2");
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
    //Check all required files
    RequiredFileExists (GetBattlefrontExePath ());
    RequiredFileExists (GetGameDataPath () + "binkw32.dll");
    RequiredFileExists (GetGameDataPath () + "eax.dll");
    RequiredFileExists (GetGameDataPath () + "unicows.dll");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\BES\\bes1.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\BES\\bes2.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\Common\\ENG\\common.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\END\\end1.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\ALL\\allcldcr.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\ALL\\allcmspd.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\ALL\\allcmspg.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\ALL\\allhthmk.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\ALL\\allhthtr.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\ALL\\allhvrnt.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\ALL\\allkwing.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\ALL\\allmarks.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\ALL\\allmedic.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\ALL\\allpilot.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\ALL\\allsccam.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\ALL\\allsspdr.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\ALL\\alltaun.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\ALL\\alltroop.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\ALL\\allwook.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\ALL\\allxwing.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\ALL\\allywing.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\ALL\\gunsspdr.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\ALL\\repgunnr.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\CIS\\cisaatp.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\CIS\\cisbdrd.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\CIS\\cisdrde.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\CIS\\cishlfrd.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\CIS\\cismafp.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\CIS\\cismttp.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\CIS\\cissbdrd.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\CIS\\cissccam.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\CIS\\cisspdrw.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\CIS\\cisstapp.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\CIS\\cisstrft.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\CIS\\repgunnr.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\Com\\comallre.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\Com\\comcisim.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\Com\\comgntrt.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\Com\\comgunnr.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\Com\\comhview.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\Com\\comunive.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\Com\\comviewf.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\IMP\\allxwing.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\IMP\\atst.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\IMP\\impatat.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\IMP\\impatatg.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\IMP\\impatstg.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\IMP\\impdark.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\IMP\\impftrtk.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\IMP\\impimplc.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\IMP\\impoff.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\IMP\\imppilot.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\IMP\\impsccam.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\IMP\\impscout.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\IMP\\impsntr.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\IMP\\impspbk.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\IMP\\impstrp.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\IMP\\imptibmr.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\IMP\\imptiftr.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\IMP\\repgunnr.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\REP\\allxwing.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\REP\\reparc.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\REP\\repatted.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\REP\\repatxtp.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\REP\\repcmspd.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\REP\\repftrtk.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\REP\\repgunnr.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\REP\\repgunsh.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\REP\\repguntr.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\REP\\rephtrop.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\REP\\repjedfi.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\REP\\repjettp.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\REP\\repmedic.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\REP\\reppilot.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\REP\\repsccam.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\REP\\repsharp.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\REP\\repspbk.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\REP\\reptroop.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\GEO\\geo1.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\HOT\\hot1.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\KAM\\kam1.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\KAS\\kas1.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\KAS\\kas2.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\KAS\\kas2_h.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\Load\\bes1.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\Load\\bes2.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\Load\\end1.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\Load\\geo1.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\Load\\hot1.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\Load\\kam1.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\Load\\kas1.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\Load\\kas2.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\Load\\load.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\Load\\nab1.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\Load\\nab2.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\Load\\rhn1.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\Load\\rhn2.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\Load\\tat1.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\Load\\tat2.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\Load\\yav1.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\core.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\mission.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\SIDE\\geo.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\SIDE\\gun.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\SIDE\\imp.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\SIDE\\rep.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\SIDE\\wok.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\Shell\\ENG\\shell.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\Sound\\bes.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\Sound\\common.bnk");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\Sound\\cw.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\Sound\\end.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\Sound\\gcw.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\Sound\\geo.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\Sound\\hot.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\Sound\\kam.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\Sound\\kas.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\Sound\\nab.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\Sound\\rhn.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\Sound\\shell.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\Sound\\tat.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\Sound\\yav.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\TAT\\tat1.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\TAT\\tat1h.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\TAT\\tat2.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\YAV\\yav1.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\YAV\\yav2.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\YAV\\yav2_h.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\NAB\\nab1_h.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\NAB\\nab2.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\NAB\\nab2_h.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\RHN\\Rhn1.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\RHN\\Rhn2.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\Load\\yav2.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\Movies\\shell.mvs");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\NAB\\nab1.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\SIDE\\all.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\SIDE\\cis.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\SIDE\\ewk.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\SIDE\\des.lvl");
    RequiredFileExists (GetGameDataPath () + "Data\\_LVL_PC\\SIDE\\gar.lvl");
    //Run the game
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    memset (&pi, 0, sizeof (pi));
    memset (&si, 0, sizeof (si));
    si.cb = sizeof (si);
    //Run game without changing resolution
    if ((SettingsFile -> ReadString ("Game_launch", "Custom_resolution_enable", "true") == "false") || (!FileExists (GetGameDataPath () + "Data\\_LVL_PC\\vidmode.ini")))
     {
      CreateProcess (GetBattlefrontExePath ().w_str (), cmdline.w_str (),  0, 0, true, 0, 0, GetGameDataPath ().w_str (), &si, &pi);
     } else //Run game using Battlebelk's Custom Resolution Launcher
     {
      //Generate vidmode.ini
      TStringList *LinesVideoMode = new TStringList ();
      LinesVideoMode -> LoadFromFile (GetGameDataPath () + "Data\\_LVL_PC\\vidmode.ini");
      String Device = LinesVideoMode -> Strings [0];
      LinesVideoMode -> Clear ();
      LinesVideoMode -> Add (Device);
      for (int i = 0; i <= 16; i++)
        for (int j = 0; j <= 16; j++) LinesVideoMode -> Add (SettingsFile -> ReadString ("Game_launch", "Custom_resolution_width", Screen -> Width) + " " + SettingsFile -> ReadString ("Game_launch", "Custom_resolution_height", Screen -> Height) + " " + IntToStr (i) + " " + IntToStr (j) + " 1");
      LinesVideoMode -> SaveToFile (GetGameDataPath () + "Data\\_LVL_PC\\vidmode.ini");
      LinesVideoMode -> Free ();
      //Saving settings for launcher
      TMemIniFile *LaunchData = new TMemIniFile (GetGameDataPath () + "SWBF1 launcher.ini");
      LaunchData -> WriteString ("CMD", "COMMAND_LINE", cmdline.Trim ());
      LaunchData -> WriteString ("IN_GAME_RESOLUTION", "WIDTH", SettingsFile -> ReadString ("Game_launch", "Custom_resolution_width", Screen -> Width));
      LaunchData -> WriteString ("IN_GAME_RESOLUTION", "HEIGHT", SettingsFile -> ReadString ("Game_launch", "Custom_resolution_height", Screen -> Height));
      LaunchData -> UpdateFile ();
      //Run game
      CreateProcess ((GetLauncherDataPath () + "Tools\\ResolutionChanger.exe").w_str (), L"",  0, 0, true, 0, 0, GetGameDataPath ().w_str (), &si, &pi);
      Sleep (2000);
      DeleteFile (GetGameDataPath () + "SWBF1 launcher.ini");
      LaunchData -> Free ();
     }
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
      //Set not readonly for file
      DWORD attr = GetFileAttributes (GetHostsFilePath ().w_str ());
      if (attr & FILE_ATTRIBUTE_READONLY) SetFileAttributes (GetHostsFilePath ().w_str (), attr ^ FILE_ATTRIBUTE_READONLY);
      //Save it
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

void __fastcall TFormMainMenu::FormShow (TObject *Sender)
 {
  TErrorSearchThread *ErrorSearchThread = new TErrorSearchThread (false);
  //Generate new Settings.ini if doesnt exists
  WriteNewStringToIniFile (SettingsFile, "Game_launch", "Window_mode", "false");
  WriteNewStringToIniFile (SettingsFile, "Game_launch", "Skip_logos", "false");
  WriteNewStringToIniFile (SettingsFile, "Game_launch", "Skip_startup_music", "false");
  WriteNewStringToIniFile (SettingsFile, "Game_launch", "Skip_menu_background", "false");
  WriteNewStringToIniFile (SettingsFile, "Game_launch", "Audio_buffer_enable", "false");
  WriteNewStringToIniFile (SettingsFile, "Game_launch", "Audio_buffer_ms", "200");
  WriteNewStringToIniFile (SettingsFile, "Game_launch", "Audio_rate_enable", "false");
  WriteNewStringToIniFile (SettingsFile, "Game_launch", "Audio_rate", "11000");
  WriteNewStringToIniFile (SettingsFile, "Game_launch", "Custom_resolution_enable", "true");
  WriteNewStringToIniFile (SettingsFile, "Game_launch", "Custom_resolution_width", Screen -> Width);
  WriteNewStringToIniFile (SettingsFile, "Game_launch", "Custom_resolution_height", Screen -> Height);
  WriteNewStringToIniFile (SettingsFile, "Language", "Name", "English");
  for (int i = 1; i <= 8; i++) WriteNewStringToIniFile (SettingsFile, "Language", "Message" + IntToStr (i), "");
  WriteNewStringToIniFile (SettingsFile, "Multiplayer", "Use_user_host", "true");
  WriteNewStringToIniFile (SettingsFile, "Multiplayer", "Host", "162.248.92.172");
  WriteNewStringToIniFile (SettingsFile, "Multiplayer", "Current_version", "1.2");
  if (SettingsFile -> ReadString ("Multiplayer", "Current_version", "1.2").Length () > 41)
   {
    SettingsFile -> WriteString ("Multiplayer", "Current_version", SettingsFile -> ReadString ("Multiplayer", "Current_version", "1.2").SubString (1, 41));
    ShowErrorM (LanguageStrings [21]);
   }
  bool QuickMessageError = false;
  for (int i = 1; i <= 8; i++)
    {
     if (SettingsFile -> ReadString ("Language", "Message" + IntToStr (i), LanguageStrings [69 + i]).Length () > 62)
      {
       SettingsFile -> WriteString ("Language", "Message" + IntToStr (i), SettingsFile -> ReadString ("Language", "Message" + IntToStr (i), LanguageStrings [69 + i]).SubString (1, 62));
       QuickMessageError = true;
      }
    }
  if (QuickMessageError) ShowErrorM (LanguageStrings [78]);
  SettingsFile -> UpdateFile ();
 }

//Search errors in addons
void __fastcall TErrorSearchThread::Execute ()
 {
  //Checking AddOn folder
  if (GetDirectoriesCount (GetAddOnPath ()) > CurrentAddonsLimit)
   {
    ErrorMessage = ReplaceStringMask (LanguageStrings [41], "number", CurrentAddonsLimit);
    Synchronize (ShowErr);
   }
  for (int i = 0; i < GetDirectoriesCount (GetAddOnPath ()); i++)
    {
     UnicodeString curAddonPath = TDirectory::GetDirectories (GetAddOnPath ()) [i];
     UnicodeString curAddonName = ExtractFileName (curAddonPath);
     if (!FileExists (curAddonPath + "\\addme.script"))
      {
       ErrorMessage = ReplaceStringMask (ReplaceStringMask (LanguageStrings [58], "name", "addme.script"), "addon", curAddonName);
       Synchronize (ShowErr);
      }
     if (!FileExists (curAddonPath + "\\Data\\_lvl_pc\\mission.lvl"))
      {
       ErrorMessage = ReplaceStringMask (ReplaceStringMask (LanguageStrings [58], "name", "mission.lvl"), "addon", curAddonName);
       Synchronize (ShowErr);
      }
     if (!FileExists (curAddonPath + "\\Data\\_lvl_pc\\core.lvl"))
      {
       ErrorMessage = ReplaceStringMask (ReplaceStringMask (LanguageStrings [58], "name", "core.lvl"), "addon", curAddonName);
       Synchronize (ShowErr);
      }
     if (!DirectoryExists (GetAllMapsPath () + curAddonName + "\\"))
      {
       ErrorMessage = ReplaceStringMask (LanguageStrings [59], "name", curAddonName);
       Synchronize (ShowErr);
      }
    }
  //Checking AllMAps folder
  for (int i = 0; i < GetDirectoriesCount (GetAllMapsPath ()); i++)
    {
     UnicodeString curAddonPath = TDirectory::GetDirectories (GetAllMapsPath ()) [i];
     UnicodeString curAddonName = ExtractFileName (curAddonPath);
     if (!FileExists (curAddonPath + "\\addme.script"))
      {
       ErrorMessage = ReplaceStringMask (ReplaceStringMask (LanguageStrings [58], "name", "addme.script"), "addon", curAddonName);
       Synchronize (ShowErr);
      }
     if (!FileExists (curAddonPath + "\\Data\\_lvl_pc\\mission.lvl"))
      {
       ErrorMessage = ReplaceStringMask (ReplaceStringMask (LanguageStrings [58], "name", "mission.lvl"), "addon", curAddonName);
       Synchronize (ShowErr);
      }
     if (!FileExists (curAddonPath + "\\Data\\_lvl_pc\\core.lvl"))
      {
       ErrorMessage = ReplaceStringMask (ReplaceStringMask (LanguageStrings [58], "name", "core.lvl"), "addon", curAddonName);
       Synchronize (ShowErr);
      }
     //Checking screens numbering
     if (DirectoryExists (GetAddOnScreensPath (curAddonName)))
      {
       for (int j = 0; j < GetFilesCount (GetAddOnScreensPath (curAddonName)); j++)
         {
          UnicodeString curScreenPath = GetAddOnScreensPath (curAddonName) + "scr_" + IntToStr (j) + ".jpg";
          if (!FileExists (curScreenPath))
           {
            ErrorMessage = ReplaceStringMask (ReplaceStringMask (LanguageStrings [60], "addon", curAddonName), "name", "scr_" + IntToStr (j) + ".jpg");
            Synchronize (ShowErr);
            break;
           }
         }
      }
    }
 }

//Show error from thread
void __fastcall TErrorSearchThread::ShowErr ()
 {
  ShowErrorM (ErrorMessage);
 }
