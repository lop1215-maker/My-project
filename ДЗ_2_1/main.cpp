#include <chrono>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <stdexcept>
#include <thread>
#include <vector>

int main() {
    const int workerCount = 4;
    const int taskCount = 20;

    if (workerCount <= 0) {
        throw std::invalid_argument("Worker count must be greater than zero");
    }

    if (taskCount < 0) {
        throw std::invalid_argument("Task count cannot be negative");
    }

    return 0;
}