#ifndef COMMLISTENERBASE_H
#define COMMLISTENERBASE_H

#include <wx/thread.h>

class CommListenerBase : public wxThread
{
    public:
        virtual ~CommListenerBase(){}
        virtual wxThread::ExitCode Entry() = 0;
        virtual void SetBrock(bool setQuit) = 0;

    protected:
        CommListenerBase():wxThread(wxTHREAD_DETACHED){}
    private:
        CommListenerBase(CommListenerBase& listener);
};

#endif // COMMLISTENERBASE_H
