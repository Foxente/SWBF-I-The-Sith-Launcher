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

#include "UnitAddonsControl.h"
#include "API.h"

#include "UnitScreenZoom.h"
#include "UnitGlobalProcess.h"

#pragma package(smart_init)
#pragma link "sListBox"
#pragma link "sBitBtn"
#pragma link "sLabel"
#pragma link "acImage"
#pragma resource "*.dfm"

TFormAddonsControl *FormAddonsControl;

TsListBox *LastObject;
int CurScreenIndex;
String LastMapName;

__fastcall TFormAddonsControl::TFormAddonsControl (TComponent* Owner) : TForm(Owner)
 {
 }

//It is the main function which updates all information on this form
void ChangeInfo (TsListBox *Sender)
 {
  LastObject = Sender;
  FormAddonsControl -> sLabelAvailabledAddons -> Caption = ReplaceStringMask (LanguageStrings [28], "count", IntToStr (FormAddonsControl -> sListBoxAvailabledAddons -> Items -> Count));
  FormAddonsControl -> sLabelSelectedAddons -> Caption = ReplaceStringMask (LanguageStrings [29], "count", IntToStr (FormAddonsControl -> sListBoxSelectedAddons -> Items -> Count));
  //When viewing the information of a new map
  if ((LastObject -> ItemIndex > -1) && (LastObject -> Items -> Strings [LastObject -> ItemIndex] != LastMapName))
   {
    UnicodeString MapName = LastObject -> Items -> Strings [LastObject -> ItemIndex];
    //Update the map name
    FormAddonsControl -> sLabelMapName -> Caption = ReplaceStringMask (LanguageStrings [30], "name", MapName);
    FormAddonsControl -> sLabelMapInfo -> Caption = LanguageStrings [31] + " "; //Eras label
    //if addon has mapinfo.txt that we can get some map info
    if (hasAddOnMapinfo (MapName))
     {
      TStringList *mapinfo = new TStringList ();
      mapinfo -> LoadFromFile (GetAddOnMapinfoPath (MapName));
      if (mapinfo -> Count >= 1) //If the file has at least 1 line
       {
        //Divide the 1st line into arguments
        TStringList *line = new TStringList ();
        line -> Delimiter = ',';
        line -> StrictDelimiter = true;
        line -> DelimitedText = mapinfo -> Strings [0];
        if (line -> Count >= 7) //If the line has at least 7 arguments
         {
          //Filling 1 line of eras label
          if (line  -> Strings [0] == "CW") FormAddonsControl -> sLabelMapInfo -> Caption = FormAddonsControl -> sLabelMapInfo -> Caption + LanguageStrings [32]; //Clone Wars
          else FormAddonsControl -> sLabelMapInfo -> Caption = FormAddonsControl -> sLabelMapInfo -> Caption + LanguageStrings [33]; //Galactic Civil War
          //Adding additional data
          FormAddonsControl -> sLabelMapInfo -> Caption = FormAddonsControl -> sLabelMapInfo -> Caption + " (" + line -> Strings [3] + " [" + line -> Strings [5] + "]" + " / " + line -> Strings [4] + " [" + line -> Strings [6] + "])";
         }

        if (mapinfo -> Count >= 2) //If the file has at least 2 lines
         {
          //Divide the 2nd line into arguments
          TStringList *line = new TStringList ();
          line -> Delimiter = ',';
          line -> StrictDelimiter = true;
          line -> DelimitedText = mapinfo -> Strings [1];
          if (line -> Count >= 7) //If the line has at least 7 arguments
           {
            //Filling 2 line of eras label
            FormAddonsControl -> sLabelMapInfo -> Caption = FormAddonsControl -> sLabelMapInfo -> Caption + ((char) 13) + String (LanguageStrings [34]).Delete (LanguageStrings [34].Length (), 1).Delete (1, 1); //Go to a new line and add indent
            if (line  -> Strings [0] == "CW") FormAddonsControl -> sLabelMapInfo -> Caption = FormAddonsControl -> sLabelMapInfo -> Caption + LanguageStrings [32]; //Clone Wars
            else FormAddonsControl -> sLabelMapInfo -> Caption = FormAddonsControl -> sLabelMapInfo -> Caption + LanguageStrings [33]; //Galactic Civil War
            //Adding additional data
            FormAddonsControl -> sLabelMapInfo -> Caption = FormAddonsControl -> sLabelMapInfo -> Caption + " (" + line -> Strings [3] + " [" + line -> Strings [5] + "]" + " / " + line -> Strings [4] + " [" + line -> Strings [6] + "])";
           }
         }
       }
     }
    //if eras are not filled then we write an unknown
    if (FormAddonsControl -> sLabelMapInfo -> Caption == LanguageStrings [31] + " ") FormAddonsControl -> sLabelMapInfo -> Caption = FormAddonsControl -> sLabelMapInfo -> Caption + LanguageStrings [35];
    //Load the 0 screen and activate visible/enable of buttons
    CurScreenIndex = 0;
    if (hasAddOnScreensFolder (MapName))
     {
      FormAddonsControl -> sImageMiniScreen -> Picture -> LoadFromFile (GetAddOnScreensPath (MapName) + "scr_0.jpg");
      FormAddonsControl -> sBitBtnPrevious -> Enabled = false;
      FormAddonsControl -> sBitBtnNext -> Enabled = false;
      if (FileExists (GetAddOnScreensPath (MapName) + "scr_1.jpg"))
       {
        FormAddonsControl -> sBitBtnPrevious -> Enabled = true;
        FormAddonsControl -> sBitBtnNext -> Enabled = true;
       }
      FormAddonsControl -> sBitBtnPrevious -> Visible = true;
      FormAddonsControl -> sBitBtnNext -> Visible = true;
      FormAddonsControl -> sBitBtnZoom -> Enabled = true;
      FormAddonsControl -> sBitBtnZoom -> Visible = true;
     } else
     //Disble butons and clean picture
     {
      FormAddonsControl -> sImageMiniScreen -> Picture = NULL;
      FormAddonsControl -> sBitBtnPrevious -> Enabled = false;
      FormAddonsControl -> sBitBtnPrevious -> Visible = false;
      FormAddonsControl -> sBitBtnNext -> Enabled = false;
      FormAddonsControl -> sBitBtnNext -> Visible = false;
      FormAddonsControl -> sBitBtnZoom -> Enabled = false;
      FormAddonsControl -> sBitBtnZoom -> Visible = false;
     }
    LastMapName = MapName;
   }
  //If ListBox doesnt have any selected element
  if (LastObject -> ItemIndex == -1)
   {
    FormAddonsControl -> sLabelMapName -> Caption = ReplaceStringMask (LanguageStrings [30], "name", LanguageStrings [35]);
    FormAddonsControl -> sLabelMapInfo -> Caption = LanguageStrings [31] + " " + LanguageStrings [35];
    FormAddonsControl -> sImageMiniScreen -> Picture = NULL;
    FormAddonsControl -> sBitBtnPrevious -> Enabled = false;
    FormAddonsControl -> sBitBtnPrevious -> Visible = false;
    FormAddonsControl -> sBitBtnNext -> Enabled = false;
    FormAddonsControl -> sBitBtnNext -> Visible = false;
    FormAddonsControl -> sBitBtnZoom -> Enabled = false;
    FormAddonsControl -> sBitBtnZoom -> Visible = false;
    LastMapName = "";
    CurScreenIndex = 0;
   }
 }

