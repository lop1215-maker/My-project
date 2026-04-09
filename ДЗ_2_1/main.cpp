#include <chrono>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <stdexcept>
#include <thread>
#include <vector>


class TaskQueue {
public:
    void push(int task) {
        std::unique_lock<std::mutex> lock(mutex_);

        if (closed_) {
            throw std::runtime_error("Cannot push a task into a closed queue");
        }

        tasks_.push(task);
        condition_.notify_one();
    }

    bool pop(int& task) {
        std::unique_lock<std::mutex> lock(mutex_);

        condition_.wait(lock, [this]() {
            return closed_ || !tasks_.empty();
        });

        if (tasks_.empty()) {
            return false;
        }

        task = tasks_.front();
        tasks_.pop();
        return true;
    }

    void close() {
        std::unique_lock<std::mutex> lock(mutex_);
        closed_ = true;
        condition_.notify_all();
    }

private:
    std::queue<int> tasks_;
    std::mutex mutex_;
    std::condition_variable condition_;
    bool closed_ = false;
};

void worker(TaskQueue& queue, int workerId) {
    (void)workerId;

    int task = 0;
    while (queue.pop(task)) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}


int main() {
    const int workerCount = 4;
    const int taskCount = 20;

    if (workerCount <= 0) {
        throw std::invalid_argument("Worker count must be greater than zero");
    }

    if (taskCount < 0) {
        throw std::invalid_argument("Task count cannot be negative");
    }

    TaskQueue queue;
    std::vector<std::thread> workers;
    workers.reserve(workerCount);

    for (int i = 0; i < workerCount; ++i) {
        workers.emplace_back(worker, std::ref(queue), i + 1);
    }

    for (int i = 1; i <= taskCount; ++i) {
        queue.push(i);
    }

    queue.close();

    for (std::thread& thread : workers) {
        if (thread.joinable()) {
            thread.join();
        }
    }

    return 0;
}