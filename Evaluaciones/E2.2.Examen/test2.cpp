#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class IVisitor;
class VGame
{
private:

public:
    string title;
    int price;
    string releaseDate;
    int serialNumber;
    virtual VGame* clone() = 0;
    VGame() { }
    VGame(string t, int p, string rD, int s): title(t),price(p), releaseDate(rD),serialNumber(s)
    {

    }

    void Concept()
    {
        cout << title << " concept development..." << "\n";
    }
    void Design()
    {
        cout << title << " design development..." << "\n";
    }
    void Planning()
    {
        cout << title << " planning development..." << "\n";
    }
    void Production()
    {
        cout << title << " production development..." << "\n";
    }
    void QA()
    {
        cout << title << " quality assurance..." << "\n";
    }
    virtual void accept(IVisitor*) = 0;
    bool operator < (const VGame& cmp) const
    {
        return (price < cmp.price);
    }
    bool operator > (const VGame& cmp) const
    {
        return (price > cmp.price);
    }
};

template<class Base, class SubClass>
class CloneCRTP: public Base{
public:
    Base* clone()
    {
        return new SubClass(dynamic_cast<SubClass&> (*this));
    }
};

class Strategy : public CloneCRTP<VGame,Strategy>
{
public:
    string* strategy1;
    string* strategy2;
    string* strategy3;
    Strategy() { }
    Strategy(string t, int p, string rD, int s)
    {
        title = t;
        price = p;
        releaseDate = rD;
        serialNumber = s;
    }
    Strategy(const Strategy& temp)
    {
        title = temp.title;
        price = temp.price;
        releaseDate = temp.releaseDate;
        serialNumber = temp.serialNumber;
    }
    VGame* clone()
    {
        return new Strategy(*this);
    }
    void accept(IVisitor* visitor);
};
class Adventure:public CloneCRTP<VGame,Adventure>
{
public:
    string* adventure1;
    string* adventure2;
    string* adventure3;
    Adventure(string t, int p, string rD, int s)
    {
        title = t;
        price = p;
        releaseDate = rD;
        serialNumber = s;
    }
    Adventure(const Adventure& temp)
    {
        title = temp.title;
        price = temp.price;
        releaseDate = temp.releaseDate;
        serialNumber = temp.serialNumber;
    }
    VGame* clone()
    {
        return new Adventure(*this);
    }
    void accept(IVisitor* visitor);
};
class Learning:public CloneCRTP<VGame,Learning>
{
public:
    string* learning1;
    string* learning2;
    string* learning3;
    Learning(string t, int p, string rD, int s)
    {
        title = t;
        price = p;
        releaseDate = rD;
        serialNumber = s;
    }
    Learning(const Learning& temp)
    {
        title = temp.title;
        price = temp.price;
        releaseDate = temp.releaseDate;
        serialNumber = temp.serialNumber;
    }
    VGame* clone()
    {
        return new Learning(*this);
    }
    void accept(IVisitor* visitor);
};

class IVisitor
{
public:
    virtual void visit(Strategy&) = 0;
    virtual void visit(Adventure&) = 0;
    virtual void visit(Learning&) = 0;
};

class IncrementVisitor : public IVisitor
{
public:
    void visit(Strategy& s)
    {
        s.price = s.price * 1.1;
    }
    void visit(Adventure& a)
    {
        a.price = a.price * 1.1;
    }
    void visit(Learning& l)
    {
        l.price = l.price * 1.1;
    }
};
class DecrementVisitor: public IVisitor
{
public:
    void visit(Strategy& s)
    {
        cout << s.price;
        s.price = s.price / 1.1;
    }
    void visit(Adventure& a)
    {
        cout << a.price;
        a.price = a.price / 1.1;
    }
    void visit(Learning& l)
    {
        l.price = l.price / 1.1;
    }

};

void Strategy::accept(IVisitor* visitor)
{
    visitor->visit(*this);
}
void Adventure::accept(IVisitor* visitor)
{
    visitor->visit(*this);
}
void Learning::accept(IVisitor* visitor)
{
    visitor->visit(*this);
}

