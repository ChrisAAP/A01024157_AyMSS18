#include <iostream>

using namespace std;

class Foo
{
    int value;
    int* pointer;

public:
    explicit Foo(int value = 0) : value(value), pointer(new int [value])
    {
        cout << "Parameter constructor\n";
    }

    Foo(const Foo& val){cout << "Copy Constructor\n"; }

    Foo& operator = (const Foo& ref)
    {
        cout << "Copy Assignment\n";
        Foo temp(ref);
        std::swap(value, temp.value);
        std::swap(pointer, temp.pointer);
        return *this;
    }

    Foo(Foo&& temp) {}
    Foo& operator = (Foo&& temp)
    {
        cout << "Move Assignment\n";
        std::swap(value, temp.value);
        std::swap(pointer, temp.pointer);
        return *this;
    }
};

int main()
{
    Foo a(5);
    // Foo b{5};        // Parameter inicialization
    // Foo c = {5,6,7}  // Parameter-list initialization

    Foo b;
    b = Foo(10);
    
}