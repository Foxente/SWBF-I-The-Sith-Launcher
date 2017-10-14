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
    //Check all required files
	TStringList *RequiredFileList = new TStringList ();
	RequiredFileList -> Add (GetBattlefrontExePath ());
	RequiredFileList -> Add (GetGameDataPath () + "binkw32.dll");
	RequiredFileList -> Add (GetGameDataPath () + "eax.dll");
	RequiredFileList -> Add (GetGameDataPath () + "unicows.dll");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\BES\\bes1.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\BES\\bes2.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\Common\\ENG\\common.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\END\\end1.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\ALL\\allcldcr.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\ALL\\allcmspd.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\ALL\\allcmspg.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\ALL\\allhthmk.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\ALL\\allhthtr.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\ALL\\allhvrnt.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\ALL\\allkwing.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\ALL\\allmarks.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\ALL\\allmedic.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\ALL\\allpilot.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\ALL\\allsccam.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\ALL\\allsspdr.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\ALL\\alltaun.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\ALL\\alltroop.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\ALL\\allwook.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\ALL\\allxwing.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\ALL\\allywing.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\ALL\\gunsspdr.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\ALL\\repgunnr.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\CIS\\cisaatp.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\CIS\\cisbdrd.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\CIS\\cisdrde.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\CIS\\cishlfrd.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\CIS\\cismafp.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\CIS\\cismttp.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\CIS\\cissbdrd.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\CIS\\cissccam.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\CIS\\cisspdrw.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\CIS\\cisstapp.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\CIS\\cisstrft.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\CIS\\repgunnr.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\Com\\comallre.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\Com\\comcisim.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\Com\\comgntrt.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\Com\\comgunnr.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\Com\\comhview.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\Com\\comunive.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\Com\\comviewf.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\IMP\\allxwing.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\IMP\\atst.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\IMP\\impatat.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\IMP\\impatatg.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\IMP\\impatstg.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\IMP\\impdark.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\IMP\\impftrtk.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\IMP\\impimplc.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\IMP\\impoff.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\IMP\\imppilot.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\IMP\\impsccam.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\IMP\\impscout.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\IMP\\impsntr.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\IMP\\impspbk.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\IMP\\impstrp.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\IMP\\imptibmr.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\IMP\\imptiftr.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\IMP\\repgunnr.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\REP\\allxwing.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\REP\\reparc.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\REP\\repatted.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\REP\\repatxtp.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\REP\\repcmspd.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\REP\\repftrtk.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\REP\\repgunnr.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\REP\\repgunsh.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\REP\\repguntr.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\REP\\rephtrop.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\REP\\repjedfi.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\REP\\repjettp.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\REP\\repmedic.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\REP\\reppilot.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\REP\\repsccam.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\REP\\repsharp.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\REP\\repspbk.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\FPM\\REP\\reptroop.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\GEO\\geo1.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\HOT\\hot1.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\KAM\\kam1.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\KAS\\kas1.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\KAS\\kas2.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\KAS\\kas2_h.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\Load\\bes1.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\Load\\bes2.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\Load\\end1.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\Load\\geo1.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\Load\\hot1.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\Load\\kam1.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\Load\\kas1.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\Load\\kas2.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\Load\\load.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\Load\\nab1.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\Load\\nab2.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\Load\\rhn1.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\Load\\rhn2.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\Load\\tat1.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\Load\\tat2.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\Load\\yav1.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\core.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\mission.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\SIDE\\geo.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\SIDE\\gun.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\SIDE\\imp.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\SIDE\\rep.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\SIDE\\wok.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\Shell\\ENG\\shell.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\Sound\\bes.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\Sound\\common.bnk");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\Sound\\cw.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\Sound\\end.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\Sound\\gcw.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\Sound\\geo.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\Sound\\hot.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\Sound\\kam.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\Sound\\kas.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\Sound\\nab.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\Sound\\rhn.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\Sound\\shell.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\Sound\\tat.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\Sound\\yav.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\TAT\\tat1.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\TAT\\tat1h.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\TAT\\tat2.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\YAV\\yav1.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\YAV\\yav2.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\YAV\\yav2_h.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\NAB\\nab1_h.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\NAB\\nab2.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\NAB\\nab2_h.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\RHN\\Rhn1.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\RHN\\Rhn2.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\Load\\yav2.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\Movies\\shell.mvs");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\NAB\\nab1.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\SIDE\\all.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\SIDE\\cis.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\SIDE\\ewk.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\SIDE\\des.lvl");
	RequiredFileList -> Add (GetGameDataPath () + "Data\\_LVL_PC\\SIDE\\gar.lvl");
	for (int I = 0; I < RequiredFileList -> Count; I++)
	  {
	   if (!IsRequiredFileExists (RequiredFileList -> Strings [1]))
		{
		 ShowErrorMessage (LanguageStrings [81]);
         RequiredFileList -> Free ();
		 return;
		}
	  }
	RequiredFileList -> Free ();
    //Patching .exe for changing game version
	TFileStream *Stream = new TFileStream (GetBattlefrontExePath (), fmOpenReadWrite | fmShareDenyWrite);
	Stream -> Position = 0x2AF12C;
    AnsiString NewVersion = SettingsFile -> ReadString ("Multiplayer", "Current_version", "1.2");
    Stream -> Write (&NewVersion [1], NewVersion.Length () + 1);
	Stream -> Free ();
    //Launch the game
	UnicodeString CmdLine = "";
	if (SettingsFile -> ReadString ("Game_launch", "Window_mode", "false") == "true") CmdLine += " /win";
	if (SettingsFile -> ReadString ("Game_launch", "Skip_logos", "false") == "true") CmdLine += " /nointro";
	if (SettingsFile -> ReadString ("Game_launch", "Skip_startup_music", "false") == "true") CmdLine += " /nostartupmusic";
	if (SettingsFile -> ReadString ("Game_launch", "Skip_menu_background", "false") == "true") CmdLine += " /nomovies";
	if (SettingsFile -> ReadString ("Game_launch", "Audio_buffer_enable", "false") == "true") CmdLine += " /audiomixbuffer " + SettingsFile -> ReadString ("Game_launch", "Audio_buffer_ms", "200");
	if (SettingsFile -> ReadString ("Game_launch", "Audio_rate_enable", "false") == "true") CmdLine += " /audiosamplerate " + SettingsFile -> ReadString ("Game_launch", "Audio_rate", "11000");
    //Run the game
	STARTUPINFO StartupInfo;
	PROCESS_INFORMATION ProcesInfo;
	memset (&ProcesInfo, 0, sizeof (ProcesInfo));
	memset (&StartupInfo, 0, sizeof (StartupInfo));
	StartupInfo.cb = sizeof (StartupInfo);
	//Run game without changing resolution
    if ((SettingsFile -> ReadString ("Game_launch", "Custom_resolution_enable", "true") == "false") || (!FileExists (GetGameDataPath () + "Data\\_LVL_PC\\vidmode.ini")))
	 {
	  CreateProcess (GetBattlefrontExePath ().w_str (), CmdLine.w_str (),  0, 0, true, 0, 0, GetGameDataPath ().w_str (), &StartupInfo, &ProcesInfo);
     } else //Run game using Battlebelk's Custom Resolution Launcher
     {
      //Generate vidmode.ini
	  TStringList *LinesVideoMode = new TStringList ();
	  LinesVideoMode -> LoadFromFile (GetGameDataPath () + "Data\\_LVL_PC\\vidmode.ini");
      String Device = LinesVideoMode -> Strings [0];
      LinesVideoMode -> Clear ();
      LinesVideoMode -> Add (Device);
	  for (int I = 0; I <= 16; I++)
		for (int J = 0; J <= 16; J++) LinesVideoMode -> Add (SettingsFile -> ReadString ("Game_launch", "Custom_resolution_width", Screen -> Width) + " " + SettingsFile -> ReadString ("Game_launch", "Custom_resolution_height", Screen -> Height) + " " + IntToStr (I) + " " + IntToStr (J) + " 1");
      LinesVideoMode -> SaveToFile (GetGameDataPath () + "Data\\_LVL_PC\\vidmode.ini");
      LinesVideoMode -> Free ();
      //Saving settings for launcher
      TMemIniFile *LaunchData = new TMemIniFile (GetGameDataPath () + "SWBF1 launcher.ini");
      LaunchData -> WriteString ("CMD", "COMMAND_LINE", CmdLine.Trim ());
      LaunchData -> WriteString ("IN_GAME_RESOLUTION", "WIDTH", SettingsFile -> ReadString ("Game_launch", "Custom_resolution_width", Screen -> Width));
      LaunchData -> WriteString ("IN_GAME_RESOLUTION", "HEIGHT", SettingsFile -> ReadString ("Game_launch", "Custom_resolution_height", Screen -> Height));
      LaunchData -> UpdateFile ();
      //Run game
	  CreateProcess ((GetLauncherDataPath () + "Tools\\ResolutionChanger.exe").w_str (), L"",  0, 0, true, 0, 0, GetGameDataPath ().w_str (), &StartupInfo, &ProcesInfo);
      Sleep (2000);
      DeleteFile (GetGameDataPath () + "SWBF1 launcher.ini");
      LaunchData -> Free ();
     }
    //Patching hosts file for Internet multiplayer game
    if (SettingsFile -> ReadString ("Multiplayer", "Use_user_host", "true") == "true")
     {
	  TStringList *OldDomens = new TStringList ();
	  OldDomens -> Delimiter = ' ';
	  OldDomens -> DelimitedText = "swbfrontpc.ms4.gamespy.com swbfrontpc.available.gamespy.com available.gamespy.com master.gamespy.com swbfrontpc.master.gamespy.com key.gamespy.com peerchat.gamespy.com gpsp.gamespy.com gpcm.gamespy.com natneg1.gamespy.com swbfront2pc.ms4.gamespy.com swbfront2pc.ms5.gamespy.com swbfront2pc.ms6.gamespy.com swbfront2pc.available.gamespy.com swbfront2pc.master.gamespy.com natneg2.gamespy.com swbfront2pc.gamestats.gamespy.com gamestats.gamespy.com swbfrontps2.ms10.gamespy.com swbfrontps2.available.gamespy.com swbfrontps2.master.gamespy.com swbfront2ps2.ms4.gamespy.com swbfront2ps2.available.gamespy.com swbfront2ps2.master.gamespy.com";
	  TStringList *Hosts = new TStringList ();
	  Hosts -> LoadFromFile (GetHostsFilePath ());
      //Get start and end positions for cyclic pass
	  int StartPos = Hosts -> IndexOf ("#Star Wars Battlefront Multiplayer Servers");
      int EndPos;
      if (StartPos == -1)
       {
        StartPos = Hosts -> Count - 1;
        EndPos = 0;
       } else
       {
        EndPos = StartPos;
        StartPos = EndPos + OldDomens -> Count;
		if (StartPos > Hosts -> Count - 1) StartPos = Hosts -> Count - 1;
       }
      //Cyclic pass for deleting exists swbf domens
	  for (int I = StartPos; I >= EndPos; I--)
        {
		 for (int J = 0; J <= OldDomens -> Count - 1; J++)
           {
			if ((Hosts -> Strings [I].Pos (OldDomens -> Strings [J]) > 0) || (Hosts -> Strings [I] == "#Star Wars Battlefront Multiplayer Servers"))
             {
			  Hosts -> Delete (I);
              break;
             }
           }
        }
      //Cyclic pass for adding redirects for old swbf domens
	  Hosts -> Add ("#Star Wars Battlefront Multiplayer Servers");
	  for (int I = 0; I <= OldDomens -> Count - 1; I++)
        {
		 Hosts -> Add (SettingsFile -> ReadString ("Multiplayer", "Host", "162.248.92.172") + " " + OldDomens -> Strings [I]);
        }
      //Set not readonly for file
	  DWORD Attributes = GetFileAttributes (GetHostsFilePath ().w_str ());
	  if (Attributes & FILE_ATTRIBUTE_READONLY) SetFileAttributes (GetHostsFilePath ().w_str (), Attributes ^ FILE_ATTRIBUTE_READONLY);
      //Save it
	  Hosts -> SaveToFile (GetHostsFilePath ());
	  Hosts -> Free ();
      OldDomens -> Free ();
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
  for (int I = 1; I <= 8; I++) WriteNewStringToIniFile (SettingsFile, "Language", "Message" + IntToStr (I), "");
  WriteNewStringToIniFile (SettingsFile, "Multiplayer", "Use_user_host", "true");
  WriteNewStringToIniFile (SettingsFile, "Multiplayer", "Host", "162.248.92.172");
  WriteNewStringToIniFile (SettingsFile, "Multiplayer", "Current_version", "1.2");
  if (SettingsFile -> ReadString ("Multiplayer", "Current_version", "1.2").Length () > 41)
   {
    SettingsFile -> WriteString ("Multiplayer", "Current_version", SettingsFile -> ReadString ("Multiplayer", "Current_version", "1.2").SubString (1, 41));
    ShowErrorMessage (LanguageStrings [21]);
   }
  bool QuickMessageError = false;
  for (int I = 1; I <= 8; I++)
    {
	 if (SettingsFile -> ReadString ("Language", "Message" + IntToStr (I), LanguageStrings [69 + I]).Length () > 62)
	  {
	   SettingsFile -> WriteString ("Language", "Message" + IntToStr (I), SettingsFile -> ReadString ("Language", "Message" + IntToStr (I), LanguageStrings [69 + I]).SubString (1, 62));
       QuickMessageError = true;
      }
    }
  if (QuickMessageError) ShowErrorMessage (LanguageStrings [78]);
  SettingsFile -> UpdateFile ();
 }

