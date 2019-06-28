/***************************************************************
 * Name:      TCP2COMApp.cpp
 * Purpose:   Code for Application Class
 * Author:    David (lw.7@foxmail.com)
 * Created:   2019-05-07
 * Copyright: David ()
 * License:
 **************************************************************/

#include "TCP2COMApp.h"

//(*AppHeaders
#include "TCP2COMMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(TCP2COMApp);

bool TCP2COMApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	TCP2COMDialog Dlg(0);
    	SetTopWindow(&Dlg);
    	Dlg.ShowModal();
    	wxsOK = false;
    }
    //*)
    return wxsOK;

}
