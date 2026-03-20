/*
There are many ways to create a thread.

 1. Function Pointer
 2. Function with Arguments
 3. Lambda Function
 4. Lambda with Capture
 5. using Functor
 6. using Member Function
 7. using Static Member Function

  A functor is a class that overloads the operator() to make it callable like a function. 
  This allows us to create threads by passing an instance of the functor class.
 */ 


#include <iostream>
#include <thread>
using namespace std;

//Pass a normal function to a thread.
void printHello()
{
    cout << "Hello from thread\n";
}
//Function with Arguments
void printSum(int a, int b) 
{
    cout << "Sum = " << (a + b) << endl;
}

//Functor (Function Object)
class MyFunctor 
{
public:
    void operator()()
    {
        cout << "Thread without parameter\n";        
    }
    void operator()(int x) 
    {
        cout << "Thread with parameter :";
		cout << "Value: " << x << endl;
    }
};
//Member Function Thread
class MyClass 
{
public:
    void display(int x) 
    {
        cout << "Value: " << x << endl;
    }
};
//Static Member Function
class MyClass1 
{
public:
    static void show()
    {
        cout << "Static function thread\n";
    }
};

int main()
{
	cout << "\n 1. Thread Creation using Function Pointer\n";
    thread t(printHello);  // Thread creation
    t.join();              // Wait for thread to finish

	cout << "\n 2. Function with Arguments\n";
    thread t11(printSum, 5, 10); // Passing arguments
    t11.join();

	cout << "\n 3. Thread Creation using Lambda Function\n";
    thread t22([]() 
            {
                cout << "Hello from lambda thread\n";
            });

	t22.join();

    cout << "\n 4. Lambda with Capture " << endl;
    int x = 10;
    thread t33([x]()
        {  
            cout << "Captured value: " << x << endl; 

        });
    t33.join();

	cout << "\n 5. Thread Creation using Functor\n";
    MyFunctor obj;
    thread t1(obj);  
    t1.join();

    MyFunctor obj1;
    thread t2(obj1,11);
    t2.join();

    thread t3(obj1, 22);
    t3.join();

	cout << "\n 6. Thread Creation using Member Function\n";
    MyClass obj66;
    thread t66(&MyClass::display, &obj66, 100);
    t66.join();

	cout << "\n 7. Thread Creation using Static Member Function\n";
	thread t77(&MyClass1::show);
	t77.join();

    return 0;
}