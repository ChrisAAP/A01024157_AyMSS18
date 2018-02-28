#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

class Command{
public:
    virtual void execute() = 0;
};

class Receiver
{
public:
    void actionEMAIL(string f, string t, string s, string b)
    {
        cout << "CONTACTING EMAIL\n";
        cout << "From: " << f << "\n";
        cout << "To: " << t << "\n";
        cout << "Subject: " << s << "\n";
        cout << "Body: " << b << "\n";
    }
    void actionPHONE(string t, string n, string m)
    {
        cout << "CONTACTING PHONE\n";
        cout << "Telefono: " << t << "\n";
        cout << "Nombre: " << n << "\n";
        cout << "Mensaje: " << m << "\n";
    }
    void actionSMS(string t, string te)
    {
        cout << "CONTACTING SMS\n";
        cout << "Telefono: " << t << "\n";
        cout << "Texto: " << te << "\n";

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

class ConcreteCommandPhone : public Command
{
private:
    Receiver *r;
    string telefono, nombre, mensaje;
public:
    ConcreteCommandPhone(Receiver *r_temp, string tel, string nom, string men) : r(r_temp), telefono(tel), nombre(nom),mensaje(men){}
    void execute()
    {
        r->actionPHONE(telefono, nombre, mensaje);
    }
};

class ConcreteCommandSMS : public Command
{
private:
    Receiver *r;
    string telefono, texto;
public:
    ConcreteCommandSMS(Receiver *r_temp, string tel, string tex) : r(r_temp), telefono(tel), texto(tex){}
    void execute()
    {
        r->actionSMS(telefono, texto);
    }
};

class ConcreteCommandEmail : public Command
{
private:
    Receiver *r;
    string from, to, subject, body;
public:
    ConcreteCommandEmail(Receiver *r_temp, string f, string t, string sub, string bod) : r(r_temp), from(f),to(t), subject(sub),body(bod){}
    void execute()
    {
        r->actionEMAIL(from, to, subject, body);
    }
};

class Cliente
{
private:
    string id;
    string nombre;
    string apellido;
    string type_comm;
    string mail;
    string phone;
    string calle;
    string numero;
    string colonia;
    Caller *caller;
    Receiver *re;
public:
    
    Cliente() {}
    Cliente(string i, string no, string a, string t, string m, string p, string ca, string nu, string co):
    id (i), nombre (no), apellido(a), type_comm(t), mail(m), phone(p), calle(ca), numero(nu), colonia(co)
    {
        re = new Receiver;
        caller = new Caller;
        if(type_comm == "mail")
        {
            caller->setCommand( new ConcreteCommandEmail(re, "us@chris.com", mail, "Changes are coming.", "There are new changes to the system."));
        }
        else if(type_comm == "sms")
        {
            caller->setCommand( new ConcreteCommandSMS(re, phone, "There are new changes to the system."));
        }
        else if(type_comm == "phone_call")
        {
            caller->setCommand( new ConcreteCommandPhone(re, phone, nombre, "There are new changes to the system."));
        }
    }
        void contact()
        {
            caller->executeAction();
        }
        void printClient()
        {
            cout <<"ID: "<< id<< "\nNombre: " << nombre << "\nApellido: " << apellido << "\nTypeCom: " << type_comm << "\nMail: " << mail << "\nPhone: " << phone << "\nCalle: " << calle << "\nNumero: "<< numero << "\nColonia: "<< colonia<< "\n";
        }
};

class Database
{
private:
    static Database* instance;
    static int counter;
    vector<Cliente*>  mahbois;
    Database(){     }
    ~Database() {   }
    static void addRef()
    {
        ++counter;
    }
    static void destroyRef()
    {
        --counter;
    }
public:
    static Database* getInstance()
    {
        if(instance == nullptr)
        {
            instance = new Database;
        }
        addRef();
        return instance;
    }
    static void destroyInstance()
    {
        destroyRef();
        if(instance!=nullptr && counter == 0)
        {
            delete instance;
            instance = nullptr;
        }
    }
    void readFile()
    {
        string line, id_d,name_d,apellido_d,type_d,mail_d,phone_d,street_d,number_d,col_d, uselessinfo;
        ifstream file;
        file.open("customers.csv");
        getline(file,uselessinfo);
        while (getline(file, id_d,',')){
            getline(file,name_d,',');
            getline(file,apellido_d,',');
            getline(file,type_d,',');
            getline(file,mail_d,',');
            getline(file,phone_d,',');
            getline(file,street_d,',');
            getline(file,number_d,',');
            getline(file,col_d,'\n');
            Cliente *boi = new Cliente(id_d,name_d,apellido_d,type_d,mail_d,phone_d,street_d,number_d,col_d);
            mahbois.push_back(boi);
        }
        file.close();
    }
    void contactMahBois()
    {
        for(int i = 0; i < mahbois.size();i++)
        {
            mahbois[i]->contact();
        }
    }
    void printMahBois()
    {
        for(int i = 0; i < mahbois.size();i++)
        {
            mahbois[i]->printClient();
        }
    }

};
Database* Database::instance = nullptr;
int Database::counter = 0;
int main()
{
    Database* instance = Database::getInstance();
    instance->readFile();
    instance->contactMahBois();

}