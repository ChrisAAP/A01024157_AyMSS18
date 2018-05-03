#include <iostream>
using namespace std;
const int SIZE = 10;

class Array
{
public:
    int *ptr;
    int one, two;
    Array(int arr[])
    {
        ptr = arr;
    }
    int &operator[](int index)
    {
        one=index;
        return ptr[index];
    }
    int & operator=(int x){
        two=x;
        return x;
    }  
    class Proxy
    {
        Array &a;
        int idx;
    public:
        Proxy(Array &a, int idx) : a(a), idx(idx) {}
        int& operator= (int x) 
        { 
            a.two = x; 
            a.ptr[idx] = x; 
            return a.ptr[idx]; 
        }
    };

    Proxy operator[] (int index) 
    { 
        return Proxy(*this, index); 
    }
};