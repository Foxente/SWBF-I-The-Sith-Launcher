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

#include "API.h"

#include "UnitLogo.h"
#include "UnitMainMenu.h"
#include "UnitSettings.h"
#include "UnitAddonsControl.h"
#include "UnitScreenZoom.h"
#include "UnitGlobalProcess.h"
#include "UnitAboutLauncher.h"
#include "UnitSelectMapMode.h"

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

//Consts
const int CURRENT_ADDONS_LIMIT = 26; //ToDo Try to fix it using 1.3 version
const UnicodeString LAUNCHER_VERSION = "0.7 BETA";
const UnicodeString OFFICIAL_LANGUAGES = "English / Русский";
const UnicodeString COMPILATION_DATE = "05.06.2017 13:07";
//Don't change theese consts
const UnicodeString AUTHOR = "FOXente (Aradam)";
const UnicodeString OFFICIAL_TOPIC = "tinyium.com/30Kp";
const UnicodeString FOXENTE_VK = "bluenik.com/2cdS";
const UnicodeString GITHUB = "bluenik.com/2cdN";
const UnicodeString LICENSE = "GPL-3.0";

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

//Get Battlefront.exe path
UnicodeString GetBattlefrontExePath ()
 {
  return GetGameDataPath () + "Battlefront.exe";
 }

//Get Addon directory path
UnicodeString GetAddOnPath ()
 {
  return GetGameDataPath () + "AddOn\\";
 }

//Get Allmaps directory path
UnicodeString GetAllMapsPath ()
 {
  return GetLauncherDataPath () + "AllMaps\\";
 }

//Get addon's mapinfo file's path
UnicodeString GetAddOnMapinfoPath (UnicodeString AddonName)
 {
  return GetAllMapsPath () + AddonName + "\\mapinfo.txt";
 }

//Get addon's screens folder path
UnicodeString GetAddOnScreensPath (UnicodeString AddonName)
 {
  return GetAllMapsPath () + AddonName + "\\Screens\\";
 }

//Get addon's modes folder path
UnicodeString GetAddOnModesPath (UnicodeString AddonName)
 {
  return GetAllMapsPath () + AddonName + "\\Modes\\";
 }

