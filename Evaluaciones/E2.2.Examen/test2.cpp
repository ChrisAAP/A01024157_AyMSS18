#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
class VGame;
class Observer;
class Observer
{
public:
    virtual void update(string, VGame*) = 0;
};

class IVisitor;
class VGame
{
private:
public:
    string title;
    int price;
    string releaseDate;
    int serialNumber;
    vector<Observer*> observers;
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
    void attach(Observer* o){
        observers.push_back(o);
    }
    void dettach(Observer* o)
    {
        for(int i = 0; i < observers.size();i++)
        {
            if(observers[i] == o)
            {
                observers.erase(observers.begin()+i);
                return;
            }
        }
    }
    void notifyAll(string release, VGame* vg)
    {
        for(int i = 0; i < observers.size(); i++)
        {
            observers[i]->update(release, vg);
        }
    }
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
        notifyAll(rD, this);
    }
    Strategy(const Strategy& temp)
    {
        title = temp.title;
        price = temp.price;
        releaseDate = temp.releaseDate;
        serialNumber = temp.serialNumber;
        notifyAll("NEW " + releaseDate, this);
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
        notifyAll(rD, this);
    }
    Adventure(const Adventure& temp)
    {
        title = temp.title;
        price = temp.price;
        releaseDate = temp.releaseDate;
        serialNumber = temp.serialNumber;
        notifyAll("NEW " + releaseDate, this);
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
        notifyAll(rD, this);
    }
    Learning(const Learning& temp)
    {
        title = temp.title;
        price = temp.price;
        releaseDate = temp.releaseDate;
        serialNumber = temp.serialNumber;
        notifyAll("NEW " + releaseDate, this);
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

class User : public Observer
{
public:
    string name;
    void update(string release, VGame *vg)
    {
        cout << "Im " << name << " and I recieved info about the " << vg->title << " video game.\n";
    }
};

class Inventory
{
public:
    vector<VGame*> stock;
    vector<VGame*> temporalUndo;
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
                temporalUndo.push_back(stock[i]);
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
                temporalUndo.push_back(stock[i]);
                stock.erase(stock.begin() + i);
            }
        }
    }
    void undo()
    {
        stock.push_back(temporalUndo[temporalUndo.size() - 1]);
        temporalUndo[temporalUndo.size() - 1];
    }
    void sortVG(bool x)
    {
        if(x)
            sort(stock.begin(), stock.end());
        else
            sort(stock.begin(), stock.end(),greater<VGame*>());
    }
    void findVG(int sN)
    {
        for(int i = 0; i < stock.size(); i++)
        {
            if (stock[i]->serialNumber == sN)
            {
                cout << "Video Game #" << i << "\n";
                cout << "Title: " << stock[i]->title << "\n";
                cout << "Release Date: " << stock[i]->releaseDate << "\n";
                cout << "Price: " << stock[i]->price << "\n";
                cout << "Serial Number: " << stock[i]->serialNumber << "\n\n";
            }
            else
                cout << "No game found \n";
        }
    }
    void findVG(string t)
    {
        for(int i = 0; i < stock.size(); i++)
        {
            if (stock[i]->title == t)
            {
                cout << "Video Game #" << i << "\n";
                cout << "Title: " << stock[i]->title << "\n";
                cout << "Release Date: " << stock[i]->releaseDate << "\n";
                cout << "Price: " << stock[i]->price << "\n";
                cout << "Serial Number: " << stock[i]->serialNumber << "\n\n";
            }
            else
                cout << "No game found \n";
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
    //Menu
    int option;
    int vgprice;
    int vgserial;
    string vgtitle;
    string vgRD;
    Inventory* store = new Inventory;
    VGame* foundGame;
    while(true)
    {
        cout << "What do you wish to do? \n" 
        << "1. Add Video Game to stock\n"
        << "2. Delete Video Game from stock\n"
        << "3. Sort Video Games in stock\n"
        << "4. Find Video Game in stock\n"
        << "5. Number of Video Games\n"
        << "6. Show all info from Video Games in stock\n"
        << "7. Price Change\n"
        << "8. Exit\n\n";
        cin >> option;
        if(option == 1)
        {
            cout << "What type of game is it?\n"
            << "1. Adventure\n"
            << "2. Strategy\n"
            << "3. Learning\n";
            cin >> option;
            if(option == 1)
            {
                cout << "What is the title?\n";
                cin >> vgtitle;
                cout << "What is the release date?\n";
                cin >> vgRD;
                cout << "What is the price?\n";
                cin >> vgprice;
                cout << "What is the serial number?\n";
                cin >> vgserial;
                foundGame = new Adventure(vgtitle,vgprice,vgRD,vgserial);
                store->addVG(foundGame);
            }
            else if(option == 2)
            {
                cout << "What is the title?\n";
                cin >> vgtitle;
                cout << "What is the release date?\n";
                cin >> vgRD;
                cout << "What is the price?\n";
                cin >> vgprice;
                cout << "What is the serial number?\n";
                cin >> vgserial;
                foundGame = new Strategy(vgtitle,vgprice,vgRD,vgserial);
                store->addVG(foundGame);
            }
            else if(option == 4)
            {
                cout << "What is the title?\n";
                cin >> vgtitle;
                cout << "What is the release date?\n";
                cin >> vgRD;
                cout << "What is the price?\n";
                cin >> vgprice;
                cout << "What is the serial number?\n";
                cin >> vgserial;
                foundGame = new Strategy(vgtitle,vgprice,vgRD,vgserial);
                store->addVG(foundGame);
            }
            else
            {
                cout << "Not an option\n\n";
            }

        }
        else if(option == 2)
        {
            cout << "1. Delete by  serial number\n"
            << "2. Delete by title\n";
            cin >> option;
            if(option == 1)
            {
                cout << "What is the serial number?\n";
                cin >> vgserial;
                store->elimVG(vgserial);
            }
            else if(option == 2)
            {
                cout << "What is the title?\n";
                cin >> vgtitle;
                store->elimVG(vgtitle);
            }
            else
            {
                cout << "ERROR NO OPTION\n";
            }

        }
        else if(option == 3)
        {
            cout << "1. Increasing Price\n"
            << "2. Decreasing Price\n";
            cin >> option;
            if(option == 1)
                store->sortVG(0);
            else if(option == 2)
                store->sortVG(1);
            else
            {
                cout << "ERROR NO OPTION\n";
            }
        }
        else if(option == 4)
        {
            cout << "1. Find by  serial number\n"
            << "2. Find by title\n";
            cin >> option;
            if(option == 1)
            {
                cout << "What is the serial number?\n";
                cin >> vgserial;
                store->findVG(vgserial);
            }
            else if(option == 2)
            {
                cout << "What is the title?\n";
                cin >> vgtitle;
                store->findVG(vgtitle);
            }
            else
            {
                cout << "ERROR NO OPTION\n";
            }

        }
        else if(option == 5)
        {
            cout << store->numberOfItems() << "\n";
        }
        else if(option == 6)
        {
            store->printALL();
        }
        else if(option == 7)
        {
            cout << "1. Increase in price\n"
            << "2. Decrease in price\n";
            cin >> option;
            if(option == 1)
            {
                store->priceChange(1);
            }
            else if(option == 2)
            {
                store->priceChange(0);
            }
            else
            {
                cout << "ERROR NO OPTION\n";
            }

        }
        else if(option == 8)
        {
            break;
        }
        else
        {
            cout << "ERROR NO OPTION\n";
        }
    }
}