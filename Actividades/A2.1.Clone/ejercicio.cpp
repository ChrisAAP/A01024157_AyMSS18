#include <iostream>
using namespace std;

class Moviles
{
public:
    int* a;
    int* b;
    int x;
    int y;
    virtual Moviles* clone() = 0;
    Moviles(){ }
    Moviles(int val): a(new int(val)), b(new int (val)), x(val),y(val)
    {

    }
    void encender()
    {
        cout << "Turn on";
    }
    void apagar()
    {
        cout << "Shut down";
    }
    void reiniciar()
    {
        cout << "Restarting";
    }
    void restaurar()
    {
        cout << "Reinstating";
    }

};
class Tablet : public Moviles
{
public:
    int* tablet;
    Moviles* clone()
    {
        return new Tablet(*this);
    }
    Tablet() { }
    Tablet(int val2): Moviles(val2), tablet(new int(val2))
    {

    }
    Tablet(const Tablet& temp)
    {
        x = temp.x;
        y = temp.y;
        a = new int(*(temp.a));
        b = new int(*(temp.b));
        tablet = new int(*(temp.tablet));
    }
};
class SmartPhone : public Moviles
{
public:
    int* smartphone;
    Moviles* clone()
    {
        return new SmartPhone(*this);
    }
    SmartPhone(){ }
    SmartPhone(int val2): Moviles(val2), smartphone(new int(val2))
    {

    }
    SmartPhone(const SmartPhone& temp)
    {
        x = temp.x;
        y = temp.y;
        a = new int(*(temp.a));
        b = new int(*(temp.b));
        smartphone = new int(*(temp.tablet));
    }
};
class SmartWatch : public Moviles
{
public:
    int* smartwatch;
    Moviles* clone()
    {
        return new SmartWatch(*this)
    }
    SmartWatch() { }
    SmartWatch(int val2): Moviles(val2), smartwatch(new int(val2))
    {

    }
    SmartWatch(const SmartWatch& temp)
    {
        x = *(temp.x);
        y = *(temp.y);
        a = new int(*(temp.a));
        b = new int(*(temp.b));
        smartwatch = new int(*(temp.smartwatch));
    }
};

int main()
{
    Tablet* t = new Tablet(5);
    Tablet t2 = *t;

    SmartPhone* sp = new SmartPhone(10);
    SmartPhone sp2 = *sp;

    SmartWatch* sw = new SmartWatch(15);
}