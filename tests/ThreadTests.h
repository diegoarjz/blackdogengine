#ifndef THREAD_TESTS_H_
#define THREAD_TESTS_H_

#include <iostream>

#include <cpptest.h>

#include "../source/System/Thread.h"

class ThreadStub : public bde::Thread{
    public:
        int nums[10];

        virtual void run() override{
            for(int i=0; i<10; ++i){
                nums[i] = i;
            }
        }

}; // class ThreadStub

class ThreadTests : public Test::Suite{
    public:
        ThreadTests(){
            TEST_ADD( ThreadTests::ThreadTests_TestRun );
        }
    private:

        void ThreadTests_TestRun(){
            ThreadStub ts;

            ts.Start();

            ts.Join();

            for(int i=0; i<10; ++i){
                TEST_ASSERT( ts.nums[i] == i );
            }
        }
};

#endif
