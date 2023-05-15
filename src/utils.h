/**
 * @file utils.h
 * @author Carlos Salguero
 * @author Sergio Garnica
 * @brief Utilities for the program
 * @version 0.1
 * @date 2023-05-12
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef UTILS_H
#define UTILS_H

// C++ standard library
#include <chrono>

namespace utils
{
    // Measures the time of a function
    /**
     * @brief
     * Measures the time of a function
     * @tparam F - Function type
     * @tparam Args - Arguments type
     * @param func - Function to measure
     * @param args - Arguments of the function
     * @return auto - Time of the function
     */
    template <typename F, typename... Args>
    auto measure_time(F func, Args &&...args)
    {
        auto start = std::chrono::high_resolution_clock::now();
        func(std::forward<Args>(args)...);
        auto end = std::chrono::high_resolution_clock::now();

        return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    }
}

#endif // UTILS_H