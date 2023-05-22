/**
 * @file thread_pool.h
 * @author Carlos Salguero
 * @author Sergio Garnica
 * @brief Declaration of the thread pool class
 * @version 0.1
 * @date 2023-05-22
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef THREAD_POOL_H
#define THREAD_POOL_H

// C++ Standard Libraries
#include <vector>
#include <queue>
#include <thread>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <future>

/**
 * @class ThreadPool
 * @brief Implements and manages a thread pool
 * @details This class implements a thread pool,
 * which is a collection of threads that are waiting to perform a task.
 */
class ThreadPool
{
public:
    // Constructor
    ThreadPool(std::size_t);

    // Destructor
    ~ThreadPool();

    // Inline methods
    /**
     * @brief
     * Add a task to the thread pool
     * @tparam F Function type
     * @tparam Args Arguments type
     * @param func Function to be executed
     * @param args Arguments to be passed to the function
     * @return std::future<typename std::result_of<F(Args...)>::type>
     *         Future object that will hold the result of the function
     * @throw std::runtime_error If the thread pool is stopped
     */
    template <class F, class... Args>
    auto enqueue(F &&func, Args &&...args)
        -> std::future<typename std::result_of<F(Args...)>::type>
    {
        try
        {
            using returnType = typename std::result_of<F(Args...)>::type;
            auto task = std::make_shared<std::packaged_task<returnType()>>(
                std::bind(std::forward<F>(func), std::forward<Args>(args)...));

            std::future<returnType> result = task->get_future();

            {
                std::unique_lock<std::mutex> lock(m_queue_mutex);

                if (m_stop)
                    throw std::runtime_error("enqueue on stopped ThreadPool");

                m_tasks.emplace([task]()
                                { (*task)(); });
            }

            m_condition.notify_one();
            return result;
        }
        catch (const std::exception &e)
        {
            throw;
        }
    }

private:
    std::vector<std::thread> m_threads;
    std::queue<std::function<void()>> m_tasks;
    std::mutex m_queue_mutex;
    std::condition_variable m_condition;
    bool m_stop;
};

#endif //! THREAD_POOL_H