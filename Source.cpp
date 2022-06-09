#include <iostream>
#include <vector>
#include "bufer.hpp"
#include "func.hpp"
#include <algorithm>
using namespace std;

int f(int a)
{
    if (a == 0)
        return true;
    return false;
}

int main()
{
    //bufer <int> arr(4);
    std::vector <int> v;

    v.push_back(0);
    v.push_back(4);
    v.push_back(4);
    v.push_back(0);
    /*
    arr.push_head(2);
    arr.push_head(4);
    arr.push_head(5);
    arr.push_head(3);
    arr.push_head(4);
    arr.push_head(5);
    arr.push_tail(3);/**/
    
    if (my::is_palindrome(v.begin(), v.end(), f))
        std::cout << "true";
    else
        std::cout << "false";
    
    return 0;
}