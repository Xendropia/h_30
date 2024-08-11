#include <iostream>
#include <vector>
#include <chrono>
#include "thread_pool.h"
#include "task.h"
#include "quicksort.h"

int main() {
    std::vector<int> array = /* инициализация вашего массива */;
    ThreadPool pool(std::thread::hardware_concurrency());
    std::shared_ptr<Task> root_task = std::make_shared<Task>();
    root_task->add_subtask();

    auto start = std::chrono::high_resolution_clock::now();

    quicksort(array, 0, array.size() - 1, root_task, pool);
    root_task->get_future().wait();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Elapsed time: " << elapsed.count() << " seconds.\n";
    return 0;
}