//Search errors in addons
void __fastcall TErrorSearchThread::Execute ()
 {
  //Checking AddOn folder
  if (GetDirectoriesCount (GetAddOnPath ()) > CURRENT_ADDONS_LIMIT)
   {
    ErrorMessage = ReplaceStringMask (LanguageStrings [41], "number", CURRENT_ADDONS_LIMIT);
    Synchronize (ShowErr);
   }
  for (int I = 0; I < GetDirectoriesCount (GetAddOnPath ()); I++)
    {
	 UnicodeString CurAddonPath = TDirectory::GetDirectories (GetAddOnPath ()) [I];
	 UnicodeString CurAddonName = ExtractFileName (CurAddonPath);
	 if (!FileExists (CurAddonPath + "\\addme.script"))
	  {
	   ErrorMessage = ReplaceStringMask (ReplaceStringMask (LanguageStrings [58], "name", "addme.script"), "addon", CurAddonName);
       Synchronize (ShowErr);
      }
	 if (!FileExists (CurAddonPath + "\\Data\\_lvl_pc\\mission.lvl"))
      {
	   ErrorMessage = ReplaceStringMask (ReplaceStringMask (LanguageStrings [58], "name", "mission.lvl"), "addon", CurAddonName);
       Synchronize (ShowErr);
      }
	 if (!FileExists (CurAddonPath + "\\Data\\_lvl_pc\\core.lvl"))
      {
	   ErrorMessage = ReplaceStringMask (ReplaceStringMask (LanguageStrings [58], "name", "core.lvl"), "addon", CurAddonName);
       Synchronize (ShowErr);
      }
	 if (!DirectoryExists (GetAllMapsPath () + CurAddonName + "\\"))
      {
	   ErrorMessage = ReplaceStringMask (LanguageStrings [59], "name", CurAddonName);
       Synchronize (ShowErr);
      }
    }
  //Checking AllMAps folder
  for (int I = 0; I < GetDirectoriesCount (GetAllMapsPath ()); I++)
    {
	 UnicodeString CurAddonPath = TDirectory::GetDirectories (GetAllMapsPath ()) [I];
	 UnicodeString CurAddonName = ExtractFileName (CurAddonPath);
	 if (!FileExists (CurAddonPath + "\\addme.script"))
	  {
	   ErrorMessage = ReplaceStringMask (ReplaceStringMask (LanguageStrings [58], "name", "addme.script"), "addon", CurAddonName);
       Synchronize (ShowErr);
      }
	 if (!FileExists (CurAddonPath + "\\Data\\_lvl_pc\\mission.lvl"))
      {
	   ErrorMessage = ReplaceStringMask (ReplaceStringMask (LanguageStrings [58], "name", "mission.lvl"), "addon", CurAddonName);
       Synchronize (ShowErr);
      }
	 if (!FileExists (CurAddonPath + "\\Data\\_lvl_pc\\core.lvl"))
      {
	   ErrorMessage = ReplaceStringMask (ReplaceStringMask (LanguageStrings [58], "name", "core.lvl"), "addon", CurAddonName);
       Synchronize (ShowErr);
      }
     //Checking screens numbering
     if (DirectoryExists (GetAddOnScreensPath (CurAddonName)))
      {
	   for (int J = 0; J < GetFilesCount (GetAddOnScreensPath (CurAddonName)); J++)
         {
		  UnicodeString CurScreenPath = GetAddOnScreensPath (CurAddonName) + "scr_" + IntToStr (J) + ".jpg";
          if (!FileExists (CurScreenPath))
           {
			ErrorMessage = ReplaceStringMask (ReplaceStringMask (LanguageStrings [60], "addon", CurAddonName), "name", "scr_" + IntToStr (J) + ".jpg");
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
  ShowErrorMessage (ErrorMessage);
 }
