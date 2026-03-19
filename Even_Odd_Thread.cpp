//Print Even Odd Using Two Threads

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

mutex m;                  // Mutex to protect shared variable 'num'
condition_variable cv;      // Condition variable for thread synchronization
int count1 = 1;                // Shared counter

// Function executed by odd thread
void oddPrint(int n)
{

    for (int i = 0; i < n; i++)
    {
        unique_lock<mutex> lock(m);   // Lock mutex before accessing shared data

        // Wait until either:
        // 1. number is odd
        // 2. OR number exceeds limit (to safely exit)
        cv.wait(lock, [] { return count1 % 2 == 1; });

        // Exit condition
        if (count1 > 10)
            break;

        // Print odd number
        cout << "Odd Thread  :" << count1 << endl;

        count1++;              // Increment shared number

        // Notify other waiting thread (even thread)
        cv.notify_all();
    }
}

// Function executed by even thread
void evenPrint(int n)
{
    for (int i = 0; i < n; i++)
    {
        unique_lock<mutex> lock(m);   // Lock mutex before accessing shared data

        // Wait until either:
        // 1. number is even
        // 2. OR number exceeds limit
        cv.wait(lock, [] { return count1 % 2 == 0; });

        // Exit condition
        if (count1 > 10)
            break;

        // Print even number
        cout << "Even Thread :" << count1 << endl;

        count1++;              // Increment shared number

        // Notify other waiting thread (odd thread)
        cv.notify_all();
    }
}

int main()
{
    int n = 10;
    // Create thread to print odd numbers
    thread t1(oddPrint, n);

    // Create thread to print even numbers
    thread t2(evenPrint, n);

    // Wait for threads to finish
    t1.join();
    t2.join();

    return 0;
}