#include <mutex>
#include <thread>
#include <deque>
#include <type_traits>
#include <chrono>
#include <string>
#include <iostream>
#include <vector>
#include <functional>
#include <condition_variable>
#include <future>

template<typename T>
class Queue{
  std::deque<T> d_;
  std::mutex m_;
  std::atomic<bool> is_closed_{false};
  std::condition_variable cond_;
public:
  void Enqueue(T&& value){
    std::unique_lock lk(m_);
    d_.push_back(std::move(value));
    cond_.notify_one();
  }
  bool WaitAndDequeue(T& value){
    std::unique_lock lk(m_);
    cond_.wait(lk,[&](){return !d_.empty() || is_closed_.load();});
    if(d_.empty()) return false;
    value=d_.front();
    d_.pop_front();
    return true;
  }

  void close(){
    is_closed_.store(true);
    cond_.notify_all();
  }
};

class ThreadPool {
public:
    ThreadPool(size_t thread_count) : workers_(thread_count){
        for (size_t i = 0; i < thread_count; ++i) {
            workers_[i] = std::thread([this,i] { work(); });
        }
    }

    ~ThreadPool() {
        stop();
    }

    template<typename F, typename... Args>
    decltype(auto) enqueue(F&& f, Args&&... args) {
        using return_type = typename std::invoke_result<F,Args...>::type;
        auto task = std::make_shared<std::packaged_task<return_type()>>(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
        std::future<return_type> res = task->get_future(); 

        Jobqueue.Enqueue([task](){(*task)();});
        return res;
    }

    void stop() {
        Jobqueue.close();
        for (auto& worker : workers_) {
            if (worker.joinable()) {
                worker.join();
            }
        }
    }

private:
    using Task = std::function<void()>;

    void work() {
        while (true) {
            Task task;
            if (Jobqueue.WaitAndDequeue(task)) {
                task();
            }else{
                break;
            }
        }
    }
    std::vector<std::thread> workers_;
    Queue<Task> Jobqueue;
};

