//
// Created by Tomáš Petříček on 22.06.2023.
//

#ifndef CSV_TEST_FIXTURES_HPP
#define CSV_TEST_FIXTURES_HPP

#include <filesystem>
#include <csv/writer.hpp>
#include <csv/reader.hpp>
#include <utility>

enum genders {
    male, female
};

struct record {
    std::string name;
    genders gender;
    int age;
    long height;
    unsigned long weight;
    double bmi;

    record(std::string name, genders gender, int age, long height, unsigned long weight, double bmi)
            :name(std::move(name)), gender(gender), age(age), height(height), weight(weight), bmi(bmi) { }

    record() = default;

    bool operator==(const record& rhs) const
    {
        return name==rhs.name &&
                gender==rhs.gender &&
                age==rhs.age &&
                height==rhs.height &&
                weight==rhs.weight &&
                bmi==rhs.bmi;
    }
};

constexpr std::size_t n_cols = 6;
using header_t = std::array<std::string, n_cols>;
using records_t = std::vector<record>;

using writer_t = csv::writer<n_cols>;
using reader_t = csv::reader<n_cols>;

const header_t actual_header{"name", "gender", "age", "height", "weight", "bmi"};
const records_t actual_records{
        {"Bazza", genders::male,   32, 162, 64, 24.2},
        {"Delta", genders::female, 89, 175, 54, 18.3},
};

const std::filesystem::path data_dir{"../../test/data"}, in_dir{data_dir/"in"}, out_dir{data_dir/"out"};
const std::string body_only_filename{"body-only.csv"}, complete_filename{"complete.csv"},
        header_only_filename{"header-only.csv"};

#endif //CSV_TEST_FIXTURES_HPP
