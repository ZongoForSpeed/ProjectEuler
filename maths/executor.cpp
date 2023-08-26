#include <thread>
#include "executor.h"

namespace executor {
    thread_pool::thread_pool() {
        start();
    }

    thread_pool::thread_pool(const uint32_t num_threads) {
        start(num_threads);
    }

    thread_pool::~thread_pool() {
        stop();
    }

    void thread_pool::start() {
        const uint32_t num_threads = std::thread::hardware_concurrency(); // Max # of threads the system supports
        start(num_threads);
    }

    void thread_pool::start(const uint32_t num_threads) {
        for (uint32_t ii = 0; ii < num_threads; ++ii) {
            threads.emplace_back(&thread_pool::threadLoop, this);
        }
    }

    std::future<void> thread_pool::queueJob(const std::function<void()> &job) {
        std::packaged_task<void()> task(job);
        std::future<void> future = task.get_future();
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            jobs.emplace(std::move(task));
        }
        mutex_condition.notify_one();
        return future;
    }

    void thread_pool::stop() {
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            should_terminate = true;
        }
        mutex_condition.notify_all();
        for (std::thread &active_thread: threads) {
            active_thread.join();
        }
        threads.clear();
    }

    void thread_pool::invoke(std::initializer_list<std::function<void()>> functions) {
        std::vector<std::future<void>> futures;
        for (auto &f: functions) {
            futures.emplace_back(queueJob(f));
        }

        for (auto &future: futures) {
            future.wait();
        }
    }

    bool thread_pool::busy() {
        bool poolbusy;
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            poolbusy = !jobs.empty();
        }
        return poolbusy;
    }

    void thread_pool::threadLoop() {
        while (true) {
            std::packaged_task<void()> job;
            {
                std::unique_lock<std::mutex> lock(queue_mutex);
                mutex_condition.wait(lock, [this] {
                    return !jobs.empty() || should_terminate;
                });
                if (should_terminate) {
                    return;
                }
                job = std::move(jobs.front());
                jobs.pop();
            }
            job();
        }
    }
}

