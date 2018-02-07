#include <iostream>
using namespace std;

int suma(int a, int b)
{
    return a+b;
}

int resta( int a, int b)
{
    return a-b;
}

int operacion(int a, int b , int(*f)(int ,int))
{
    return f(a,b);
}
typedef int(*f)(int, int);
f getOperation(char o)
{
    if(o == 'r') return resta;
    else return suma;
}

int (*getf(char s))(int a, int b)
{
    if(s == 'r') return resta;
    else return suma;
}

int main()
{
    cout << operacion(2,2,suma) << "\n";
    cout << operacion(3,1,resta)<< "\n";
    
    cout << getOperation('s')(2,2);
    cout << getf('s')(4,2);
}