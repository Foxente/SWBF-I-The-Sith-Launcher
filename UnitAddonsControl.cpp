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
#include "UnitSelectMapMode.h"

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
    if (HasAddOnMapinfo (MapName))
     {
      TStringList *MapInfo = new TStringList ();
      MapInfo -> LoadFromFile (GetAddOnMapinfoPath (MapName));
      if (MapInfo -> Count >= 1) //If the file has at least 1 line
       {
        //Divide the 1st line into arguments
        TStringList *Line = new TStringList ();
        Line -> Delimiter = ',';
        Line -> StrictDelimiter = true;
        Line -> DelimitedText = MapInfo -> Strings [0];
        if (Line -> Count >= 7) //If the line has at least 7 arguments
         {
          //Filling 1 line of eras label
          if (Line  -> Strings [0] == "CW") FormAddonsControl -> sLabelMapInfo -> Caption = FormAddonsControl -> sLabelMapInfo -> Caption + LanguageStrings [32]; //Clone Wars
          else FormAddonsControl -> sLabelMapInfo -> Caption = FormAddonsControl -> sLabelMapInfo -> Caption + LanguageStrings [33]; //Galactic Civil War
          //Adding additional data
          FormAddonsControl -> sLabelMapInfo -> Caption = FormAddonsControl -> sLabelMapInfo -> Caption + " (" + Line -> Strings [3] + " [" + Line -> Strings [5] + "]" + " / " + Line -> Strings [4] + " [" + Line -> Strings [6] + "])";
         }

        if (MapInfo -> Count >= 2) //If the file has at least 2 lines
         {
          //Divide the 2nd line into arguments
          TStringList *line = new TStringList ();
          Line -> Delimiter = ',';
          Line -> StrictDelimiter = true;
          Line -> DelimitedText = MapInfo -> Strings [1];
          if (Line -> Count >= 7) //If the line has at least 7 arguments
           {
            //Filling 2 line of eras label
            FormAddonsControl -> sLabelMapInfo -> Caption = FormAddonsControl -> sLabelMapInfo -> Caption + ((char) 13) + String (LanguageStrings [34]).Delete (LanguageStrings [34].Length (), 1).Delete (1, 1); //Go to a new line and add indent
            if (Line  -> Strings [0] == "CW") FormAddonsControl -> sLabelMapInfo -> Caption = FormAddonsControl -> sLabelMapInfo -> Caption + LanguageStrings [32]; //Clone Wars
            else FormAddonsControl -> sLabelMapInfo -> Caption = FormAddonsControl -> sLabelMapInfo -> Caption + LanguageStrings [33]; //Galactic Civil War
            //Adding additional data
            FormAddonsControl -> sLabelMapInfo -> Caption = FormAddonsControl -> sLabelMapInfo -> Caption + " (" + Line -> Strings [3] + " [" + Line -> Strings [5] + "]" + " / " + Line -> Strings [4] + " [" + Line -> Strings [6] + "])";
           }
         }
        Line -> Free ();
       }
      MapInfo -> Free ();
     }
    //if eras are not filled then we write an unknown
    if (FormAddonsControl -> sLabelMapInfo -> Caption == LanguageStrings [31] + " ") FormAddonsControl -> sLabelMapInfo -> Caption = FormAddonsControl -> sLabelMapInfo -> Caption + LanguageStrings [35];
    //Load the 0 screen and activate visible/enable of buttons
    CurScreenIndex = 0;
    if (HasAddOnScreensFolder (MapName))
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
  TSearchRec SearchResult;
  for (int I = FindFirst (GetAddOnPath () + "*", faDirectory, SearchResult); !I; I = FindNext (SearchResult))
    {
     if ((SearchResult.Name == ".") || (SearchResult.Name == "..")) continue;
     if (SearchResult.Attr & faDirectory) sListBoxSelectedAddons -> Items -> Add (SearchResult.Name); //Added folders only
    }
  FindClose (SearchResult);
  //Uploading all available maps
  for (int I = FindFirst (GetAllMapsPath () + "*", faDirectory, SearchResult); !I; I = FindNext (SearchResult))
    {
     if ((SearchResult.Name == ".") || (SearchResult.Name == "..") || (sListBoxSelectedAddons -> Items -> IndexOf (SearchResult.Name) > -1)) continue;
     if (SearchResult.Attr & faDirectory) sListBoxAvailabledAddons -> Items -> Add (SearchResult.Name); //Added folders only
    }
  FindClose (SearchResult);
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
   CurScreenIndex = GetFilesCount (GetAddOnScreensPath (LastObject -> Items -> Strings [LastObject -> ItemIndex])) - 1;
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

