#ifndef AUTORESETEVENT_H_
#define AUTORESETEVENT_H_

#include "../DataTypes.h"
#include "ConditionalVariable.h"
#include "Mutex.h"

namespace bde{
    /**
     * Signals an event to a thread and automatically resets itself
     *
     * @author Diego Jesus <diego.a.r.jz@gmail.com>
     * @date 17 Jun 2015
     */
    class AutoResetEvent{
        private:
            Mutex mMutex;
            ConditionalVariable mCondVariable;
            BOOLEAN mSignalled;
        public:
            AutoResetEvent();

            void Notify();
            void Wait();
    }; // class AutoResetEvent
} // namespace bde

#else
namespace bde{
    class AutoResetEvent;
} // namespace bde
#endif
