#include <vector>
#include <iostream>

class my_int
{
protected:
    int date_;
public:
    my_int ()
    {
    }

    int get_date ()
    {
        return date_;
    }

    void operator = (const my_int &other)
    {
        date_=other.date_;
    }

    void operator = (int date)
    {
        date_=date;
    }

    bool operator == (const my_int &other)
    {
        return date_==other.date_ ? true : false;
    }

    bool operator != (const my_int &other)
    {
        return date_==other.date_ ? false : true;
    }

    int operator + (const my_int &other)
    {
        return date_+other.date_;
    }

    int operator - (const my_int &other)
    {
        return date_+other.date_;
    }

    int operator * (const my_int &other)
    {
        return date_*other.date_;
    }

    int operator / (const my_int &other)
    {
        return date_/(other.date_);
    }

    void operator += (const my_int &other)
    {
        date_+=other.date_;
    }

    void operator -= (const my_int &other)
    {
        date_-=other.date_;
    }

    void operator *= (const my_int &other)
    {
        date_*=other.date_;
    }
    
    void operator /= (const my_int &other)
    {
        date_/=other.date_;
    }

    int operator << (const my_int &other)
    {
        return date_<<other.date_;
    }

    int  operator >> (const my_int &other)
    {
        return date_>>other.date_;
    }
};

