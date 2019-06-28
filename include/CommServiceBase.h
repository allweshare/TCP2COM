#ifndef COMMSERVICEBASE_H
#define COMMSERVICEBASE_H

#include "CommListenerBase.h"
#include "FrameObserver.h"
#include <iostream>
#include <vector>

class CommServiceBase
{
    public:
        virtual ~CommServiceBase();
        //打开通信链路
        virtual void open() = 0;
        //发送数据
        virtual void send(uint8_t * data,uint32_t size) = 0;
        //关闭通信链路
        virtual void close() = 0;
        //添加协议帧观察者
        void addObserver(FrameObserver* observer);
        //获取当前通信链路的监听线程
        CommListenerBase* getCommListener();
        //通知所有观察者
        void notifyObservers(FrameObserver::DataSource source,uint8_t * data,size_t len);
        //通信链路是否已经打开
        bool isOpen(void);
    protected:
        //标识通信服务是否还在运行
        bool isRun;
        CommServiceBase();              //该类不可实例化

        /**
        *   每种通信模式使用自己的方式接收数据
        **/
        CommListenerBase* listener;
    private:
        std::vector<FrameObserver*> observerList;
        CommServiceBase(CommServiceBase& commService);

};

#endif // COMMSERVICEBASE_H
