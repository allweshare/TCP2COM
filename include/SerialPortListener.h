#ifndef SERIALPORTLISTENER_H
#define SERIALPORTLISTENER_H

#include <iostream>
#include <iomanip>
#include <wx/thread.h>

#include <windows.h>
#include "CommListenerBase.h"

class SerialPortListener : public CommListenerBase
{
    public:
        SerialPortListener(HANDLE hCom,uint8_t * recv_buff,const size_t recv_len);
        virtual ~SerialPortListener();
        void SetBrock(bool setQuit);
    protected:
        wxThread::ExitCode Entry();
    private:
        HANDLE hComPort;
        uint8_t * RECV_BUFF;
        const size_t BUFF_SIZE;
        volatile bool isQuit;
        int readComPort(uint8_t * read_buff,unsigned long readLen);
};

#endif // SERIALPORTLISTENER_H
