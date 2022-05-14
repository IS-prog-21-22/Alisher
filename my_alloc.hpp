#include <cstdlib>
#include <new>
#include <limits>
#include "Mlist.hpp"

#define limit 5e7

template <class T>
class my_alloc
{
public:
    typedef T value_type;
    template <class U> constexpr my_alloc(const my_alloc <U>&) : my_alloc() {}

    template <class Type>

    struct rebind {
        typedef my_alloc<Type> other;
    };

    T* allocate(std::size_t n) {

        if (n > std::numeric_limits<std::size_t>::max() / sizeof(T))
            throw std::bad_array_new_length();


        if (sizeof(T) * n + UsMem > limit)
            throw std::bad_alloc();

        UsMem += sizeof(T) * n;

        iter = memory + fpath.push(n);
        fpath.print();

        return iter;
    }

    void deallocate(T* p, std::size_t n) noexcept {

        fpath.del(p - memory, n);
        fpath.print();
    }

private:
    T* memory;
    T* iter;

    Mlist fpath;

    int UsMem = 0;

public:
    my_alloc()
    {
        memory = (T*)malloc(limit);
    }
};

template <class T, class U>
bool operator==(const my_alloc <T>&, const my_alloc <U>&) { return true; }
template <class T, class U>
bool operator != (const my_alloc <T>&, const my_alloc <U>&) { return false; }