//Open screen in original size
void __fastcall TFormAddonsControl::sBitBtnZoomClick (TObject *Sender)
 {
  FormScreenZoom -> ShowModal ();
 }

//Unsellect map
void __fastcall TFormAddonsControl::sBitBtnUnselectClick (TObject *Sender)
 {
  if (sListBoxSelectedAddons -> ItemIndex != -1)
   {
    int CurIndex = sListBoxSelectedAddons -> ItemIndex;
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
    if (sListBoxSelectedAddons -> Items -> Count - 1 < CurIndex) CurIndex -= 1;
    sListBoxSelectedAddons -> ItemIndex = CurIndex;
    ChangeInfo (sListBoxSelectedAddons);
   }
 }

//Sellect map
void __fastcall TFormAddonsControl::sBitBtnSelectClick (TObject *Sender)
 {
  if (sListBoxAvailabledAddons -> ItemIndex != -1)
   {
    if (sListBoxSelectedAddons -> Count >= CURRENT_ADDONS_LIMIT)
     {
      ShowErrorMessage (ReplaceStringMask (LanguageStrings [41], "number", IntToStr (CURRENT_ADDONS_LIMIT)));
     } else
     {
      int CurIndex = sListBoxAvailabledAddons -> ItemIndex;
      UnicodeString MapName = sListBoxAvailabledAddons -> Items -> Strings [sListBoxAvailabledAddons -> ItemIndex];
      //Creating thread
      ProcessName = LanguageStrings [39];
      ProcessId = 2;
      ProcessArguments [0] = MapName;
      FormGlobalProcess -> ShowModal ();
      //Append additional mode
      if (HasAddOnModesFolder (MapName))
       {
        FormSelectMapMode -> sComboBoxMapMode -> Clear ();
        FormSelectMapMode -> sComboBoxMapMode -> Items -> Add ("Standart");
        //Uploading all available modes
        TSearchRec SearchResult;
        for (int I = FindFirst (GetAddOnModesPath (MapName) + "*", faDirectory, SearchResult); !I; I = FindNext (SearchResult))
          {
           if ((SearchResult.Name == ".") || (SearchResult.Name == "..")) continue;
           if (SearchResult.Attr & faDirectory) FormSelectMapMode -> sComboBoxMapMode -> Items -> Add (SearchResult.Name); //Added folders only
          }
        FindClose (SearchResult);
        FormSelectMapMode -> sComboBoxMapMode -> ItemIndex = 0;
        //Show dialog of selecting the mode
        SetFormToScreenCenter (FormSelectMapMode);
        FormSelectMapMode -> ShowModal ();
        //if user selects non standrat mode
        if (FormSelectMapMode -> sComboBoxMapMode -> ItemIndex > 0)
         {
          TSearchRec SearchResult;
          for (int I = FindFirst (GetAddOnModesPath (MapName) + FormSelectMapMode -> sComboBoxMapMode -> Items -> Strings [FormSelectMapMode -> sComboBoxMapMode -> ItemIndex] + "\\*.*", faAnyFile, SearchResult); !I; I = FindNext (SearchResult))
            {
             if (!(SearchResult.Attr & faDirectory)) //Copy files only
              {
               if (SearchResult.Name == "mission.lvl")
                {
                 CopyFile ((GetAddOnModesPath (MapName) + FormSelectMapMode -> sComboBoxMapMode -> Items -> Strings [FormSelectMapMode -> sComboBoxMapMode -> ItemIndex] + "\\mission.lvl").w_str (), (GetAddOnPath () + MapName + "\\Data\\_lvl_pc\\mission.lvl").w_str (), false);
                }
              }
            }
          FindClose (SearchResult);
         }
       }
      //Updating information
      sListBoxSelectedAddons -> Items -> Add (MapName);
      sListBoxSelectedAddons -> ItemIndex = sListBoxSelectedAddons -> Items -> IndexOf (MapName);
      sListBoxAvailabledAddons -> Items -> Delete (sListBoxAvailabledAddons -> ItemIndex);
      if (sListBoxAvailabledAddons -> Items -> Count - 1 < CurIndex) CurIndex -= 1;
      sListBoxAvailabledAddons -> ItemIndex = CurIndex;
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

