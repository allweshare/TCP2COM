#ifndef FRAMEOBSERVER_H
#define FRAMEOBSERVER_H

#include <stdint.h>

class FrameObserver
{
    public:
        //FrameObserver();
        //virtual ~FrameObserver();

        /**
        * 定义数据的来源
        **/
        typedef enum {
            COMPORT,    //串口
            NETWORK     //网络
        } DataSource;

        //定义接收数据的事件
        virtual void onReciveData(DataSource source,uint8_t * data,size_t len) = 0;

    protected:

    private:
};

#endif // FRAMEOBSERVER_H
