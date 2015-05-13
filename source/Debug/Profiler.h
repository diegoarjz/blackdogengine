//
//  Profiler.h
//  BlackDogEngine
//
//  Created by Diego Jesus on 6/8/13.
//  Copyright (c) 2013 Black Dog Games. All rights reserved.
//

#ifndef PROFILER_H_
#define PROFILER_H_

#include <iostream>
#include <map>
#include <string>

#include "../DataTypes.h"
#include "../System/Time.h"

#define PROFILE(name) bde::Profiler ___PROFILER___(name)

namespace bde {
    class Profiler{
    public:
        struct ProfileInfo{
            U32             nCalls;
            TimeDifference  time;
        };
    private:
        static std::map<std::string, ProfileInfo> sCalls;

        Time        mStartTime;
        std::string mName;
    public:
        Profiler(std::string name);

        ~Profiler();

        static std::map<std::string, ProfileInfo> GetCalls() { return sCalls; }

        static void Print(std::ostream& o);
    }; // class Profiler
} // namespace bde

#else
namespace bde{
    class Profiler;
} // namespace bde

#endif
