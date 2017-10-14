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

#ifndef APIH
#define APIH

#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>

#include <IniFiles.hpp>
#include <Registry.hpp>
#include <IOUtils.hpp>
#include <StrUtils.hpp>

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
extern PACKAGE const int CURRENT_ADDONS_LIMIT;
extern PACKAGE const UnicodeString LAUNCHER_VERSION;
extern PACKAGE const UnicodeString OFFICIAL_LANGUAGES;
extern PACKAGE const UnicodeString COMPILATION_DATE;
extern PACKAGE const UnicodeString AUTHOR;
extern PACKAGE const UnicodeString OFFICIAL_TOPIC;
extern PACKAGE const UnicodeString FOXENTE_VK;
extern PACKAGE const UnicodeString GITHUB;
extern PACKAGE const UnicodeString LICENSE;

//Api methods
UnicodeString GetGameDataPath ();
UnicodeString GetLauncherDataPath ();
UnicodeString GetBattlefrontExePath ();
UnicodeString GetAddOnPath ();
UnicodeString GetAllMapsPath ();
UnicodeString GetAddOnMapinfoPath (UnicodeString AddonName);
UnicodeString GetAddOnScreensPath (UnicodeString AddonName);
UnicodeString GetAddOnModesPath (UnicodeString AddonName);
UnicodeString GetHostsFilePath ();
UnicodeString GetOnlyFileName (UnicodeString FilePath);
UnicodeString WriteNewStringToIniFile (TMemIniFile *IniFile, UnicodeString Section, UnicodeString Ident, UnicodeString Value);
UnicodeString ReplaceStringMask (UnicodeString CurrentString, UnicodeString Mask, UnicodeString Replacement);
UnicodeString GetAbsPath (UnicodeString Path);
AnsiString UnicodeStringToCFGFileHEX (UnicodeString Text);
String BoolToRealString (bool Value);
int GetFilesCount (UnicodeString Path);
int GetDirectoriesCount (UnicodeString Path);
bool IsBattlefrontRunning ();
bool HasAddOnMapinfo (UnicodeString AddonName);
bool HasAddOnScreensFolder (UnicodeString AddonName);
bool HasAddOnModesFolder (UnicodeString AddonName);
bool IsRequiredFileExists (UnicodeString FilePath);
void ApplyLanguageFromFile (UnicodeString FilePath);
void SetFormToScreenCenter (TForm* Form);
void UnvisibleForm (TForm* Form);
void ShowErrorMessage (UnicodeString Error);

#endif
