#include "server.hpp"

void ThreadPool::_start(int total) {
    for (int i = 0; i < total; i++) {
        auto lambda = [=]() {
            while (true) {
                std::shared_ptr<std::function<void()>> task;

                {
                    std::unique_lock<std::mutex> lock(this->_mtx);

                    this->_cv.wait(lock, [=]() {
                        return this->_isStop || !this->_tasks.empty();
                    });

                    if (this->_isStop && this->_tasks.empty()) break;

                    task = std::move(_tasks.front());
                    this->_tasks.pop();
                }

                (*task)();
            }
        };

        this->_threads.emplace_back(lambda);
    }
}

void ThreadPool::_stop() noexcept {
    {
        std::unique_lock<std::mutex> lock(this->_mtx);
        this->_isStop = true;
    }

    this->_cv.notify_all();

    for (auto &thread : this->_threads) {
        thread.detach();
    }
}

ThreadPool::ThreadPool(int total) {
    this->_start(total);
}

ThreadPool::~ThreadPool() {
    this->_stop();
}

void ThreadPool::enqueue(std::function<void()> task) {
    std::shared_ptr<std::function<void()>> taskPtr = std::make_shared<std::function<void()>>(std::move(task));

    {
        std::unique_lock<std::mutex> lock(this->_mtx);
        this->_tasks.emplace(taskPtr);
    }

    this->_cv.notify_one();
}
