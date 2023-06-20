//
// Created by Tomáš Petříček on 19.06.2023.
//

#ifndef CSV_WRITER_HPP
#define CSV_WRITER_HPP

#include <ios>
#include <fstream>
#include "stringifier.hpp"
#include "base.hpp"

namespace csv {
    template<std::size_t n_cols, class Stringifier = stringifier>
    class writer final : public base<n_cols, std::ofstream> {
        using base_type = base<n_cols, std::ofstream>;
        constexpr static std::ios_base::openmode default_open_mode = std::ios_base::out;

        void write_value(std::size_t i, const std::string& val)
        {
            char sep = (i<n_cols-1) ? this->delim_ : '\n';
            this->file_ << val << sep;
        }

    public:
        explicit writer(const std::filesystem::path& path, char delim = base_type::default_delim,
                std::ios_base::openmode mode = default_open_mode)
                :base_type{delim}
        {
            this->file_ = typename base_type::file_stream_type{path.string(), mode};
        }

        void write_header(const std::array<std::string, n_cols>& header)
        {
            for (std::size_t i{0}; i<header.size(); i++)
                write_value(i, header[i]);
        }

        template<class ...Types>
        void write_row(const Types& ...outputs)
        {
            static_assert(sizeof...(Types)==n_cols);

            std::size_t i{0};
            auto write_line = [&](auto& out) {
                write_value(i++, Stringifier::to_string(out));
            };

            (write_line(outputs), ...);
        }
    };
}

#endif //CSV_WRITER_HPP
