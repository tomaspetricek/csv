//
// Created by Tomáš Petříček on 19.06.2023.
//

#ifndef CSV_PARSER_HPP
#define CSV_PARSER_HPP

#include <concepts>
#include <string>
#include <boost/convert.hpp>
#include <boost/convert/strtol.hpp>

namespace csv {
    struct parser {
        template<class Number>
        requires std::is_arithmetic_v<Number>
        inline static Number parse(std::string_view data)
        {
            return boost::convert<Number>(data, boost::cnv::strtol()).value();
        }

        template<class Enum>
        requires std::is_enum_v<Enum>
        inline static Enum parse(const std::string_view& data)
        {
            return static_cast<Enum>(parse<typename std::underlying_type<Enum>::type>(data));
        }

        template<class T>
        requires std::same_as<T, std::string>
        inline static std::string parse(std::string_view data)
        {
            return {data.begin(), data.end()};
        }
    };
}

#endif //CSV_PARSER_HPP
