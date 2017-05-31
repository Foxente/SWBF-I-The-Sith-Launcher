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

#ifndef UnitMainMenuH
#define UnitMainMenuH

#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "sBitBtn.hpp"
#include "sLabel.hpp"
#include <Vcl.Buttons.hpp>

class TFormMainMenu : public TForm
 {
  __published :   // IDE-managed Components
    TsBitBtn *sBitBtnPlay;
    TsBitBtn *sBitBtnSetAdditionalMap;
    TsBitBtn *sBitBtnAboutLauncher;
    TsLabel *sLabelComingSoon;
    TsBitBtn *sBitBtnSettings;
    void __fastcall FormClose (TObject *Sender, TCloseAction &Action);
    void __fastcall sBitBtnSettingsClick (TObject *Sender);
    void __fastcall sBitBtnPlayClick (TObject *Sender);
    void __fastcall sBitBtnSetAdditionalMapClick (TObject *Sender);
    void __fastcall sBitBtnAboutLauncherClick (TObject *Sender);
    void __fastcall FormShow (TObject *Sender);
  private :       // User declarations
  public :        // User declarations
    __fastcall TFormMainMenu (TComponent* Owner);
 };

class TErrorSearchThread : public TThread
 {
  private:
  protected:
    void __fastcall Execute ();
    void __fastcall ShowErr ();
  public:
    __fastcall TErrorSearchThread (bool CreateSuspended);
 };

extern PACKAGE TFormMainMenu *FormMainMenu;

#endif
