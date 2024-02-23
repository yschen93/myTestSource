#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__

#include <vector>
#include <thread>
#include <memory>
#include <condition_variable>
#include <queue>
#include <future>
#include <mutex>
#include <functional>

class ThreadPool
{
public:
    ThreadPool(size_t number);

    template<typename F, typename... ARGS>
    auto Enqueue(F&& f, ARGS&&... args)
        -> std::future<typename std::result_of<F(ARGS...)>::type>;

    ~ThreadPool();
private:
    std::vector<std::thread> threads_;
    std::mutex mtx_;
    std::condition_variable cv_;
    std::queue<std::function<void>()> tasks_;
    std::atomic<bool> is_running_;
};

ThreadPool::ThreadPool(size_t number)
    : is_running_(true)
{
    for (size_t i = 0; i < number; ++i)
    {
        threads_.emplace_back([this](){
            
            std::function<void()> task;

            for (; ;)
            {
                {
                    std::unique_lock<std::mutex> lck(mtx_);
                    cv_.wait(lck, [this](){
                        return (!tasks_.empty() || !is_running_);
                    });

                    if (!is_running_ && tasks_.empty())
                        return ;

                    task = std::move(tasks_.front());
                    tasks_.pop();
                }

                task();
            }
        });
    }
}

template<typename F, typename... ARGS>
auto ThreadPool::Enqueue(F&& f, ARGS&&... args)
    -> std::future<typename std::result_of<F(ARGS...)>::type>
{
    using return_type = typename std::result_of<F(ARGS...)>::type;
    auto wrapper = std::make_shared<std::packaged_task<return_type()>>(std::bind(std::forward<F>(f), 
        std::forward<ARGS>(args)...));
    
    auto res = wrapper->get_future();
    auto task = [wrapper](){
        (*wrapper)();
    };

    {
        std::unique_lock<std::mutex> lck(mtx_);

        if (false == is_running_.load())
            throw std::runtime_error("Enqueue on stopped thread pool");
        tasks_.emplace(task);
    }

    cv_.notify_one();
    return res;
}

ThreadPool::~ThreadPool()
{
    {
        std::unique_lock<std::mutex> lck(mtx_);
        is_running_.store(false);
    }

    cv_.notify_all();
    for (auto& thread : threads_)
        thread.join();
}

#endif