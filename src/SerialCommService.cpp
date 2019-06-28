#include "SerialCommService.h"
#include "SerialPortListener.h"
#include "FactoryPreset.h"

//网络收发缓冲区都设置为10KB大小
SerialCommService::SerialCommService() : RECV_BUFF_SIZE(10240),SEND_BUFF_SIZE(10240)
{
    recv_buff = new uint8_t[RECV_BUFF_SIZE];
    send_buff = new uint8_t[SEND_BUFF_SIZE];
    isRun = false;
}

/**
*   打开串口
**/
void SerialCommService::open()
{
    if(isRun)
    {
        close();
    }
    //从配置文件中读取串口
    FactoryPreset& preset = FactoryPreset::getPreset();
    preset.config->SetPath("/TCPServer");

    wxString commPort = preset.config->Read("COMP");
    wxString baudrate = preset.config->Read("BAUD");
    wxString dataBits = preset.config->Read("DATB");
    wxString parityBits = preset.config->Read("PARI");
    wxString stopsBits = "1";

    //这里串口号需要加前缀
    hComPort = CreateFile(commPort,                         //通信口
                           GENERIC_READ|GENERIC_WRITE,      //允许读写
                           0,                               //独占方式
                           NULL,                            //安全属性
                           OPEN_EXISTING,                   //
                           FILE_FLAG_OVERLAPPED,            //重叠IO,异步串口
                           NULL);                           //不使用模板

    if(hComPort == INVALID_HANDLE_VALUE)
    {
        cerr<<"Can't open SerialPort: "<<commPort<<" ! File:"<<__FILE__<<"; Line:"<<__LINE__<<endl;
    }else{
        //cout<<"Create File Success ! "<<endl;
        //------------------------------
        DCB comPortDCB;

        //设置输入输出缓冲区大小
        SetupComm(hComPort,RECV_BUFF_SIZE,SEND_BUFF_SIZE);

        COMMTIMEOUTS commTimeout;
        //设置读取超时
        commTimeout.ReadIntervalTimeout = 100;
        commTimeout.ReadTotalTimeoutMultiplier = 100;		//读取和写入操作可能分多次进行,每次的间隔超时
        commTimeout.ReadTotalTimeoutConstant = 200;	        //这里是总的读取超时,如果数据量很大,应加大该数值
        //设置写入超时
        commTimeout.WriteTotalTimeoutMultiplier = 100;
        commTimeout.WriteTotalTimeoutConstant = 100;
        SetCommTimeouts(hComPort,&commTimeout);

        //获取到之前的串口参数
        GetCommState(hComPort,&comPortDCB);

        long baudrateVal;
        if(baudrate.ToLong(&baudrateVal)) {
            comPortDCB.BaudRate = (DWORD)baudrateVal;
        }
        long byteBitsVal;
        if(dataBits.ToLong(&byteBitsVal)) {
            comPortDCB.ByteSize = (BYTE)byteBitsVal;
        }

        if(parityBits == "None") {
            comPortDCB.Parity = NOPARITY;
        }else if(parityBits == "Odd") {
            comPortDCB.Parity = ODDPARITY;
        }else if(parityBits == "Even") {
            comPortDCB.Parity = EVENPARITY;
        }else if(parityBits == "Mark") {
            comPortDCB.Parity = MARKPARITY;
        }else if(parityBits == "Space") {
            comPortDCB.Parity = SPACEPARITY;
        }else {
            cerr<<"SerialPort ParityBits invalid: "<<parityBits<<" ! File:"<<__FILE__<<"; Line:"<<__LINE__<<endl;
        }

        if(stopsBits == "1"){
            comPortDCB.StopBits = ONESTOPBIT;
        }else if(stopsBits == "1.5"){
            comPortDCB.StopBits = ONE5STOPBITS;
        }else if(stopsBits == "2"){
            comPortDCB.StopBits = TWOSTOPBITS;
        }else{
            cerr<<"SerialPort StopBits invalid: "<<stopsBits<<" ! File:"<<__FILE__<<"; Line:"<<__LINE__<<endl;
        }
        //修改串口参数
        SetCommState(hComPort,&comPortDCB);
        //清空发送和接收缓冲区
        PurgeComm(hComPort,PURGE_TXCLEAR|PURGE_RXCLEAR);
        //------------------------------
        //创建串口监听线程
        listener = new SerialPortListener(hComPort,recv_buff,RECV_BUFF_SIZE);

        //标记服务为运行态
        isRun = true;
    }
}

/**
*   通过串口发送数据
**/
void SerialCommService::send(uint8_t * data,uint32_t len)
{
    BOOL bWriteRet;
    DWORD dwWritedNum;
    OVERLAPPED ovlpWrite;

    memset(&ovlpWrite,0,sizeof(OVERLAPPED));
    ovlpWrite.hEvent = CreateEvent(NULL,TRUE,FALSE,NULL);
    bWriteRet = WriteFile(hComPort,data,len,&dwWritedNum,&ovlpWrite);
    if(!bWriteRet)			//在异步串口中,ReadFile返回FALSE不一定就是读取错误
	{
	    if(GetLastError() == ERROR_IO_PENDING)
		{
		    //阻塞一段时间直到串口读取操作完成
		    WaitForSingleObject(ovlpWrite.hEvent,1000);
		}
	}
}

/**
*   关闭当前串口
**/
void SerialCommService::close()
{
    //先确保Listener已经关闭
    if(listener != NULL)
    {
        //listener->SetBrock(true);
        listener->TestDestroy();
//        if(listener->Delete() == wxTHREAD_NO_ERROR)
//        {
//            cout<<"SerialPort Listener Has be Terminated !"<<endl;
//        }
    }
    //关闭串口
    CloseHandle(hComPort);
    isRun = false;
}

SerialCommService::~SerialCommService()
{
    delete [] recv_buff;
    delete [] send_buff;

    //不用手动释放DETACHED线程,在线程结束时自己会释放资源
    //delete listener;
}
