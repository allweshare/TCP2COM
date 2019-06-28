/***************************************************************
 * Name:      TCP2COMMain.h
 * Purpose:   Defines Application Frame
 * Author:    David (lw.7@foxmail.com)
 * Created:   2019-05-07
 * Copyright: David ()
 * License:
 **************************************************************/

#ifndef TCP2COMMAIN_H
#define TCP2COMMAIN_H

//(*Headers(TCP2COMDialog)
#include <wx/button.h>
#include <wx/choice.h>
#include <wx/dialog.h>
#include <wx/listbox.h>
#include <wx/sizer.h>
#include <wx/statline.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/timer.h>
//*)

#include "FrameObserver.h"

class TCP2COMDialog: public wxDialog, public FrameObserver
{
    public:

        TCP2COMDialog(wxWindow* parent,wxWindowID id = -1);
        virtual ~TCP2COMDialog();

        void updateComports();  //每次重新加载虚拟串口列表后,跟着刷新下拉列表框的选项

    private:

        //(*Handlers(TCP2COMDialog)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnInit(wxInitDialogEvent& event);
        void OnbtnInstallClick(wxCommandEvent& event);
        void OnbtnReloadClick(wxCommandEvent& event);
        void OnbtnRemoveClick(wxCommandEvent& event);
        void OnbtnAddPairClick(wxCommandEvent& event);
        void OnbtnOpenClick(wxCommandEvent& event);
        void OnbtnStopClick(wxCommandEvent& event);
        void OncmbCompSelect(wxCommandEvent& event);
        void OnClose(wxCloseEvent& event);
        void OncmbBaudrateSelect(wxCommandEvent& event);
        void OncmbDatabitsSelect(wxCommandEvent& event);
        void OncmbParitysSelect(wxCommandEvent& event);
        void OnTimer1Trigger(wxTimerEvent& event);
        //*)

        //(*Identifiers(TCP2COMDialog)
        static const long ID_STATICTEXT1;
        static const long ID_STATICTEXT2;
        static const long ID_TEXTCTRL1;
        static const long ID_STATICTEXT3;
        static const long ID_TEXTCTRL2;
        static const long ID_STATICLINE1;
        static const long ID_STATICTEXT9;
        static const long ID_CHOICE2;
        static const long ID_STATICTEXT10;
        static const long ID_CHOICE3;
        static const long ID_STATICTEXT11;
        static const long ID_CHOICE4;
        static const long ID_STATICTEXT12;
        static const long ID_CHOICE5;
        static const long ID_BUTTON1;
        static const long ID_BUTTON2;
        static const long ID_STATICTEXT6;
        static const long ID_STATICLINE3;
        static const long ID_STATICTEXT7;
        static const long ID_STATICLINE2;
        static const long ID_STATICTEXT5;
        static const long ID_LISTBOX1;
        static const long ID_TEXTCTRL3;
        static const long ID_STATICTEXT8;
        static const long ID_TEXTCTRL4;
        static const long ID_BUTTON3;
        static const long ID_BUTTON4;
        static const long ID_BUTTON5;
        static const long ID_BUTTON6;
        static const long ID_TIMER1;
        //*)

        //(*Declarations(TCP2COMDialog)
        wxBoxSizer* BoxSizer1;
        wxButton* btnAddPair;
        wxButton* btnClose;
        wxButton* btnInstall;
        wxButton* btnOpen;
        wxButton* btnReload;
        wxButton* btnRemove;
        wxChoice* cmbBaudrate;
        wxChoice* cmbComport;
        wxChoice* cmbDatabits;
        wxChoice* cmbParitys;
        wxListBox* listComPairs;
        wxStaticLine* StaticLine1;
        wxStaticLine* StaticLine2;
        wxStaticLine* StaticLine3;
        wxStaticText* StaticText10;
        wxStaticText* StaticText11;
        wxStaticText* StaticText12;
        wxStaticText* StaticText1;
        wxStaticText* StaticText2;
        wxStaticText* StaticText3;
        wxStaticText* StaticText5;
        wxStaticText* StaticText8;
        wxStaticText* StaticText9;
        wxStaticText* labComState;
        wxStaticText* labNetState;
        wxTextCtrl* txtCompA;
        wxTextCtrl* txtCompB;
        wxTextCtrl* txtHost;
        wxTextCtrl* txtPort;
        wxTimer Timer1;
        //*)

        //观察者模式的接收函数
        void onReciveData(FrameObserver::DataSource source,uint8_t * data,size_t len);

        DECLARE_EVENT_TABLE()
};

#endif // TCP2COMMAIN_H
