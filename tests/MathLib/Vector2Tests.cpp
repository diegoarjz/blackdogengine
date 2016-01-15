#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Vector2
#include <boost/test/unit_test.hpp>

#include "../../source/MathLib/Vector2.h"

using namespace bde;

BOOST_AUTO_TEST_CASE(construction)
{
    Vector2f v1(1,2);
    Vector2f v2(v1);
    float f[] = {2,3};
    Vector2f v3(f);
    Vector2f v4;
    
    BOOST_CHECK( v1.X() == 1 && v1.Y() == 2 );
    BOOST_CHECK( v2.X() == v1.X() && v2.Y() == v1.Y() );
    BOOST_CHECK( v3.X() == 2 && v3.Y() == 3 );
    BOOST_CHECK( v4.X() == 0 && v4.Y() == 0);
}

BOOST_AUTO_TEST_CASE(assignment)
{
    Vector2f v1(1,2);
    Vector2f v2;
    
    v2 = v1;
    BOOST_CHECK( v2.X() == 1 && v2.Y() == 2);
}

BOOST_AUTO_TEST_CASE(arithmetics)
{
    Vector2f v1(1,2);
    Vector2f v2(2,3);
    
    auto s = v1+v2;
    auto m = v1-v2;
    auto sm = 2*v1;
    auto ms = v1*2;
    auto ds = v1/2;
    auto sd = 2/v1;
    
    BOOST_CHECK( s == Vector2f(3,5) );
    BOOST_CHECK( m == Vector2f(-1,-1) );
    BOOST_CHECK( sm == Vector2f(2,4) );
    BOOST_CHECK( ms == Vector2f(2,4) );
    BOOST_CHECK( ds == Vector2f(0.5,1) );
    BOOST_CHECK( sd == Vector2f(2,1) );
}

BOOST_AUTO_TEST_CASE(comparison)
{
    Vector2f v1(1,2);
    Vector2f v2(2,3);
    Vector2f v3(1,2);
    
    BOOST_CHECK( v1 == v3 );
    BOOST_CHECK( v1 != v2 );
}