//Get hosts file's path
UnicodeString GetHostsFilePath ()
 {
  TRegistry *Registry = new TRegistry (KEY_READ | KEY_WOW64_64KEY);
  Registry -> RootKey = HKEY_LOCAL_MACHINE;
  // Win NT, 2000, XP, 2003, Vista, 7, 8, 10
  if (Registry -> OpenKeyReadOnly ("SYSTEM\\CurrentControlSet\\Services\\Tcpip\\Parameters"))
   {
    return GetAbsPath (Registry -> ReadString ("DataBasePath")) + "\\hosts";
   }
  // Win Mobile
  if (Registry -> OpenKeyReadOnly ("Comm\\Tcpip"))
   {
    return GetAbsPath (Registry -> ReadString ("Hosts")) + "\\hosts";
   }
  // Win 95, 98, Me
  if (FileExists (GetAbsPath ("%windir%\\hosts"))) return GetAbsPath ("%windir%\\hosts");
  if (FileExists (GetAbsPath ("%SystemDrive%\\Windows\\System32\\drivers\\etc\\hosts"))) return GetAbsPath ("%SystemDrive%\\Windows\\System32\\drivers\\etc\\hosts");
  //else
  return "C:\\WINDOWS\\system32\\drivers\\etc\\hosts";
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

//Get absolute path from environnment string
UnicodeString GetAbsPath (UnicodeString Path)
 {
  const int BUFFER_SIZE = 4096;
  wchar_t ReturnPath [BUFFER_SIZE] = {0};
  ExpandEnvironmentStrings (Path.w_str (), ReturnPath, BUFFER_SIZE);
  return UnicodeString (ReturnPath);
 }

//Convert any unicode string to hex string like in SWBF cdg files
AnsiString UnicodeStringToCFGFileHEX (UnicodeString Text)
 {
  AnsiString Result;
  for (int I = 1; I <= Text.Length (); I++)
    {
     Result += AnsiReverseString (IntToHex (Text [I], 4));
    }
  return "20000000" + Result;
 }

//Converte boolean to string type
String BoolToRealString (bool Value)
 {
  if (Value) return "true"; else return "false";
 }

//Get file count in folder
int GetFilesCount (UnicodeString Path)
 {
  return TDirectory::GetFiles (Path).Length;
 }

//Get directories count in folder
int GetDirectoriesCount (UnicodeString Path)
 {
  return TDirectory::GetDirectories (Path).Length;
 }

//Checking is Battlefront.exe running
bool IsBattlefrontRunning ()
 {
  return FindWindow (NULL, L"Star Wars Battlefront") != 0;
 }

//Checking is addon has mapinfo.txt
bool HasAddOnMapinfo (UnicodeString AddonName)
 {
  return FileExists (GetAddOnMapinfoPath (AddonName));
 }

//Checking is addon has screens
bool HasAddOnScreensFolder (UnicodeString AddonName)
 {
  return DirectoryExists (GetAddOnScreensPath (AddonName));
 }

//Checking is addon has additional modes
bool HasAddOnModesFolder (UnicodeString AddonName)
 {
  return DirectoryExists (GetAddOnModesPath (AddonName));
 }

//If file doesn't exists that will be error shown and the application terminate
bool IsRequiredFileExists (UnicodeString FilePath)
 {
  if (!FileExists (FilePath))
   {
    ShowErrorMessage (ReplaceStringMask (LanguageStrings [1], "path", FilePath));
    return false;
   } else return true;
 }

//Apply new program's language from file
void ApplyLanguageFromFile (UnicodeString FilePath)
 {
  //Loading of language
  //Last LanguageStrings index = 81
  LanguageFile = new TMemIniFile (FilePath);
  LanguageStrings [2] = WriteNewStringToIniFile (LanguageFile, "FormCaption", "Name", "SWBF I The Sith Launcher");
  LanguageStrings [0] = WriteNewStringToIniFile (LanguageFile, "FormCaption", "Logo", "Created by %name%");
  LanguageStrings [7] = WriteNewStringToIniFile (LanguageFile, "FormCaption", "Settings", "Settings");
  LanguageStrings [36] = WriteNewStringToIniFile (LanguageFile, "FormCaption", "ScreenViewer", "Screen Viewer");
  LanguageStrings [37] = WriteNewStringToIniFile (LanguageFile, "FormCaption", "Process", "Process is in progress: %name%");
  LanguageStrings [54] = WriteNewStringToIniFile (LanguageFile, "FormCaption", "MapMode", "Select map mode");
  LanguageStrings [1] = WriteNewStringToIniFile (LanguageFile, "Error", "1", "File '%path%' doesn't exists!");
  LanguageStrings [21] = WriteNewStringToIniFile (LanguageFile, "Error", "2", "The version identifier must be no more than 41 characters long!");
  LanguageStrings [41] = WriteNewStringToIniFile (LanguageFile, "Error", "3", "SWBF limit of simultaneously installed maps - %number%. Exceeding the limit threatens the inability of some maps and crash games!");
  LanguageStrings [58] = WriteNewStringToIniFile (LanguageFile, "Error", "4", "File '%name%' is missing in the addon '%addon%'!");
  LanguageStrings [59] = WriteNewStringToIniFile (LanguageFile, "Error", "5", "Map '%name%' exists only in the AddOn folder. Copy it to AllMaps folder!");
  LanguageStrings [60] = WriteNewStringToIniFile (LanguageFile, "Error", "6", "Listing screenshots in the addon '%addon%' is wrong. File '%name%' doesn't exist!");
  LanguageStrings [78] = WriteNewStringToIniFile (LanguageFile, "Error", "7", "The length of a quick message should not exceed 62 characters!");
  LanguageStrings [81] = WriteNewStringToIniFile (LanguageFile, "Error", "8", "Put the game files into GameData folder!");
  LanguageStrings [3] = WriteNewStringToIniFile (LanguageFile, "Button", "1", "Play");
  LanguageStrings [4] = WriteNewStringToIniFile (LanguageFile, "Button", "2", "Set additional maps");
  LanguageStrings [5] = WriteNewStringToIniFile (LanguageFile, "Button", "3", "About %name%");
  LanguageStrings [8] = WriteNewStringToIniFile (LanguageFile, "Button", "4", "Save");
  LanguageStrings [9] = WriteNewStringToIniFile (LanguageFile, "Button", "5", "Cancel");
  LanguageStrings [22] = WriteNewStringToIniFile (LanguageFile, "Button", "6", "Download");
  LanguageStrings [23] = WriteNewStringToIniFile (LanguageFile, "Button", "7", "Video instruction");
  LanguageStrings [6] = WriteNewStringToIniFile (LanguageFile, "Label", "1", "Coming Soon");
  LanguageStrings [10] = WriteNewStringToIniFile (LanguageFile, "Label", "2", "Launch settings");
  LanguageStrings [11] = WriteNewStringToIniFile (LanguageFile, "Label", "3", "Multiplayer settings");
  LanguageStrings [19] = WriteNewStringToIniFile (LanguageFile, "Label", "4", "The current version identifier of the game");
  LanguageStrings [20] = WriteNewStringToIniFile (LanguageFile, "Label", "5", "Global LAN network");
  LanguageStrings [28] = WriteNewStringToIniFile (LanguageFile, "Label", "6", "Available maps (%count%):");
  LanguageStrings [29] = WriteNewStringToIniFile (LanguageFile, "Label", "7", "Selected maps (%count%):");
  LanguageStrings [30] = WriteNewStringToIniFile (LanguageFile, "Label", "8", "Name: %name%");
  LanguageStrings [31] = WriteNewStringToIniFile (LanguageFile, "Label", "9", "Eras:");
  LanguageStrings [32] = WriteNewStringToIniFile (LanguageFile, "Label", "10", "Clone Wars");
  LanguageStrings [33] = WriteNewStringToIniFile (LanguageFile, "Label", "11", "Galactic Civil War");
  LanguageStrings [34] = WriteNewStringToIniFile (LanguageFile, "Label", "12", "|          |");
  LanguageStrings [35] = WriteNewStringToIniFile (LanguageFile, "Label", "13", "Unknown");
  LanguageStrings [40] = WriteNewStringToIniFile (LanguageFile, "Label", "14", "Wait a bit...");
  LanguageStrings [56] = WriteNewStringToIniFile (LanguageFile, "Label", "15", "Language settings");
  LanguageStrings [57] = WriteNewStringToIniFile (LanguageFile, "Label", "16", "Current language");
  LanguageStrings [61] = WriteNewStringToIniFile (LanguageFile, "Label", "17", "Quick messages:");
  LanguageStrings [80] = WriteNewStringToIniFile (LanguageFile, "Label", "18", "pixels");
  LanguageStrings [12] = WriteNewStringToIniFile (LanguageFile, "CheckBox", "1", "Run the game in the windowed mode");
  LanguageStrings [13] = WriteNewStringToIniFile (LanguageFile, "CheckBox", "2", "Skip logos and splash screens");
  LanguageStrings [14] = WriteNewStringToIniFile (LanguageFile, "CheckBox", "3", "Skip music at startup");
  LanguageStrings [15] = WriteNewStringToIniFile (LanguageFile, "CheckBox", "4", "Disable the animated background in the menu");
  LanguageStrings [16] = WriteNewStringToIniFile (LanguageFile, "CheckBox", "5", "Size of audio buffer (milliseconds)");
  LanguageStrings [17] = WriteNewStringToIniFile (LanguageFile, "CheckBox", "6", "Sound quality");
  LanguageStrings [18] = WriteNewStringToIniFile (LanguageFile, "CheckBox", "7", "Host of servers (Internet)");
  LanguageStrings [79] = WriteNewStringToIniFile (LanguageFile, "CheckBox", "8", "In-game resolution");
  LanguageStrings [24] = WriteNewStringToIniFile (LanguageFile, "Link", "TunngleDownload", "http://tinyium.com/30Lb");
  LanguageStrings [25] = WriteNewStringToIniFile (LanguageFile, "Link", "TunngleVideoInstruction", "http://tinyium.com/30Ld");
  LanguageStrings [26] = WriteNewStringToIniFile (LanguageFile, "Link", "GameRangerDownload", "http://tinyium.com/30Lg");
  LanguageStrings [27] = WriteNewStringToIniFile (LanguageFile, "Link", "GameRangerInstruction", "");
  LanguageStrings [38] = WriteNewStringToIniFile (LanguageFile, "Process", "1", "Deletion");
  LanguageStrings [39] = WriteNewStringToIniFile (LanguageFile, "Process", "2", "Copying");
  LanguageStrings [55] = WriteNewStringToIniFile (LanguageFile, "Process", "3", "Compilation");
  LanguageStrings [42] = WriteNewStringToIniFile (LanguageFile, "Information", "1", "The game Star Wars Battlefront I belongs to @ 2004 Lucasfilm Entertainment Company, LLC.");
  LanguageStrings [43] = WriteNewStringToIniFile (LanguageFile, "Information", "2", "%projectname% was developed by @ 2017 %name%.");
  LanguageStrings [44] = WriteNewStringToIniFile (LanguageFile, "Information", "3", "The copyright for additional maps (addons) belongs to the creators of these maps.");
  LanguageStrings [45] = WriteNewStringToIniFile (LanguageFile, "Information", "4", "Launcher Version: %number%");
  LanguageStrings [46] = WriteNewStringToIniFile (LanguageFile, "Information", "5", "Languages Of The Project: %names%");
  LanguageStrings [47] = WriteNewStringToIniFile (LanguageFile, "Information", "6", "Compilation Date: %date%");
  LanguageStrings [48] = WriteNewStringToIniFile (LanguageFile, "Information", "7", "Developer: %name%");
  LanguageStrings [49] = WriteNewStringToIniFile (LanguageFile, "Information", "8", "Official topic on SWBFGamers.com: %link%");
  LanguageStrings [50] = WriteNewStringToIniFile (LanguageFile, "Information", "9", "FOXEnte in vk.com: %link%");
  LanguageStrings [51] = WriteNewStringToIniFile (LanguageFile, "Information", "10", "%name% - software for SWBF I. Allows you to manage addons and extends the number of gaming opportunities.");
  LanguageStrings [52] = WriteNewStringToIniFile (LanguageFile, "Information", "11", "Contacting Me (%name%):");
  LanguageStrings [53] = WriteNewStringToIniFile (LanguageFile, "Information", "12", "Source Code: %link% (%license%)");
  LanguageStrings [62] = WriteNewStringToIniFile (LanguageFile, "QuickMessage", "Title1", "FOLLOW ME!");
  LanguageStrings [63] = WriteNewStringToIniFile (LanguageFile, "QuickMessage", "Title2", "DEFEND THIS POSITION!");
  LanguageStrings [64] = WriteNewStringToIniFile (LanguageFile, "QuickMessage", "Title3", "FALL BACK!");
  LanguageStrings [65] = WriteNewStringToIniFile (LanguageFile, "QuickMessage", "Title4", "ENEMY SIGHTED!");
  LanguageStrings [66] = WriteNewStringToIniFile (LanguageFile, "QuickMessage", "Title5", "GRENADE!");
  LanguageStrings [67] = WriteNewStringToIniFile (LanguageFile, "QuickMessage", "Title6", "PICK ME UP!");
  LanguageStrings [68] = WriteNewStringToIniFile (LanguageFile, "QuickMessage", "Title7", "I NEED AMMO!");
  LanguageStrings [69] = WriteNewStringToIniFile (LanguageFile, "QuickMessage", "Title8", "I NEED HEALTH!");
  LanguageStrings [70] = WriteNewStringToIniFile (LanguageFile, "QuickMessage", "1", "FOLLOW ME!");
  LanguageStrings [71] = WriteNewStringToIniFile (LanguageFile, "QuickMessage", "2", "DEFEND THIS POSITION!");
  LanguageStrings [72] = WriteNewStringToIniFile (LanguageFile, "QuickMessage", "3", "FALL BACK!");
  LanguageStrings [73] = WriteNewStringToIniFile (LanguageFile, "QuickMessage", "4", "ENEMY SIGHTED!");
  LanguageStrings [74] = WriteNewStringToIniFile (LanguageFile, "QuickMessage", "5", "GRENADE!");
  LanguageStrings [75] = WriteNewStringToIniFile (LanguageFile, "QuickMessage", "6", "PICK ME UP!");
  LanguageStrings [76] = WriteNewStringToIniFile (LanguageFile, "QuickMessage", "7", "I NEED AMMO!");
  LanguageStrings [77] = WriteNewStringToIniFile (LanguageFile, "QuickMessage", "8", "I NEED HEALTH!");
  LanguageFile -> UpdateFile ();
  //Apply
  FormLogo -> Caption = LanguageStrings [2];
  FormMainMenu -> Caption = LanguageStrings [2];
  FormMainMenu -> sBitBtnPlay -> Caption = LanguageStrings [3];
  FormMainMenu -> sBitBtnSetAdditionalMap -> Caption = LanguageStrings [4];
  FormMainMenu -> sBitBtnAboutLauncher -> Caption = ReplaceStringMask (LanguageStrings [5], "name", LanguageStrings [2]);
  FormMainMenu -> sLabelComingSoon -> Caption = LanguageStrings [6];
  FormAddonsControl -> Caption = LanguageStrings [4];
  FormSettings -> Caption = LanguageStrings [7];
  FormSettings -> sBitBtnSave -> Caption = LanguageStrings [8];
  FormSettings -> sBitBtnCancel -> Caption = LanguageStrings [9];
  FormSettings -> sLabelLaunchSettings -> Caption = LanguageStrings [10];
  FormSettings -> sLabeMultiplayerSettings -> Caption = LanguageStrings [11];
  FormSettings -> sCheckBoxWindowedMode -> Caption = LanguageStrings [12];
  FormSettings -> sCheckBoxSkipSpalshScreens -> Caption = LanguageStrings [13];
  FormSettings -> sCheckBoxSkipStartupMusic -> Caption = LanguageStrings [14];
  FormSettings -> sCheckBoxDisableAnimatedMenuBackground -> Caption = LanguageStrings [15];
  FormSettings -> sCheckBoxAudioBufferSize -> Caption = LanguageStrings [16];
  FormSettings -> sCheckBoxSoundQuality -> Caption = LanguageStrings [17];
  FormSettings -> sCheckBoxInternetHost -> Caption = LanguageStrings [18];
  FormSettings -> sCheckBoxGameResolution -> Caption = LanguageStrings [79];
  FormSettings -> sLabelCurrentGameVersion -> Caption = LanguageStrings [19];
  FormSettings -> sLabelLANNetwork -> Caption = LanguageStrings [20];
  FormSettings -> sBitBtnDownloadTunngle -> Caption = LanguageStrings [22];
  FormSettings -> sBitBtnTunngleVideo -> Caption = LanguageStrings [23];
  FormSettings -> sBitBtnDownloadGameRanger -> Caption = LanguageStrings [22];
  FormSettings -> sBitBtnGameRangerVideo -> Caption = LanguageStrings [23];
  FormSettings -> sLabelLanguageSettings -> Caption = LanguageStrings [56];
  FormSettings -> sLabelGeneralLanguage -> Caption = LanguageStrings [57];
  FormSettings -> sLabelMessagesText -> Caption = LanguageStrings [61];
  FormSettings -> sLabelPixels -> Caption = LanguageStrings [80];
  int CurIndex = FormSettings -> sComboBoxSelectingMessage -> ItemIndex;
  FormSettings -> sComboBoxSelectingMessage -> Clear ();
  for (int I = 62; I <= 69; I++) FormSettings -> sComboBoxSelectingMessage -> Items -> Add (LanguageStrings [I]);
  FormSettings -> sComboBoxSelectingMessage -> ItemIndex = CurIndex;
  FormScreenZoom -> Caption = LanguageStrings [36];
  FormGlobalProcess -> sLabelWait -> Caption = LanguageStrings [40];
  FormSelectMapMode -> Caption = LanguageStrings [54];
  FormAboutLauncher -> Caption = FormMainMenu -> sBitBtnAboutLauncher -> Caption;
  FormAboutLauncher -> sRichEditInfo -> Lines -> Clear ();
  FormAboutLauncher -> sRichEditInfo -> Lines -> Add (LanguageStrings [42]);
  FormAboutLauncher -> sRichEditInfo -> Lines -> Add (ReplaceStringMask (ReplaceStringMask (LanguageStrings [43], "name", AUTHOR), "projectname", LanguageStrings [2]));
  FormAboutLauncher -> sRichEditInfo -> Lines -> Add (LanguageStrings [44]);
  FormAboutLauncher -> sRichEditInfo -> Lines -> Add ("");
  FormAboutLauncher -> sRichEditInfo -> Lines -> Add (ReplaceStringMask (LanguageStrings [51], "name", LanguageStrings [2]));
  FormAboutLauncher -> sRichEditInfo -> Lines -> Add (ReplaceStringMask (ReplaceStringMask (LanguageStrings [53], "link", GITHUB), "license", LICENSE));
  FormAboutLauncher -> sRichEditInfo -> Lines -> Add ("");
  FormAboutLauncher -> sRichEditInfo -> Lines -> Add (ReplaceStringMask (LanguageStrings [45], "number", LAUNCHER_VERSION));
  FormAboutLauncher -> sRichEditInfo -> Lines -> Add (ReplaceStringMask (LanguageStrings [46], "names", OFFICIAL_LANGUAGES));
  FormAboutLauncher -> sRichEditInfo -> Lines -> Add (ReplaceStringMask (LanguageStrings [47], "date", COMPILATION_DATE));
  FormAboutLauncher -> sRichEditInfo -> Lines -> Add (ReplaceStringMask (LanguageStrings [48], "name", AUTHOR));
  FormAboutLauncher -> sRichEditInfo -> Lines -> Add ("");
  FormAboutLauncher -> sRichEditInfo -> Lines -> Add (ReplaceStringMask (LanguageStrings [49], "link", OFFICIAL_TOPIC));
  FormAboutLauncher -> sRichEditInfo -> Lines -> Add (ReplaceStringMask (LanguageStrings [50], "link", FOXENTE_VK));
  FormAboutLauncher -> sRichEditInfo -> Lines -> Add ("");
  FormAboutLauncher -> sRichEditInfo -> Lines -> Add (ReplaceStringMask (LanguageStrings [52], "name", "Aradam"));
  FormAboutLauncher -> sRichEditInfo -> Lines -> Add ("Mail: aradam@o-coder.pp.ua");
  FormAboutLauncher -> sRichEditInfo -> Lines -> Add ("PM: microify.com/2f2X");
  FormAboutLauncher -> sRichEditInfo -> Lines -> Add ("VK: microify.com/2f2a");
  FormAboutLauncher -> sRichEditInfo -> Lines -> Add ("OK: microify.com/2f2h");
  FormAboutLauncher -> sRichEditInfo -> Lines -> Add ("Facebook: microify.com/2f2m");
  FormAboutLauncher -> sRichEditInfo -> Lines -> Add ("Telegram: microify.com/2f2o");
  FormAboutLauncher -> sRichEditInfo -> Lines -> Add ("Gitter: microify.com/2f2r");
  FormAboutLauncher -> sRichEditInfo -> Lines -> Add ("Twitter: microify.com/2f2t");
  //Changing elements positions
  FormMainMenu -> sLabelComingSoon -> Left = (FormMainMenu -> Width - FormMainMenu -> sLabelComingSoon -> Width) / 2; //change pos for this label to center of form with
  FormSettings -> sEditMilliseconds -> Left = FormSettings -> sCheckBoxAudioBufferSize -> Left + FormSettings -> sCheckBoxAudioBufferSize -> Width + 5;
  FormSettings -> sTrackBarSoundQuality -> Left = FormSettings -> sCheckBoxSoundQuality -> Left + FormSettings -> sCheckBoxSoundQuality -> Width + 5;
  FormSettings -> sLabelCurQuality -> Left = FormSettings -> sTrackBarSoundQuality -> Left + FormSettings -> sTrackBarSoundQuality -> Width + 5;
  FormSettings -> sLabelMinQuality -> Left = FormSettings -> sTrackBarSoundQuality -> Left;
  FormSettings -> sLabelMaxQuality -> Left = FormSettings -> sTrackBarSoundQuality -> Left + FormSettings -> sTrackBarSoundQuality -> Width - FormSettings -> sLabelMaxQuality -> Width;
  FormSettings -> sEditHost -> Left = FormSettings -> sCheckBoxInternetHost -> Left + FormSettings -> sCheckBoxInternetHost -> Width + 5;
  FormSettings -> sEditVersion -> Left = FormSettings -> sLabelCurrentGameVersion -> Left + FormSettings -> sLabelCurrentGameVersion -> Width + 8;
  FormSettings -> sBitBtnDownloadTunngle -> Left = FormSettings -> sLabelLANNetwork -> Left + FormSettings -> sLabelLANNetwork -> Width;
  FormSettings -> sBitBtnTunngleVideo -> Left = FormSettings -> sBitBtnDownloadTunngle -> Left;
  FormSettings -> sImageTunngle -> Left = FormSettings -> sBitBtnDownloadTunngle -> Left + FormSettings -> sBitBtnDownloadTunngle -> Width / 2 - FormSettings -> sImageTunngle -> Width / 2;
  FormSettings -> sLabelTunngle -> Left = FormSettings -> sBitBtnDownloadTunngle -> Left + FormSettings -> sBitBtnDownloadTunngle -> Width / 2 - FormSettings -> sLabelTunngle -> Width / 2;
  FormSettings -> sBitBtnDownloadGameRanger -> Left = FormSettings -> sBitBtnDownloadTunngle -> Left + 130;
  FormSettings -> sBitBtnGameRangerVideo -> Left = FormSettings -> sBitBtnDownloadGameRanger -> Left;
  FormSettings -> sImageGameRanger -> Left = FormSettings -> sImageTunngle -> Left + 130;
  FormSettings -> sLabelGameRanger -> Left = FormSettings -> sBitBtnDownloadGameRanger -> Left + FormSettings -> sBitBtnDownloadGameRanger -> Width / 2 - FormSettings -> sLabelGameRanger -> Width / 2;
  FormSettings -> sComboBoxLanguages -> Left = FormSettings -> sLabelGeneralLanguage -> Left + FormSettings -> sLabelGeneralLanguage -> Width + 8;
  FormSettings -> sComboBoxSelectingMessage -> Left = FormSettings -> sLabelMessagesText -> Left + FormSettings -> sLabelMessagesText -> Width + 5;
  FormSettings -> sEditMessageText -> Left = FormSettings -> sComboBoxSelectingMessage -> Left + FormSettings -> sComboBoxSelectingMessage -> Width + 5;
  FormSettings -> sEditWidth -> Left = FormSettings -> sCheckBoxGameResolution -> Left + FormSettings -> sCheckBoxGameResolution -> Width + 5;
  FormSettings -> sLabelResolutionDelimiter -> Left = FormSettings -> sEditWidth -> Left + FormSettings -> sEditWidth -> Width + 5;
  FormSettings -> sEditHeight -> Left = FormSettings -> sLabelResolutionDelimiter -> Left + FormSettings -> sLabelResolutionDelimiter -> Width + 5;
  FormSettings -> sLabelPixels -> Left = FormSettings -> sEditHeight -> Left + FormSettings -> sEditHeight -> Width + 5;
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
void ShowErrorMessage (UnicodeString Error)
 {
  Application -> MessageBox (Error.c_str (), UnicodeString ("ERROR").c_str (), MB_OK);
 }
