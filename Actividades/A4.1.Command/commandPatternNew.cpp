#include <iostream>

using namespace std;

class Command 
{
public:
    virtual void execute() = 0;
};

class Receiver 
{
public:
    void method1() 
    {
        cout << "Method 1\n";
    }
};

class Caller 
{
private:
    Command *cmd;
public:
    void setCommand(Command *cmd_temp) 
    {
        cmd = cmd_temp;
    }
    void executeAction() 
    {
        cmd->execute();
    }

};

class ConcreteCommand : public Command 
{
private:
    Receiver *r;
public:
    ConcreteCommand(Receiver *r_temp) : r(r_temp) {}
    void execute() 
    {
        r -> method1();
    }
    
};

int main() {
    Receiver *r = new Receiver;
    
    ConcreteCommand *cmd = new ConcreteCommand(r);
    
    Caller *caller = new Caller;
    
    caller->setCommand(cmd);
    caller->executeAction();
    
    return 1;
}