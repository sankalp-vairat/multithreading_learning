#include <iostream>
#include <condition_variable>
#include <Windows.h>

std::mutex mtx;
std::condition_variable cond;
bool flag = true;
int count = 0;

void function(int thread_id) {
      while (count < 10) {
            std::unique_lock<std::mutex> lock(mtx);
            cond.wait(lock, [=]() {return (((count % 2 == 0) && (thread_id == 1)) || ((count % 2 == 1) && (thread_id == 2))); });
            std::cout << "thread_id: " << thread_id << " count: " << count++ <<  std::endl;
            cond.notify_one();
          }
}

int main()
{
      std::thread t1(function, 1);
      std::thread t2(function, 2);

      t1.join();
      t2.join();
}
