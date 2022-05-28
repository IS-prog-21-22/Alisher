#include <iostream>
#include <vector>
#include <istream>
#include <cmath>

template <int ... arg>
class Pol
{
private:

    static constexpr int size = sizeof...(arg);
    static constexpr int polynom[size] = { arg... };

    constexpr int step(int data, int s)
    {
        int res = 1;
        for (int i = 0; i < s; i++)
            res *= data;
        return res;
    }

public:
    constexpr int geter(int dot)
    {
        int res = 0;

        for (int i = 0; i < size; i++)
        {
            int p = step(dot, i);
            res += polynom[i] * p;
        }

        return res;
    }

    void out (std::ostream& out)
    {
        for (int i = 0; i < size; i++)
        {
            if (i != 0)
                out << " + ";

            out << polynom[i];
            
            if (i == 0)
                continue;
            
            out << "x^" << i;
        }
    }
};




int main()
{
    Pol<0> arr;

    arr.out(std::cout);

    static_assert(arr.geter(2) == 0, "ploho");

    return 0;
}