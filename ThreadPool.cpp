#include <iostream>  
#include <windows.h>
#include <vector>  
#include <queue>
#include <thread>  
#include <mutex>
#include <condition_variable>  
using Delegate = void (*)(void*);
using namespace std;  
  
// 线程池任务  
struct Task {  
    Delegate func;
    void* arg;  
};  
  
// 线程池  
class ThreadPool {  
public:  
    ThreadPool(int poolSize) : stop(false) {  
        for (int i = 0; i < poolSize; i++) {  
            threads.emplace_back([this] {  
                while (!stop) {  
                    unique_lock<std::mutex> lock(this->mutex);  
                    condition.wait(lock, [this] { return !this->tasks.empty() || stop; });  //有任务或者线程池销毁时继续
                    if (stop && tasks.empty()) {  
                        break;  
                    }  
                    Task task = tasks.front();  
                    tasks.pop();  
                    lock.unlock();  
                    task.func(task.arg);  
                }  
            });  
        }  
    }  
  
    ~ThreadPool() {  
        stop = true;  
        condition.notify_all();  
        for (auto& thread : threads) {  
            thread.join();  
        }  
    }  
  
    void addTask(Delegate func, void* arg) {  
        Task task{func, arg};  
        unique_lock<std::mutex> lock(mutex);
        tasks.push(task);  
        condition.notify_one();  
    }  

private:  
    vector<thread> threads;  
    queue<Task> tasks;  
    mutex mutex;  
    condition_variable condition;  
    bool stop;  
};  

// 示例任务1：输出奇数序列  
void task1(void* arg) {  
    for (int i = 1; i <= *(int*)arg * 2; i += 2) {  
        cout << i << " ";  
    }  
    cout << endl;  
}  
  
// 示例任务2：输出平方序列  
void task2(void* arg) {  
    for (int i = 1; i <= *(int*)arg; i++) {  
        cout << i * i << " ";  
    }  
    cout << endl;  
}  
  
int main() {  
    ThreadPool pool(2); // 创建包含2个线程的线程池  
    int* res=new int(5);
    Delegate delegate=task1;
    pool.addTask(delegate, res); // 添加任务1，输出1到10的奇数序列  
    delegate=task2;
    pool.addTask(delegate, res); // 添加任务2，输出1到5的平方序列  
    Sleep(5); // 等它们执行完毕
    return 0;  
}