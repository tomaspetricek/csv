//
// Created by Tomáš Petříček on 19.06.2023.
//

#ifndef CSV_STRINGIFIER_HPP
#define CSV_STRINGIFIER_HPP

#include <string>

namespace csv {
    struct stringifier {
        template<class T>
        inline static std::string to_string(const T& data)
        {
            return std::to_string(data);
        }

        inline static std::string to_string(const std::string& data)
        {
            return data;
        }

        inline static std::string to_string(const char* data)
        {
            return data;
        }
    };
}

#endif //CSV_STRINGIFIER_HPP
