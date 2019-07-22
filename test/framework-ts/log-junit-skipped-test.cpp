//  (C) Copyright Raffi Enficiaud 2019.
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/test for the library home page.
//
// ***************************************************************************

// Boost.Test

#define BOOST_TEST_MODULE junit should not indicate skipped
#include <boost/test/unit_test.hpp>
namespace utf = boost::unit_test;
namespace tt = boost::test_tools;

struct skip_with_message
{
    std::string message;
    skip_with_message(std::string m)
    : message(m) {}

    tt::assertion_result operator()(utf::test_unit_id)
    {
        tt::assertion_result ans(false);
        ans.message() << "test is skipped because " << message;
        return ans;
    }
};

BOOST_AUTO_TEST_CASE( test1 )
{
    BOOST_CHECK( 2 + 2 == 4 );
}

BOOST_AUTO_TEST_CASE( test2, * utf::precondition(skip_with_message("it sucks !!")) )
{
    BOOST_CHECK_EQUAL(0, 1);
}

BOOST_AUTO_TEST_CASE( test3, * utf::disabled())
{
    BOOST_CHECK_EQUAL(0, 1);
}
