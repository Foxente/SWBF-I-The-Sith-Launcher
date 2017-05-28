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

#pragma package(smart_init)
#pragma link "sLabel"
#pragma link "sCheckBox"
#pragma link "sEdit"
#pragma link "sTrackBar"
#pragma link "sBitBtn"
#pragma link "acImage"
#pragma resource "*.dfm"
TFormSettings *FormSettings;

__fastcall TFormSettings::TFormSettings (TComponent* Owner) : TForm (Owner)
 {
 }

void __fastcall TFormSettings::sBitBtnCancelClick (TObject *Sender)
 {
  Close ();
 }


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
  SettingsFile -> WriteString ("Multiplayer", "Current_version", sEditVersion -> Text);
  SettingsFile -> UpdateFile ();
  Close ();
 }

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
