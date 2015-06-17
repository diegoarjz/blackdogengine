#ifndef MUTEX_H_
#define MUTEX_H_

#if USE_PTHREAD == 1

#include <pthread.h>

#else

#include <thread>

#endif

namespace bde {
    /**
     * Implements a mutex
     * @author  Diego Jesus <diego.a.r.jz@gmail.com>
     * @date    18 May 2015
     */
    class Mutex {
      private:
#if USE_PTHREAD == 1
        pthread_mutex_t mMutex;
#else
        std::mutex mMutex;
#endif

      public:
        /* ****************************
         * Construction & Destruction *
         * ***************************/
        Mutex();
        ~Mutex();

        void Lock();
        void Unlock();
        bool TryLock();

        friend class ConditionalVariable;
    }; // class Mutex
} // namespace bde

#else
namespace bde {
    class Mutex;
} // namespace bde
#endif
