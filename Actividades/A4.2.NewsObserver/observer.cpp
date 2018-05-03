#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Subject;
class Observer;

class Observer 
{
public:
    virtual void update(string, Subject*) = 0;
};

class Subject
{
public:
    void attach(Observer* o) 
    {
        observers.push_back(o);
    }
    void dettach(Observer* o) 
    {
        for(int i = 0; i < observers.size(); i++) 
        {
            if(observers[i] == o) 
            {
                observers.erase(observers.begin()+i);
                return;
            }
        }
    }
    void notifyAll(string move, Subject* s) 
    {
        for(int i = 0; i < observers.size(); i++) 
        {
            observers[i]->update(move, s);
        }
    }
    virtual string whoami() = 0;
private:
    vector<Observer*> observers;
};

class Trump : public Subject 
{
public:
    void makeNoise() 
    {
        notifyAll("Trump talk", this);
    }
    string whoami() 
    {
        return "I am trump";
    }
};

class Anaya : public Subject 
{
public:
    void makeNoise() 
    {
        notifyAll("Anaya talk", this);
    }
    string whoami()
    {
        return "I am Anaya";
    }
};

class Meade : public Subject 
{
public:
    void makeNoise() 
    {
        notifyAll("Meade talk", this);
    }
    string whoami() 
    {
        return "I am Meade";
    }
};

class Zavala : public Subject 
{
public:
    void makeNoise() 
    {
        notifyAll("Zavala talk", this);
    }
    string whoami() 
    {
        return "I am Zavala";
    }
};

class AMLO : public Subject 
{
public:
    void makeNoise() 
    {
        notifyAll("AMLO talk", this);
    }
    string whoami() 
    {
        return "I am voldemort";
    }
};

class MVSNews : public Observer
{
public:
    void update(string move, Subject* s) 
    {
        cout << "MVS News: " << s->whoami() << " says " << move << '\n';
    }
};

class TelevisaNews : public Observer 
{
public:
    void update(string move, Subject* s) 
    {
        cout << "Televisa Noticias: " << s->whoami() << " says " << move << '\n';
    }
};

class AztecaNews : public Observer 
{
public:
    void update(string move, Subject* s) 
    {
        cout << "Azteca Noticias: " << s->whoami() << " says " << move << '\n';
    }
};

int main() 
{
    AMLO *president = new AMLO();
    TelevisaNews *news1 = new TelevisaNews();
    AztecaNews *news2 = new AztecaNews();
    president->attach(news1);
    president->attach(news2);
    president->makeNoise();
}