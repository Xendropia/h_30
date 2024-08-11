#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <vector>
#include "task.h"
#include "thread_pool.h"

void quicksort(std::vector<int>& array, int left, int right, std::shared_ptr<Task> parent_task, ThreadPool& pool);

#endif // QUICKSORT_H