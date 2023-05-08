/**
 * @file utils.h
 * @author Carlos Salguero
 * @author Sergio Garnica
 * @brief Declaration of the utils namespace
 * @version 0.1
 * @date 2023-05-07
 *
 * @copyright Copyright (c) 2023
 *
 */

export module utils;
import <chrono>;

export namespace utils
{
    template <typename Func>
    std::chrono::milliseconds::rep measure_time(Func &&function)
    {
        auto start = std::chrono::high_resolution_clock::now();

        function();

        auto end = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::milliseconds>(
                   end - start)
            .count();
    }

    // Add declaration for the function being measured
    void my_function();
}
