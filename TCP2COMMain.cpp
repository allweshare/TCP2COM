/***************************************************************
 * Name:      TCP2COMMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    David (lw.7@foxmail.com)
 * Created:   2019-05-07
 * Copyright: David ()
 * License:
 **************************************************************/

#include "TCP2COMMain.h"
#include <wx/msgdlg.h>
#include <wx/tokenzr.h>
#include <iostream>

#include "FactoryPreset.h"
#include "VirtualCom.h"
#include "NetCommService.h"
#include "SerialCommService.h"

//(*InternalHeaders(TCP2COMDialog)
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/settings.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

using namespace std;

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(TCP2COMDialog)
const long TCP2COMDialog::ID_STATICTEXT1 = wxNewId();
const long TCP2COMDialog::ID_STATICTEXT2 = wxNewId();
const long TCP2COMDialog::ID_TEXTCTRL1 = wxNewId();
const long TCP2COMDialog::ID_STATICTEXT3 = wxNewId();
const long TCP2COMDialog::ID_TEXTCTRL2 = wxNewId();
const long TCP2COMDialog::ID_STATICLINE1 = wxNewId();
const long TCP2COMDialog::ID_STATICTEXT9 = wxNewId();
const long TCP2COMDialog::ID_CHOICE2 = wxNewId();
const long TCP2COMDialog::ID_STATICTEXT10 = wxNewId();
const long TCP2COMDialog::ID_CHOICE3 = wxNewId();
const long TCP2COMDialog::ID_STATICTEXT11 = wxNewId();
const long TCP2COMDialog::ID_CHOICE4 = wxNewId();
const long TCP2COMDialog::ID_STATICTEXT12 = wxNewId();
const long TCP2COMDialog::ID_CHOICE5 = wxNewId();
const long TCP2COMDialog::ID_BUTTON1 = wxNewId();
const long TCP2COMDialog::ID_BUTTON2 = wxNewId();
const long TCP2COMDialog::ID_STATICTEXT6 = wxNewId();
const long TCP2COMDialog::ID_STATICLINE3 = wxNewId();
const long TCP2COMDialog::ID_STATICTEXT7 = wxNewId();
const long TCP2COMDialog::ID_STATICLINE2 = wxNewId();
const long TCP2COMDialog::ID_STATICTEXT5 = wxNewId();
const long TCP2COMDialog::ID_LISTBOX1 = wxNewId();
const long TCP2COMDialog::ID_TEXTCTRL3 = wxNewId();
const long TCP2COMDialog::ID_STATICTEXT8 = wxNewId();
const long TCP2COMDialog::ID_TEXTCTRL4 = wxNewId();
const long TCP2COMDialog::ID_BUTTON3 = wxNewId();
const long TCP2COMDialog::ID_BUTTON4 = wxNewId();
const long TCP2COMDialog::ID_BUTTON5 = wxNewId();
const long TCP2COMDialog::ID_BUTTON6 = wxNewId();
const long TCP2COMDialog::ID_TIMER1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(TCP2COMDialog,wxDialog)
    //(*EventTable(TCP2COMDialog)
    //*)
END_EVENT_TABLE()

