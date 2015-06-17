
#include "AutoResetEvent.h"

namespace bde{

    AutoResetEvent::AutoResetEvent(){
        mSignalled = false;
    }

    void AutoResetEvent::Notify(){
        //mMutex.Lock();
        mSignalled = true;
        mCondVariable.NotifyOne();
    }

    void AutoResetEvent::Wait(){
        //mMutex.Lock();
        if( !mSignalled ){
            mCondVariable.Wait(mMutex);
        }
        mSignalled = false;
    }
} // namespace bde
