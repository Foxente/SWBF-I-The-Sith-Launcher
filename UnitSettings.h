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

#ifndef UnitSettingsH
#define UnitSettingsH

#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "sLabel.hpp"
#include "sCheckBox.hpp"
#include "sEdit.hpp"
#include "sTrackBar.hpp"
#include <Vcl.ComCtrls.hpp>
#include "sBitBtn.hpp"
#include <Vcl.Buttons.hpp>
#include "acImage.hpp"
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Graphics.hpp>
#include <ShellAPi.hpp>

class TFormSettings : public TForm
 {
  __published:  // IDE-managed Components
    TsLabel *sLabelLaunchSettings;
    TsCheckBox *sCheckBoxWindowedMode;
    TsCheckBox *sCheckBoxSkipSpalshScreens;
    TsCheckBox *sCheckBoxSkipStartupMusic;
    TsCheckBox *sCheckBoxDisableAnimatedMenuBackground;
    TsCheckBox *sCheckBoxAudioBufferSize;
    TsEdit *sEditMilliseconds;
    TsCheckBox *sCheckBoxSoundQuality;
    TsTrackBar *sTrackBarSoundQuality;
    TsLabel *sLabelCurQuality;
    TsLabel *sLabelMaxQuality;
    TsLabel *sLabelMinQuality;
    TsLabel *sLabeMultiplayerSettings;
    TsCheckBox *sCheckBoxInternetHost;
    TsEdit *sEditHost;
    TsLabel *sLabelCurrentGameVersion;
    TsEdit *sEditVersion;
    TsLabel *sLabelLANNetwork;
    TsBitBtn *sBitBtnSave;
    TsBitBtn *sBitBtnCancel;
    TsImage *sImageGameRanger;
    TsImage *sImageTunngle;
    TsLabel *sLabelTunngle;
    TsLabel *sLabelGameRanger;
    TsBitBtn *sBitBtnDownloadTunngle;
    TsBitBtn *sBitBtnTunngleVideo;
    TsBitBtn *sBitBtnDownloadGameRanger;
    TsBitBtn *sBitBtnGameRangerVideo;
    void __fastcall sBitBtnCancelClick (TObject *Sender);
    void __fastcall FormShow (TObject *Sender);
    void __fastcall sTrackBarSoundQualityChange (TObject *Sender);
    void __fastcall sCheckBoxAudioBufferSizeClick (TObject *Sender);
    void __fastcall sCheckBoxSoundQualityClick (TObject *Sender);
    void __fastcall sCheckBoxInternetHostClick (TObject *Sender);
    void __fastcall sBitBtnSaveClick (TObject *Sender);
    void __fastcall sBitBtnDownloadTunngleClick (TObject *Sender);
    void __fastcall sBitBtnTunngleVideoClick (TObject *Sender);
    void __fastcall sBitBtnDownloadGameRangerClick (TObject *Sender);
    void __fastcall sBitBtnGameRangerVideoClick (TObject *Sender);
  private:  // User declarations
  public:   // User declarations
    __fastcall TFormSettings (TComponent* Owner);
 };

extern PACKAGE TFormSettings *FormSettings;

#endif
