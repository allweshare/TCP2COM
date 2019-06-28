#ifndef TCPSERVERLISTENER_H
#define TCPSERVERLISTENER_H

#include <iostream>
#include <iomanip>
#include <wx/thread.h>
#include <wx/socket.h>
#include <wx/sckstrm.h>

#include "CommListenerBase.h"

class TCPServerListener : public CommListenerBase
{
    public:
        TCPServerListener(wxSocketServer* socket,uint8_t * recv_buff,const size_t recv_len);
        virtual ~TCPServerListener();
        void SetBrock(bool setQuit);
        wxSocketBase* getClient();
        void writeData(uint8_t* data,size_t len);
    protected:
        wxThread::ExitCode Entry();
    private:
        wxSocketServer* serverSocket;
        uint8_t * RECV_BUFF;
        const size_t BUFF_SIZE;
        volatile bool isQuit;
        wxSocketInputStream* inputStream;
        wxSocketOutputStream* outputStream;
        wxSocketBase* socket;

        int readNetPort(uint8_t * read_buff,unsigned long readLen);
};

#endif // TCPSERVERLISTENER_H
