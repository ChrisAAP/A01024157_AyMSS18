#include <iostream>

using namespace std;

class Vehiculo
{
public:
    virtual void Ensamblado() = 0;
    virtual void Hojalateria() = 0;
    virtual void Pintura() = 0;
    virtual void Entrega() = 0;

};

class Dodge: public Vehiculo
{
public:
    void Ensamblado()
    {
        cout << "Ensamblado DODGE\n";
    }
    void Hojalateria()
    {
        cout << "Hojalateria DODGE\n";
    }
    void Pintura()
    {
        cout << "Pintura DODGE\n";
    }
    void Entrega()
    {
        cout << "Entrega DODGE\n";
    }
};

class BMW : public Vehiculo
{
public:
    void Ensamblado()
    {
        cout << "Ensamblado BMW\n";
    }
    void Hojalateria()
    {
        cout << "Hojalateria BMW\n";
    }
    void Pintura()
    {
        cout << "Pintura BMW\n";
    }
    void Entrega()
    {
        cout << "Entrega BMW\n";
    }
};

class VV : public Vehiculo{
public:
    void Ensamblado()
    {
        cout << "Ensamblado VV\n";
    }
    void Hojalateria()
    {
        cout << "Hojalateria VV\n";
    }
    void Pintura()
    {
        cout << "Pintura VV\n";
    }
    void Entrega()
    {
        cout << "Entrega VV\n";
    }
};

class Nissan : public Vehiculo{
public:
    void Ensamblado()
    {
        cout << "Ensamblado NISSAN\n";
    }
    void Hojalateria()
    {
        cout << "Hojalateria NISSAN\n";
    }
    void Pintura()
    {
        cout << "Pintura NISSAN\n";
    }
    void Entrega()
    {
        cout << "Entrega NISSAN\n";
    }
};


class Creator
{
public:
    template<class Car>
    Car* factoryMethod()
    {
        return new Car;
    }
    template<class Car>
    Car* create()
    {
        Car* myProduct;
        myProduct = factoryMethod<Car>();
        myProduct->Ensamblado();
        myProduct->Hojalateria();
        myProduct->Pintura();
        myProduct->Entrega();
        return myProduct;
    }
};
/*
template<class Car>
Car* Creator::factoryMethod
{
    return new Car;
}
*/
int main()
{
    Creator* cliente = new Creator();
    Vehiculo* miProducto = cliente->create<Dodge>();
    Vehiculo* miNewProducto = cliente->create<Nissan>();

    return 1;
}