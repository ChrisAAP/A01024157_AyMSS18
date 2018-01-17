
#include <iostream>
using namespace std;
class Prueba
{
public: 
    int* val;
    int val2;
    Prueba()
    {
        cout << "Default Constructor \n";
    }
    Prueba(int val):val(new int(val)), val2(val)
    {
        cout << "Params " << val << "\n";
    }
    Prueba(const Prueba& temp)
    {
        cout << "Copy constructor \n";
        val2 = *(temp.val);
        val = new int (*(temp.val));
    }
    
};

int main()
{
    Prueba p;
    Prueba* z = new Prueba(2);
    Prueba w = *z;

    cout << " \nbefore\n\n";

    cout << "z val: "<< *(z->val) << "\n";
    cout << "w val: "<< *(w.val) << "\n";

    *(w.val) = 8;

    cout << " \nafter\n\n";

    cout << "z val: "<< *(z->val) << "\n";
    cout << "w val: "<< *(w.val) << "\n";
    return 0;
}