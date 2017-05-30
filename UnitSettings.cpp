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

__fastcall TFormSettings::TFormSettings (TComponent* Owner) : TForm (Owner)
 {
 }

void __fastcall TFormSettings::sBitBtnCancelClick (TObject *Sender)
 {
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
  sTrackBarSoundQuality -> Position = StrToInt (SettingsFile -> ReadString ("Game_launch", "Audio_rate", "11000"));
  sLabelCurQuality -> Caption = IntToStr (sTrackBarSoundQuality -> Position);
  sCheckBoxInternetHost -> Checked = StrToBool (SettingsFile -> ReadString ("Multiplayer", "Use_user_host", "true"));
  sEditHost -> Enabled = sCheckBoxInternetHost -> Checked;
  sEditHost -> Text = SettingsFile -> ReadString ("Multiplayer", "Host", "162.248.92.172");
  sEditVersion -> Text = SettingsFile -> ReadString ("Multiplayer", "Current_version", "1.3");
  //Load list of languages
  sComboBoxLanguages -> Clear ();
  TSearchRec sr;
  for (int i = FindFirst (GetLauncherDataPath () + "Languages\\*", faDirectory, sr); !i; i = FindNext (sr))
    {
     if ((sr.Name == ".") || (sr.Name == "..")) continue;
     if (sr.Attr & faDirectory) sComboBoxLanguages -> Items -> Add (sr.Name); //Added folders only
    }
  sComboBoxLanguages -> ItemIndex = sComboBoxLanguages -> Items -> IndexOf (SettingsFile -> ReadString ("Language", "Name", "English"));
  if (sComboBoxLanguages -> ItemIndex == -1) sComboBoxLanguages -> ItemIndex = 0;
  FindClose (sr);
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
  SettingsFile -> WriteString ("Multiplayer", "Use_user_host", BoolToRealString (sCheckBoxInternetHost -> Checked));
  if (sEditHost -> Text == "") sEditHost -> Text = "162.248.92.172";
  SettingsFile -> WriteString ("Multiplayer", "Host", sEditHost -> Text);
  //Version can not consist of only spaces or be empty ""
  sEditVersion -> Text = sEditVersion -> Text.Trim (); //deleting all spaces at the beginning and end of the line
  if (sEditVersion -> Text == "") sEditVersion -> Text = "1.3";
  SettingsFile -> WriteString ("Multiplayer", "Current_version", sEditVersion -> Text);
  SettingsFile -> WriteString ("Language", "Name", sComboBoxLanguages -> Text);
  //Save ini
  SettingsFile -> UpdateFile ();
  //Patching language
  ProcessName = LanguageStrings [38];
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
  //Apply language
  ApplyLanguageFromFile (GetLauncherDataPath () + "Languages\\" + sComboBoxLanguages -> Text + "\\Language.ini");
 }
