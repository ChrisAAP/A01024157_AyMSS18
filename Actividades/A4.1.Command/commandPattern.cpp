#include <iostream>

using namespace std;

template<int n>
class Repeat : Repeat<n-1>
{
public:
    Repeat()
    {
        cout << "Number: " << n << "\n";
    }
};
template<>
class Repeat<0>
{

};

int main()
{
    Repeat<100> r;
}