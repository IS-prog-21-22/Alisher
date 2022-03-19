#include <iostream>
#include "my_int_arr.h"

using namespace std;
int main()
{
    my_int_arr arr1(3, 6), arr2(7, 3);
    arr1[2] = 5;
    cout << arr1[2] + arr2[3];
    return 0;
}