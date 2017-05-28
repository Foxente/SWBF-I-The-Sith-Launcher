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
    //Coping folder from AllMaps to AddOn
    TDirectory::Copy (GetAllMapsPath () + ProcessArguments [0], GetAddOnPath () + ProcessArguments [0]);
   }
  //Closing form
  Synchronize (FormClosing);
 }

void __fastcall TGlobalProcessThread::FormClosing ()
 {
  FormGlobalProcess -> Close ();
 }
