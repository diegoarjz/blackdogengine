#ifndef TIME_H_
#define TIME_H_

#include <ostream>

#include "../DataTypes.h"

namespace bde {

    /**
    * Represents a diference between times.
    */
    struct TimeDifference {
        TIME_T mTimeDifference;
    };

    /**
    * Represents time in the Black Dog Engine.
    *
    * Provides operators for simple calculations with time.
    *
    * @author Diego Jesus <diego.a.r.jz@gmail.com>
    */
    class Time {
      private:
        TIME_T  mTimestamp; ///< Timestamp in miliseconds
      public:
        /* ***************************
        * Construction & Destruction *
        * ***************************/
        /**
        * Instatiates an object with current time.
        */
        Time();
        Time(const TIME_T &timestamp);

        /* *******************
         * Getters & Setters *
         * ******************/
        TIME_T  GetTimestamp() const;
        void    SetTimestamp(const TIME_T &timestamp);

        /* **********
        * Operators *
        * **********/
        TimeDifference  operator-(const Time &t2);
        Time            operator+(const TimeDifference &diff);
        Time            operator-(const TimeDifference &diff);
        Time           &operator+=(const TimeDifference &diff);
        Time           &operator-=(const TimeDifference &diff);

      public:

        /**
        * Returns the amount of miliseconds since.
        * 1970-01-01 00:00:00 +0000 (UTC)
        */
        static TIME_T CurrentMiliseconds();

    };

    TimeDifference  operator-(const TimeDifference &t1, const TimeDifference &t2);
    TimeDifference  operator+(const TimeDifference &t1, const TimeDifference &t2);
    TimeDifference &operator-=(TimeDifference &t1, const TimeDifference &t2);
    TimeDifference &operator+=(TimeDifference &t1, const TimeDifference &t2);

    std::ostream &operator<< (std::ostream &o, const Time &t);

} // namespace bde

#endif
