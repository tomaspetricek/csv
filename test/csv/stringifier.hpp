//
// Created by Tomáš Petříček on 20.06.2023.
//

#ifndef CSV_TEST_STRINGIFIER_HPP
#define CSV_TEST_STRINGIFIER_HPP

#include <boost/test/unit_test.hpp>
#include <string>
#include <csv/stringifier.hpp>

BOOST_AUTO_TEST_SUITE(stringifier_test)
    BOOST_AUTO_TEST_CASE(no_exception_test)
    {
        BOOST_REQUIRE_EQUAL(csv::stringifier::to_string<int>(-1), std::string{"-1"});
        BOOST_REQUIRE_EQUAL(csv::stringifier::to_string<long>(-1000), std::string{"-1000"});
        BOOST_REQUIRE_EQUAL(csv::stringifier::to_string<long long>(-1000), std::string{"-1000"});
        BOOST_REQUIRE_EQUAL(csv::stringifier::to_string<unsigned long>(1000), std::string{"1000"});
        BOOST_REQUIRE_EQUAL(csv::stringifier::to_string<unsigned long long>(1000), std::string{"1000"});

        BOOST_REQUIRE_EQUAL(csv::stringifier::to_string<float>(100.0), std::string{"100.000000"});
        BOOST_REQUIRE_EQUAL(csv::stringifier::to_string<double>(100.0), std::string{"100.000000"});
        BOOST_REQUIRE_EQUAL(csv::stringifier::to_string<long double>(100.0), std::string{"100.000000"});

        BOOST_REQUIRE_EQUAL(csv::stringifier::to_string(std::string{"name"}), std::string{"name"});
        BOOST_REQUIRE_EQUAL(csv::stringifier::to_string("name"), std::string{"name"});
    }
BOOST_AUTO_TEST_SUITE_END()

#endif //CSV_TEST_STRINGIFIER_HPP
