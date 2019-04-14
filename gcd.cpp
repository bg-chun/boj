#include <iostream>

int gcd_reculsive(int a, int b)
{
    int r = a%b;
    a = b;
    b = r;
    if ( b == 0)
    {
        return a;
    }
    
    return gcd_reculsive(a, b);
}

int gcd_non_reculsive(int a, int b)
{
    while(b != 0)
    {
        int r = a%b;
        a = b;
        b = r;
    }
    
    return a;
}

int main()
{
    int a = 64;
    int b = 12;
    
    std::cout << gcd_reculsive(a, b) << std::endl;
    
    std::cout << gcd_non_reculsive(a, b) << std::endl;
    
    return 0;
}
