//
//  Profiler.cpp
//  BlackDogEngine
//
//  Created by Diego Jesus on 6/8/13.
//  Copyright (c) 2013 Black Dog Games. All rights reserved.
//

#include "Profiler.h"
#include "../System/Time.h"

namespace bde {

    std::map<std::string, Profiler::ProfileInfo> Profiler::sCalls;

    Profiler::Profiler(std::string name) {
        mStartTime = Time();
        mName = name;
    }

    Profiler::~Profiler() {
        if (sCalls.find(mName) == sCalls.end()) {
            sCalls[mName].nCalls = 0;
            sCalls[mName].time = TimeDifference({0});
        }

        sCalls[mName].nCalls++;
        sCalls[mName].time += Time() - mStartTime;
    }

    void Profiler::Print(std::ostream &o) {
        std::map<std::string, ProfileInfo>::const_iterator iter;

        for(iter = sCalls.begin(); iter != sCalls.end(); ++iter) {
            o << iter->first;
            o << " # calls: " << (iter->second).nCalls;
            o << " time: " << (iter->second).time.mTimeDifference;
            o << " average: " << (iter->second).time.mTimeDifference/(float)((
                        iter->second).nCalls) << "ms" << std::endl;
        }
    }
}
