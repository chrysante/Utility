#pragma once

#include "__base.hpp"
_UTL_SYSTEM_HEADER_

#include <cstddef>

namespace utl {

/// Checks if \p number is prime
inline constexpr bool __is_prime(std::size_t number) {
    if (number < 2) {
        return false;
    }
    if (number < 4) {
        return true;
    }
    if (number % 2 == 0 || number % 3 == 0) {
        return false;
    }

    for (std::size_t divisor = 6; (divisor - 1) * (divisor - 1) <= number;
         divisor += 6)
    {
        if (number % (divisor - 1) == 0) {
            return false;
        }

        if (number % (divisor + 1) == 0) {
            return false;
        }
    }
    return true;
}

/// Returns the smallest prime not less than \p number
/// If \p number is prime \p number is returned
inline constexpr std::size_t __next_prime(std::size_t number) {
    if (number == 2) {
        return 2;
    }
    if (number % 2 == 0) {
        number += 1;
    }
    while (!__is_prime(number)) {
        number += 2;
    }
    return number;
}

} // namespace utl
