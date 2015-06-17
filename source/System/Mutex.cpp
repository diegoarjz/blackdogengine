#include "Mutex.h"

namespace bde {

    /* ****************************
     * Construction & Destruction *
     * ***************************/
    Mutex::Mutex() {
#if USE_PTHREAD == 1
        pthread_mutex_init(&mMutex, 0);
#else
#endif
    }

    Mutex::~Mutex() {
#if USE_PTHREAD == 1
        pthread_mutex_destroy(&mMutex);
#else
#endif
    }

    void Mutex::Lock() {
#if USE_PTHREAD == 1
        pthread_mutex_lock(&mMutex);
#else
        mMutex.lock();
#endif
    }

    void Mutex::Unlock() {
#if USE_PTHREAD == 1
        pthread_mutex_unlock(&mMutex);
#else
        mMutex.unlock();
#endif
    }

    bool Mutex::TryLock() {
#if USE_PTHREAD == 1
        return (pthread_mutex_trylock(&mMutex) == 0);
#else
        return mMutex.try_lock();
#endif
    }

} // namespace bde
