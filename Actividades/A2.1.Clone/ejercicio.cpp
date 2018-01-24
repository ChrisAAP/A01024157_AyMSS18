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
        smartphone = new int(*(temp.smartphone));
    }
};
class SmartWatch : public Moviles
{
public:
    int* smartwatch;
    Moviles* clone()
    {
        return new SmartWatch(*this);
    }
    SmartWatch() { }
    SmartWatch(int val2): Moviles(val2), smartwatch(new int(val2))
    {

    }
    SmartWatch(const SmartWatch& temp)
    {
        x = temp.x;
        y = temp.y;
        a = new int(*(temp.a));
        b = new int(*(temp.b));
        smartwatch = new int(*(temp.smartwatch));
    }
};

int main()
{
    Moviles *t = new Tablet(1);
    Moviles *s = new SmartPhone(2);
    Moviles *w = new SmartWatch(3);

    Moviles *t2 = t->clone();
    Moviles *s2 = s->clone();
    Moviles *w2 = w->clone();

    cout << "t:\n  x:" << t->x << "\n";
    cout << "t2:\n  x:" << t->x << "\n";

    cout << "s:\n  x:" << s->x << "\n";
    cout << "s2:\n  x:" << s->x << "\n";

    cout << "w:\n  x:" << w->x << "\n";
    cout << "w2:\n  x:" << w->x << "\n";

    t2->x = 4;
    s2->x = 5;
    w2->x = 6;

    cout << "t:\n  x:" << t->x << "\n";
    cout << "t2:\n  x:" << t2->x << "\n";

    cout << "s:\n  x:" << s->x << "\n";
    cout << "s2:\n  x:" << s2->x << "\n";

    cout << "w:\n  x:" << w->x << "\n";
    cout << "w2:\n  x:" << w2->x << "\n";
}