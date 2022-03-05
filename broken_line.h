#include "dot.h"
#include <vector>
#include <cmath>
class broken_line: public dot
{
protected:
    using dot :: get_x;
    using dot :: get_y;
    using dot :: set_O;

    std::vector <dot> arr_dot_;
public:
    int size_dot_=0;
    broken_line()
    {}
    broken_line (std::vector <dot> &arr_dot)
    : arr_dot_(arr_dot)
    , size_dot_(arr_dot.size())
    {}
    broken_line (const broken_line &other)
    : arr_dot_(other.arr_dot_)
    , size_dot_(other.size_dot_)
    {}
    void operator = (const broken_line &other)
    {
        arr_dot_=other.arr_dot_;
        size_dot_=other.size_dot_;
    }
    void set_dot  (std::vector <dot> &arr_dot)
    {
        arr_dot_=arr_dot;
        size_dot_=arr_dot_.size();
    }
    double  length()
    {
        double sum_pow=0;
        for (int i=0; i<size_dot_-1; i++)
        {
            sum_pow+=sqrt(abs(pow(arr_dot_[i].get_x()-arr_dot_[i+1].get_x(), 2)-pow(arr_dot_[i].get_y()-arr_dot_[i+1].get_y(), 2)));
        }
        return sum_pow;
    }
    std::vector <dot> &get_arr ()
    {
        return arr_dot_;
    }
};