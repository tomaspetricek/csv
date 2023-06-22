#include <iostream>
#include <array>
#include <tuple>
#include <csv/reader.hpp>
#include <utils.hpp>
#include <csv/writer.hpp>

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
};

int main()
{
    std::filesystem::path data_dir{"../../src/data"};
    std::filesystem::path in_dir{data_dir/"in"}, out_dir{data_dir/"out"};
    std::string record_file{"records.csv"};

    // read records
    constexpr std::size_t n_cols{6};
    csv::reader<n_cols> reader{{in_dir/record_file}};
    std::array<std::string, n_cols> header;
    std::vector<record> records;

    static_assert(std::is_enum_v<genders>);
    std::cout << "read duration: " << measure_duration([&]() {
        reader.read_header(header);
        record r;
        while (reader.read_row(r.name, r.gender, r.age, r.height, r.weight, r.bmi))
            records.emplace_back(r);
    }) << std::endl;

    // write records
    csv::writer<n_cols> writer{{out_dir/record_file}};
    std::cout << "write duration: " << measure_duration([&]() {
        writer.write_header(header);
        for (const auto& r: records)
            writer.write_row(r.name, r.gender, r.age, r.height, r.weight, r.bmi);
    }) << std::endl;

    return EXIT_SUCCESS;
}
