#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

class PrintOddEven {
    public:
        static int counter;
        static mutex m;
    void odd() {
        while(counter < 10) {
            std::lock_guard<mutex> lock(m);
            if((counter % 2 == 1)&& counter < 100) {
                cout << counter <<" : Thread is"<< std::this_thread::get_id() << endl;
                counter++;
            }
        }
    }


    void even() {
        while(counter < 10) {
            std::lock_guard<mutex> lock(m);
            if((counter % 2 == 0) && counter <= 100) {
                cout << counter <<" : Even Thread is"<< std::this_thread::get_id() << endl;
                counter++;
            }
        }
    }

    thread* getOddThread() {
        return new thread([=]() {odd();});
    }

    thread* getEvenThread() {
        return new thread([=] () {even();});
    }

};

int PrintOddEven::counter = 0;
mutex PrintOddEven::m;

int main() {
    PrintOddEven p;
    thread *t = p.getOddThread();
    thread *t1 = p.getEvenThread();

    t->join();
    t1->join();

return 0;
}
