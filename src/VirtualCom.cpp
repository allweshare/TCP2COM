#include "VirtualCom.h"
#include "FactoryPreset.h"
#include <wx/filename.h>
#include <wx/dir.h>
#include <wx/tokenzr.h>
#include <windows.h>
#include <iostream>

using namespace std;

VirtualCom::VirtualCom()
{

}

/**
* 加载虚拟串口列表
**/
void VirtualCom::loadCommPairs(CommPairType* commPairs,size_t* numOfPairs)
{
    uint8_t pariCount = 0;
    uint8_t i = 0;
    long cvtIndex = 0;

    char* resp = new char[1024];
    memset(resp,0,1024);

    FactoryPreset& preset = FactoryPreset::getPreset();
    wxString cmdStr = preset.vcom_driver_path + " list";

    execReadBack(cmdStr,resp,1024);
    cout<<resp<<endl;
    //-------------------------------------
    wxString readBuff(resp);
    wxStringTokenizer token(readBuff,"\r\n =",wxTOKEN_STRTOK);

    for(i=0;i<32;i++) {
        if(token.HasMoreTokens()) {
            wxString pars = token.GetNextToken();
            if(pars.Left(2) == "CN") {
                //cout<<"Find Pair: "<<pars.substr(4,1)<<endl;
                if(pars.substr(4,1).ToLong(&cvtIndex)) {
                    commPairs[pariCount].index = (uint8_t)cvtIndex;
                }
                token.GetNextToken();
                wxString port = token.GetNextToken();
                if(pars.substr(3,1) == "A") {
                    commPairs[pariCount].comA = port;
                    //cout<<"PortA: "<<port<<endl;
                }
                if(pars.substr(3,1) == "B") {
                    commPairs[pariCount].comB = port;
                    //cout<<"PortB: "<<port<<endl;

                    pariCount ++;
                }
            }
        }else{
            break;
        }
    }

    //输出数量
    *(size_t *)numOfPairs = pariCount;
    //-------------------------------------
    delete [] resp;
}

/**
* 创建一对新的虚拟串口
**/
void VirtualCom::createComPair(wxString comportA,wxString comportB)
{
    FactoryPreset& preset = FactoryPreset::getPreset();
    wxString cmdStr = preset.vcom_driver_path + " install PortName=" + comportA + " PortName=" + comportB;
    cout<<"Command: "<<cmdStr<<endl;
    char* resp = new char[1024];
    memset(resp,0,1024);
    execReadBack(cmdStr,resp,1024);
    delete [] resp;
}

/**
* 删除指定的一对虚拟串口
**/
void VirtualCom::removeComPair(uint8_t pairIndex)
{
    FactoryPreset& preset = FactoryPreset::getPreset();
    wxString cmdStr = preset.vcom_driver_path + " remove " + wxString::Format("%d",pairIndex);
    cout<<"Command: "<<cmdStr<<endl;
    char* resp = new char[1024];
    memset(resp,0,1024);
    execReadBack(cmdStr,resp,1024);
    delete [] resp;
}

/**
* 安装虚拟串口驱动
**/
uint8_t VirtualCom::installDriver()
{
    uint8_t ret = 0;
    FactoryPreset& preset = FactoryPreset::getPreset();
    wxString cmdStr = preset.vcom_driver_path + " preinstall";
    cout<<"Command: "<<cmdStr<<endl;

    char* resp = new char[1024];
    memset(resp,0,1024);
    ret = execReadBack(cmdStr,resp,1024);
    cout<<resp<<endl;
    delete [] resp;
    return ret;
}

/**
* 执行一个指令并读取其命令行响应
* 传入的命令必须加.exe
**/
uint8_t VirtualCom::execReadBack(wxString cmd,char* read_buff,size_t buff_len)
{
    wxStringTokenizer token(cmd," ");
    wxString dirPath;
    if(token.HasMoreTokens()) {
        wxString exePath = token.GetNextToken();
        //cout<<"First: "<<exePath<<endl;
        //获取指定命令的运行目录
        if(wxFileExists(exePath))
        {
            wxFileName filePath(exePath);
            dirPath = filePath.GetPath(wxPATH_GET_VOLUME | wxPATH_GET_SEPARATOR);
            //cout<<"Exists: "<<dirPath<<endl;
        }else{
            return -1;
        }
    }
    //---------------------------------------
    DWORD bytesRead;
    HANDLE hRead,hWrite;
    SECURITY_ATTRIBUTES sa;
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.lpSecurityDescriptor = NULL;
    sa.bInheritHandle = TRUE;

    if(!CreatePipe(&hRead,&hWrite,&sa,0))
    {
        return -1;
    }

    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    si.cb = sizeof(STARTUPINFO);
    GetStartupInfo(&si);
    si.hStdError = hWrite;
    si.hStdOutput = hWrite;
    si.wShowWindow = SW_HIDE;
    si.dwFlags = STARTF_USESHOWWINDOW|STARTF_USESTDHANDLES;

    TCHAR wchar_cmd[256];
    wcscpy(wchar_cmd,cmd.wc_str());

    TCHAR wchar_path[256];
    wcscpy(wchar_path,dirPath.wc_str());

    if(!CreateProcess(NULL,wchar_cmd,NULL,NULL,TRUE,0,NULL,wchar_path,&si,&pi))
    {
        return -1;
    }

    WaitForSingleObject(pi.hProcess,INFINITE);
    //printf("Process Terminate !\r\n");

    CloseHandle(hWrite);
    //printf("Get Output OK !\r\n");

    ReadFile(hRead,read_buff,buff_len,&bytesRead,NULL);
    return 0;
}

VirtualCom::~VirtualCom()
{
    //dtor
}
