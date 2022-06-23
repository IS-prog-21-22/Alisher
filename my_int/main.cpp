#include <iostream>
#include "polynom.hpp"
#include <fstream>


int main()
{
    std::ifstream fin ("in.txt");
    std::ofstream fout ("out.txt");

    polynom p1;
    polynom p2;

    fin >> p1;
    fin >> p2;

    fout <<"(" << p1 << ") * (" << p2 << ")" << " =\n";
    fout << p1*p2;
     
    return 0;
}