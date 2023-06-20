#include <iostream>
#include <array>
#include <tuple>
#include "include/reader.hpp"

struct sample {
    int season;
    std::string gender;
    double height;
};

int main()
{
    constexpr std::size_t n_cols{3};
    csv::reader<n_cols> reader{{"../data/in/complete.csv"}};
    std::array<std::string, n_cols> header;
    std::vector<sample> samples;

    reader.read_header(header);
    sample s;
    while (reader.read_row(s.season, s.gender, s.height))
        samples.emplace_back(s);

    std::cout << samples.back().gender << std::endl
              << "size: " << samples.size() << std::endl;
    return 0;
}
