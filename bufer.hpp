template <typename T>
class bufer
{
protected:
     
    int _size;
    int _element = 0;

    int _head_it = 0;
    int _tail_it;

    T* _bufer;
    bool* _is_element;


    void go_head(int plus)
    {
        for (int i = 0; i < plus; i++)
        {
            _head_it++;

            if (_head_it == _size)
                _head_it = 0;

            if (_head_it == _tail_it)
                _tail_it++;

            if (_tail_it == _size)
                _tail_it = 0;
        }
    }
    void go_tail(int plus)
    {
        for (int i = 0; i < plus; i++)
        {
            _tail_it--;

            if (_tail_it == -1)
                _tail_it = _size - 1;

            if (_tail_it == _head_it)
                _head_it--;

            if (_head_it == -1)
                _head_it = _size - 1;
        }
    }

public:

    bufer(int _size)
    {
        this->_size = _size;
        _tail_it = _size - 1;
        _bufer = new T[_size];
        _is_element = new bool[_size];
        for (int i = 0; i < _size; i++)
            _is_element[i] = false;
    }

    bufer()
    {
        _size = 7;
        _tail_it = _size - 1;
        _bufer = new T[_size];
        _is_element = new bool[_size];
        for (int i = 0; i < _size; i++)
            _is_element[i] = false;
    }

    //template <typename I>
    class iterator : public std::iterator<std::random_access_iterator_tag, T>
    {
    public:
        using difference_type = std::ptrdiff_t;

        T* _ptr;

        T* __bufer;
        int __head_it;
        int __tail_it;
        int __size;

        iterator(T* ptr, T* _bufer, int _head_it, int _tail_it,int _size)
        {
            _ptr = ptr;
            __bufer = _bufer;
            __head_it = _head_it;
            __tail_it = _tail_it;
            __size = _size;
        }

        T& operator*()
        {
            return *_ptr;
        }

        iterator& operator++() 
        {
            if (_ptr == &__bufer[__head_it])
                _ptr = &__bufer[__tail_it];
            else if (_ptr == &__bufer[__size - 1])
                _ptr = __bufer;
            else
                _ptr++;
            return *this; 
        }
        
        iterator& operator--()
        {
            if (_ptr == &__bufer[__tail_it])
                _ptr = &__bufer[__head_it];
            else if (_ptr == __bufer)
                _ptr = &__bufer[__size - 1];
            else
                _ptr--;
            return *this;
        }

        bool operator == (iterator it)
        {
            if (it._ptr == _ptr)
                return true;
            else
                return false;
        }

        bool operator != (iterator it)
        {
            if (it._ptr != _ptr)
                return true;
            else
                return false;
        }

        iterator& operator+=(int n)
        {
            if (__size < n)
                throw std::runtime_error("'n' cannot be more than the number of arguments");

            if (_ptr - __bufer + n < __size)
                _ptr += n;
            else
            {
                n -=__size - (_ptr - __bufer);
                _ptr =__bufer + n;
            }

            return *this;
        }

        iterator& operator -= (int n)
        {
            if (__size < n)
                throw std::runtime_error("'n' cannot be more than the number of arguments");
            
            if (_ptr - __bufer >= n)
                _ptr -= n;
            else
            {
                n -= _ptr - __bufer;
                _ptr = __bufer + __size - 1 - n;
            }

            return *this;
        }
        
        iterator operator + (int n)
        {
            iterator other = *this;
            other += n;
            return other;
        }

        iterator operator - (int n)
        {
            iterator other = *this;
            other -= n;
            return other;
        }
    };

    iterator begin() 
        { return iterator(&_bufer[_tail_it], _bufer, _head_it, _tail_it, _size);}
    iterator end()
        { return iterator(&_bufer[_head_it+1], _bufer, _head_it, _tail_it, _size);}

    int size()
    {
        return _size;
    }
    int element()
    {
        return _element;
    }

    void push_head(T data)
    {
        go_head(1);
        _bufer[_head_it] = data;
        if (_element != _size)
        {
            _element++;
            _is_element[_head_it] = true;
        }

        if (_element == 1)
            _tail_it = _head_it;


    }

    void push_tail(T data)
    {
        go_tail(1);
        _bufer[_tail_it] = data;
        if (_element != _size)
        {
            _element++;
            _is_element[_head_it] = true;
        }
        if (_element == 1)
            _tail_it = _head_it;
    }

    void del_head ()
    {
        if (_element == 0)
        {
            std::cout << "\nError! Your deleted all arguments";
            exit(1);
        }
        _is_element[_head_it] = false;
        _element--;
        go_head(-1);
    }

    void del_tail()
    {
        if (_element == 0)
        {
            std::cout << "\nError! Your deleted all arguments";
            exit(1);
        }
        _is_element[_tail_it] = false;
        _element--;
        go_tail(-1);
    }

    T& operator [] (iterator it)
    {
        return *it;
    }

    T& operator [] (int it)
    {
        if (it >= _size)
        {
            std::cout << "\nError! Index can't be bigger that bufer size";
            exit(1);
        }

        if (it >= _element)
        {
            std::cout << "\nError! This element was deleted";
            exit(1);
        }

        if (_element == 0)
        {
            std::cout << "\nError! All elements was deleted";
            exit(1);
        }

        int i = 0;
        int pr_it;
        int index = 0;

        while (i != it + 1)
        {
            pr_it = _tail_it + index;

            if (_tail_it + i >= _size)
                pr_it -= _size;

            if (_is_element[pr_it])
                i++;
            index++;
        }

        return _bufer[pr_it];
    }
};
