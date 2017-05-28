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

#include "UnitScreenZoom.h"
#include "API.h"

#include "UnitAddonsControl.h"

#pragma package(smart_init)
#pragma link "acImage"
#pragma link "sBitBtn"
#pragma resource "*.dfm"

TFormScreenZoom *FormScreenZoom;

__fastcall TFormScreenZoom::TFormScreenZoom (TComponent* Owner) : TForm (Owner)
 {
 }

//Load image from file and change form size
void ShowImage ()
 {
  UnicodeString Path = GetAddOnScreensPath (LastObject -> Items -> Strings [LastObject -> ItemIndex]) + "scr_" + IntToStr (CurScreenIndex) + ".jpg";
  FormScreenZoom -> sImageFullScreen -> AutoSize = true;
  FormScreenZoom -> sImageFullScreen -> Picture -> LoadFromFile (Path);
  FormScreenZoom -> sImageFullScreen -> AutoSize = false;
  //Change image size if image over then screen size
  if (FormScreenZoom -> sImageFullScreen -> Height > Screen -> Height) FormScreenZoom -> sImageFullScreen -> Height = Screen -> Height;
  if (FormScreenZoom -> sImageFullScreen -> Width > Screen -> Width) FormScreenZoom -> sImageFullScreen -> Width = Screen -> Width;
  //Change form sise like in image
  FormScreenZoom -> Height = FormScreenZoom -> sImageFullScreen -> Height;
  FormScreenZoom -> Width = FormScreenZoom -> sImageFullScreen -> Width;
 }

//Previous screen
void __fastcall TFormScreenZoom::sBitBtnPreviousClick (TObject *Sender)
 {
  FormAddonsControl -> sBitBtnPreviousClick (NULL);
  ShowImage ();
 }

//Next screen
void __fastcall TFormScreenZoom::sBitBtnNextClick (TObject *Sender)
 {
  FormAddonsControl -> sBitBtnNextClick (NULL);
  ShowImage ();
 }

void __fastcall TFormScreenZoom::FormShow (TObject *Sender)
 {
  //Set form above the rest
  SetWindowPos (Handle, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE);
  //Load image
  ShowImage ();
  //Set position to screen center
  SetFormToScreenCenter (FormScreenZoom);
 }

