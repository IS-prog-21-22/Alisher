#include <string>
#include <stack>

namespace my_f
{
    std::string toString(int data)
    {
        std::string returned="";
        std::stack <char> arr;

        if (data<0)
        {
            returned+=" - ";
            data*=-1;
        }
        else
            returned+=" + ";

        while (data!=0)
        {
            arr.push(data%10+'0');
            data/=10;
        }

        while (!arr.empty())
        {
            returned+=arr.top();
            arr.pop();
        }

        return returned;
    }
    
    std::string toString_no_sing(int data)
    {
        std::string returned="";
        std::stack <char> arr;

        if (data<0)
            data*=-1;

        while (data!=0)
        {
            arr.push(data%10+'0');
            data/=10;
        }

        while (!arr.empty())
        {
            returned+=arr.top();
            arr.pop();
        }

        return returned;
    }

    int abs(int a)
    {
        return a>0? a : a*-1;
    }

    int max(int left, int right)
    {
        return left>right ? left : right;
    }
}
