/*
What is an Atomic Variable:
An atomic variable is a thread-safe variable that ensures operations like read, write, and 
update happen without interruption, preventing race conditions without using locks.

An atomic variable is a variable that can be accessed and modified by multiple threads 
safely without using a mutex.

Key Idea:
Operation happens completely or not at all (no interruption)

Simple Example (Problem without Atomic)
int counter = 0;

void increment()
{
    counter++; // Not thread-safe
}
Issue:
counter++ is NOT a single step
It is:
Read
Increment
Write
 Multiple threads can clash , wrong result
Solution: std::atomic

What’s happening?
 counter++ is handled atomically
 No race condition
 No mutex needed
 Important Atomic Operations:
 atomic<int> x(0);

x++;            // increment
x--;            // decrement
x += 5;         // add
x.load();       // read value
x.store(10);    // write value

Use atomic when:
Simple variable (counter, flag)
No complex logic
High performance needed

When NOT to Use Atomic?
Avoid atomic if:
Multiple variables involved
Complex logic (if/else, multiple steps)
Need transaction-like behavior
Use mutex instead

*/

#include <iostream>
#include <thread>
#include <atomic>
using namespace std;

atomic<int> counter(0);  // Atomic variable

void increment() 
{
    for (int i = 0; i < 10; i++) 
    {
        counter++;   //  Thread-safe
    }
}

int main() 
{
    thread t1(increment);
    thread t2(increment);

    t1.join();
    t2.join();

    cout << "Final Counter: " << counter << endl; // Always 20
    return 0;
}