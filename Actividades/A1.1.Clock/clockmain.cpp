#include "clock1.hpp"

using namespace std;

int main()
{
    Clock* instance = Clock::getInstance();
    cout << instance->getTime() << "\n";
    Clock* instance2 = Clock::getInstance();
    cout << instance2->getTime() << "\n";
    cout << instance << "\n" << instance2 << "\n";

    instance->Clock::destroyInstance();
    instance2->Clock::destroyInstance();

    instance = nullptr;
    instance2 = nullptr;

    cout << instance->getTime() << "\n";
    cout << instance2->getTime() << "\n";
    cout << instance << "\n" << instance2 << "\n";
    return 0;
}