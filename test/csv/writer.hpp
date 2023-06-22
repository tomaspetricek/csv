//
// Created by Tomáš Petříček on 22.06.2023.
//

#ifndef CSV_TEST_WRITER_HPP
#define CSV_TEST_WRITER_HPP

#include <boost/test/unit_test.hpp>
#include <csv/writer.hpp>
#include "common.hpp"

BOOST_AUTO_TEST_SUITE(writer_test)
    BOOST_AUTO_TEST_CASE(write_header_only_file_test)
    {
        { // must close
            writer_t writer{out_dir/header_only_filename};
            writer.write_header(actual_header);
        }
        reader_t reader{out_dir/header_only_filename};
        header_t expect_header;

        BOOST_REQUIRE(reader.read_header(expect_header));
        BOOST_TEST(expect_header==actual_header);
    }

    BOOST_AUTO_TEST_CASE(write_body_only_file_test) {
        {
            writer_t writer{out_dir/body_only_filename};
            for (const auto& r : actual_records)
                writer.write_row(r.name, r.gender, r.age, r.height, r.weight, r.bmi);
        }

        reader_t reader{out_dir/body_only_filename};
        records_t expect_records;
        record r;

        while (reader.read_row(r.name, r.gender, r.age, r.height, r.weight, r.bmi))
            expect_records.emplace_back(r);
        BOOST_TEST(expect_records==actual_records);
    }

    BOOST_AUTO_TEST_CASE(write_complete_file_test) {
        {
            writer_t writer{out_dir/complete_filename};
            writer.write_header(actual_header);
            for (const auto& r : actual_records)
                writer.write_row(r.name, r.gender, r.age, r.height, r.weight, r.bmi);
        }

        reader_t reader{out_dir/complete_filename};
        header_t expect_header;
        records_t expect_records;
        record r;

        BOOST_REQUIRE(reader.read_header(expect_header));
        BOOST_TEST(expect_header==actual_header);

        while (reader.read_row(r.name, r.gender, r.age, r.height, r.weight, r.bmi))
            expect_records.emplace_back(r);
        BOOST_TEST(expect_records==actual_records);
    }

    BOOST_AUTO_TEST_CASE(use_different_delimiter_test)
    {
        char delim{';'};
        std::string filename{"diff-delim.csv"};
        {
            writer_t writer{out_dir/filename, delim};
            writer.write_header(actual_header);
        }
        reader_t reader{{out_dir/filename}, delim};
        header_t expect_header;

        BOOST_REQUIRE(reader.read_header(expect_header));
        BOOST_TEST(expect_header==actual_header);
    }

    BOOST_AUTO_TEST_CASE(use_append_mode_test) {
        std::string filename{"exists.csv"};
        record add{"Lily", genders::female, 18, 182, 57, 17.2};
        auto actual_records_extended{actual_records};
        actual_records_extended.emplace_back(add);
        {
            writer_t writer{out_dir/filename};
            writer.write_header(actual_header);
            for (const auto& r : actual_records)
                writer.write_row(r.name, r.gender, r.age, r.height, r.weight, r.bmi);
        }
        {
            writer_t writer{{out_dir/filename}, writer_t::default_delimiter, std::ios_base::app};
            writer.write_row(add.name, add.gender, add.age, add.height, add.weight, add.bmi);
        }

        reader_t reader{out_dir/filename};
        header_t expect_header;
        records_t expect_records;
        record r;

        BOOST_REQUIRE(reader.read_header(expect_header));
        BOOST_TEST(expect_header==actual_header);

        while (reader.read_row(r.name, r.gender, r.age, r.height, r.weight, r.bmi))
            expect_records.emplace_back(r);
        BOOST_TEST(expect_records==actual_records_extended);
    }
BOOST_AUTO_TEST_SUITE_END()

#endif //CSV_TEST_WRITER_HPP