class Creator
{
private:
    static Creator* instance;
    static int counter;
    Creator()
    {
        cout << "Constructing creator\n";
    }
    ~Creator()
    {
        cout << "Destroying creator\n";
    }
    static void addRef()
    {
        ++counter;
    }
    static void destoryRef()
    {
        --counter;
    }
public:
    static Creator* getInstance()
    {
        if(instance == nullptr)
        {
            instance = new Creator;
        }
        addRef();
        return instance;
    }
    static void destoryInstance()
    {
        destoryRef();
        if(instance != nullptr && counter == 0)
        {
            delete instance;
            instance = nullptr;
        }
    }
    template<class Game>
    Game* factoryMethod(string t, int p, string rD, int s)
    {
        return new Game(t,p,rD,s);
    }
    template<class Game>
    Game* create(string t, int p, string rD, int s)
    {
        Game* myGame = factoryMethod<Game>(t,p,rD,s);
        myGame->Concept();
        myGame->Design();
        myGame->Planning();
        myGame->Production();
        myGame->QA();
        return myGame;
    }
};
Creator* Creator::instance = nullptr;
int Creator::counter = 0;

class Inventory
{
public:
    vector<VGame*> stock;
    Inventory()
    {
        
    }

    void addVG(VGame* game)
    {
        stock.push_back(game);
    }

    void elimVG(string t)
    {
        for(int i = 0; i < stock.size(); i++)
        {
            if (stock[i]->title == t)
            {
                stock.erase(stock.begin() + i);
            }
        }
    }
    void elimVG(int sN)
    {
        for(int i = 0; i < stock.size(); i++)
        {
            if (stock[i]->serialNumber == sN)
            {
                stock.erase(stock.begin() + i);
            }
        }
    }
    void undo()
    {

    }
    void sortVG(bool x)
    {
        if(x)
            sort(stock.begin(), stock.end());
        else
            sort(stock.begin(), stock.end(),greater<VGame*>());
    }
    VGame* findVG(int sN)
    {
        for(int i = 0; i < stock.size(); i++)
        {
            if (stock[i]->serialNumber == sN)
            {
                return stock[i];
            }
        }
    }
    VGame* findVG(string t)
    {
        for(int i = 0; i < stock.size(); i++)
        {
            if (stock[i]->title == t)
            {
                return stock[i];
            }
        }
    }
    int numberOfItems()
    {
        return stock.size();
    }
    void printALL()
    {
        for(int i = 0; i < stock.size(); i++)
        {
            cout << "Video Game #" << i << "\n";
            cout << "Title: " << stock[i]->title << "\n";
            cout << "Release Date: " << stock[i]->releaseDate << "\n";
            cout << "Price: " << stock[i]->price << "\n";
            cout << "Serial Number: " << stock[i]->serialNumber << "\n\n";
        }
    }

    void accept (IVisitor* visitor)
    {
        for(int i = 0; i < stock.size(); i++)
        {
            stock[i]->accept(visitor);
        }
    }

    void priceChange(bool priceAlteration)
    {
        if(priceAlteration)
        {
            IncrementVisitor* incrementVisitor = new IncrementVisitor;
            accept(incrementVisitor);
        }
        else
        {
            DecrementVisitor* decrementvisitor = new DecrementVisitor;
            accept(decrementvisitor);          
        }
    }

};

int main () {
    //Testing Prototype
    /*
    VGame *CarFry5 = new Adventure("CarFry5", 60, "April 5",3245);
    VGame *CarFry4 = CarFry5->clone();
    CarFry4->title = "CarFry4";

    cout << "5:" << CarFry5->title << "\n";
    cout << "4:" << CarFry4->title << "\n";
    */
    //Testing Factory
    /*
    Creator* client = new Creator();
    VGame* mario = client->create<Adventure>("Mario", 60, "April 6",3245);
    cout << mario->title;
    */
    //Testing Singleton
    /*
    Creator* client = Creator::getInstance();
    VGame* mario = client->create<Adventure>("Mario", 60, "April 6",3245);
    cout << mario->title;
    */
    //Testing Visitor
    /*
    Inventory* store = new Inventory;
    VGame *Zelda =  new Adventure("BOTW", 60, "March 20", 3245);
    store->addVG(Zelda);
    store->printALL();
    store->priceChange(1);
    store->printALL();
    */
    //Testing Sort
    /*
    Inventory* store = new Inventory;
    VGame* Vermintide = new Adventure("WarHammer", 30, "Feb 5", 5);
    VGame* Vermintide2 = new Adventure("WarHammer2", 60, "Feb 6", 6);
    store->addVG(Vermintide);
    store->addVG(Vermintide2);
    store->sortVG(0);
    store->printALL();
    store->sortVG(1);
    store->printALL();
    */
    //Testing Visitor && Prototype
    /*
    Inventory* store = new Inventory;
    VGame *Zelda =  new Adventure("BOTW", 60, "March 20", 3245);
    VGame *Zelda2 = Zelda->clone();
    store->addVG(Zelda);
    store->addVG(Zelda2);
    store->printALL();
    store->priceChange(1);
    store->printALL();
    */
}