//
// Created by Tomáš Petříček on 20.06.2023.
//

#ifndef CSV_TEST_READER_HPP
#define CSV_TEST_READER_HPP

#include <boost/test/unit_test.hpp>
#include <string>
#include <csv/reader.hpp>

BOOST_AUTO_TEST_SUITE(reader_test)
    BOOST_AUTO_TEST_CASE(constructor_exception_test)
    {
        BOOST_REQUIRE_THROW(csv::reader<1> reader{{"not-exists.csv"}}, std::invalid_argument);
    }
BOOST_AUTO_TEST_SUITE_END()

#endif //CSV_TEST_READER_HPP
