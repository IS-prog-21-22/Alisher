#include "my_int.h"

class my_int_arr : public my_int
{
private:
    std::vector <my_int> my_arr;

public:

    my_int_arr(int size)
    {
        my_arr.resize(size);
    }
    
    my_int_arr(int size, my_int date)
    {
        my_arr.resize(size, date);
    }

    my_int_arr(int size, int date)
    {
        my_int ch;
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
        my_int ch;
        ch=date;
        my_arr.resize(size, ch);
    }

    int set_size(int size, my_int date)
    {
        my_arr.resize(size, date);
    }

    my_int &operator [] (int it)
    {
        return my_arr[it];
    }
};