TCP2COMDialog::TCP2COMDialog(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(TCP2COMDialog)
    wxBoxSizer* BoxSizer2;
    wxBoxSizer* BoxSizer3;
    wxBoxSizer* BoxSizer4;
    wxBoxSizer* BoxSizer5;
    wxFlexGridSizer* FlexGridSizer1;
    wxFlexGridSizer* FlexGridSizer3;

    Create(parent, id, _("网络转串口"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
    SetClientSize(wxSize(300,500));
    SetBackgroundColour(wxColour(147,214,242));
    BoxSizer1 = new wxBoxSizer(wxVERTICAL);
    BoxSizer1->Add(91,12,0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("TCP Server"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    StaticText1->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHT));
    wxFont StaticText1Font(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("黑体"),wxFONTENCODING_DEFAULT);
    StaticText1->SetFont(StaticText1Font);
    BoxSizer1->Add(StaticText1, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1 = new wxFlexGridSizer(0, 2, 0, 0);
    FlexGridSizer1->AddGrowableCol(0);
    FlexGridSizer1->AddGrowableCol(1);
    StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("主机："), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    wxFont StaticText2Font(10,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("黑体"),wxFONTENCODING_DEFAULT);
    StaticText2->SetFont(StaticText2Font);
    FlexGridSizer1->Add(StaticText2, 0, wxTOP|wxBOTTOM|wxLEFT|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    txtHost = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxSize(150,22), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    FlexGridSizer1->Add(txtHost, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("端口："), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    wxFont StaticText3Font(10,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("黑体"),wxFONTENCODING_DEFAULT);
    StaticText3->SetFont(StaticText3Font);
    FlexGridSizer1->Add(StaticText3, 0, wxTOP|wxBOTTOM|wxLEFT|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    txtPort = new wxTextCtrl(this, ID_TEXTCTRL2, wxEmptyString, wxDefaultPosition, wxSize(150,22), 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    FlexGridSizer1->Add(txtPort, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1->Add(FlexGridSizer1, 0, wxALL|wxEXPAND, 5);
    StaticLine1 = new wxStaticLine(this, ID_STATICLINE1, wxDefaultPosition, wxSize(10,3), wxLI_HORIZONTAL, _T("ID_STATICLINE1"));
    BoxSizer1->Add(StaticLine1, 0, wxALL|wxEXPAND, 5);
    FlexGridSizer3 = new wxFlexGridSizer(0, 4, 0, 0);
    StaticText9 = new wxStaticText(this, ID_STATICTEXT9, _("串口:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
    wxFont StaticText9Font(10,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("黑体"),wxFONTENCODING_DEFAULT);
    StaticText9->SetFont(StaticText9Font);
    FlexGridSizer3->Add(StaticText9, 1, wxTOP|wxBOTTOM|wxLEFT|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    cmbComport = new wxChoice(this, ID_CHOICE2, wxDefaultPosition, wxSize(70,22), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE2"));
    cmbComport->Append(_("COM10"));
    cmbComport->Append(_("COM11"));
    FlexGridSizer3->Add(cmbComport, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText10 = new wxStaticText(this, ID_STATICTEXT10, _("波特率:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
    wxFont StaticText10Font(10,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("黑体"),wxFONTENCODING_DEFAULT);
    StaticText10->SetFont(StaticText10Font);
    FlexGridSizer3->Add(StaticText10, 1, wxTOP|wxBOTTOM|wxLEFT|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    cmbBaudrate = new wxChoice(this, ID_CHOICE3, wxDefaultPosition, wxSize(70,22), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE3"));
    cmbBaudrate->Append(_("300"));
    cmbBaudrate->Append(_("600"));
    cmbBaudrate->Append(_("1200"));
    cmbBaudrate->Append(_("2400"));
    cmbBaudrate->Append(_("4800"));
    cmbBaudrate->SetSelection( cmbBaudrate->Append(_("9600")) );
    cmbBaudrate->Append(_("19200"));
    cmbBaudrate->Append(_("38400"));
    cmbBaudrate->Append(_("43000"));
    cmbBaudrate->Append(_("56000"));
    cmbBaudrate->Append(_("57600"));
    cmbBaudrate->Append(_("115200"));
    FlexGridSizer3->Add(cmbBaudrate, 1, wxTOP|wxBOTTOM|wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText11 = new wxStaticText(this, ID_STATICTEXT11, _("数据位:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT11"));
    wxFont StaticText11Font(10,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("黑体"),wxFONTENCODING_DEFAULT);
    StaticText11->SetFont(StaticText11Font);
    FlexGridSizer3->Add(StaticText11, 1, wxTOP|wxBOTTOM|wxLEFT|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    cmbDatabits = new wxChoice(this, ID_CHOICE4, wxDefaultPosition, wxSize(70,22), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE4"));
    cmbDatabits->Append(_("6"));
    cmbDatabits->Append(_("7"));
    cmbDatabits->SetSelection( cmbDatabits->Append(_("8")) );
    FlexGridSizer3->Add(cmbDatabits, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText12 = new wxStaticText(this, ID_STATICTEXT12, _("校验位:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT12"));
    wxFont StaticText12Font(10,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("黑体"),wxFONTENCODING_DEFAULT);
    StaticText12->SetFont(StaticText12Font);
    FlexGridSizer3->Add(StaticText12, 1, wxTOP|wxBOTTOM|wxLEFT|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    cmbParitys = new wxChoice(this, ID_CHOICE5, wxDefaultPosition, wxSize(70,22), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE5"));
    cmbParitys->SetSelection( cmbParitys->Append(_("None")) );
    cmbParitys->Append(_("Odd"));
    cmbParitys->Append(_("Even"));
    cmbParitys->Append(_("Mark"));
    cmbParitys->Append(_("Space"));
    FlexGridSizer3->Add(cmbParitys, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1->Add(FlexGridSizer3, 0, wxALL|wxEXPAND, 5);
    BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    btnOpen = new wxButton(this, ID_BUTTON1, _("打开"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    btnOpen->SetFocus();
    wxFont btnOpenFont(10,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("黑体"),wxFONTENCODING_DEFAULT);
    btnOpen->SetFont(btnOpenFont);
    BoxSizer2->Add(btnOpen, 1, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
    btnClose = new wxButton(this, ID_BUTTON2, _("关闭"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    wxFont btnCloseFont(10,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("黑体"),wxFONTENCODING_DEFAULT);
    btnClose->SetFont(btnCloseFont);
    BoxSizer2->Add(btnClose, 1, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
    BoxSizer1->Add(BoxSizer2, 0, wxTOP|wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
    labNetState = new wxStaticText(this, ID_STATICTEXT6, _("网络未开启"), wxDefaultPosition, wxSize(110,14), wxALIGN_CENTRE, _T("ID_STATICTEXT6"));
    wxFont labNetStateFont(8,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("黑体"),wxFONTENCODING_DEFAULT);
    labNetState->SetFont(labNetStateFont);
    BoxSizer5->Add(labNetState, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticLine3 = new wxStaticLine(this, ID_STATICLINE3, wxDefaultPosition, wxSize(3,10), wxLI_HORIZONTAL, _T("ID_STATICLINE3"));
    BoxSizer5->Add(StaticLine3, 0, wxLEFT|wxRIGHT|wxEXPAND, 5);
    labComState = new wxStaticText(this, ID_STATICTEXT7, _("COM4已打开"), wxDefaultPosition, wxSize(110,14), wxALIGN_CENTRE, _T("ID_STATICTEXT7"));
    wxFont labComStateFont(8,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("黑体"),wxFONTENCODING_DEFAULT);
    labComState->SetFont(labComStateFont);
    BoxSizer5->Add(labComState, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1->Add(BoxSizer5, 0, wxTOP|wxLEFT|wxRIGHT|wxEXPAND, 5);
    StaticLine2 = new wxStaticLine(this, ID_STATICLINE2, wxDefaultPosition, wxSize(10,3), wxLI_HORIZONTAL, _T("ID_STATICLINE2"));
    BoxSizer1->Add(StaticLine2, 0, wxALL|wxEXPAND, 5);
    StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _("Virtual COM"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
    StaticText5->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHT));
    wxFont StaticText5Font(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("黑体"),wxFONTENCODING_DEFAULT);
    StaticText5->SetFont(StaticText5Font);
    BoxSizer1->Add(StaticText5, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    listComPairs = new wxListBox(this, ID_LISTBOX1, wxDefaultPosition, wxSize(246,66), 0, 0, 0, wxDefaultValidator, _T("ID_LISTBOX1"));
    BoxSizer1->Add(listComPairs, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    txtCompA = new wxTextCtrl(this, ID_TEXTCTRL3, _("COMx"), wxDefaultPosition, wxSize(58,22), 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
    BoxSizer3->Add(txtCompA, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText8 = new wxStaticText(this, ID_STATICTEXT8, _("<=>"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
    BoxSizer3->Add(StaticText8, 0, wxTOP|wxBOTTOM|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    txtCompB = new wxTextCtrl(this, ID_TEXTCTRL4, _("COMx"), wxDefaultPosition, wxSize(58,22), 0, wxDefaultValidator, _T("ID_TEXTCTRL4"));
    BoxSizer3->Add(txtCompB, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btnAddPair = new wxButton(this, ID_BUTTON3, _("添加"), wxDefaultPosition, wxSize(50,24), 0, wxDefaultValidator, _T("ID_BUTTON3"));
    wxFont btnAddPairFont(10,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("黑体"),wxFONTENCODING_DEFAULT);
    btnAddPair->SetFont(btnAddPairFont);
    BoxSizer3->Add(btnAddPair, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1->Add(BoxSizer3, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
    btnReload = new wxButton(this, ID_BUTTON4, _("加载"), wxDefaultPosition, wxSize(65,24), 0, wxDefaultValidator, _T("ID_BUTTON4"));
    wxFont btnReloadFont(10,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("黑体"),wxFONTENCODING_DEFAULT);
    btnReload->SetFont(btnReloadFont);
    BoxSizer4->Add(btnReload, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btnRemove = new wxButton(this, ID_BUTTON5, _("删除"), wxDefaultPosition, wxSize(65,24), 0, wxDefaultValidator, _T("ID_BUTTON5"));
    wxFont btnRemoveFont(10,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("黑体"),wxFONTENCODING_DEFAULT);
    btnRemove->SetFont(btnRemoveFont);
    BoxSizer4->Add(btnRemove, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btnInstall = new wxButton(this, ID_BUTTON6, _("安装驱动"), wxDefaultPosition, wxSize(65,24), 0, wxDefaultValidator, _T("ID_BUTTON6"));
    wxFont btnInstallFont(10,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("黑体"),wxFONTENCODING_DEFAULT);
    btnInstall->SetFont(btnInstallFont);
    BoxSizer4->Add(btnInstall, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1->Add(BoxSizer4, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SetSizer(BoxSizer1);
    Timer1.SetOwner(this, ID_TIMER1);
    SetSizer(BoxSizer1);
    Layout();
    Center();

    Connect(ID_CHOICE2,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&TCP2COMDialog::OncmbCompSelect);
    Connect(ID_CHOICE3,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&TCP2COMDialog::OncmbBaudrateSelect);
    Connect(ID_CHOICE4,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&TCP2COMDialog::OncmbDatabitsSelect);
    Connect(ID_CHOICE5,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&TCP2COMDialog::OncmbParitysSelect);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&TCP2COMDialog::OnbtnOpenClick);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&TCP2COMDialog::OnbtnStopClick);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&TCP2COMDialog::OnbtnAddPairClick);
    Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&TCP2COMDialog::OnbtnReloadClick);
    Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&TCP2COMDialog::OnbtnRemoveClick);
    Connect(ID_BUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&TCP2COMDialog::OnbtnInstallClick);
    Connect(ID_TIMER1,wxEVT_TIMER,(wxObjectEventFunction)&TCP2COMDialog::OnTimer1Trigger);
    Connect(wxID_ANY,wxEVT_INIT_DIALOG,(wxObjectEventFunction)&TCP2COMDialog::OnInit);
    Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&TCP2COMDialog::OnClose);
    //*)
}

TCP2COMDialog::~TCP2COMDialog()
{
    //(*Destroy(TCP2COMDialog)
    //*)
}

void TCP2COMDialog::OnQuit(wxCommandEvent& event)
{
    Close();
}

void TCP2COMDialog::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

/**
* 观察者模式的接收函数
**/
void TCP2COMDialog::onReciveData(FrameObserver::DataSource source,uint8_t * data,size_t len)
{
    //从网络收到数据
    if(source == FrameObserver::DataSource::NETWORK) {
        //cout<<"Redirect to comport !"<<endl;

        SerialCommService& comService = SerialCommService::getService();
        comService.send(data,len);
    }
    //从串口收到数据
    if(source == FrameObserver::DataSource::COMPORT) {
        //cout<<"Redirect to netport !"<<endl;

        NetCommService& netService = NetCommService::getService();
        netService.send(data,len);
    }
}

/**
* 更新下拉列表框中的选项
**/
void TCP2COMDialog::updateComports()
{
    unsigned int i = 0;
    long portNO;
    cmbComport->Clear();
    for(i=0;i<listComPairs->GetCount();i++)
    {
        cout<<"Item: "<<listComPairs->GetString(i)<<endl;
        wxStringTokenizer token(listComPairs->GetString(i)," <=>",wxTOKEN_STRTOK);
        while(token.HasMoreTokens()) {
            wxString field = token.NextToken();
            if(field.Left(3) == "COM" && field.substr(3).ToLong(&portNO)) {
                //cout<<"Field: "<<field<<endl;
                cmbComport->Append(field);
            }
        }
    }
    //----------------------------------------
    //检查配置文件中上次设置的串口
    FactoryPreset& preset = FactoryPreset::getPreset();
    preset.config->SetPath("/TCPServer");
    wxString cacheComP = preset.config->Read("COMP");
    cmbComport->SetStringSelection(cacheComP);
}

/**
* 只允许进程打开一个实例
**/
void TCP2COMDialog::OnInit(wxInitDialogEvent& event)
{
    HANDLE hMutex = CreateMutex(NULL,TRUE,_("TCP2COM"));
    if(hMutex && ERROR_ALREADY_EXISTS == GetLastError())
    {
        HWND hWnd = ::FindWindow(NULL,TEXT("网络转串口"));
        if(hWnd != NULL)
        {
            ::SwitchToThisWindow(hWnd,TRUE);
            ::ShowWindow(hWnd,SW_SHOWNORMAL);
        }
        //如果相同的进程已存在则关闭当前进程
        ExitProcess(0);
    }
    //-------------------------------------------
    FactoryPreset& preset = FactoryPreset::getPreset();
    preset.config->SetPath("TCPServer");
    txtHost->SetValue(preset.config->Read("HOST"));
    txtPort->SetValue(preset.config->Read("PORT"));
    /**
    * 界面初始化完成后自动加载所有的虚拟串口
    **/
    wxCommandEvent* loadCaller = new wxCommandEvent(wxEVT_COMMAND_BUTTON_CLICKED,ID_BUTTON4);
    OnbtnReloadClick(*loadCaller);

    cmbBaudrate->SetStringSelection(preset.config->Read("BAUD"));
    cmbDatabits->SetStringSelection(preset.config->Read("DATB"));
    cmbParitys->SetStringSelection(preset.config->Read("PARI"));
    //-------------------------------------------
    NetCommService& netService = NetCommService::getService();
    netService.addObserver(this);
    SerialCommService& comService = SerialCommService::getService();
    comService.addObserver(this);

    btnClose->Enable(false);
    Timer1.Start(500);
}

/**
* 安装虚拟串口驱动
**/
void TCP2COMDialog::OnbtnInstallClick(wxCommandEvent& event)
{
    btnInstall->Enable(false);
    VirtualCom& manager = VirtualCom::getManager();
    manager.installDriver();
    btnInstall->Enable(true);
}

/**
* 加载虚拟串口列表
**/
void TCP2COMDialog::OnbtnReloadClick(wxCommandEvent& event)
{
    int i = 0;
    size_t numOfPairs = 0;
    btnReload->Enable(false);
    VirtualCom& manager = VirtualCom::getManager();
    VirtualCom::CommPairType* commPairs = new VirtualCom::CommPairType[32];
    manager.loadCommPairs(commPairs,&numOfPairs);

    listComPairs->Clear();
    for(i=0;i<(int)numOfPairs;i++)
    {
        wxString item = "ComPair " + wxString::Format("%d",commPairs[i].index) + "    " + commPairs[i].comA + "<=>" + commPairs[i].comB;
        listComPairs->Append(item);
    }

    //---------------------------------
    delete [] commPairs;
    btnReload->Enable(true);

    //更新下拉列表框
    updateComports();
}

/**
* 删除指定的一对虚拟串口
**/
void TCP2COMDialog::OnbtnRemoveClick(wxCommandEvent& event)
{
    int i = 0;
    long pairIndex = 0;

    btnRemove->Enable(false);
    if(listComPairs->GetSelection() >= 0) {
        //cout<<"Delete Virtual Com Pair : "<<
        //listComPairs->GetString(listComPairs->GetSelection())<<endl;

        wxStringTokenizer token(listComPairs->GetString(listComPairs->GetSelection()),
                                " <=>",wxTOKEN_STRTOK);
        for(i=0;i<32;i++) {
            if(token.HasMoreTokens()) {
                if(token.NextToken() == "ComPair") {
                    if(token.NextToken().ToLong(&pairIndex)) {
                        cout<<"Delete Pair "<<pairIndex<<" !"<<endl;
                        VirtualCom& manager = VirtualCom::getManager();
                        manager.removeComPair((uint8_t)pairIndex);
                    }

                    /**
                    * 删除一对虚拟串口后需要重新加载虚拟串口列表
                    **/
                    wxCommandEvent* loadCaller = new wxCommandEvent(wxEVT_COMMAND_BUTTON_CLICKED,ID_BUTTON4);
                    OnbtnReloadClick(*loadCaller);

                    break;
                }
            }
        }
    }
    btnRemove->Enable(true);
}

/**
* 添加一对指定的虚拟串口
**/
void TCP2COMDialog::OnbtnAddPairClick(wxCommandEvent& event)
{
    long portA,portB;
    btnAddPair->Enable(false);
    if(txtCompA->GetValue().Left(3) == "COM" && txtCompB->GetValue().Left(3) == "COM") {
        if(txtCompA->GetValue().substr(3).ToLong(&portA) && txtCompB->GetValue().substr(3).ToLong(&portB)) {
            if(portA != portB) {        //一对虚拟串口的两个串口号不可能一样
                VirtualCom& manager = VirtualCom::getManager();
                manager.createComPair(txtCompA->GetValue(),txtCompB->GetValue());
                /**
                * 创建新的虚拟串口后需要重新加载虚拟串口列表
                **/
                wxCommandEvent* loadCaller = new wxCommandEvent(wxEVT_COMMAND_BUTTON_CLICKED,ID_BUTTON4);
                OnbtnReloadClick(*loadCaller);
            }
        }
    }
    btnAddPair->Enable(true);
}

/**
* 打开通信口
**/
void TCP2COMDialog::OnbtnOpenClick(wxCommandEvent& event)
{
    cmbComport->Enable(false);
    cmbBaudrate->Enable(false);
    cmbDatabits->Enable(false);
    cmbParitys->Enable(false);

    //保存输入的主机地址和端口号
    FactoryPreset& preset = FactoryPreset::getPreset();
    preset.config->SetPath("/TCPServer");
    preset.config->Write("HOST",txtHost->GetValue());
    preset.config->Write("PORT",txtPort->GetValue());
    preset.SaveConfig();

    //打开网络
    NetCommService& netService = NetCommService::getService();
    netService.open();
    //打开串口
    SerialCommService& comService = SerialCommService::getService();
    comService.open();

    btnOpen->Enable(false);
    btnClose->Enable(true);
}

/**
* 关闭通信口
**/
void TCP2COMDialog::OnbtnStopClick(wxCommandEvent& event)
{
    cmbComport->Enable(true);
    cmbBaudrate->Enable(true);
    cmbDatabits->Enable(true);
    cmbParitys->Enable(true);

    NetCommService& netService = NetCommService::getService();
    netService.close();
    SerialCommService& comService = SerialCommService::getService();
    comService.close();

    btnOpen->Enable(true);
    btnClose->Enable(false);
}

/**
* 当重新选择串口后,保存到配置文件
**/
void TCP2COMDialog::OncmbCompSelect(wxCommandEvent& event)
{
    FactoryPreset& preset = FactoryPreset::getPreset();
    preset.config->SetPath("/TCPServer");
    preset.config->Write("COMP",event.GetString());
    preset.SaveConfig();
}

void TCP2COMDialog::OnClose(wxCloseEvent& event)
{
    NetCommService& netService = NetCommService::getService();
    netService.close();
    SerialCommService& comService = SerialCommService::getService();
    comService.close();

    EndDialog(0);
}

void TCP2COMDialog::OncmbBaudrateSelect(wxCommandEvent& event)
{
    FactoryPreset& preset = FactoryPreset::getPreset();
    preset.config->SetPath("/TCPServer");
    preset.config->Write("BAUD",event.GetString());
    preset.SaveConfig();
}

void TCP2COMDialog::OncmbDatabitsSelect(wxCommandEvent& event)
{
    FactoryPreset& preset = FactoryPreset::getPreset();
    preset.config->SetPath("/TCPServer");
    preset.config->Write("DATB",event.GetString());
    preset.SaveConfig();
}

void TCP2COMDialog::OncmbParitysSelect(wxCommandEvent& event)
{
    FactoryPreset& preset = FactoryPreset::getPreset();
    preset.config->SetPath("/TCPServer");
    preset.config->Write("PARI",event.GetString());
    preset.SaveConfig();
}

/**
* 计时器用于检测网络和串口的通信状态
**/
void TCP2COMDialog::OnTimer1Trigger(wxTimerEvent& event)
{
    //检测网络状态
    NetCommService& netService = NetCommService::getService();
    if(netService.isOpen() && btnOpen->IsEnabled() == false) {      //已开启网络
        if(netService.clientCount == 0) {
            labNetState->SetLabel("网络未连接...");
            labNetState->SetForegroundColour(*(wxColour *)wxYELLOW);
        }
        if(netService.clientCount == 1) {
            labNetState->SetLabel("网络连接正常!");
            labNetState->SetForegroundColour(*(wxColour *)wxBLUE);
        }
        if(netService.clientCount > 1) {
            labNetState->SetLabel("网络连接异常!");
            labNetState->SetForegroundColour(*(wxColour *)wxRED);
        }
    }else{
        labNetState->SetLabel("网络未打开...");
        labNetState->SetForegroundColour(*(wxColour *)wxBLACK);
    }
    //----------------------------------------------
    //检测串口状态
    SerialCommService& compService = SerialCommService::getService();
    if(compService.isOpen()) {
        labComState->SetLabel("串口已打开!");
        labComState->SetForegroundColour(*(wxColour *)wxBLUE);
    }else{
        labComState->SetLabel("串口未打开...");
        labComState->SetForegroundColour(*(wxColour *)wxBLACK);
    }
}
