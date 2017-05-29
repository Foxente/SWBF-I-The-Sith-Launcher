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
   }
  //Closing form
  Synchronize (FormClosing);
 }

void __fastcall TGlobalProcessThread::FormClosing ()
 {
  FormGlobalProcess -> Close ();
 }
