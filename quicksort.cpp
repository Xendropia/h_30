#include "quicksort.h"

void quicksort(std::vector<int>& array, int left, int right, std::shared_ptr<Task> parent_task, ThreadPool& pool) {
    if (left >= right) {
        if (parent_task) parent_task->complete_subtask();
        return;
    }

    int pivot = partition(array, left, right);

    if ((pivot - left > 100000) && pool.has_idle_threads()) {
        auto subtask = std::make_shared<Task>();
        subtask->add_subtask();
        pool.push_task([=, &array, &pool] {
            quicksort(array, left, pivot - 1, subtask, pool);
        });
        quicksort(array, pivot + 1, right, subtask, pool);
        subtask->get_future().wait();
    } else {
        quicksort(array, left, pivot - 1, parent_task, pool);
        quicksort(array, pivot + 1, right, parent_task, pool);
    }

    if (parent_task) parent_task->complete_subtask();
}

int partition(std::vector<int>& array, int left, int right) {
    int pivot = array[right];
    int i = left - 1;
    for (int j = left; j < right; ++j) {
        if (array[j] < pivot) {
            std::swap(array[++i], array[j]);
        }
    }
    std::swap(array[i + 1], array[right]);
    return i + 1;
}