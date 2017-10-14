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

#include "UnitSettings.h"
#include "API.h"

#include "UnitGlobalProcess.h"

#pragma package(smart_init)
#pragma link "sLabel"
#pragma link "sCheckBox"
#pragma link "sEdit"
#pragma link "sTrackBar"
#pragma link "sBitBtn"
#pragma link "acImage"
#pragma link "sComboBox"
#pragma resource "*.dfm"

TFormSettings *FormSettings;
UnicodeString QuickMessages [9];
int LastSelIndex;

__fastcall TFormSettings::TFormSettings (TComponent* Owner) : TForm (Owner)
 {
 }

void __fastcall TFormSettings::sBitBtnCancelClick (TObject *Sender)
 {
  //Apply old language
  ApplyLanguageFromFile (GetLauncherDataPath () + "Languages\\" + SettingsFile -> ReadString ("Language", "Name", "English") + "\\Language.ini");
  Close ();
 }

//Loading vars from ini
void __fastcall TFormSettings::FormShow (TObject *Sender)
 {
  sCheckBoxWindowedMode -> Checked = StrToBool (SettingsFile -> ReadString ("Game_launch", "Window_mode", "false"));
  sCheckBoxSkipSpalshScreens -> Checked = StrToBool (SettingsFile -> ReadString ("Game_launch", "Skip_logos", "false"));
  sCheckBoxSkipStartupMusic -> Checked = StrToBool (SettingsFile -> ReadString ("Game_launch", "Skip_startup_music", "false"));
  sCheckBoxDisableAnimatedMenuBackground -> Checked = StrToBool (SettingsFile -> ReadString ("Game_launch", "Skip_menu_background", "false"));
  sCheckBoxSkipStartupMusic -> Checked = StrToBool (SettingsFile -> ReadString ("Game_launch", "Skip_startup_music", "false"));
  sCheckBoxAudioBufferSize -> Checked = StrToBool (SettingsFile -> ReadString ("Game_launch", "Audio_buffer_enable", "false"));
  sEditMilliseconds -> Enabled = sCheckBoxAudioBufferSize -> Checked;
  sEditMilliseconds -> Text = SettingsFile -> ReadString ("Game_launch", "Audio_buffer_ms", "200");
  sCheckBoxSoundQuality -> Checked = StrToBool (SettingsFile -> ReadString ("Game_launch", "Audio_rate_enable", "false"));
  sTrackBarSoundQuality -> Enabled = FormSettings -> sCheckBoxSoundQuality -> Checked;
  sLabelMinQuality -> Enabled = FormSettings -> sCheckBoxSoundQuality -> Checked;
  sLabelMaxQuality -> Enabled = FormSettings -> sCheckBoxSoundQuality -> Checked;
  sLabelCurQuality -> Enabled = FormSettings -> sCheckBoxSoundQuality -> Checked;
  sTrackBarSoundQuality -> Position = StrToInt (SettingsFile -> ReadString ("Game_launch", "Audio_rate", "11000"));
  sLabelCurQuality -> Caption = IntToStr (sTrackBarSoundQuality -> Position);
  sCheckBoxGameResolution -> Checked = StrToBool (SettingsFile -> ReadString ("Game_launch", "Custom_resolution_enable", "true"));
  sEditWidth -> Text = SettingsFile -> ReadString ("Game_launch", "Custom_resolution_width", Screen -> Width);
  sEditHeight -> Text = SettingsFile -> ReadString ("Game_launch", "Custom_resolution_height", Screen -> Height);
  sEditWidth -> Enabled = sCheckBoxGameResolution -> Checked;
  sEditHeight -> Enabled = sCheckBoxGameResolution -> Checked;
  sLabelResolutionDelimiter -> Enabled = sCheckBoxGameResolution -> Checked;
  sLabelPixels -> Enabled = sCheckBoxGameResolution -> Checked;
  sCheckBoxInternetHost -> Checked = StrToBool (SettingsFile -> ReadString ("Multiplayer", "Use_user_host", "true"));
  sEditHost -> Enabled = sCheckBoxInternetHost -> Checked;
  sEditHost -> Text = SettingsFile -> ReadString ("Multiplayer", "Host", "162.248.92.172");
  sEditVersion -> Text = SettingsFile -> ReadString ("Multiplayer", "Current_version", "1.2");
  //Load list of languages
  sComboBoxLanguages -> Clear ();
  TSearchRec SearchResult;
  for (int I = FindFirst (GetLauncherDataPath () + "Languages\\*", faDirectory, SearchResult); !I; I = FindNext (SearchResult))
    {
	 if ((SearchResult.Name == ".") || (SearchResult.Name == "..")) continue;
	 if (SearchResult.Attr & faDirectory) sComboBoxLanguages -> Items -> Add (SearchResult.Name); //Added folders only
    }
  sComboBoxLanguages -> ItemIndex = sComboBoxLanguages -> Items -> IndexOf (SettingsFile -> ReadString ("Language", "Name", "English"));
  if (sComboBoxLanguages -> ItemIndex == -1) sComboBoxLanguages -> ItemIndex = 0;
  FindClose (SearchResult);
  //loading all quick messages
  for (int I = 1; I <= 8; I++) QuickMessages [I] = SettingsFile -> ReadString ("Language", "Message" + IntToStr (I), "");
  LastSelIndex = 0;
  if (QuickMessages [1] == "") sEditMessageText -> Text = LanguageStrings [70];
  else sEditMessageText -> Text = QuickMessages [1];
 }

