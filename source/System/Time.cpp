
#include "Time.h"
#include <stdexcept>

namespace bde {

#ifdef __APPLE__

#include <sys/time.h>
#include <unistd.h>

#elif __linux

#include <sys/time.h>
#include <unistd.h>

#endif

    Time::Time() {
        mTimestamp = CurrentMiliseconds();
    }

    Time::Time(const TIME_T &timestamp) {
        mTimestamp = timestamp;
    }

    /* *******************
     * Getters & Setters *
     * ******************/
    TIME_T  Time::GetTimestamp() const {
        return mTimestamp;
    }

    void    Time::SetTimestamp(const TIME_T &timestamp) {
        mTimestamp = timestamp;
    }

    TIME_T Time::CurrentMiliseconds() {
#ifdef __APPLE__
        struct timeval tv;

        if( gettimeofday(&tv, NULL) < 0 ) {
            throw std::runtime_error("Could not get time of day.");
        }

        //return (kDelta.tv_sec*1000000 + kDelta.tv_usec);
        return (1000*(double)(tv.tv_sec) + (double)(tv.tv_usec)/1000);
#elif __linux

        if( gettimeofday(&tv, NULL) < 0 ) {
            throw std::runtime_error("Could not get time of day.");
        }

        //return (kDelta.tv_sec*1000000 + kDelta.tv_usec);
        return (1000*(double)(tv.tv_sec) + (double)(tv.tv_usec)/1000);
#endif
    }

    TimeDifference  Time::operator-(const Time &t2) {
        return TimeDifference( {mTimestamp - t2.mTimestamp} );
    }

    Time            Time::operator+(const TimeDifference &diff) {
        return Time( mTimestamp + diff.mTimeDifference );
    }

    Time            Time::operator-(const TimeDifference &diff) {
        return Time( mTimestamp - diff.mTimeDifference );
    }

    Time           &Time::operator+=(const TimeDifference &diff) {
        mTimestamp += diff.mTimeDifference;
        return *this;
    }

    Time           &Time::operator-=(const TimeDifference &diff) {
        mTimestamp -= diff.mTimeDifference;
        return *this;
    }

    TimeDifference  operator-(const TimeDifference &t1, const TimeDifference &t2) {
        return TimeDifference( {t1.mTimeDifference - t2.mTimeDifference} );
    }

    TimeDifference  operator+(const TimeDifference &t1, const TimeDifference &t2) {
        return TimeDifference( {t1.mTimeDifference + t2.mTimeDifference} );
    }

    TimeDifference &operator-=(TimeDifference &t1, const TimeDifference &t2) {
        t1.mTimeDifference -= t2.mTimeDifference;
        return t1;
    }

    TimeDifference &operator+=(TimeDifference &t1, const TimeDifference &t2) {
        t1.mTimeDifference += t2.mTimeDifference;
        return t1;
    }

    std::ostream &operator<< (std::ostream &o, const Time &t) {
        o << t.GetTimestamp() << "ms";
        return o;
    }

} // namespace bde
