#pragma once

#include <stdexcept>
#include <type_traits>

template<typename T>
T constexpr factorial_(T n) {
    return (n == 1 || n == 0) ? 1 : factorial_(n - 1) * n;
}


template<typename T>
T constexpr factorial(T n) {
    if (n < 0) {
        throw std::runtime_error("Negative values are not allowed.");
    }
    
    if (std::is_floating_point<T>::value) {
        throw std::runtime_error("Floating-point types are not allowed.");
    }
    
    return factorial_(n);
}
