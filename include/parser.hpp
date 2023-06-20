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
        template<class T>
        inline static T parse(std::string_view data)
        {
            return boost::convert<T>(data, boost::cnv::strtol()).value();
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
