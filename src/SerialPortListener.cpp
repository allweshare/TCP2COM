#include "SerialPortListener.h"
#include "SerialCommService.h"
#include "FactoryPreset.h"

SerialPortListener::SerialPortListener(HANDLE hCom,uint8_t * recv_buff,const size_t recv_len) :
    hComPort(hCom),
    RECV_BUFF(recv_buff),
    BUFF_SIZE(recv_len),
    isQuit(false)
{
    if(wxThread::Run() == wxTHREAD_NO_ERROR)
    {
        FactoryPreset& preset = FactoryPreset::getPreset();
        preset.config->SetPath("/TCPServer");
        cout<<"开始监听 "<<preset.config->Read("COMP")<<" 通信口!"<<endl;
    }else{
        cerr<<"不能启动串口读取线程! File:"<<__FILE__<<"; Line:"<<__LINE__<<endl;
    }
}

/**
*   具体的线程函数
**/
wxThread::ExitCode SerialPortListener::Entry()
{
    isQuit = false;
    while(!TestDestroy())
    {
        /**
        *   避免过多的占用系统CPU
        *   这里加一点休眠释放一点时间片
        *   取值应在10ms至100ms之间,取决于每两次接收数据的间隔
        *   如果取消掉该延迟会导致CPU占用率爆满
        **/
        Sleep(10);

        //开始读取串口数据
        if(isQuit == false)
        {
            //清空缓冲区并重新读取
            memset(RECV_BUFF,0,BUFF_SIZE);
            readComPort(RECV_BUFF,BUFF_SIZE);
        }else{
            isQuit = true;
            Delete();
            break;
        }
    }
    return (wxThread::ExitCode)0;
}

/**
*   从串口读取数据
**/
int SerialPortListener::readComPort(uint8_t * read_buff,unsigned long readLen)
{
    DWORD i = 0;
	DWORD dwBytesRead = readLen;
	BOOL bReadRet;
	DWORD dwErrorFlag;
	COMSTAT statCom;
	OVERLAPPED ovlpRead;

	ClearCommError(hComPort,&dwErrorFlag,&statCom);
	if(!statCom.cbInQue)
	{
		return -1;			//读取缓冲区中没有数据
	}
	memset(&ovlpRead,0,sizeof(OVERLAPPED));
	ovlpRead.hEvent = CreateEvent(NULL,TRUE,FALSE,NULL);
	bReadRet = ReadFile(hComPort,read_buff,readLen,&dwBytesRead,&ovlpRead);
	if(!bReadRet)			//在异步串口中,ReadFile返回FALSE不一定就是读取错误
	{
		if(GetLastError() == ERROR_IO_PENDING)
		{
            GetOverlappedResult(hComPort,
					&ovlpRead,
					&dwBytesRead,
					TRUE		//一直阻塞直到串口读取操作完成
			);
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

            //通知观察者接收数据
            SerialCommService& comService = SerialCommService::getService();
            comService.notifyObservers(FrameObserver::DataSource::COMPORT,read_buff,dwBytesRead);

            //----------------------------------------------------
            //这里清空缓冲区可能会导致接收缓冲区数据丢失
            //PurgeComm(hComPort, PURGE_TXABORT|PURGE_RXABORT|PURGE_TXCLEAR|PURGE_RXCLEAR);
			return dwBytesRead;
		}
	}
	return dwBytesRead;
}

/**
*   如果setQuit = true,将强迫线程退出
**/
void SerialPortListener::SetBrock(bool setQuit)
{
    isQuit = setQuit;
}

SerialPortListener::~SerialPortListener()
{
    //dtor
}
