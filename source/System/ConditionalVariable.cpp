#include "ConditionalVariable.h"

namespace bde {

    ConditionalVariable::ConditionalVariable() {
#if USE_PTHREAD == 1
        pthread_cond_init(&mConditional, 0);
#else
#endif
    }

    ConditionalVariable::~ConditionalVariable() {
#if USE_PTHREAD == 1
        pthread_cond_destroy(&mConditional);
#else
#endif
    }

    void ConditionalVariable::NotifyOne() {
#if USE_PTHREAD == 1
        pthread_cond_signal(&mConditional);
#else
        mConditional.notify_one();
#endif
    }

    void ConditionalVariable::NotifyAll() {
#if USE_PTHREAD == 1
        pthread_cond_broadcast(&mConditional);
#else
        mConditional.notify_all();
#endif
    }

    void ConditionalVariable::Wait(Mutex &mutex) {
#if USE_PTHREAD == 1
        pthread_cond_wait(mConditional, mutex.mMutex);
#else
        std::unique_lock<std::mutex> lck(mutex.mMutex);
        mConditional.wait(lck);
#endif
    }
} // namespace bde
