#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <vector>
#include <queue>
#include <thread>
#include <functional>
#include <condition_variable>

class ThreadPool {
public:
    explicit ThreadPool(size_t threads);
    template<class F, class... Args>
    auto push_task(F&& f, Args&&... args) -> std::future<typename std::result_of<F(Args...)>::type>;
    bool has_idle_threads();
    ~ThreadPool();

private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    std::mutex queue_mutex;
    std::condition_variable condition;
    bool stop;
};

#endif // THREAD_POOL_H