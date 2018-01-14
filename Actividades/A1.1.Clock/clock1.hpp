#ifndef CLOCK1
#define CLOCK1


#include <iostream>
#include <string>
#include <time.h>

using namespace std;

class Clock {
private:
    static Clock* instance;
    static int counter;
    Clock()
    {
        cout << "Constucting!\n";
    }
    ~Clock()
    {
        cout << "Destoying!\n";
    }
    static void addRef()
    {
        ++counter;
    }
    static void destroyRef()
    {
        --counter;
    }
public:
    static Clock* getInstance()
    {
        if(instance  == nullptr)
        {
            instance = new Clock;
        }
        addRef();
        return instance;
    }
    static void destroyInstance()
    {
        destroyRef(); 
        if(instance!=nullptr && counter == 0)
        {
            delete instance;
            instance = nullptr;
        }
        cout << "instance: " << instance << "\n";
    }
    string getTime()
    {
        time_t rawtime;
        struct tm * timeinfo;
        time ( &rawtime );
        timeinfo = localtime ( &rawtime );
        return asctime(timeinfo);
    }
};
Clock* Clock::instance = nullptr;
int Clock::counter = 0;
#endif