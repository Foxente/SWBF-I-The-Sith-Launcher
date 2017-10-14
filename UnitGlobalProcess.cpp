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
    TSearchRec SearchResult;
    for (int I = FindFirst (GetAllMapsPath () + ProcessArguments [0] + "\\Data\\_lvl_pc\\*", faAnyFile, SearchResult); !I; I = FindNext (SearchResult))
      {
       if ((SearchResult.Name == ".") || (SearchResult.Name == "..")) continue;
       //Compressed files
       if (ExtractFileExt (SearchResult.Name) == ".zip")
        {
         TZipForge *Archiver = new TZipForge (NULL);
         Archiver -> FileName = GetAllMapsPath () + ProcessArguments [0] + "\\Data\\_lvl_pc\\" + SearchResult.Name;
         Archiver -> OpenArchive ();
         Archiver -> BaseDir = GetAddOnPath () + ProcessArguments [0] + "\\Data\\_lvl_pc\\";
         Archiver -> ExtractFiles ("*");
        } else //other files and folders
        {
         if (SearchResult.Attr & faDirectory) TDirectory::Copy (GetAllMapsPath () + ProcessArguments [0] + "\\Data\\_lvl_pc\\" + SearchResult.Name, GetAddOnPath () + ProcessArguments [0] + "\\Data\\_lvl_pc\\" + SearchResult.Name);
         else CopyFile ((GetAllMapsPath () + ProcessArguments [0] + "\\Data\\_lvl_pc\\" + SearchResult.Name).w_str (), (GetAddOnPath () + ProcessArguments [0] + "\\Data\\_lvl_pc\\" + SearchResult.Name).w_str (), false);
        }
      }
    FindClose (SearchResult);
   } else
  if (ProcessId == 3)
   {
    UnicodeString LanguageName = SettingsFile -> ReadString ("Language", "Name", "English");
    //Changing quick messages
    TStringList *LangFile = new TStringList ();
    LangFile -> LoadFromFile (GetLauncherDataPath () + "Languages\\" + LanguageName + "\\core.lvl\\english.cfg");
    int DoneMessages = 0;
    bool DelNextLines = false;
    UnicodeString FullMessage;
    AnsiString HexMessage;
    for (int I = 0; DoneMessages < 8; I++)
      {
       if (LangFile -> Strings [I] == "      {")
        {
         DelNextLines = true;
         continue;
        }
       if (LangFile -> Strings [I] == "      }")
        {
         DelNextLines = false;
         DoneMessages += 1;
         FullMessage = SettingsFile -> ReadString ("Language", "Message" + IntToStr (DoneMessages), "");
         if (FullMessage == "") FullMessage = LanguageStrings [69 + DoneMessages];
         HexMessage = UnicodeStringToCFGFileHEX (FullMessage);
         LangFile -> Insert (I, "        Size(" + IntToStr (HexMessage.Length () / 2) + ");");
         while (HexMessage != "")
           {
            if (HexMessage.Length () > 64)
             {
              LangFile -> Insert (I + 1, "        Value(\"" + HexMessage.SubString (1, 64) + "\");");
              HexMessage = HexMessage.SubString (65, HexMessage.Length ());
              I += 1;
             } else
             {
              LangFile -> Insert (I + 1, "        Value(\"" + HexMessage + "\");");
              HexMessage = "";
              I += 1;
             }
           }
         I += 1;
         continue;
        }
       if (DelNextLines)
        {
         LangFile -> Delete (I);
         I -= 1;
        }
      }
    LangFile -> SaveToFile (GetLauncherDataPath () + "Languages\\" + LanguageName + "\\core.lvl\\english.cfg");
    LangFile -> Free ();
    //Compilation core.lvl
    //Copy fonts to Compilation folder
    TSearchRec SearchResult;
    for (int I = FindFirst (GetLauncherDataPath () + "Languages\\" + LanguageName + "\\core.lvl\\Fonts\\*.font", faAnyFile, SearchResult); !I; I = FindNext (SearchResult))
      {
       if (!(SearchResult.Attr & faDirectory)) CopyFile ((GetLauncherDataPath () + "Languages\\" + LanguageName + "\\core.lvl\\Fonts\\" + SearchResult.Name).w_str (), (GetLauncherDataPath () + "Compilation\\core.lvl\\output\\" + SearchResult.Name).w_str (), false); //Added files only
      }
    FindClose (SearchResult);
    //Compile .cfg -> loc
    STARTUPINFO StartupInfo;
    PROCESS_INFORMATION ProcesInfo;
    memset (&ProcesInfo, 0, sizeof (ProcesInfo));
    memset (&StartupInfo, 0, sizeof (StartupInfo));
    StartupInfo.cb = sizeof (StartupInfo);
    //Minimized window
    StartupInfo.dwFlags = STARTF_USESHOWWINDOW;
    StartupInfo.wShowWindow = false;
    CreateProcess ((GetLauncherDataPath () + "Tools\\LocalizeMunge.exe").w_str (), L" -inputfile english.cfg", 0, 0, true, 0, 0, (GetLauncherDataPath () + "Languages\\" + LanguageName + "\\core.lvl\\").w_str (), &StartupInfo, &ProcesInfo);
    WaitForSingleObject (ProcesInfo.hProcess, INFINITE);
    DeleteFile (GetLauncherDataPath () + "Languages\\" + LanguageName + "\\core.lvl\\.log");
    DeleteFile (GetLauncherDataPath () + "Compilation\\core.lvl\\output\\english.loc");
    MoveFile ((GetLauncherDataPath () + "Languages\\" + LanguageName + "\\core.lvl\\english.loc").w_str (), (GetLauncherDataPath () + "Compilation\\core.lvl\\output\\english.loc").w_str ());
    //Compile all files into core.lvl
    CreateProcess ((GetLauncherDataPath () + "Tools\\LevelPack.exe").w_str (), L" -sourcedir req\\ -platform pc -inputdir output\\ -outputdir .\\ -inputfile !*.req -continue", 0, 0, true, 0, 0, (GetLauncherDataPath () + "Compilation\\core.lvl\\").w_str (), &StartupInfo, &ProcesInfo);;
    WaitForSingleObject (ProcesInfo.hProcess, INFINITE);
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
