/*
Thread Synchronization using std::condition_variable
Use Case:
Producer-Consumer Problem

To implement the producer-consumer problem with condition_variable,
you need:
A shared buffer queue to store data.
A mutex to ensure only one thread accesses the buffer at a time.
One or two condition_variable objects to signal state changes (e.g., buffer is no longer empty or no longer full).
unique_lock for managing the mutex while interacting with the condition variable.
Better Approach: lock_guard (RAII)
 lock_guard<mutex> lock(mtx); //  Auto lock/unlock

*/
#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
using namespace std;

queue<int> buffer;
const int MAX_SIZE = 5;

mutex m;
condition_variable cv;

void producer() 
{
    for (int i = 1; i <= 10; ++i) 
    {
        unique_lock<mutex> lock(m);

        // Wait until buffer has space
        cv.wait(lock, [] { return buffer.size() < MAX_SIZE; });

        buffer.push(i);
        cout << "Produced: " << i << endl;

        lock.unlock();        // Unlock before notifying
        cv.notify_one();      // Notify consumer
    }
}

void consumer() 
{
    for (int i = 1; i <= 10; ++i) 
    {
        unique_lock<mutex> lock(m);

        // Wait until buffer has data
        cv.wait(lock, [] { return !buffer.empty(); });

        int val = buffer.front();
        buffer.pop();

        cout << "Consumed: " << val << endl;

        lock.unlock();
        cv.notify_one();      // Notify producer
    }
}

int main() 
{
    thread t1(producer);
    thread t2(consumer);

    t1.join();
    t2.join();

    return 0;
}