#include <iostream>
using namespace std;

class Prototype
{
public:
    virtual Prototype* clone() = 0;
};
class Concrete1 : public Prototype
{
public:
    Prototype* clone()
    {
        return new Concrete1(*this);
    }
};
int main()
{
    Concrete1* c1 = new Concrete1;
}