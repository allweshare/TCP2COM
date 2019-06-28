#ifndef SERIALCOMMSERVICE_H
#define SERIALCOMMSERVICE_H

#include <set>
#include <string>
#include <sstream>

#include "CommServiceBase.h"
#include <windows.h>

class SerialCommService : public CommServiceBase
{
    public:
        static SerialCommService& getService()
        {
            static SerialCommService service;
            return service;
        }
        ~SerialCommService();
        //打开通信链路
        void open();
        //发送数据
        void send(uint8_t * data,uint32_t len);
        //关闭通信链路
        void close();
    protected:

    private:
        HANDLE hComPort;                    //串口句柄
        const size_t RECV_BUFF_SIZE;
        uint8_t * recv_buff;                //接收缓冲区
        const size_t SEND_BUFF_SIZE;
        uint8_t * send_buff;                //发送缓冲区

        //禁用拷贝构造
        SerialCommService();
        SerialCommService(const SerialCommService&);
        void operator=(SerialCommService&);
};

#endif // SERIALCOMMSERVICE_H
