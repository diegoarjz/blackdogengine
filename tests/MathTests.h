#ifndef LINE2TESTS_H_
#define LINE2TESTS_H_

#include <cpptest.h>

#include "../source/MathLib/Line2.h"

class Line2Tests : public Test::Suite{
    public:
        Line2Tests(){

        }
    protected:
        bde::Line2 mHorizontal;
        bde::Line2 mVertical;

        virtual void setup(){
            mHorizontal = bde::Line2( bde::Vector2(0,0), bde::Vector2(1,0) );
            mVertical   = bde::Line2( bde::Vector2(0,0), bde::Vector2(0,1) );
        }
    private:

        void Line2Tests_TestProjection(){
            bde::Vector2 v(1,3);

            bde::Vector2 p1 = mHorizontal.Projection( v );
            bde::Vector2 p2 = mVertical.Projection( v );

            TEST_ASSERT( p1 == Vector2(1,0) );
            TEST_ASSERT( p2 == Vector2(0,3) );
        }
}; // class Line2Tests
#endif
