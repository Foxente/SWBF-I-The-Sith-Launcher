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
extern PACKAGE const int CurrentAddonsLimit;
extern PACKAGE const UnicodeString LauncherVersion;
extern PACKAGE const UnicodeString OfficialLanguages;
extern PACKAGE const UnicodeString CompilationDate;
extern PACKAGE const UnicodeString Author;
extern PACKAGE const UnicodeString OfficialTopic;
extern PACKAGE const UnicodeString FOXenteVk;
extern PACKAGE const UnicodeString GitHub;
extern PACKAGE const UnicodeString License;

//Api methods
UnicodeString GetGameDataPath ();
UnicodeString GetLauncherDataPath ();
UnicodeString GetBattlefrontExePath ();
UnicodeString GetAddOnPath ();
UnicodeString GetAllMapsPath ();
UnicodeString GetAddOnMapinfoPath (UnicodeString AddonName);
UnicodeString GetAddOnScreensPath (UnicodeString AddonName);
UnicodeString GetHostsFilePath ();
UnicodeString GetOnlyFileName (UnicodeString FilePath);
UnicodeString WriteNewStringToIniFile (TMemIniFile *IniFile, UnicodeString Section, UnicodeString Ident, UnicodeString Value);
UnicodeString ReplaceStringMask (UnicodeString CurrentString, UnicodeString Mask, UnicodeString Replacement);
UnicodeString GetAbsPath (UnicodeString Path);
String BoolToRealString (bool Value);
int GetFileCount (UnicodeString Path);
bool IsBattlefrontRunning ();
bool hasAddOnMapinfo (UnicodeString AddonName);
bool hasAddOnScreensFolder (UnicodeString AddonName);
void RequiredFileExists (UnicodeString FilePath);
void ApplyLanguageFromFile (UnicodeString FilePath);
void SetFormToScreenCenter (TForm* Form);
void UnvisibleForm (TForm* Form);
void ShowErrorM (UnicodeString Error);

#endif
