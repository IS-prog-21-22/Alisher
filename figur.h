#include "polygon.h"

class triangle : public polygon
{
private:
    virtual bool rule()
    {
        if (size_dot_ != 4)
        {
            std::cout << "*ERROR! THIS BROKEN LINE NEED TO HAVE ONLY THREE SEGMENT\n";
            return false;
        }
        if (arr_dot_[0].get_x() != arr_dot_[size_dot_ - 1].get_x() || arr_dot_[0].get_y() != arr_dot_[size_dot_ - 1].get_y())
        {
            std::cout << "*ERROR! THIS BROKEN LINE NOT CLOSED\n";
            return false;
        }
        return true;
    }
public:
    triangle()
    {}
    triangle(std::vector <dot>& arr_dot)
    {
        arr_dot_ = arr_dot;
        size_dot_ = arr_dot.size();
    }
    triangle(closed_broken_line& other)
    {
        arr_dot_ = other.get_arr();
        size_dot_ = other.size_dot_;
    }
    triangle(broken_line& other)
    {
        arr_dot_ = other.get_arr();
        size_dot_ = other.size_dot_;
    }
    triangle(polygon& other)
    {
        arr_dot_ = other.get_arr();
        size_dot_ = other.size_dot_;
    }
    triangle(triangle& other)
    {
        arr_dot_ = other.get_arr();
        size_dot_ = other.size_dot_;
    }
    void operator = (triangle& other)
    {
        arr_dot_ = other.get_arr();
        size_dot_ = other.size_dot_;
    }
};
/////////////

class trapezoid : public polygon
{
private:
    bool parallel(dot& a1, dot& a2, dot& b1, dot& b2)
    {
        double k2 = b2.get_y() - b1.get_y();
        int ch=b2.get_x() - b1.get_x();
        k2 /= ch;

        double k1 = a2.get_y() - a1.get_y();
        ch = a2.get_x() - a1.get_x();
        k1 /= ch;

        if (k1 == k2)
            return true;
        return false;
    }
    virtual bool rule()
    {
        if (size_dot_ != 4)
        {
            std::cout << "*ERROR! THIS BROKEN LINE NEED TO HAVE ONLY THREE SEGMENT\n";
            return false;
        }
        if (arr_dot_[0].get_x() != arr_dot_[size_dot_ - 1].get_x() || arr_dot_[0].get_y() != arr_dot_[size_dot_ - 1].get_y())
        {
            std::cout << "*ERROR! THIS BROKEN LINE NOT CLOSED\n";
            return false;
        }

        bool par1, par2;
        par1 = parallel(arr_dot_[0], arr_dot_[1], arr_dot_[2], arr_dot_[3]);
        par2 = parallel(arr_dot_[0], arr_dot_[3], arr_dot_[1], arr_dot_[2]);
        if (par1 && par2 || !par1 && !par2)
        {
            std::cout << "*ERROR! TRAPESOID NEED TO HAVE TWO PARALLEL SEGMENT\n";
            return false;
        }

        if (size_dot_ > 4)
            for (int i = 2; i < size_dot_ - 1; i++)
            {
                for (int j = 0; j < i; j++)
                {
                    if (intersection(arr_dot_[i], arr_dot_[i + 1], arr_dot_[j], arr_dot_[j + 1]))
                    {
                        std::cout << "*ERROR! IT IS NOT CLOSED BROKEN LINE.\n";
                        std::cout << "THIS FIGUR HAVE INTERSACTION SEGMENT\n";
                        return false;
                    }
                }

            }

        return true;
    }
public:
    trapezoid()
    {}
    trapezoid(std::vector <dot>& arr_dot)
    {
        arr_dot_ = arr_dot;
        size_dot_ = arr_dot.size();
    }
    trapezoid(closed_broken_line& other)
    {
        arr_dot_ = other.get_arr();
        size_dot_ = other.size_dot_;
    }
    trapezoid(broken_line& other)
    {
        arr_dot_ = other.get_arr();
        size_dot_ = other.size_dot_;
    }
    trapezoid(polygon& other)
    {
        arr_dot_ = other.get_arr();
        size_dot_ = other.size_dot_;
    }
    trapezoid(trapezoid& other)
    {
        arr_dot_ = other.get_arr();
        size_dot_ = other.size_dot_;
    }
    void operator = (trapezoid& other)
    {
        arr_dot_ = other.get_arr();
        size_dot_ = other.size_dot_;
    }
};
////////////////

class right_triangle: public polygon
{
private:

    virtual bool rule()
    {
        if (size_dot_ != 4)
        {
            std::cout << "*ERROR! THIS BROKEN LINE NEED TO HAVE ONLY THREE SEGMENT\n";
            return false;
        }

        if (arr_dot_[0].get_x() != arr_dot_[size_dot_ - 1].get_x() || arr_dot_[0].get_y() != arr_dot_[size_dot_ - 1].get_y())
        {
            std::cout << "*ERROR! THIS BROKEN LINE NOT CLOSED\n";
            return false;
        }

        std::vector <dot> new_dots (2);
        new_dots[0]=arr_dot_[0];
        new_dots[1]=arr_dot_[1];
        broken_line b_line(new_dots);
        int line_length=b_line.length();
        for (int i=1; i<3; i++)
        {
            new_dots[0]=arr_dot_[i];
            new_dots[1]=arr_dot_[i+1];
            broken_line b_line(new_dots);
            if (b_line.length()!=line_length)
            {
                std::cout << "*ERROR! THIS TRIANGLE DOESN'T RIGHT\n";
                return false;
            }
        }

        return true;
    }
public:
    right_triangle()
    {}
    right_triangle(std::vector <dot>& arr_dot)
    {
        arr_dot_ = arr_dot;
        size_dot_ = arr_dot.size();
    }
    right_triangle(closed_broken_line& other)
    {
        arr_dot_ = other.get_arr();
        size_dot_ = other.size_dot_;
    }
    right_triangle(broken_line& other)
    {
        arr_dot_ = other.get_arr();
        size_dot_ = other.size_dot_;
    }
    right_triangle(polygon& other)
    {
        arr_dot_ = other.get_arr();
        size_dot_ = other.size_dot_;
    }
    right_triangle(right_triangle& other)
    {
        arr_dot_ = other.get_arr();
        size_dot_ = other.size_dot_;
    }
    void operator = (right_triangle& other)
    {
        arr_dot_ = other.get_arr();
        size_dot_ = other.size_dot_;
    }
};
