#include <iostream>
#include <vector>

using namespace std;

class my
{
private:
    vector <int> arr;
public:
    my (int size, int n)
    {
        arr.resize(size, n);
    }
    int &operator [] (int it)
    {
        return arr[it];
    }
};

int main()
{
    my inte(10, 2);

    cout << inte[1];
    return 0;
}