#include "NetCommService.h"
#include "FactoryPreset.h"
#include "TCPServerListener.h"

//串口收发缓冲区都设置为10KB大小
NetCommService::NetCommService() : clientCount(0),RECV_BUFF_SIZE(10240),SEND_BUFF_SIZE(10240)
{
    recv_buff = new uint8_t[RECV_BUFF_SIZE];
    send_buff = new uint8_t[SEND_BUFF_SIZE];
    isRun = false;
}

/**
*   开启网络端口
**/
void NetCommService::open()
{
    if(isRun)
    {
        close();
    }

    //从配置文件中读取网络通信参数
    FactoryPreset& preset = FactoryPreset::getPreset();
    preset.config->SetPath("/TCPServer");
    wxString localIP = preset.config->Read("HOST");
    wxString localPort = preset.config->Read("PORT");

    cout<<"建立服务器连接: "<<localIP<<" : "<<localPort<<endl;

    wxIPV4address localAddr;
    localAddr.Hostname(localIP);
    localAddr.Service(localPort);

    socketServer = new wxSocketServer(localAddr);
    if(!socketServer->Ok())
    {
        //不能启动服务器
        //更新状态栏显示信息
        cerr<<"服务器Socket不能启动! File:"<<__FILE__<<"; Line:"<<__LINE__<<endl;
    }else{
        //只检测连接事件
        socketServer->SetNotify(wxSOCKET_CONNECTION_FLAG);

        cout<<"服务器Socket成功启动! "<<endl;
        listener = new TCPServerListener(socketServer,recv_buff,RECV_BUFF_SIZE);

        //标记服务为运行态
        isRun = true;
    }
}

/**
*   通过网络发送数据
**/
void NetCommService::send(uint8_t * data,uint32_t len)
{
    if(listener != NULL) {
        TCPServerListener* tcpListener = (TCPServerListener *)listener;
        if(tcpListener != NULL)
            tcpListener->writeData(data,len);
    }
}

/**
*   关闭网络端口
**/
void NetCommService::close()
{
    if(listener != NULL)
    {
        listener->SetBrock(true);
    }
    if(socketServer != NULL)
    {
        socketServer->Close();
    }
}

NetCommService::~NetCommService()
{
    delete [] recv_buff;
    delete [] send_buff;
}
