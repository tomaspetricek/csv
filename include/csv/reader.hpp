//
// Created by Tomáš Petříček on 19.06.2023.
//

#ifndef CSV_READER_HPP
#define CSV_READER_HPP

#include <cstddef>
#include <fstream>
#include <sstream>
#include "base.hpp"
#include "parser.hpp"

namespace csv {
    template<std::size_t n_cols, class Parser = parser>
    class reader : public base<n_cols, std::ifstream> {
        std::size_t first_{0};
        std::string line_;
        using base_type = base<n_cols, std::ifstream>;

        template<class Value>
        void parse_value(Value& val)
        {
            std::size_t next, last{line_.size()};
            if (first_>last)
                throw std::runtime_error{"Not enough values"};

            if ((next = line_.find(this->delim_, first_))!=std::string::npos) {
                last = next;
            }
            else {
                next = line_.size();
            }
            std::basic_string<char, std::char_traits<char>, std::allocator<char>> data{line_.data()+first_, last-first_};
            first_ = next+1;

            try {
                val = Parser::template parse<Value>(data);
            }
            catch (...) {
                std::throw_with_nested(std::runtime_error{"Unable to parse: "+std::string{data}});
            }
        }

        bool read_line()
        {
            bool read{false};
            if (std::getline(this->file_, line_)) {
                line_.erase(std::remove(line_.begin(), line_.end(), '\r'), line_.end());
                first_ = 0;
                read = true;
            }
            return read;
        }

    public:
        explicit reader(const std::filesystem::path& path, char delim = base_type::default_delimiter)
                :base_type{delim}
        {
            if (!std::filesystem::exists(path))
                throw std::invalid_argument("File does not exist: "+path.string());

            this->file_ = typename base_type::file_stream_type{path.string()};

            if (!this->file_.is_open())
                throw std::runtime_error("Cannot open: "+path.string());
        }

        bool read_header(std::array<std::string, n_cols>& header)
        {
            bool read{read_line()};
            if (read) {
                for (std::size_t i{0}; i<header.size(); i++)
                    parse_value(header[i]);
            }
            return read;
        }

        template<class ...Types>
        bool read_row(Types& ...inputs)
        {
            static_assert(sizeof...(Types)==n_cols);
            bool read{read_line()};
            if (read) {
                auto parse_line = [&](auto& in) {
                    parse_value(in);
                };
                (parse_line(inputs), ...);
            }
            return read;
        }
    };
}

#endif //CSV_READER_HPP
