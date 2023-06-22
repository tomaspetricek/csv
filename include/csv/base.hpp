//
// Created by Tomáš Petříček on 19.06.2023.
//

#ifndef CSV_BASE_HPP
#define CSV_BASE_HPP

#include <cstddef>

namespace csv {
    template<std::size_t n_cols, class FileStream>
    class base {
        static_assert(n_cols>0);

    protected:
        FileStream file_;
        char delim_;

        explicit base(char delim = default_delimiter)
                :delim_(delim) { }

    public:
        constexpr static std::size_t column_count = n_cols;
        using file_stream_type = FileStream;
        constexpr static char default_delimiter = ',';
    };
}

#endif //CSV_BASE_HPP
