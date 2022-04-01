#include "dot.h"
#include <vector>
#include <cmath>
class broken_line
{
protected:
    std::vector <dot> arr_dot_;
public:
    broken_line()
    {}
    broken_line (std::vector <dot> &arr_dot) : arr_dot_(arr_dot)
    {}
    broken_line (const broken_line &other) : arr_dot_(other.arr_dot_)
    {}
    void operator = (const broken_line &other)
    {
        arr_dot_=other.arr_dot_;
    }
    void set_dot  (std::vector <dot> &arr_dot)
    {
        arr_dot_=arr_dot;
    }
    double  length()
    {
        double sum_pow=0;
        for (int i=0; i<arr_dot_.size()-1; i++)
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