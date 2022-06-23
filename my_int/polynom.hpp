#include <istream>
#include <vector>
#include <stdexcept>
#include "my_f.hpp"

class polynom
{
private:
    std::vector <int> arr;

    void fixed()
    {
        std::vector <int> returned;
        bool flag=true;
        for (int i=0; i<arr.size(); i++)
        {
            if (arr[i]==0 && flag)
                continue;
            else
            {
                flag=false;
                returned.push_back(arr[i]);
            }
        }

        arr=returned;
    }

public:
    polynom ()
    {}

    polynom (int n, int data, ...)
    {
        int *ptr = &data;
        for (int i=n; i>0; i--)
        {
            arr.push_back(*ptr);
            ptr++;
        }
    }   

    polynom (const polynom &other)
    {
        arr = other.arr;
    }
    
    polynom (const std::vector <int> &other)
    {
        arr=other;
    }

    std::vector <int> get() const
    {
        return arr;
    }

    void push (int data)
    {
        arr.push_back(data);
    }

    int get_size() const
    {
        return arr.size();
    }

    void set_size(int size)
    {
        arr.resize(size);
    }

    polynom operator = (const polynom &other)
    {
        arr=other.arr;
        return polynom(arr);
    }

    bool operator == (const polynom &other)
    {
        return other.arr==arr;
    }

    bool operator != (const polynom &other)
    {
        return other.arr!=arr;
    }

    void operator += (const polynom &other)
    {
        if (arr.size()>=other.arr.size())
        {
            int j=arr.size()-1;
            for (int i=other.arr.size()-1; i>=0; i--)
            {
                arr[j]+=other.arr[i];
                j--;
            }
        }
        else
        {
            int j=other.arr.size()-1;
            std::vector <int> new_arr=other.arr;
            
            for (int i=arr.size()-1; i>=0; i--)
            {
                new_arr[j]+=arr[i];
                j--;
            }

            arr=new_arr;
        }

        fixed();
    }

    polynom operator + (const polynom &other)
    {
        polynom returned(arr);
        returned += other;

        return returned;
    }

    void operator -= (const polynom &other)
    {
        polynom new_arr = *this;
        new_arr *= -1;
        new_arr+=other;
        new_arr *= -1;
        new_arr.fixed();
        arr=new_arr.get();
    }

    polynom operator - (const polynom &other)
    {
        polynom returned(arr);
        returned -= other;

        return returned;
    }

    void operator *= (int n)
    {
        for (int i=0; i<arr.size(); i++)
            arr[i]*=n;
    }

    polynom operator * (int n)
    {
        polynom returned(arr);
        returned*=n;
        return returned;
    }

    void operator *= (const polynom &other)
    {
        polynom ret=*this * other;
        arr=ret.get();
    }

    polynom operator *(const polynom &other)
    {
        int rsize = arr.size();
        int osize = other.arr.size();

        std::vector <int> ret(rsize+osize-1, 0);
        
        for (int i=0; i<rsize; i++)
            for (int j=0; j<osize; j++)
                ret[i+j]+=arr[i]*other.arr[j];
        
        polynom returned(ret);
        return returned;
    }

    void operator /= (int n)
    {
        for (int i=0; i<arr.size(); i++)
            arr[i]/=n;
    }

    polynom operator / (int n)
    {
        polynom returned(arr);
        returned/=n;
        return returned;
    }

    int operator [] (unsigned int i) const 
    {
        if (i>=arr.size())
            return 0;
        return arr[i];
    } 

    friend std::ostream &operator << (std::ostream &out, const polynom &other);
    friend std::istream &operator >> (std::istream &in, const polynom &other);
};

std::ostream &operator << (std::ostream &out, const polynom &other)
{
    std::string returned="";

    for(int i=0; i<other.arr.size()-1; i++)
    {
        if (other.arr[i]==1)
        {
            returned+="x^";
            returned+=my_f::toString_no_sing(other.arr.size()-i-1);
        }
        else if(other.arr[i]!=0)
        {
            returned+=my_f::toString(other.arr[i]);
            returned+="x^";
            returned+=my_f::toString_no_sing(other.arr.size()-i-1);
        }
    }

    if (other.arr[other.arr.size()-1]!=0)
        returned+=my_f::toString(other.arr[other.arr.size()-1]);

    return out << returned;
}

void operator >> (std::istream &in, polynom &other)
{
    int n;
    in >> n;

    int data;
    for (int i=0; i<n; i++)
    {
        in >> data;
        other.push(data);
    }
}