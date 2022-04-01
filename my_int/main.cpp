#include <iostream>
#include "polynom.h"

using namespace std;
int main()
{
    vector<int> arr (3, 2);
    polynom arr1(3), arr2;
    arr1.push(3);
    arr2=arr;
    std::cout << arr1;
    return 0;
}