#ifndef CONDITIONALVARIABLE_H_
#define CONDITIONALVARIABLE_H_

#if USE_PTHREAD == 1

#include <pthread.h>

#else

#include <thread>

#endif

#include "Mutex.h"

namespace bde{
    /**
     * Implements a conditional variable for thread
     * synchronisation
     *
     * @author  Diego Jesus <diego.a.r.jz@gmail.com>
     * @date    18 May 2015
     */
    class ConditionalVariable{
        private:
#if USE_PTHREAD == 1
            pthread_cond_t mConditional;
#else
            std::condition_variable mConditional;
#endif
        public:

            /* ****************************
             * Construction & Destruction *
             * ***************************/
            ConditionalVariable();
            ~ConditionalVariable();

            void NotifyOne();
            void NotifyAll();

            void Wait(Mutex mutex);
    }; // class ConditionalVariable
} // namespace bde

#else
namespace bde{
    class ConditionalVariable;
} // namespace bde
#endif
