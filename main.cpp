#include <iostream>
#include <array>
#include <tuple>
#include <reader.hpp>
#include <utils.hpp>
#include <writer.hpp>

using namespace csv;

struct sample {
    int num1{};
    long num2{};
    long long num3{};
    unsigned long num4{};
    std::string code;
    unsigned long long num5{};
    int num6{};
    long num7{};
};

int main()
{
    constexpr std::size_t n_cols{8};
    csv::reader<n_cols> reader{{"../data/in/custom_1988_2020.csv"}};
    std::array<std::string, n_cols> header;
    std::vector<sample> samples;

    auto read_duration = csv::measure_duration([&]() {
        sample s;
        while (reader.read_row(s.num1, s.num2, s.num3, s.code, s.num4, s.num5, s.num6, s.num7))
            samples.emplace_back(s);
    });
    std::cout << "read duration: " << read_duration << std::endl;

    csv::writer<n_cols> writer{"../data/out/custom_1988_2020.csv"};
    auto write_duration = csv::measure_duration([&]() {
        for (const auto& s : samples)
            writer.write_row(s.num1, s.num2, s.num3, s.code, s.num4, s.num5, s.num6, s.num7);
    });
    std::cout << "write duration: " << write_duration << std::endl;

    return 0;
}