void __fastcall TFormAddonsControl::FormShow (TObject *Sender)
 {
  //Cleaning listboxes
  sListBoxAvailabledAddons -> Clear ();
  sListBoxSelectedAddons -> Clear ();
  //Uploading all selected maps
  TSearchRec sr;
  for (int i = FindFirst (GetAddOnPath () + "*", faDirectory, sr); !i; i = FindNext (sr))
    {
     if ((sr.Name == ".") || (sr.Name == "..")) continue;
     if (sr.Attr & faDirectory) sListBoxSelectedAddons -> Items -> Add (sr.Name); //Added folders only
    }
  FindClose (sr);
  //Uploading all available maps
  for (int i = FindFirst (GetAllMapsPath () + "*", faDirectory, sr); !i; i = FindNext (sr))
    {
     if ((sr.Name == ".") || (sr.Name == "..") || (sListBoxSelectedAddons -> Items -> IndexOf (sr.Name) > -1)) continue;
     if (sr.Attr & faDirectory) sListBoxAvailabledAddons -> Items -> Add (sr.Name); //Added folders only
    }
  FindClose (sr);
  //Update all labels, images and etc.
  ChangeInfo (sListBoxSelectedAddons);
 }

//Changing info in that moment when user clicks on any sListBox
void __fastcall TFormAddonsControl::sListBoxesClick (TObject *Sender)
 {
  ChangeInfo ((TsListBox*) Sender);
 }

