#include "closed_broken_line.h"
class polygon :public closed_broken_line
{
protected:
    bool intersection(dot &a1, dot &a2, dot &b1, dot &b2)
    {
        dot va(a1.get_x()-a2.get_x(), a1.get_x()-a2.get_x());
        dot vb(b1.get_x()-b2.get_x(), b1.get_y()-b2.get_y());
        dot v1(a1.get_x()-b1.get_x(), a1.get_y()-b1.get_y());
        dot v2(a1.get_x()-b2.get_x(), a1.get_y()-b2.get_y());
        dot v3(b1.get_x()-a2.get_x(), b1.get_y()-a2.get_y());

        double angle1=va.get_x()*v1.get_y()-va.get_y()*v1.get_x();
        double angle2=va.get_x()*v2.get_y()-va.get_y()*v2.get_x();
        double angle3=vb.get_x()*v1.get_y()-vb.get_y()*v1.get_x();
        double angle4=vb.get_x()*v3.get_y()-vb.get_y()*v3.get_x();

        if (angle1*angle2<0 && angle3*angle4<0)
            return true;
        else
            return false;

    }
    virtual bool rule ()
    {
        if (arr_dot_.size()<4)
        {
            std::cout << "*ERROR! THIS BROKEN LINE NEED TO HAVE THREE SEGMENT\n";
            return false;
        }
        if (arr_dot_[0].get_x()!=arr_dot_[arr_dot_.size()-1].get_x() || arr_dot_[0].get_y()!=arr_dot_[arr_dot_.size()-1].get_y())
        {
            std::cout<<"*ERROR! THIS BROKEN LINE NOT CLOSED\n";
            return false;
        }
        if (arr_dot_.size()>4)
            for (int i=2; i<arr_dot_.size()-1; i++)
            {
                for (int j=0; j<i; j++)
                {
                    if (intersection(arr_dot_[i], arr_dot_[i+1], arr_dot_[j], arr_dot_[j+1]))
                    {
                        std::cout<<"*ERROR! IT IS NOT CLOSED BROKEN LINE.\n";
                        std::cout<<"THIS FIGUR HAVE INTERSACTION SEGMENT\n";
                        return false;
                    }
                }

            }
        return true;
    }
public:
    polygon()
    {}
    polygon (std::vector <dot> &arr_dot)
    {
        arr_dot_=arr_dot;
    }
    polygon (closed_broken_line &other)
    {
        arr_dot_=other.get_arr();
    }
    polygon (broken_line &other)
    {
        arr_dot_=other.get_arr();
    }
    polygon (polygon &other)
    {
        arr_dot_=other.arr_dot_;
    }
    void operator = (polygon &other)
    {
        arr_dot_=other.get_arr();
    }
    double square()
    {
        if (!rule())
            return -1;
        double s=0;
        for (int i=0; i<arr_dot_.size()-1; i++)
            s+=arr_dot_[i].get_x()*arr_dot_[i+1].get_y();
        s+=arr_dot_[arr_dot_.size()-1].get_x()*arr_dot_[0].get_y();
        for (int i=0; i<arr_dot_.size()-1; i++)
            s-=arr_dot_[i+1].get_x()*arr_dot_[i].get_y();
        s-=arr_dot_[0].get_x()*arr_dot_[arr_dot_.size()-1].get_y();
        s/=2;
        return abs(s);
    } 
};