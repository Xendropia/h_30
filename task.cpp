#include "task.h"

Task::Task() : active_subtasks(std::make_shared<std::atomic<int>>(0)) {}

void Task::add_subtask() {
    ++(*active_subtasks);
}

void Task::complete_subtask() {
    if (--(*active_subtasks) == 0) {
        prom.set_value();
    }
}

std::future<void> Task::get_future() {
    return prom.get_future();
}