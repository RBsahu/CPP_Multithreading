/*
Thread synchronization:
Only one thread accesses shared data at a time to avoid race condition.
Why mutex?
To prevent race conditions and ensure thread-safe access to shared resources.

Better Approach: std::lock_guard (RAII)
Why better?
Automatically releases lock (exception-safe)
*/

#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

int counter = 0;     // Shared variable
int counter2 = 0;     // Shared variable 2
mutex mtx;           // Lock


void increment() 
{
    mtx.lock();      //  Lock (only one thread allowed)

    counter++;       // Critical section (shared data)
    cout << "Counter: " << counter << endl;

    mtx.unlock();    //  Unlock (next thread can enter)
}

void increment2(int id) 
{
    for (int i = 0; i < 5; ++i) 
    {
        lock_guard<mutex> lock(mtx); //  Auto lock/unlock

        counter2++;
        cout << "Thread " << id << " -> Counter2: " << counter2 << endl;
    } //  Automatically unlocked here
}

int main() 
{
    thread t1(increment);
    thread t2(increment);

    t1.join();
    t2.join();

    thread t11(increment2, 11);
    thread t22(increment2, 22);

    t11.join();
    t22.join();

    return 0;
}