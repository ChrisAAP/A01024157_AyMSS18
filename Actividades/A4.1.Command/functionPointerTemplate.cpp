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

template<class T, class Function>
T doTemplateFunction(T a, T b , Function f)
{
    return f(a,b);
}

template <class Function>
Function getTemplateOperation(char s)
{
    if(s == 'r') return resta;
    else return suma;
}

int main()
{
    cout << doTemplateFunction(2,2,suma) << "\n";
    cout << getTemplateOperation<int(*)(int, int)>('s')(2,2) << "\n";
}