#include "CommServiceBase.h"

using namespace std;

CommServiceBase::CommServiceBase()
{
    //ctor
}

void CommServiceBase::addObserver(FrameObserver* observer)
{
    for(vector<FrameObserver *>::iterator itert = observerList.begin();itert != observerList.end();)
    {
        if(observer == *itert)
        {
            itert = observerList.erase(itert);
        }else{
            itert ++;
        }
    }
    observerList.push_back(observer);
}

/**
* 通知所有观察者
**/
void CommServiceBase::notifyObservers(FrameObserver::DataSource source,uint8_t * data,size_t len)
{
    for(vector<FrameObserver*>::iterator itert = observerList.begin();itert != observerList.end(); itert ++)
    {
        (*itert)->onReciveData(source,data,len);
    }
}

CommListenerBase* CommServiceBase::getCommListener()
{
    return listener;
}

/**
*   通信链路是否已经打开
**/
bool CommServiceBase::isOpen(void)
{
    return isRun;
}

CommServiceBase::~CommServiceBase()
{
    //dtor
}
