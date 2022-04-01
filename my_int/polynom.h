#include <vector>
#include <iostream>

class polynom
{
private:
    std::vector <int> my_arr;

public:


    polynom()
    {}
    polynom (std::vector <int> arr)
    {
        my_arr=arr;
    }
    polynom(int size)
    {
        my_arr.resize(size);
    }
//
    void del (int it)
    {
        if (it>=my_arr.size())
            return;
        std::vector <int> new_arr;
        for (int i=0; i<my_arr.size(); i++)
        {
            if (i==it)
                continue;
            new_arr.push_back(my_arr[i]);
        }
        my_arr=new_arr;
    }
    
    void prematuring ()
    {
        int size=my_arr.size();
        for (int i=1; i<my_arr.size(); i++)
        {
            int j=0;
            while (j<i && j<my_arr.size())
            {
                if (my_arr[i]==my_arr[j])
                {
                    my_arr[j]*=2;
                    del(i);
                }
                else if (my_arr[i]==-my_arr[j])
                {
                    del(i);
                    del(j);
                }
                j++;
            }
        }

        if (size!=my_arr.size())
            prematuring();
    }

//
    int get_size()
    {
        return my_arr.size();
    }

    void push (int data)
    {
        my_arr.push_back(data);
        prematuring();
    }
  
//
    int &operator [] (int it)
    {
        return my_arr[it];
    }

    polynom& operator=( polynom& other) 
    {
        if (this == &other) {
            return *this;
        }
        my_arr.resize(other.get_size());
        for (int i=0; i<my_arr.size(); i++)
            my_arr[i]=other[i];
        return *this;
    }
    polynom& operator=( std::vector <int> other ) 
    {
        my_arr.resize(other.size());
        for (int i=0; i<my_arr.size(); i++)
            my_arr[i]=other[i];
        return *this;
    }

    bool operator == (polynom & other)
    {
        if (other.get_size()!=my_arr.size())
            return false;
        for (int i=0; i<my_arr.size(); i++)
            if (my_arr[i]!=other[i])
                return false;
        return true;
    }
    
    bool operator != (polynom & other)
    {
        if (other.get_size()!=my_arr.size())
            return true;
        for (int i=0; i<my_arr.size(); i++)
            if (my_arr[i]!=other[i])
                return true;
    }
    
    std::vector <int> operator += (polynom &other)
    {
        polynom other_;
        other_=other;
        while (other_.get_size()!=0) 
        {
            my_arr.push_back(other_[0]);
            other_.del(0);
            prematuring();
        }
        return my_arr;
    }

    std::vector <int> operator -= (polynom &other)
    {
        polynom other_;
        other_=other;
        while (other_.get_size()!=0) 
        {
            my_arr.push_back(-other_[0]);
            other_.del(0);
            prematuring();
        }
        return my_arr;
    }

    std::vector <int> operator + (polynom &other)
    {
        
        polynom first;
        first=*this;
        return first+=other;
    }
    
    std::vector <int> operator - (polynom &other)
    {
        
        polynom first;
        first=*this;
        return first-=other;
    }

    std::vector <int> operator *= (int n)
    {
        for (int j=0; j<my_arr.size(); j++)
            my_arr[j]*=n;
        return my_arr;
    }

    std::vector <int> operator /= (int n)
    {
        for (int j=0; j<my_arr.size(); j++)
            my_arr[j]/=n;
        prematuring();
        return my_arr;
    }

    std::vector <int> operator * (int n)
    {
        polynom first;
        first=*this;
        return first*=n;
    }

    std::vector <int> operator / (int n)
    {
        polynom first;
        first=*this;
        return first/=n;
    }

//
    
    friend std::ostream& operator<< (std::ostream &out, const polynom &POLYNOM);
    friend std::istream& operator>> (std::istream &in, const polynom &POLYNOM);
};
    
std::ostream& operator<< (std::ostream &out, const polynom &POLYNOM)
{
    out << "(";
    for (int i=0; i<POLYNOM.my_arr.size()-1; i++)
        out << POLYNOM.my_arr[i] << ", ";
    out << POLYNOM.my_arr[POLYNOM.my_arr.size()-1] << ")";
    return out; 
}

std::istream& operator>> (std::istream &in, const polynom &POLYNOM)
{
    for (int i=0; i<POLYNOM.my_arr.size(); i++)
    {
        in >> POLYNOM.my_arr[i];
    }
    return in; 
}