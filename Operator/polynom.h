#include <vector>
#include <iostream>

class polynom
{
private:
    std::vector <int> my_arr;



public:

    void set (int data, int it)
    {
        my_arr[it]=data;
    }

    polynom(int size)
    {
        my_arr.resize(size);
    }
    
    polynom(int size, int date)
    {
        my_arr.resize(size, date);
    }

    polynom(int size, int date)
    {
        int ch;
        ch=date;
        my_arr.resize(size, ch);
    }


    int get_size()
    {
        return my_arr.size();
    }

    int set_size(int size)
    {
        my_arr.resize(size);
    }

    int set_size(int size, int date)
    {
        int ch;
        ch=date;
        my_arr.resize(size, ch);
    }

    int set_size(int size, int date)
    {
        my_arr.resize(size, date);
    }

    void del (int it)
    {
        if (it>=my_arr.size())
            return;
        vector <int> new_arr;
        for (int i=0; i<my_arr.size(); i++)
        {
            if (i==it)
                continue;
            new_arr.push_back(my_arr[i]);
        }
        my_arr=new_arr;
    }
    void push (int data)
    {
        my_arr.push_back(data);
    }
    int &operator [] (int it)
    {
        return my_arr[it];
    }

    void operator = (polynom & other)
    {
        my_arr.resize(other.get_size());
        for (int i=0; i<other.get_size(); i++)
            my_arr[i]=other[i];
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
    
    void operator += (polynom &other)
    {
        int new_size=my_arr.size()+other.get_size();
        my_arr.resize(new_size);
        for (int i=my_arr.size(); i<new_size; i++)
            my_arr[i]=other[i-my_arr.size()];
    }

    void operator -= (polynom other)
    {
        for (int i=0; i<other.get_size(); i++)
            for (int i=0; i<my_arr.size(); i++)
            {
                if (my_arr[i]==other[i])
                    del(i);
            }
    }

    polynom & operator + (polynom other)
    {
        polynom new_arr(other.get_size()+my_arr.size());

        for (int i=0; i<my_arr.size(); i++)
        {
            new_arr.push(my_arr[i]);
        }
        
        for (int i=0; i<other.get_size(); i++)
        {
            new_arr.push(other[i]);
        }

        return new_arr;
    }

    polynom & operator - (polynom other)
    {
        polynom new_arr(other.get_size()+my_arr.size());

        for (int i=0; i<my_arr.size(); i++)
        {
            new_arr.push(my_arr[i]);
        }
        
        for (int i=0; i<other.get_size(); i++)
        {
            if (new_arr[i]==other[i])
                new_arr.del(i);
        }

        return new_arr;
    }

    polynom &operator * (int n)
    {
        polynom new_arr(my_arr.size()*n);
        for (int i=0; i<n; i++)
        {
            for (int i=0; i<my_arr.size(); i++)
                new_arr.push(my_arr[i]);
        }
        return new_arr;
    }

    polynom &operator / (int n)
    {
        polynom new_arr(my_arr.size()/n);
        for (int i=0; i<my_arr.size()/n; i++)
            new_arr.push(my_arr[i]);
        return new_arr;
    }

    void operator /= (int n)
    {
        polynom new_arr(my_arr.size()/n);
        for (int i=0; i<my_arr.size()/n; i++)
            new_arr.push(my_arr[i]);
        my_arr.resize(new_arr.get_size());

        for (int i=0; i<my_arr.size()/n; i++)
            my_arr[i]=new_arr[i];
    }

    void operator *= (int n)
    {
        polynom new_arr(my_arr.size()*n);
        for (int i=0; i<n; i++)
        {
            for (int i=0; i<my_arr.size(); i++)
                new_arr.push(my_arr[i]);
        }
        my_arr.resize(new_arr.get_size());
        for (int i=0; i<my_arr.size()/n; i++)
            my_arr[i]=new_arr[i];
    }

    void operator << ()
    {
        for (int i=0; i<my_arr.size(); i++)
            cout << my_arr[i];
    }

    void operator >> (int data)
    {
        my_arr.push_back(data);
    }
};