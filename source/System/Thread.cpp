#include "Thread.h"
#include "../Debug/Logger.h"

namespace bde{

    /* ****************************
     * Construction & Destruction *
     * ***************************/
    Thread::Thread(){

    }

    Thread::~Thread(){

    }

    void Thread::Start(){
        LOG_INFO("Starting Thread");
#if USE_PTHREAD == 1
        pthread_create(&mThread, 0, Thread::dispatch, this);
#else
        mThread = std::thread(Thread::dispatch, this);
#endif
        LOG_INFO("Thread Started");
    }

    void Thread::Join(){
#if USE_PTHREAD == 1
        pthread_join(mThread,0);
#else
        mThread.join();
#endif
    }

    void* Thread::dispatch(void *ptr){
        LOG_INFO("Dispatching");
#if USE_PTHREAD == 1
        if(!ptr) return 0;

        static_cast<Thread*>(ptr)->run();
        pthread_exit(ptr);

        return 0;
#else
        if(!ptr) return 0;

        static_cast<Thread*>(ptr)->run();

        return 0;
#endif
        LOG_INFO("Dispatched");
    }

} // namespace bde
