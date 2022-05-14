#include <iostream>

#define modul(a) ((a)<0? ((a)*-1) : (a))
#define nop 99999999

class Mlist
{
private:

    struct dir
    {
    public:
        int data;
        dir* next = nullptr;
        dir* prev = nullptr;

        int Nmem = -1;

        dir()
        {}

        dir(int d)
        {
            data = d;
        }
    };

    dir* head = new dir(0);
    dir* tail = head;


public:

    ~Mlist()
    {
        dir* watching = tail;

        while (watching != head)
        {
            watching = watching->next;
            dir* PrWatch = watching->prev;
            delete(PrWatch);
        }

        delete(watching);
    }

    int push(int data)
    {
        int returned;

        if (head == tail)
        {
            head->data += data;
            return head->data;
        }
        else
        {
            dir* watching = tail;
            dir* minU = new dir(-1);

            int min = nop;

            while (watching != head)
            {
                int ch = watching->Nmem;
                if (ch < min && ch >= data)
                {
                    min = ch;
                    minU = watching;
                }
                watching = watching->next;
            }

            if (min == nop)
            {
                returned = head->data;
                head->data += data;
                return returned;
            }
            else
            {
                returned = minU->data;
                minU->data += data;
                minU->Nmem -= data;

                if (minU->Nmem == 0)
                {
                    dir* deleted = minU->next;
                    minU->data *= 2;
                    minU->Nmem = deleted->Nmem;
                    minU->next = deleted->next;
                    deleted->next->prev = minU;
                    delete(deleted);
                }

                return returned;
            }
        }
    }

    void del(int byte, int number)
    {
        if (byte > 2e6 || number > 2e6 || byte < 0 || number < 0)
            return;

        int summ = 0;

        dir* watching = tail;

        while (true)
        {
            if (watching==nullptr)
                return;

            summ += watching->data;

            if (summ >= byte)
                break;
            summ += watching->Nmem;
            watching = watching->next;
        }

        if (byte - summ + watching->data == 0)
        {
            watching->data -= number;

            if (watching->prev != nullptr)
                watching->prev->Nmem += number;
            else
            {
                dir* NewEl = new dir(0);
                NewEl->next = tail;
                NewEl->Nmem = number;
                tail->prev = NewEl;
                tail = tail->prev;
            }

            if (watching->data == 0 && watching == head)
            {
                watching->prev->next = nullptr;
                head = watching->prev;
                delete(watching);
            }

            return;
        }
        else if (summ == byte + number)
        {
            watching->data -= number;
            if (watching->next != nullptr)
                watching->Nmem += number;

            if (watching->data == 0 && watching == head && head!=tail)
            {
                watching->prev->next = nullptr;
                head = watching->prev;
                delete(watching);
            }

            return;
        }

        summ -= watching->data;
        int LeftDate = byte - summ;
        int RightDate = watching->data - LeftDate - number;

        dir* NewEl = new dir(RightDate);

        if (tail == head)
        {
            head = NewEl;
            tail->data = LeftDate;
            tail->next = head;
            tail->Nmem = number;
            head->prev = tail;
        }
        else if (watching == head)
        {
            head = NewEl;
            watching->data = LeftDate;
            watching->next = head;
            watching->Nmem = number;
            head->prev = watching;
        }
        else
        {
            watching->next->prev = NewEl;
            watching->next = NewEl;
            NewEl->Nmem = watching->Nmem;
            watching->Nmem = number;
            watching->data = LeftDate;
        }
    }

    void print()
    {
        dir* watching = tail;
        while (watching != head->next)
        {
            std::cout << watching->data << ":" << watching->Nmem << "|";
            watching = watching->next;
        }
        std::cout << std::endl;
    }
};