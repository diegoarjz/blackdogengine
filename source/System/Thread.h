#ifndef THREAD_H_
#define THREAD_H_

#if USE_PTHREAD == 1

#include <pthread.h>

#else

#include <thread>

#endif

namespace bde {
    /**
     * Encapsulates a native thread.
     *
     * @author  Diego Jesus <diego.a.r.jz@gmail.com>
     * @date    18 May 2015
     */
    class Thread {
      private:
#if USE_PTHREAD == 1
        pthread_t mThread;
#else
        std::thread mThread;
#endif

      protected:
        /**
         * Sub classes should implement this method
         * for custom behaviour.
         */
        virtual void run() = 0;
      public:
        /* ****************************
         * Construction & Destruction *
         * ***************************/
        Thread();
        virtual ~Thread();

        /**
         * Starts the thread
         */
        void Start();
        /**
         * Waits for the thread to finish and joins the
         * execution.
         */
        void Join();

      private: // Static Methods
        static void *dispatch(void *);
    }; // class Thread

} // namespace Thread

#else
namespace bde {
    class Thread;
} // namespace Thread
#endif
