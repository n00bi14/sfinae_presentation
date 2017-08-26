#include <iostream>
#include <chrono>
#include <ctime>

void getString(std::string s)
{
    s.append(50000, 'X');
}

void getStringReference(std::string& s)
{
    s.append(50000, 'X');
}


int main()
{
    long epsCount = 0, epsRefCount = 0;

    std::chrono::time_point<std::chrono::system_clock> start, end;

    for(int i = 0; i <= 1000; i++)
    {
        std::string s1;
        s1.append(5000000, 'X');

        start = std::chrono::system_clock::now();
        getString(s1);
        end = std::chrono::system_clock::now();


        std::chrono::microseconds eps = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        epsCount += eps.count();
        /*
        std::cout << "elapsed time by value: ";
        std::cout << eps.count();
        std::cout << "us\n";
        */



        std::string s2;
        s2.append(5000000, 'X');

        start = std::chrono::system_clock::now();
        getStringReference(s2);
        end = std::chrono::system_clock::now();

        std::chrono::microseconds epsRef = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        epsRefCount += epsRef.count();
        /*
        std::cout << "elapsed time by reference: ";
        std::cout << epsRef.count();
        std::cout << "us\n";
        */
    }

    long factor = epsCount / epsRefCount;
    std::cout << "Factor: " << factor << std::endl;

    return 0;
}