void __fastcall TFormSettings::sTrackBarSoundQualityChange (TObject *Sender)
 {
  sLabelCurQuality -> Caption = IntToStr (sTrackBarSoundQuality -> Position);
 }

void __fastcall TFormSettings::sCheckBoxAudioBufferSizeClick (TObject *Sender)
 {
  sEditMilliseconds -> Enabled = sCheckBoxAudioBufferSize -> Checked;
 }

void __fastcall TFormSettings::sCheckBoxSoundQualityClick (TObject *Sender)
 {
  sTrackBarSoundQuality -> Enabled = FormSettings -> sCheckBoxSoundQuality -> Checked;
  sLabelMinQuality -> Enabled = FormSettings -> sCheckBoxSoundQuality -> Checked;
  sLabelMaxQuality -> Enabled = FormSettings -> sCheckBoxSoundQuality -> Checked;
  sLabelCurQuality -> Enabled = FormSettings -> sCheckBoxSoundQuality -> Checked;
 }

void __fastcall TFormSettings::sCheckBoxInternetHostClick (TObject *Sender)
 {
  sEditHost -> Enabled = sCheckBoxInternetHost -> Checked;
 }

//Saving vars to ini
void __fastcall TFormSettings::sBitBtnSaveClick (TObject *Sender)
 {
  SettingsFile -> WriteString ("Game_launch", "Window_mode", BoolToRealString (sCheckBoxWindowedMode -> Checked));
  SettingsFile -> WriteString ("Game_launch", "Skip_logos", BoolToRealString (sCheckBoxSkipSpalshScreens -> Checked));
  SettingsFile -> WriteString ("Game_launch", "Skip_startup_music", BoolToRealString (sCheckBoxSkipStartupMusic -> Checked));
  SettingsFile -> WriteString ("Game_launch", "Skip_menu_background", BoolToRealString (sCheckBoxDisableAnimatedMenuBackground -> Checked));
  SettingsFile -> WriteString ("Game_launch", "Audio_buffer_enable", BoolToRealString (sCheckBoxAudioBufferSize -> Checked));
  if ((sEditMilliseconds -> Text == "") || (StrToInt (sEditMilliseconds -> Text) == 0)) sEditMilliseconds -> Text = "200";
  SettingsFile -> WriteString ("Game_launch", "Audio_buffer_ms", sEditMilliseconds -> Text);
  SettingsFile -> WriteString ("Game_launch", "Audio_rate_enable", BoolToRealString (sCheckBoxSoundQuality -> Checked));
  SettingsFile -> WriteString ("Game_launch", "Audio_rate", IntToStr (sTrackBarSoundQuality -> Position));
  SettingsFile -> WriteString ("Game_launch", "Custom_resolution_enable", BoolToRealString (sCheckBoxGameResolution -> Checked));
  SettingsFile -> WriteString ("Game_launch", "Custom_resolution_width", sEditWidth -> Text);
  SettingsFile -> WriteString ("Game_launch", "Custom_resolution_height", sEditHeight -> Text);
  SettingsFile -> WriteString ("Multiplayer", "Use_user_host", BoolToRealString (sCheckBoxInternetHost -> Checked));
  if (sEditHost -> Text == "") sEditHost -> Text = "162.248.92.172";
  SettingsFile -> WriteString ("Multiplayer", "Host", sEditHost -> Text);
  //Version can not consist of only spaces or be empty ""
  sEditVersion -> Text = sEditVersion -> Text.Trim (); //deleting all spaces at the beginning and end of the line
  if (sEditVersion -> Text == "") sEditVersion -> Text = "1.2";
  SettingsFile -> WriteString ("Multiplayer", "Current_version", sEditVersion -> Text);
  SettingsFile -> WriteString ("Language", "Name", sComboBoxLanguages -> Text);
  //Saving Quick messages
  sComboBoxSelectingMessageSelect (NULL);
  for (int i = 1; i <= 8; i++) SettingsFile -> WriteString ("Language", "Message" + IntToStr (i), QuickMessages [i]);
  //Save ini
  SettingsFile -> UpdateFile ();
  //Patching language
  ProcessName = LanguageStrings [55];
  ProcessId = 3;
  FormGlobalProcess -> ShowModal ();
  Close ();
 }

