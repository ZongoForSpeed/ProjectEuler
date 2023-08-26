#pragma once

#include <functional>
#include <future>
#include <queue>

namespace executor {

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"

    class thread_pool {
    public:
        thread_pool();
        explicit thread_pool(const uint32_t num_threads);

        ~thread_pool();

        std::future<void> queueJob(const std::function<void()> &job);

        void invoke(std::initializer_list<std::function<void()>> functions);

        bool busy();

    private:
        void threadLoop();

        void start();

        void start(const uint32_t num_threads);

        void stop();

        bool should_terminate = false;           // Tells threads to stop looking for jobs
        std::mutex queue_mutex;                  // Prevents data races to the job queue
        std::condition_variable mutex_condition; // Allows threads to wait on new jobs or termination
        std::vector<std::thread> threads;
        std::queue<std::packaged_task<void()>> jobs;
    };

#pragma clang diagnostic pop

}
