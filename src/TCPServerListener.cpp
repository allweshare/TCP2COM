#include "TCPServerListener.h"
#include "NetCommService.h"

using namespace std;

TCPServerListener::TCPServerListener(wxSocketServer* socket,uint8_t * recv_buff,const size_t recv_len) :
    serverSocket(socket),
    RECV_BUFF(recv_buff),
    BUFF_SIZE(recv_len),
    isQuit(false)
{
    if(wxThread::Run() == wxTHREAD_NO_ERROR)
    {
        wxIPV4address remoteAddr;
        serverSocket->GetLocal(remoteAddr);
        cout<<"开始监听 "<<remoteAddr.IPAddress()<<" : "<<remoteAddr.Service()<<" 网络端口!"<<endl;
    }else{
        cerr<<"无法侦听网络端口! File:"<<__FILE__<<"; Line:"<<__LINE__<<endl;
    }
}

wxThread::ExitCode TCPServerListener::Entry()
{
    isQuit = false;
    NetCommService& netService = NetCommService::getService();

    while(!TestDestroy())
    {
        /**
        *   以无阻塞的方式接收socket连接
        *   立即返回不阻塞GUI
        **/
        socket = serverSocket->Accept(true);
        if(socket == NULL)
        {
            Sleep(1000);             //如果没有接收到连接休眠1秒,防止CPU占满
        }else{

            wxIPV4address remoteAddr;
            socket->GetPeer(remoteAddr);
            cout<<"接收到客户端连接: "<<remoteAddr.IPAddress()<<" : "<<remoteAddr.Service()<<endl;
            //增加计数
            wxAtomicInc(netService.clientCount);

            //在接收完数据之前,阻塞别的操作,不阻塞GUI
            //socket->SetFlags(wxSOCKET_WAITALL|wxSOCKET_BLOCK);
            socket->SetFlags(wxSOCKET_NOWAIT);
            inputStream = new wxSocketInputStream(*socket);
            outputStream = new wxSocketOutputStream(*socket);

            while(!TestDestroy())
            {
                /**
                *   避免过多的占用系统CPU
                *   这里加一点休眠释放一点时间片
                *   取值应在100ms至500ms之间,取决于每两次接收数据的间隔
                *   如果取消掉该延迟会导致CPU占用率爆满
                **/
                Sleep(200);

                if(isQuit == false)
                {
                    //------------------------------------------
                    if(socket->IsData())
                    {   //有新的数据接收到
                        readNetPort(RECV_BUFF,BUFF_SIZE);
                    }
                    if(socket->IsDisconnected())
                    {   //检测到客户端断开连接
                        cout<<"检测到客户端断开连接! "<<remoteAddr.IPAddress()<<" : "<<remoteAddr.Service()<<" ......"<<endl;
                        socket->Close();
                        //递减计数
                        if(netService.clientCount > 0) {
                            wxAtomicDec(netService.clientCount);
                        }
                        break;
                    }
                }else{
                    //当服务器要关闭时要先关掉所有客户端的连接
                    socket->Close();
                    //递减客户端连接数
                    if(netService.clientCount > 0) {
                        wxAtomicDec(netService.clientCount);
                    }
                    isQuit = true;
                    Delete();
                    break;
                }
            }
        }
    }
    return (wxThread::ExitCode)0;
}

/**
* 向当前的输出流写入数据
**/
void TCPServerListener::writeData(uint8_t* data,size_t len)
{
    if(outputStream != NULL) {
        outputStream->Write(data,len);
    }
}

/**
*   读取网口数据
**/
int TCPServerListener::readNetPort(uint8_t * read_buff,unsigned long readLen)
{
    size_t i = 0;
    inputStream->Read(read_buff,readLen);
    size_t dwBytesRead = inputStream->LastRead();
    //----------------------------------------------------
    //输出原始数据
    if(dwBytesRead > 6)
    {
        //如果数据量大于6字节
        for(i=0;i<3;i++)
        {
            cout<<"0x"<<setiosflags(ios::uppercase)<<hex<<setfill('0')<<setw(2)<<(int)read_buff[i]<<" ";
        }
        cout<<"... ";
        for(i=(dwBytesRead-3);i<dwBytesRead;i++)
        {
            cout<<"0x"<<setiosflags(ios::uppercase)<<hex<<setfill('0')<<setw(2)<<(int)read_buff[i]<<" ";
        }
        cout<<dec<<endl;
    }else{
        //如果数据量小于6字节
        for(i=0;i<dwBytesRead;i++)
        {
            cout<<"0x"<<setiosflags(ios::uppercase)<<hex<<setfill('0')<<setw(2)<<(int)read_buff[i]<<" ";
        }
        cout<<dec<<endl;
    }
    //----------------------------
    NetCommService& netService = NetCommService::getService();
    netService.notifyObservers(FrameObserver::DataSource::NETWORK,read_buff,dwBytesRead);

    return dwBytesRead;
}

wxSocketBase* TCPServerListener::getClient()
{
    return socket;
}

void TCPServerListener::SetBrock(bool setQuit)
{
    isQuit = setQuit;
}

TCPServerListener::~TCPServerListener()
{
    if(socket != NULL)
    {
        socket->Destroy();
    }
}