//Opening links
void __fastcall TFormSettings::sBitBtnDownloadTunngleClick (TObject *Sender)
 {
  ShellExecute (Handle, L"open", LanguageStrings [24].w_str (), 0, 0, SW_NORMAL);
 }

void __fastcall TFormSettings::sBitBtnTunngleVideoClick (TObject *Sender)
 {
  ShellExecute (Handle, L"open", LanguageStrings [25].w_str (), 0, 0, SW_NORMAL);
 }

void __fastcall TFormSettings::sBitBtnDownloadGameRangerClick (TObject *Sender)
 {
  ShellExecute (Handle, L"open", LanguageStrings [26].w_str (), 0, 0, SW_NORMAL);
 }

void __fastcall TFormSettings::sBitBtnGameRangerVideoClick (TObject *Sender)
 {
  //ShellExecute (Handle, L"open", LanguageStrings [27].w_str (), 0, 0, SW_NORMAL);
 }

void __fastcall TFormSettings::sComboBoxLanguagesSelect (TObject *Sender)
 {
  //Determine is it needed translate the sEditMessageText
  bool NeedTranslate = false;
  if (sEditMessageText -> Text == LanguageStrings [69 + LastSelIndex + 1]) NeedTranslate = true;
  //Apply language
  ApplyLanguageFromFile (GetLauncherDataPath () + "Languages\\" + sComboBoxLanguages -> Text + "\\Language.ini");
  //Translating the sEditMessageText
  if (NeedTranslate)
   {
    sEditMessageText -> Text = LanguageStrings [69 + LastSelIndex + 1];
   }
 }

void __fastcall TFormSettings::sComboBoxSelectingMessageSelect (TObject *Sender)
 {
  //Remeber entered text
  if (sEditMessageText -> Text == LanguageStrings [69 + LastSelIndex + 1]) QuickMessages [LastSelIndex + 1] = "";
  else QuickMessages [LastSelIndex + 1] = sEditMessageText -> Text;
  //Change text in edit
  int Index = FormSettings -> sComboBoxSelectingMessage -> ItemIndex + 1;
  sEditMessageText -> Text = QuickMessages [Index];
  if (sEditMessageText -> Text == "") sEditMessageText -> Text = LanguageStrings [69 + Index];
  LastSelIndex = sComboBoxSelectingMessage -> ItemIndex;
 }

void __fastcall TFormSettings::sCheckBoxGameResolutionClick (TObject *Sender)
 {
  sEditWidth -> Enabled = sCheckBoxGameResolution -> Checked;
  sEditHeight -> Enabled = sCheckBoxGameResolution -> Checked;
  sLabelResolutionDelimiter -> Enabled = sCheckBoxGameResolution -> Checked;
  sLabelPixels -> Enabled = sCheckBoxGameResolution -> Checked;
 }