//Opening previous screen
void __fastcall TFormAddonsControl::sBitBtnPreviousClick (TObject *Sender)
 {
  CurScreenIndex -= 1;
  if (!FileExists (GetAddOnScreensPath (LastObject -> Items -> Strings [LastObject -> ItemIndex]) + "scr_" + IntToStr (CurScreenIndex) + ".jpg"))
   CurScreenIndex = GetFileCount (GetAddOnScreensPath (LastObject -> Items -> Strings [LastObject -> ItemIndex])) - 1;
  sImageMiniScreen -> Picture -> LoadFromFile (GetAddOnScreensPath (LastObject -> Items -> Strings [LastObject -> ItemIndex]) + "scr_" + IntToStr (CurScreenIndex) + ".jpg");
 }

//Opening the next screen
void __fastcall TFormAddonsControl::sBitBtnNextClick (TObject *Sender)
 {
  CurScreenIndex += 1;
  if (!FileExists (GetAddOnScreensPath (LastObject -> Items -> Strings [LastObject -> ItemIndex]) + "scr_" + IntToStr (CurScreenIndex) + ".jpg"))
   CurScreenIndex = 0;
  sImageMiniScreen -> Picture -> LoadFromFile (GetAddOnScreensPath (LastObject -> Items -> Strings [LastObject -> ItemIndex]) + "scr_" + IntToStr (CurScreenIndex) + ".jpg");
 }

void __fastcall TFormAddonsControl::sBitBtnZoomClick (TObject *Sender)
 {
  FormScreenZoom -> ShowModal ();
 }

//Unsellect map
void __fastcall TFormAddonsControl::sBitBtnUnselectClick (TObject *Sender)
 {
  if (sListBoxSelectedAddons -> ItemIndex != -1)
   {
    int curIndex = sListBoxSelectedAddons -> ItemIndex;
    UnicodeString MapName = sListBoxSelectedAddons -> Items -> Strings [sListBoxSelectedAddons -> ItemIndex];
    //Creating thread
    ProcessName = LanguageStrings [38];
    ProcessId = 1;
    ProcessArguments [0] = GetAddOnPath () + MapName;
    FormGlobalProcess -> ShowModal ();
    //Updating information
    sListBoxAvailabledAddons -> Items -> Add (MapName);
    sListBoxAvailabledAddons -> ItemIndex = sListBoxAvailabledAddons -> Items -> IndexOf (MapName);
    sListBoxSelectedAddons -> Items -> Delete (sListBoxSelectedAddons -> ItemIndex);
    if (sListBoxSelectedAddons -> Items -> Count - 1 < curIndex) curIndex -= 1;
    sListBoxSelectedAddons -> ItemIndex = curIndex;
    ChangeInfo (sListBoxSelectedAddons);
   }
 }

//Sellect map
void __fastcall TFormAddonsControl::sBitBtnSelectClick (TObject *Sender)
 {
  if (sListBoxAvailabledAddons -> ItemIndex != -1)
   {
    if (sListBoxSelectedAddons -> Count >= CurrentAddonsLimit)
     {
      ShowErrorM (ReplaceStringMask (LanguageStrings [41], "number", IntToStr (CurrentAddonsLimit)));
     } else
     {
      int curIndex = sListBoxAvailabledAddons -> ItemIndex;
      UnicodeString MapName = sListBoxAvailabledAddons -> Items -> Strings [sListBoxAvailabledAddons -> ItemIndex];
      //Creating thread
      ProcessName = LanguageStrings [39];
      ProcessId = 2;
      ProcessArguments [0] =  MapName;
      FormGlobalProcess -> ShowModal ();
      //Updating information
      sListBoxSelectedAddons -> Items -> Add (MapName);
      sListBoxSelectedAddons -> ItemIndex = sListBoxSelectedAddons -> Items -> IndexOf (MapName);
      sListBoxAvailabledAddons -> Items -> Delete (sListBoxAvailabledAddons -> ItemIndex);
      if (sListBoxAvailabledAddons -> Items -> Count - 1 < curIndex) curIndex -= 1;
      sListBoxAvailabledAddons -> ItemIndex = curIndex;
      ChangeInfo (sListBoxAvailabledAddons);
     }
   }
 }

 //Open the addon in folder
void __fastcall TFormAddonsControl::sBitBtnOpenExplorerClick (TObject *Sender)
 {
  if (LastObject -> ItemIndex > -1)
   {
    //Open addon in AddOn
    if (LastObject == sListBoxAvailabledAddons) ShellExecute (Handle, L"open", (GetAllMapsPath () + LastObject -> Items -> Strings [LastObject -> ItemIndex]).w_str (), NULL, NULL, SW_RESTORE);
    //Open addon in AllMaps
    else ShellExecute (Handle, L"open", (GetAddOnPath () + LastObject -> Items -> Strings [LastObject -> ItemIndex]).w_str (), NULL, NULL, SW_SHOW);
   }
 }

