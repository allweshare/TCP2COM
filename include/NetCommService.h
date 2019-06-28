#ifndef NETCOMMSERVICE_H
#define NETCOMMSERVICE_H

#include "CommServiceBase.h"
#include <wx/string.h>
#include <wx/socket.h>
#include <wx/event.h>
#include <wx/atomic.h>

class NetCommService : public CommServiceBase
{
    public:
        static NetCommService& getService()
        {
            static NetCommService service;
            return service;
        }
        ~NetCommService();

        //打开通信链路
        void open();
        //发送数据
        void send(uint8_t * data,uint32_t len);
        //关闭通信链路
        void close();
        //统计客户端连接数
        wxAtomicInt clientCount;
    protected:

    private:
        const size_t RECV_BUFF_SIZE;
        uint8_t * recv_buff;                //接收缓冲区
        const size_t SEND_BUFF_SIZE;
        uint8_t * send_buff;                //发送缓冲区

        wxSocketServer* socketServer;       //服务器端Socket

        //禁用拷贝构造
        NetCommService();
        NetCommService(const NetCommService&);
        void operator=(NetCommService&);
};

#endif // NETCOMMSERVICE_H
