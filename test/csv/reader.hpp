//
// Created by Tomáš Petříček on 20.06.2023.
//

#ifndef CSV_TEST_READER_HPP
#define CSV_TEST_READER_HPP

#include <boost/test/unit_test.hpp>
#include <string>
#include <array>
#include <vector>
#include <csv/reader.hpp>
#include "common.hpp"

BOOST_AUTO_TEST_SUITE(reader_test)
    BOOST_AUTO_TEST_CASE(constructor_exception_test)
    {
        BOOST_REQUIRE_THROW(csv::reader<1> reader{{in_dir/"not-exist.csv"}}, std::invalid_argument);
    }

    BOOST_AUTO_TEST_CASE(read_empty_file_test)
    {
        reader_t reader{{in_dir/"empty.csv"}};
        header_t header;
        record r;

        BOOST_REQUIRE(!reader.read_header(header));
        BOOST_REQUIRE(!reader.read_row(r.name, r.gender, r.age, r.height, r.weight, r.bmi));
    }

    BOOST_AUTO_TEST_CASE(read_header_only_file_test)
    {
        reader_t reader{{in_dir/header_only_filename}};
        header_t expect_header;
        record r;

        BOOST_REQUIRE(reader.read_header(expect_header));
        BOOST_TEST(expect_header==actual_header);
        BOOST_REQUIRE(!reader.read_row(r.name, r.gender, r.age, r.height, r.weight, r.bmi));
    }

    BOOST_AUTO_TEST_CASE(read_body_only_file_test)
    {
        reader_t reader{{in_dir/body_only_filename}};
        records_t expect_records;
        record r;

        while (reader.read_row(r.name, r.gender, r.age, r.height, r.weight, r.bmi))
            expect_records.emplace_back(r);
        BOOST_TEST(expect_records==actual_records);
    }

    BOOST_AUTO_TEST_CASE(read_complete_file_test)
    {
        reader_t reader{{in_dir/complete_filename}};
        header_t expect_header;
        records_t expect_records;
        record r;

        BOOST_REQUIRE(reader.read_header(expect_header));
        BOOST_TEST(expect_header==actual_header);

        while (reader.read_row(r.name, r.gender, r.age, r.height, r.weight, r.bmi))
            expect_records.emplace_back(r);
        BOOST_TEST(expect_records==actual_records);
    }

    BOOST_AUTO_TEST_CASE(incorrect_delimiter_test)
    {
        reader_t reader{{in_dir/complete_filename}, ';'};
        header_t expect_header;
        BOOST_REQUIRE_THROW(reader.read_header(expect_header), std::runtime_error);
    }

    BOOST_AUTO_TEST_CASE(incorrect_type_exception_test)
    {
        reader_t reader{{in_dir/complete_filename}};
        header_t expect_header;
        record r;
        BOOST_REQUIRE_THROW(reader.read_row(r.name, r.gender, r.age, r.height, r.weight, r.bmi), std::runtime_error);
    }

    BOOST_AUTO_TEST_CASE(excessive_column_count_test)
    {
        csv::reader<n_cols+1> reader{{in_dir/complete_filename}};
        std::array<std::string, n_cols+1> expect_header;
        BOOST_REQUIRE_THROW(reader.read_header(expect_header), std::runtime_error);
    }
BOOST_AUTO_TEST_SUITE_END()

#endif //CSV_TEST_READER_HPP
