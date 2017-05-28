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

#ifndef UnitAddonsControlH
#define UnitAddonsControlH

#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "sListBox.hpp"
#include "sBitBtn.hpp"
#include "sLabel.hpp"
#include <Vcl.Buttons.hpp>
#include "acImage.hpp"
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Graphics.hpp>

class TFormAddonsControl : public TForm
 {
  __published :   // IDE-managed Components
    TsListBox *sListBoxAvailabledAddons;
    TsListBox *sListBoxSelectedAddons;
    TsLabel *sLabelAvailabledAddons;
    TsLabel *sLabelSelectedAddons;
    TsBitBtn *sBitBtnSelect;
    TsBitBtn *sBitBtnUnselect;
    TsBitBtn *sBitBtnOpenExplorer;
    TsImage *sImageMiniScreen;
    TsLabel *sLabelMapName;
    TsLabel *sLabelMapInfo;
    TsBitBtn *sBitBtnPrevious;
    TsBitBtn *sBitBtnZoom;
    TsBitBtn *sBitBtnNext;
    void __fastcall FormShow (TObject *Sender);
    void __fastcall sListBoxesClick (TObject *Sender);
    void __fastcall sBitBtnPreviousClick (TObject *Sender);
    void __fastcall sBitBtnNextClick (TObject *Sender);
    void __fastcall sBitBtnZoomClick (TObject *Sender);
    void __fastcall sBitBtnUnselectClick (TObject *Sender);
    void __fastcall sBitBtnSelectClick (TObject *Sender);
    void __fastcall sBitBtnOpenExplorerClick(TObject *Sender);
  private :       // User declarations
  public :        // User declarations
    __fastcall TFormAddonsControl (TComponent* Owner);
 };

extern PACKAGE TFormAddonsControl *FormAddonsControl;
extern PACKAGE TsListBox *LastObject;
extern PACKAGE int CurScreenIndex;

#endif
