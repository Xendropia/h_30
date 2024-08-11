#ifndef TASK_H
#define TASK_H

#include <future>
#include <memory>
#include <atomic>

struct Task {
    std::promise<void> prom;
    std::shared_ptr<std::atomic<int>> active_subtasks;

    Task();
    void add_subtask();
    void complete_subtask();
    std::future<void> get_future();
};

#endif // TASK_H