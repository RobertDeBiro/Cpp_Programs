#include <iostream>

class A
{
public:
    int x;
    A(int x) { this->x = x; }
    A(A& p)
    {
        p.x = 3; // Since p is reference to received object,
                 // this changes the value of attribute x from p1 object
        
        x = 6; // This changes the value of attribute x from object which
               // calls this consturctor - p2 object
    }
};

int main()
{
    std::cout << "*****************************************************\n";

    A p1(2);
    A p2(p1);
    std::cout << p2.x + p1.x << std::endl;

    std::cout << "*****************************************************\n";
    return 0;
}
