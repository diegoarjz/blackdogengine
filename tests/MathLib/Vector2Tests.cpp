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
    
    BOOST_CHECK( v1.X() == 1 && v1.Y() == 2 );
    BOOST_CHECK( v2.X() == v1.X() && v2.Y() == v1.Y() );
    BOOST_CHECK( v3.X() == 2 && v3.Y() == 3 );
}

BOOST_AUTO_TEST_CASE(assignment)
{
    
}

BOOST_AUTO_TEST_CASE(member_access)
{
    
}

BOOST_AUTO_TEST_CASE(arithmetics)
{
    
}

BOOST_AUTO_TEST_CASE(comparison)
{
    
}