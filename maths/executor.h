#pragma once

#include <functional>
#include <future>
#include <queue>

namespace executor {

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"

    template<typename T>
    class thread_pool {
    public:
        thread_pool() {
            start();
        }

        explicit thread_pool(const uint32_t num_threads) {
            start(num_threads);
        }

        ~thread_pool() {
            stop();
        }

        std::future<T> queueJob(const std::function<T()> &job) {
            std::packaged_task<T()> task(job);
            std::future<T> future = task.get_future();
            {
                std::unique_lock<std::mutex> lock(queue_mutex);
                jobs.emplace(std::move(task));
            }
            mutex_condition.notify_one();
            return future;
        }

        void invoke(std::initializer_list<std::function<T()>> functions) {
            std::vector<std::future<void>> futures;
            for (auto &f: functions) {
                futures.emplace_back(queueJob(f));
            }

            for (auto &future: futures) {
                future.wait();
            }
        }

        bool busy() {
            bool poolbusy;
            {
                std::unique_lock<std::mutex> lock(queue_mutex);
                poolbusy = !jobs.empty();
            }
            return poolbusy;
        }

    private:
        void threadLoop() {
            while (true) {
                std::packaged_task<T()> job;
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

        void start() {
            const uint32_t num_threads = std::thread::hardware_concurrency(); // Max # of threads the system supports
            start(num_threads);
        }

        void start(const uint32_t num_threads) {
            for (uint32_t ii = 0; ii < num_threads; ++ii) {
                threads.emplace_back(&thread_pool::threadLoop, this);
            }
        }

        void stop() {
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

        bool should_terminate = false;           // Tells threads to stop looking for jobs
        std::mutex queue_mutex;                  // Prevents data races to the job queue
        std::condition_variable mutex_condition; // Allows threads to wait on new jobs or termination
        std::vector<std::thread> threads;
        std::queue<std::packaged_task<T()>> jobs;
    };

#pragma clang diagnostic pop

}
