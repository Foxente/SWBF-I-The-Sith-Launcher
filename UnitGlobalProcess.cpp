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
#include <System.hpp>
#pragma hdrstop

#include "UnitGlobalProcess.h"
#include "API.h"

#pragma package(smart_init)
#pragma link "sLabel"
#pragma resource "*.dfm"

TFormGlobalProcess *FormGlobalProcess;

int ProcessId;
UnicodeString ProcessName;
UnicodeString ProcessArguments [10];

__fastcall TFormGlobalProcess::TFormGlobalProcess (TComponent* Owner) : TForm (Owner)
 {
 }

__fastcall TGlobalProcessThread::TGlobalProcessThread (bool CreateSuspended) : TThread (CreateSuspended)
 {
 }

void __fastcall TFormGlobalProcess::FormShow (TObject *Sender)
 {
  Caption = ReplaceStringMask (LanguageStrings [37], "name", ProcessName);
  SetFormToScreenCenter (FormGlobalProcess);
  //Running thread
  TGlobalProcessThread *GlobalProcessThread = new TGlobalProcessThread (false);
 }

void __fastcall TGlobalProcessThread::Execute ()
 {
  FreeOnTerminate = true;
  if (ProcessId == 1)
   {
    //Deleting folder from AddOn
    TDirectory::Delete (ProcessArguments [0], true);
   } else
  if (ProcessId == 2)
   {
    //Coping some files from AllMaps to AddOn
    TDirectory::CreateDirectoryW (GetAddOnPath () + ProcessArguments [0] + "\\Data\\_lvl_pc\\");
    CopyFile ((GetAllMapsPath () + ProcessArguments [0] + "\\addme.script").w_str (), (GetAddOnPath () + ProcessArguments [0] + "\\addme.script").w_str (), false);
    //Unpacking or coping main addon files
    TSearchRec sr;
    for (int i = FindFirst (GetAllMapsPath () + ProcessArguments [0] + "\\Data\\_lvl_pc\\*", faAnyFile, sr); !i; i = FindNext (sr))
      {
       if ((sr.Name == ".") || (sr.Name == "..")) continue;
       //Compressed files
       if (ExtractFileExt (sr.Name) == ".zip")
        {
         TZipForge *Archiver = new TZipForge (NULL);
         Archiver -> FileName = GetAllMapsPath () + ProcessArguments [0] + "\\Data\\_lvl_pc\\" + sr.Name;
         Archiver -> OpenArchive ();
         Archiver -> BaseDir = GetAddOnPath () + ProcessArguments [0] + "\\Data\\_lvl_pc\\";
         Archiver -> ExtractFiles ("*");
        } else //other files and folders
        {
         if (sr.Attr & faDirectory) TDirectory::Copy (GetAllMapsPath () + ProcessArguments [0] + "\\Data\\_lvl_pc\\" + sr.Name, GetAddOnPath () + ProcessArguments [0] + "\\Data\\_lvl_pc\\" + sr.Name);
         else CopyFile ((GetAllMapsPath () + ProcessArguments [0] + "\\Data\\_lvl_pc\\" + sr.Name).w_str (), (GetAddOnPath () + ProcessArguments [0] + "\\Data\\_lvl_pc\\" + sr.Name).w_str (), false);
        }
      }
    FindClose (sr);
   } else
  if (ProcessId == 3)
   {
    UnicodeString LanguageName = SettingsFile -> ReadString ("Language", "Name", "English");
    //Changing quick messages
    TStringList *LangFile = new TStringList ();
    LangFile -> LoadFromFile (GetLauncherDataPath () + "Languages\\" + LanguageName + "\\core.lvl\\localize.cfg");
    int DoneMessages = 0;
    bool DelNextLines = false;
    UnicodeString FullMessage;
    AnsiString HexMessage;
    for (int i = 0; DoneMessages < 8; i++)
      {
       if (LangFile -> Strings [i] == "      {")
        {
         DelNextLines = true;
         continue;
        }
       if (LangFile -> Strings [i] == "      }")
        {
         DelNextLines = false;
         DoneMessages += 1;
         FullMessage = SettingsFile -> ReadString ("Language", "Message" + IntToStr (DoneMessages), "");
         if (FullMessage == "") FullMessage = LanguageStrings [69 + DoneMessages];
         HexMessage = UnicodeStringToCFGFileHEX (FullMessage);
         LangFile -> Insert (i, "        Value(\"" + HexMessage + "\");");
         LangFile -> Insert (i, "        Size(" + IntToStr (HexMessage.Length () / 2) + ");");
         i += 2;
         continue;
        }
       if (DelNextLines)
        {
         LangFile -> Delete (i);
         i -= 1;
        }
      }
    LangFile -> SaveToFile (GetLauncherDataPath () + "Languages\\" + LanguageName + "\\core.lvl\\localize.cfg");
    //Compilation core.lvl
    //Copy fonts to Compilation folder
    TSearchRec sr;
    for (int i = FindFirst (GetLauncherDataPath () + "Languages\\" + LanguageName + "\\core.lvl\\Fonts\\*.font", faAnyFile, sr); !i; i = FindNext (sr))
      {
       if (!(sr.Attr & faDirectory)) CopyFile ((GetLauncherDataPath () + "Languages\\" + LanguageName + "\\core.lvl\\Fonts\\" + sr.Name).w_str (), (GetLauncherDataPath () + "Compilation\\core.lvl\\output\\" + sr.Name).w_str (), false); //Added files only
      }
    FindClose (sr);
    //Compile .cfg -> loc
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    memset (&pi, 0, sizeof (pi));
    memset (&si, 0, sizeof (si));
    si.cb = sizeof (si);
    //Minimized window
    si.dwFlags = STARTF_USESHOWWINDOW;
    si.wShowWindow = false;
    RenameFile (GetLauncherDataPath () + "Languages\\" + LanguageName + "\\core.lvl\\localize.cfg", GetLauncherDataPath () + "Languages\\" + LanguageName + "\\core.lvl\\english.cfg");
    CreateProcess ((GetLauncherDataPath () + "Tools\\LocalizeMunge.exe").w_str (), L" -inputfile english.cfg", 0, 0, true, 0, 0, (GetLauncherDataPath () + "Languages\\" + LanguageName + "\\core.lvl\\").w_str (), &si, &pi);
    WaitForSingleObject (pi.hProcess, INFINITE);
    RenameFile (GetLauncherDataPath () + "Languages\\" + LanguageName + "\\core.lvl\\english.cfg", GetLauncherDataPath () + "Languages\\" + LanguageName + "\\core.lvl\\localize.cfg");
    DeleteFile (GetLauncherDataPath () + "Languages\\" + LanguageName + "\\core.lvl\\.log");
    DeleteFile (GetLauncherDataPath () + "Compilation\\core.lvl\\output\\english.loc");
    MoveFile ((GetLauncherDataPath () + "Languages\\" + LanguageName + "\\core.lvl\\english.loc").w_str (), (GetLauncherDataPath () + "Compilation\\core.lvl\\output\\english.loc").w_str ());
    //Compile all files into core.lvl
    CreateProcess ((GetLauncherDataPath () + "Tools\\LevelPack.exe").w_str (), L" -sourcedir req\\ -platform pc -inputdir output\\ -outputdir .\\ -inputfile !*.req -continue", 0, 0, true, 0, 0, (GetLauncherDataPath () + "Compilation\\core.lvl\\").w_str (), &si, &pi);;
    WaitForSingleObject (pi.hProcess, INFINITE);
    DeleteFile (GetLauncherDataPath () + "Compilation\\core.lvl\\.log");
    DeleteFile (GetGameDataPath () + "Data\\_LVL_PC\\core.lvl");
    MoveFile ((GetLauncherDataPath () + "Compilation\\core.lvl\\core.lvl").w_str (), (GetGameDataPath () + "Data\\_LVL_PC\\core.lvl").w_str ());
   }
  //Closing form
  Synchronize (FormClosing);
 }

void __fastcall TGlobalProcessThread::FormClosing ()
 {
  FormGlobalProcess -> Close ();
 }
