#include "FactoryPreset.h"

#include <iostream>
#include <wx/stdpaths.h>
#include <wx/filename.h>
#include <wx/wfstream.h>
#include <wx/dir.h>
#include <wx/msgdlg.h>

using namespace std;

FactoryPreset::FactoryPreset() :
    app_exe_path(wxStandardPaths::Get().GetExecutablePath()),       //获取可执行程序路径
    app_root_dir(app_exe_path.GetPath(wxPATH_GET_VOLUME | wxPATH_GET_SEPARATOR)),
    cfg_file_path(app_root_dir+"config.ini")                        //配置文件路径
{
    cout<<"FactoryPreset init ..."<<endl;

    SYSTEM_INFO si;
    GetNativeSystemInfo(&si);
    if(si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64 ||
       si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64) {
        vcom_driver_path = app_root_dir + "com0com_x64\\setupc.exe";
    }else{
        vcom_driver_path = app_root_dir + "com0com_x86\\setupc.exe";
    }
    cout<<"VCOM Driver: "<<vcom_driver_path<<endl;

    //---------------------------------------------
    if(!wxFile::Exists(cfg_file_path))
    {
        wxFileOutputStream outStream(cfg_file_path);    //文件输出流
        cout<<"Create Default Configuration !"<<endl;
        //如果配置文件不存在，创建默认配置
        wxFileConfig* defaultCfg = new wxFileConfig();
        defaultCfg->SetPath("/TCPServer");
        defaultCfg->Write("HOST","127.0.0.1");          //默认TCP服务器地址
        defaultCfg->Write("PORT","8888");               //默认TCP端口
        defaultCfg->Write("COMP","COM1");               //默认串口
        defaultCfg->Write("BAUD","19200");              //默认波特率
        defaultCfg->Write("DATB","8");                  //默认数据位
        defaultCfg->Write("PARI","None");               //默认校验位

        defaultCfg->Save(outStream);
        //及时关闭文件流
        outStream.Close();
    }

    /**
    *   到这一步必须确保已经存在默认配置
    **/
    wxFileInputStream inStream(cfg_file_path);
    if(inStream.IsOk())
    {
        config = make_shared<wxFileConfig>(inStream);
    }

}

void FactoryPreset::SaveConfig()
{
    if(config != NULL)
    {
        wxFileOutputStream outStream(cfg_file_path);    //文件输出流
        if(outStream.IsOk())
        {
            config->Save(outStream);
        }
    }
}

FactoryPreset::~FactoryPreset()
{
    //dtor
}
