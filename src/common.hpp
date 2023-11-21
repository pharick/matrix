#ifndef M42_COMMON_HPP
#define M42_COMMON_HPP

#include <concepts>

namespace m42
{

    template <typename T>
    concept Arithmetic = std::is_arithmetic_v<T>;

}

#endif
