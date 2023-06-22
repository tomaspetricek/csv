//
// Created by Tomáš Petříček on 20.06.2023.
//

#ifndef CSV_TEST_PARSER_HPP
#define CSV_TEST_PARSER_HPP

#include <boost/test/unit_test.hpp>
#include <string>
#include <csv/parser.hpp>

BOOST_AUTO_TEST_SUITE(parser_test)
    BOOST_AUTO_TEST_CASE(no_exception_test)
    {
        BOOST_REQUIRE_EQUAL(csv::parser::parse<int>("-1"), -1);
        BOOST_REQUIRE_EQUAL(csv::parser::parse<long>("-1000"), -1000);
        BOOST_REQUIRE_EQUAL(csv::parser::parse<long long>("-1000"), -1000);
        BOOST_REQUIRE_EQUAL(csv::parser::parse<unsigned long>("1000"), 1000);
        BOOST_REQUIRE_EQUAL(csv::parser::parse<unsigned long long>("1000"), 1000);

        BOOST_REQUIRE_EQUAL(csv::parser::parse<float>("100.0"), 100.0);
        BOOST_REQUIRE_EQUAL(csv::parser::parse<double>("100.0"), 100.0);
        BOOST_REQUIRE_EQUAL(csv::parser::parse<long double>("100.0"), 100.0);

        BOOST_REQUIRE_EQUAL(csv::parser::parse<std::string>("name"), std::string{"name"});
    }

    BOOST_AUTO_TEST_CASE(exception_test)
    {
        std::string text{"name"};
        BOOST_REQUIRE_THROW(csv::parser::parse<int>(text), boost::wrapexcept<boost::bad_optional_access>);
        BOOST_REQUIRE_THROW(csv::parser::parse<long>(text), boost::wrapexcept<boost::bad_optional_access>);
        BOOST_REQUIRE_THROW(csv::parser::parse<long long>(text), boost::wrapexcept<boost::bad_optional_access>);
        BOOST_REQUIRE_THROW(csv::parser::parse<unsigned long>(text), boost::wrapexcept<boost::bad_optional_access>);
        BOOST_REQUIRE_THROW(csv::parser::parse<unsigned long long>(text),
                boost::wrapexcept<boost::bad_optional_access>);

        BOOST_REQUIRE_THROW(csv::parser::parse<float>(text), boost::wrapexcept<boost::bad_optional_access>);
        BOOST_REQUIRE_THROW(csv::parser::parse<double>(text), boost::wrapexcept<boost::bad_optional_access>);
        BOOST_REQUIRE_THROW(csv::parser::parse<long double>(text), boost::wrapexcept<boost::bad_optional_access>);
    }
BOOST_AUTO_TEST_SUITE_END()

#endif //CSV_TEST_PARSER_HPP
