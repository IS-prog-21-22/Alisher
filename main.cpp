
/*
location:
    top white
    bottom yellow
    befor blue
    left red
    right orange
    back green

designation:
    1,1 1,2 1,3
    2,1 2,2 2,3
    3,1 3,2 3,3

*/

#define faceds 6

#define WHITE 0
#define ORANGE 1
#define GREEN 2
#define RED 3
#define BLUE 4
#define YELLOW 5

#define RIGHT 0
#define LEFT 1

#define GRAFIX 1

#define next_line std::cout << "\n____________________\n"

#include <iostream>
#include <ostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <sstream>
#include <SFML/Graphics.hpp>

void wait(int it)
{
    sf::Clock clock;
    float curTime;
    while (true)
    {

        curTime = clock.getElapsedTime().asMilliseconds();
        if (curTime > it)
            break;
    }
}

std::vector <std::string> divide_string(std::string line)
{
    std::string word;
    std::vector <std::string> words;

    std::istringstream iss(line, std::istringstream::in);
    while (iss >> word)
        words.push_back(word);

    return words;
}

class cub
{
private:

    int iteration = 0;

    std::string start;
    std::string finish;

    bool is_build=false;

    std::vector<std::vector<std::vector<char>>> _cube;
    char color[6] = {'w', 'o', 'g', 'r', 'b', 'y'};

    struct cor
    {
        short color;
        short line;
        short column;

        bool operator == (cor& other)
        {
            if (color == other.color && line == other.line && column == other.column)
                return true;
            else
                return false;
        }

        bool operator != (cor& other)
        {
            if (color == other.color && line == other.line && column == other.column)
                return false;
            else
                return true;
        }
    };


    cor find_double(short first, short second)
    {
        char f_color = color[first];
        char s_color = color[second];

        if (_cube[WHITE][1][2] == f_color && _cube[ORANGE][0][1] == s_color)
            return cor{ WHITE, 1, 2 };
        if (_cube[WHITE][1][2] == s_color && _cube[ORANGE][0][1] == f_color)
            return cor{ ORANGE, 0, 1 };

        if (_cube[WHITE][0][1] == f_color && _cube[GREEN][0][1] == s_color)
            return cor{ WHITE, 0, 1 };
        if (_cube[WHITE][0][1] == s_color && _cube[GREEN][0][1] == f_color)
            return cor{ GREEN, 0, 1 };

        if (_cube[WHITE][1][0] == f_color && _cube[RED][0][1] == s_color)
            return cor{ WHITE, 1, 0 };
        if (_cube[WHITE][1][0] == s_color && _cube[RED][0][1] == f_color)
            return cor{ RED, 0, 1 };

        if (_cube[WHITE][2][1] == f_color && _cube[BLUE][0][1] == s_color)
            return cor{ WHITE, 2, 1 };
        if (_cube[WHITE][2][1] == s_color && _cube[BLUE][0][1] == f_color)
            return cor{ BLUE, 0, 1 };

        if (_cube[YELLOW][1][2] == f_color && _cube[ORANGE][2][1] == s_color)
            return cor{ YELLOW, 1, 2 };
        if (_cube[YELLOW][1][2] == s_color && _cube[ORANGE][2][1] == f_color)
            return cor{ ORANGE, 2, 1 };

        if (_cube[YELLOW][2][1] == f_color && _cube[GREEN][2][1] == s_color)
            return cor{ YELLOW, 2, 1 };
        if (_cube[YELLOW][2][1] == s_color && _cube[GREEN][2][1] == f_color)
            return cor{ GREEN, 2, 1 };

        if (_cube[YELLOW][1][0] == f_color && _cube[RED][2][1] == s_color)
            return cor{ YELLOW, 1, 0 };
        if (_cube[YELLOW][1][0] == s_color && _cube[RED][2][1] == f_color)
            return cor{ RED, 2, 1 };

        if (_cube[YELLOW][0][1] == f_color && _cube[BLUE][2][1] == s_color)
            return cor{ YELLOW, 0, 1 };
        if (_cube[YELLOW][0][1] == s_color && _cube[BLUE][2][1] == f_color)
            return cor{ BLUE, 2, 1 };

        if (_cube[ORANGE][1][0] == f_color && _cube[BLUE][1][2] == s_color)
            return cor{ ORANGE, 1, 0 };
        if (_cube[ORANGE][1][0] == s_color && _cube[BLUE][1][2] == f_color)
            return cor{ BLUE, 1, 2 };

        if (_cube[ORANGE][1][2] == f_color && _cube[GREEN][1][0] == s_color)
            return cor{ ORANGE, 1, 2 };
        if (_cube[ORANGE][1][2] == s_color && _cube[GREEN][1][0] == f_color)
            return cor{ GREEN, 1, 0 };

        if (_cube[RED][1][0] == f_color && _cube[GREEN][1][2] == s_color)
            return cor{ RED, 1, 0 };
        if (_cube[RED][1][0] == s_color && _cube[GREEN][1][2] == f_color)
            return cor{ GREEN, 1, 2 };

        if (_cube[RED][1][2] == f_color && _cube[BLUE][1][0] == s_color)
            return cor{ RED, 1, 2 };
        if (_cube[RED][1][2] == s_color && _cube[BLUE][1][0] == f_color)
            return cor{ BLUE, 1, 0 };

        return cor{ -1, -1, -1 };
    }
    bool compare_double(short first, short second, cor comp)
    {
        cor s = find_double(first, second);
        return s == comp;
    }

    cor find_triple(short first, short second, short third)
    {
        char f_color = color[first];
        char s_color = color[second];
        char t_color = color[third];

        if (_cube[WHITE][2][2] == f_color && _cube[BLUE][0][2] == s_color && _cube[ORANGE][0][0]==t_color)
            return cor{ WHITE, 2, 2 };
        if (_cube[WHITE][2][2] == f_color && _cube[BLUE][0][2] == t_color && _cube[ORANGE][0][0] == s_color)
            return cor{ WHITE, 2, 2 };
        if (_cube[BLUE][0][2] == f_color && _cube[WHITE][2][2] == s_color && _cube[ORANGE][0][0] == t_color)
            return cor{ BLUE, 0, 2 };
        if (_cube[BLUE][0][2] == f_color && _cube[WHITE][2][2] == t_color && _cube[ORANGE][0][0] == s_color)
            return cor{ BLUE, 0, 2 };
        if (_cube[ORANGE][0][0] == f_color && _cube[WHITE][2][2] == s_color && _cube[BLUE][0][2] == t_color)
            return cor{ ORANGE, 0, 0 };
        if (_cube[ORANGE][0][0] == f_color && _cube[WHITE][2][2] == t_color && _cube[ORANGE][0][2] == s_color)
            return cor{ ORANGE, 0, 0 };

        if (_cube[WHITE][0][2] == f_color && _cube[ORANGE][0][2] == s_color && _cube[GREEN][0][0] == t_color)
            return cor{ WHITE, 0, 2 };
        if (_cube[WHITE][0][2] == f_color && _cube[ORANGE][0][2] == t_color && _cube[GREEN][0][0] == s_color)
            return cor{ WHITE, 0, 2 };
        if (_cube[ORANGE][0][2] == f_color && _cube[WHITE][0][2] == s_color && _cube[GREEN][0][0] == t_color)
            return cor{ ORANGE, 0, 2 };
        if (_cube[ORANGE][0][2] == f_color && _cube[WHITE][0][2] == t_color && _cube[GREEN][0][0] == s_color)
            return cor{ ORANGE, 0, 2 };
        if (_cube[GREEN][0][0] == f_color && _cube[ORANGE][0][2] == s_color && _cube[WHITE][0][2] == t_color)
            return cor{ GREEN, 0, 0 };
        if (_cube[GREEN][0][0] == f_color && _cube[ORANGE][0][2] == t_color && _cube[WHITE][0][2] == s_color)
            return cor{ GREEN, 0, 0 };

        if (_cube[WHITE][0][0] == f_color && _cube[GREEN][0][2] == s_color && _cube[RED][0][0] == t_color)
            return cor{ WHITE, 0, 0 };
        if (_cube[WHITE][0][0] == f_color && _cube[GREEN][0][2] == t_color && _cube[RED][0][0] == s_color)
            return cor{ WHITE, 0, 0 };
        if (_cube[GREEN][0][2] == f_color && _cube[WHITE][0][0] == s_color && _cube[RED][0][0] == t_color)
            return cor{ GREEN, 0, 2 };
        if (_cube[GREEN][0][2] == f_color && _cube[WHITE][0][0] == t_color && _cube[RED][0][0] == s_color)
            return cor{ GREEN, 0, 2 };
        if (_cube[RED][0][0] == f_color && _cube[WHITE][0][0] == s_color && _cube[GREEN][0][2] == t_color)
            return cor{ RED, 0, 0 };
        if (_cube[RED][0][0] == f_color && _cube[WHITE][0][0] == t_color && _cube[GREEN][0][2] == s_color)
            return cor{RED, 0, 0 };

        if (_cube[WHITE][2][0] == f_color && _cube[RED][0][2] == s_color && _cube[BLUE][0][0] == t_color)
            return cor{ WHITE, 2, 0};
        if (_cube[WHITE][2][0] == f_color && _cube[RED][0][2] == t_color && _cube[BLUE][0][0] == s_color)
            return cor{ WHITE, 2, 0 };
        if (_cube[RED][0][2] == f_color && _cube[WHITE][2][0] == s_color && _cube[BLUE][0][0] == t_color)
            return cor{ RED, 0, 2};
        if (_cube[RED][0][2] == f_color && _cube[WHITE][2][0] == t_color && _cube[BLUE][0][0] == s_color)
            return cor{ RED, 0, 2 };
        if (_cube[BLUE][0][0] == f_color && _cube[WHITE][2][0] == s_color && _cube[RED][0][2] == t_color)
            return cor{BLUE, 0, 0};
        if (_cube[BLUE][0][0] == f_color && _cube[WHITE][2][0] == t_color && _cube[RED][0][2] == s_color)
            return cor{ BLUE, 0, 0 };
        //
        if (_cube[YELLOW][0][2] == f_color && _cube[BLUE][2][2] == s_color && _cube[ORANGE][2][0] == t_color)
            return cor{ YELLOW , 0, 2 };
        if (_cube[YELLOW][0][2] == f_color && _cube[ORANGE][2][2] == t_color && _cube[ORANGE][2][0] == s_color)
            return cor{ YELLOW , 0, 2 };
        if (_cube[BLUE][2][2] == f_color && _cube[YELLOW][0][2] == s_color && _cube[ORANGE][2][0] == t_color)
            return cor{ BLUE , 2, 2 };
        if (_cube[BLUE][2][2] == f_color && _cube[YELLOW][0][2] == t_color && _cube[ORANGE][2][0] == s_color)
            return cor{ BLUE , 2, 2 };
        if (_cube[ORANGE][2][0] == f_color && _cube[YELLOW][0][2] == s_color && _cube[BLUE][2][2] == t_color)
            return cor{ ORANGE , 2, 0 };
        if (_cube[ORANGE][2][0] == f_color && _cube[YELLOW][0][2] == t_color && _cube[BLUE][2][2] == s_color)
            return cor{ ORANGE , 2, 0 };

        if (_cube[YELLOW][2][2] == f_color && _cube[GREEN][2][0] == s_color && _cube[ORANGE][2][2] == t_color)
            return cor{ YELLOW , 2, 2 };
        if (_cube[YELLOW][2][2] == f_color && _cube[GREEN][2][0] == t_color && _cube[ORANGE][2][2] == s_color)
            return cor{ YELLOW , 2, 2 };
        if (_cube[GREEN][2][0] == f_color && _cube[YELLOW][2][2] == s_color && _cube[ORANGE][2][2] == t_color)
            return cor{ GREEN , 2, 0};
        if (_cube[GREEN][2][0] == f_color && _cube[YELLOW][2][2] == t_color && _cube[ORANGE][2][2] == s_color)
            return cor{ GREEN , 2, 0 };
        if (_cube[ORANGE][2][2] == f_color && _cube[YELLOW][2][2] == s_color && _cube[GREEN][2][0] == t_color)
            return cor{ ORANGE , 2, 2 };
        if (_cube[ORANGE][2][2] == f_color && _cube[YELLOW][2][2] == t_color && _cube[GREEN][2][0] == s_color)
            return cor{ ORANGE , 2, 2 };

        if (_cube[YELLOW][2][0] == f_color && _cube[RED][2][0] == s_color && _cube[GREEN][2][2] == t_color)
            return cor{ YELLOW , 2, 0 };
        if (_cube[YELLOW][2][0] == f_color && _cube[RED][2][0] == t_color && _cube[GREEN][2][2] == s_color)
            return cor{ YELLOW , 2, 0 };
        if (_cube[RED][2][0] == f_color && _cube[YELLOW][2][0] == s_color && _cube[GREEN][2][2] == t_color)
            return cor{ RED, 2, 0 };
        if (_cube[RED][2][0] == f_color && _cube[YELLOW][2][0] == t_color && _cube[GREEN][2][2] == s_color)
            return cor{ RED, 2, 0 };
        if (_cube[GREEN][2][2] == f_color && _cube[YELLOW][2][0] == s_color && _cube[RED][2][0] == t_color)
            return cor{ GREEN, 2, 2 };
        if (_cube[GREEN][2][2] == f_color && _cube[YELLOW][2][0] == t_color && _cube[RED][2][0] == s_color)
            return cor{ GREEN, 2, 2 };

        if (_cube[YELLOW][0][0] == f_color && _cube[RED][2][2] == s_color && _cube[BLUE][2][0] == t_color)
            return cor{ YELLOW, 0, 0};
        if (_cube[YELLOW][0][0] == f_color && _cube[RED][2][2] == t_color && _cube[BLUE][2][0] == s_color)
            return cor{ YELLOW, 0, 0 };
        if (_cube[RED][2][2] == f_color && _cube[YELLOW][0][0] == s_color && _cube[BLUE][2][0] == t_color)
            return cor{ RED, 2, 2 };
        if (_cube[RED][2][2] == f_color && _cube[YELLOW][0][0] == t_color && _cube[BLUE][2][0] == s_color)
            return cor{ RED, 2, 2 };
        if (_cube[BLUE][2][0] == f_color && _cube[YELLOW][0][0] == s_color && _cube[RED][2][2] == t_color)
            return cor{ BLUE, 2, 0 };
        if (_cube[BLUE][2][0] == f_color && _cube[YELLOW][0][0] == t_color && _cube[RED][2][2] == s_color)
            return cor{ BLUE, 2, 0 };
    }
    bool compare_triple(short first, short second, short treaple, cor comp)
    {
        cor s = find_triple(first, second, treaple);
        return s == comp;
    }

    void protate(short color, short direction, short it)
    {
        switch (color)
        {
            case WHITE:
            {
                direction == RIGHT ? white_right(it) : white_left(it);
                break;
            }
            case ORANGE:
            {
                direction == RIGHT ? orange_right(it) : orange_left(it);
                break;
            }
            case GREEN:
            {
                direction == RIGHT ? green_right(it) : green_left(it);
                break;
            }
            case RED:
            {
                direction == RIGHT ? red_right(it) : red_left(it);
                break;
            }
            case BLUE:
            {
                direction == RIGHT ? blue_right(it) : blue_left(it);
                break;
            }
            case YELLOW:
            {
               direction == RIGHT ? yellow_right(it) : yellow_left(it);
               break;
            }
            default:
                break;
        }

    }

public:
    int per;

    friend std::istream& operator>> (std::istream& input, cub& my_class);
    friend std::ostream& operator<< (std::ostream& output, cub& my_class);
    friend void grafix_on(cub& my_class, int time_1, int time_2);

    void set_iter(int it)
    {
        iteration = it;
    }

    cub()
    {
        _cube.resize(faceds, std::vector<std::vector<char>>(3, std::vector<char>(3)));

        for (int k = 0; k < faceds; k++)
            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                    _cube[k][i][j] = color[k];
    }

    cub(std::string comand)
    {
        _cube.resize(faceds, std::vector<std::vector<char>>(3, std::vector<char>(3)));

        for (int k = 0; k < faceds; k++)
            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                    _cube[k][i][j] = color[k];

        std::vector <std::string> arr = divide_string(comand);

        for (int i = 0; i < arr.size(); i++)
        {
            if (arr[i] == "U")
                white_right(1);
            else if (arr[i] == "U2")
                white_right(2);
            else if (arr[i] == "U'")
                white_left(1);
            else if (arr[i] == "R")
                orange_right(1);
            else if (arr[i] == "R2")
                orange_right(2);
            else if (arr[i] == "R'")
                orange_left(1);
            else if (arr[i] == "B")
                green_right(1);
            else if (arr[i] == "B2")
                green_right(2);
            else if (arr[i] == "B'")
                green_left(1);
            else if (arr[i] == "L")
                red_right(1);
            else if (arr[i] == "L2")
                red_right(2);
            else if (arr[i] == "L'")
                red_left(1);
            else if (arr[i] == "F")
                blue_right(1);
            else if (arr[i] == "F2")
                blue_right(2);
            else if (arr[i] == "F'")
                blue_left(1);
            else if (arr[i] == "D")
                yellow_right(1);
            else if (arr[i] == "D2")
                yellow_right(2);
            else if (arr[i] == "D'")
                yellow_left(1);
        }
    }

    void white_right(int it)
    {
        for (int k = 0; k < it; k++)
        {
        char save_orange[3];
        std::vector <std::vector<char>> save_top(3, std::vector <char>(3));

        for (int i = 0; i < 3; i++)
            save_orange[i] = _cube[ORANGE][0][i];

        save_top = _cube[WHITE];
        
        for (int i = ORANGE; i <= BLUE; i++)
            for (int j = 0; j < 3; j++)
                _cube[i][0][j] = _cube[i + 1][0][j];

        for (int i = 0; i < 3; i++)
            _cube[BLUE][0][i] = save_orange[i];

        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                _cube[WHITE][i][j] = save_top[2-j][i];
        }

        next_line;
        std::cout << "white_right " << it  << '\n';
        std::cout << *this;

        switch (it % 4)
        {
            case 1:
                if (is_build)
                    finish += "U ";
                else
                    start += "U ";
                break;
            case 2:
                if (is_build)
                    finish += "U2 ";
                else
                    start += "U2 ";
                break;
            case 3:
                if (is_build)
                    finish += "U' ";
                else
                    start += "U' ";
                break;
            default:
                break;
        }

        
        wait(iteration);
    }

    void white_left(int it)
    {
        for (int k = 0; k < it; k++)
        {
            char save_blue[3];
            std::vector <std::vector<char>> save_top(3, std::vector <char>(3));

            for (int i = 0; i < 3; i++)
                save_blue[i] = _cube[BLUE][0][i];

            save_top = _cube[WHITE];

            for (int i = BLUE; i >=ORANGE; i--)
                for (int j = 0; j < 3; j++)
                    _cube[i][0][j] = _cube[i - 1][0][j];

            for (int i = 0; i < 3; i++)
                _cube[ORANGE][0][i] = save_blue[i];

            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                    _cube[WHITE][i][j] = save_top[j][2-i];
        }

        next_line;
        std::cout << "white_left " << it << '\n';
        std::cout << *this;

        switch (it % 4)
        {
                case 1:
                    if (is_build)
                        finish += "U' ";
                    else
                        start += "U' ";
                    break;
                case 2:
                    if (is_build)
                        finish += "U2 ";
                    else
                        start += "U2 ";
                    break;
                case 3:
                    if (is_build)
                        finish += "U ";
                    else
                        start += "U ";
                    break;
                default:
                    break;

        }
            
        wait(iteration);
    }

    void orange_right(int it)
    {
        for (int k = 0; k < it; k++)
        {
            char save_yellow[3];
            std::vector <std::vector<char>> save_top(3, std::vector <char>(3));

            for (int i = 0; i < 3; i++)
                save_yellow[i] = _cube[YELLOW][i][2];

            save_top = _cube[ORANGE];

            for (int i = 0; i < 3; i++)
                _cube[YELLOW][i][2] = _cube[GREEN][2-i][0];

            for (int i = 0; i < 3; i++)
                _cube[GREEN][i][0] = _cube[WHITE][2-i][2];

            for (int i = 0; i < 3; i++)
                _cube[WHITE][i][2] = _cube[BLUE][i][2];

            for (int i = 0; i < 3; i++)
                _cube[BLUE][i][2] = save_yellow[i];

            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                    _cube[ORANGE][i][j] = save_top[2 - j][i];
        }


        next_line;
        std::cout << "orange_right " << it << '\n';
        std::cout << *this;

        switch (it % 4)
        {
            case 1:
                if (is_build)
                    finish += "R ";
                else
                    start += "R ";
                break;
            case 2:
                if (is_build)
                    finish += "R2 ";
                else
                    start += "R2 ";
                break;
            case 3:
                if (is_build)
                    finish += "R' ";
                else
                    start += "R' ";
                break;
            default:
                break;

        }


        wait(iteration);
    }

    void orange_left(int it)
    {
        for (int k = 0; k < it; k++)
        {
            char save_blue[3];
            std::vector <std::vector<char>> save_top(3, std::vector <char>(3));

            for (int i = 0; i < 3; i++)
                save_blue[i] = _cube[BLUE][i][2];

            save_top = _cube[ORANGE];

            for (int i = 0; i < 3; i++)
                _cube[BLUE][i][2] = _cube[WHITE][i][2];

            for (int i = 0; i < 3; i++)
                _cube[WHITE][i][2] = _cube[GREEN][2 - i][0];

            for (int i = 0; i < 3; i++)
                _cube[GREEN][i][0] = _cube[YELLOW][2-i][2];

            for (int i = 0; i < 3; i++)
                _cube[YELLOW][i][2] = save_blue[i];

            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                    _cube[ORANGE][i][j] = save_top[j][2 - i];
        }

        next_line;
        std::cout << "orange_left " << it << '\n';
        std::cout << *this;

        switch (it % 4)
        {
            case 1:
                if (is_build)
                    finish += "R' ";
                else
                    start += "R' ";
                break;
            case 2:
                if (is_build)
                    finish += "R2 ";
                else
                    start += "R2 ";
                break;
            case 3:
                if (is_build)
                    finish += "R ";
                else
                    start += "R ";
                break;
            default:
                break;

        }

        wait(iteration);
    }

    void green_right(int it)
    {
        for (int k = 0; k < it; k++)
        {
            char save_yellow[3];
            std::vector <std::vector<char>> save_top(3, std::vector <char>(3));

            for (int i = 0; i < 3; i++)
                save_yellow[i] = _cube[YELLOW][2][2-i];

            save_top = _cube[GREEN];

            for (int i = 0; i < 3; i++)
                _cube[YELLOW][2][i] = _cube[RED][i][0];

            for (int i = 0; i < 3; i++)
                _cube[RED][i][0] = _cube[WHITE][0][2-i];

            for (int i = 0; i < 3; i++)
                _cube[WHITE][0][i] = _cube[ORANGE][i][2];

            for (int i = 0; i < 3; i++)
                _cube[ORANGE][i][2] = save_yellow[i];

            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                    _cube[GREEN][i][j] = save_top[2 - j][i];
        }

        next_line;
        std::cout << "green_right " << it << '\n';
        std::cout << *this;

        switch (it % 4)
        {
            case 1:
                if (is_build)
                    finish += "B ";
                else
                    start += "B ";
                break;
            case 2:
                if (is_build)
                    finish += "B2 ";
                else
                    start += "B2 ";
                break;
            case 3:
                if (is_build)
                    finish += "B' ";
                else
                    start += "B' ";
                break;
            default:
                break;

        }

        wait(iteration);
    }

    void green_left(int it)
    {
        for (int k = 0; k < it; k++)
        {
            char save_yellow[3];
            std::vector <std::vector<char>> save_top(3, std::vector <char>(3));

            for (int i = 0; i < 3; i++)
                save_yellow[i] = _cube[YELLOW][2][i];

            save_top = _cube[GREEN];

            for (int i = 0; i < 3; i++)
                _cube[YELLOW][2][2-i] = _cube[ORANGE][i][2];

            for (int i = 0; i < 3; i++)
                _cube[ORANGE][i][2] = _cube[WHITE][0][i];

            for (int i = 0; i < 3; i++)
                _cube[WHITE][0][i] = _cube[RED][2-i][0];

            for (int i = 0; i < 3; i++)
                _cube[RED][i][0] = save_yellow[i];

            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                    _cube[GREEN][i][j] = save_top[j][2 - i];
        }

        next_line;
        std::cout << "green_left " << it << '\n';
        std::cout << *this;

        switch (it % 4)
        {
            case 1:
                if (is_build)
                    finish += "B' ";
                else
                    start += "B' ";
                break;
            case 2:
                if (is_build)
                    finish += "B2 ";
                else
                    start += "B2 ";
                break;
            case 3:
                if (is_build)
                    finish += "B ";
                else
                    start += "B ";
                break;
            default:
                break;


        }
        wait(iteration);
    }

    void red_right(int it)
    {
        for (int k = 0; k < it; k++)
        {
            char save_yellow[3];
            std::vector <std::vector<char>> save_top(3, std::vector <char>(3));

            for (int i = 0; i < 3; i++)
                save_yellow[i] = _cube[YELLOW][2-i][0];

            save_top = _cube[RED];

            for (int i = 0; i < 3; i++)
                _cube[YELLOW][i][0] = _cube[BLUE][i][0];

            for (int i = 0; i < 3; i++)
                _cube[BLUE][i][0] = _cube[WHITE][i][0];



            for (int i = 0; i < 3; i++)
                _cube[WHITE][i][0] = _cube[GREEN][2-i][2];

            for (int i = 0; i < 3; i++)
                _cube[GREEN][i][2] = save_yellow[i];

            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                    _cube[RED][i][j] = save_top[2 - j][i];
        }

        next_line;
        std::cout << "red_right " << it << '\n';
        std::cout << *this;

        switch (it % 4)
        {
            case 1:
                if (is_build)
                    finish += "L ";
                else
                    start += "L ";
                break;
            case 2:
                if (is_build)
                    finish += "L2 ";
                else
                    start += "L2 ";
                break;
            case 3:
                if (is_build)
                    finish += "L' ";
                else
                    start += "L' ";
                break;
            default:
                break;
        }
        wait(iteration);
    }

    void red_left(int it)
    {
        for (int k = 0; k < it; k++)
        {
            char save_yellow[3];
            std::vector <std::vector<char>> save_top(3, std::vector <char>(3));

            for (int i = 0; i < 3; i++)
                save_yellow[i] = _cube[YELLOW][i][0];

            save_top = _cube[RED];

            for (int i = 0; i < 3; i++)
                _cube[YELLOW][i][0] = _cube[GREEN][2-i][2];

            for (int i = 0; i < 3; i++)
                _cube[GREEN][i][2] = _cube[WHITE][2-i][0];

            for (int i = 0; i < 3; i++)
                _cube[WHITE][i][0] = _cube[BLUE][i][0];

            for (int i = 0; i < 3; i++)
                _cube[BLUE][i][0] = save_yellow[i];

            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                    _cube[RED][i][j] = save_top[j][2 - i];
        }

        next_line;
        std::cout << "red_left " << it << '\n';
        std::cout << *this;

        switch (it % 4)
        {
            case 1:
                if (is_build)
                    finish += "L' ";
                else
                    start += "L' ";
                break;
            case 2:
                if (is_build)
                    finish += "L2 ";
                else
                    start += "L2 ";
                break;
            case 3:
                if (is_build)
                    finish += "L ";
                else
                    start += "L ";
                break;
            default:
                break;

        }

        wait(iteration);
    }

    void blue_right(int it)
    {
        for (int k = 0; k < it; k++)
        {
            char save_yellow[3];
            std::vector <std::vector<char>> save_top(3, std::vector <char>(3));

            for (int i = 0; i < 3; i++)
                save_yellow[i] = _cube[YELLOW][0][i];

            save_top = _cube[BLUE];

            for (int i = 0; i < 3; i++)
                _cube[YELLOW][0][i] = _cube[ORANGE][2-i][0];

            for (int i = 0; i < 3; i++)
                _cube[ORANGE][i][0] = _cube[WHITE][2][i];

            for (int i = 0; i < 3; i++)
                _cube[WHITE][2][i] = _cube[RED][2 - i][2];

            for (int i = 0; i < 3; i++)
                _cube[RED][i][2] = save_yellow[i];

            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                    _cube[BLUE][i][j] = save_top[2 - j][i];
        }

        next_line;
        std::cout << "blue_right " << it << '\n';
        std::cout << *this;

        switch (it % 4)
        {
            case 1:
                if (is_build)
                    finish += "F ";
                else
                    start += "F ";
                break;
            case 2:
                if (is_build)
                    finish += "F2 ";
                else
                    start += "F2 ";
                break;
            case 3:
                if (is_build)
                    finish += "F' ";
                else
                    start += "F' ";
                break;
            default:
                break;

        }

        wait(iteration);
    }

    void blue_left(int it)
    {
        for (int k = 0; k < it; k++)
        {
            char save_yellow[3];
            std::vector <std::vector<char>> save_top(3, std::vector <char>(3));

            for (int i = 0; i < 3; i++)
                save_yellow[i] = _cube[YELLOW][0][2-i];

            save_top = _cube[BLUE];

            for (int i = 0; i < 3; i++)
                _cube[YELLOW][0][i] = _cube[RED][i][2];

            for (int i = 0; i < 3; i++)
                _cube[RED][i][2] = _cube[WHITE][2][2-i];

            for (int i = 0; i < 3; i++)
                _cube[WHITE][2][i] = _cube[ORANGE][i][0];

            for (int i = 0; i < 3; i++)
                _cube[ORANGE][i][0] = save_yellow[i];

            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                    _cube[BLUE][i][j] = save_top[j][2 - i];
        }

        next_line;
        std::cout << "blue_left " << it << '\n';
        std::cout << *this;

        switch (it % 4)
        {
            case 1:
                if (is_build)
                    finish += "F' ";
                else
                    start += "F' ";
                break;
            case 2:
                if (is_build)
                    finish += "F2 ";
                else
                    start += "F2 ";
                break;
            case 3:
                if (is_build)
                    finish += "F ";
                else
                    start += "F ";
                break;
            default:
                break;

        }


        wait(iteration);
    }

    void yellow_left(int it)
    {
        for (int k = 0; k < it; k++)
        {
            char save_blue[3];
            std::vector <std::vector<char>> save_top(3, std::vector <char>(3));

            for (int i = 0; i < 3; i++)
                save_blue[i] = _cube[BLUE][2][i];

            save_top = _cube[YELLOW];

            for (int i = 0; i < 3; i++)
                _cube[BLUE][2][i] = _cube[ORANGE][2][i];

            for (int i = 0; i < 3; i++)
                _cube[ORANGE][2][i] = _cube[GREEN][2][i];

            for (int i = 0; i < 3; i++)
                _cube[GREEN][2][i] = _cube[RED][2][i];

            for (int i = 0; i < 3; i++)
                _cube[RED][2][i] = save_blue[i];

            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                    _cube[YELLOW][i][j] = save_top[j][2 - i];
        }

        next_line;
        std::cout << "yellow_left " << it << '\n';
        std::cout << *this;

        switch (it % 4)
        {
            case 1:
                if (is_build)
                    finish += "D' ";
                else
                    start += "D' ";
                break;
            case 2:
                if (is_build)
                    finish += "D2 ";
                else
                    start += "D2 ";
                break;
            case 3:
                if (is_build)
                    finish += "D ";
                else
                    start += "D ";
                break;
            default:
                break;

        }

        wait(iteration);
    }

    void yellow_right(int it)
    {
        for (int k = 0; k < it; k++)
        {
            char save_blue[3];
            std::vector <std::vector<char>> save_top(3, std::vector <char>(3));

            for (int i = 0; i < 3; i++)
                save_blue[i] = _cube[BLUE][2][i];

            save_top = _cube[YELLOW];

            for (int i = 0; i < 3; i++)
                _cube[BLUE][2][i] = _cube[RED][2][i];

            for (int i = 0; i < 3; i++)
                _cube[RED][2][i] = _cube[GREEN][2][i];

            for (int i = 0; i < 3; i++)
                _cube[GREEN][2][i] = _cube[ORANGE][2][i];

            for (int i = 0; i < 3; i++)
                _cube[ORANGE][2][i] = save_blue[i];

            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                    _cube[YELLOW][i][j] = save_top[2 - j][i];
        }

        next_line;
        std::cout << "yellow_right " << it << '\n';
        std::cout << *this;

        switch (it % 4)
        {
            case 1:
                if (is_build)
                    finish += "D ";
                else
                    start += "D ";
                break;
            case 2:
                if (is_build)
                    finish += "D2 ";
                else
                    start += "D2 ";
                break;
            case 3:
                if (is_build)
                    finish += "D' ";
                else
                    start += "D' ";
                break;
            default:
                break;

        }

        wait(iteration);
    }

    bool is_building()
    {
        for (int k = WHITE; k <= YELLOW; k++)
            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                    if (_cube[k][i][j] != color[k])
                        return false;
         return true;
    }

    void mixing(int seed)
    {
        is_build = false;

        std::cout << "<Mixing>:";
        srand(seed);

        for (int i = 0; i < 20; i++)
        {
            short faced = rand()%6;
            
            short direct = rand()%2;

            short it = rand() % 4;

            protate(faced, direct, it);
        }

    }

    void building()
    {
        is_build = true;

        std::cout << "<Building>:";
        //Крестовина

        if (!compare_double(WHITE, ORANGE, cor{ WHITE, 1, 2 }))
        {
            if (compare_double(WHITE, ORANGE, cor{ WHITE, 0, 1 }))
            {
                green_left(2);
                yellow_left(1);
                orange_left(2);
            }
            else if (compare_double(WHITE, ORANGE, cor{ WHITE, 1, 0 }))
            {
                red_left(2);
                yellow_left(2);
                orange_left(2);
            }
            else if (compare_double(WHITE, ORANGE, cor{ WHITE, 0, 1 }))
            {
                blue_left(2);
                yellow_right(1);
                orange_left(2);
            }
            else if (compare_double(WHITE, ORANGE, cor{ ORANGE, 0, 1 }))
            {
                orange_left(1);
                blue_right(1);
                yellow_right(1);
                orange_left(2);
            }
            else if (compare_double(WHITE, ORANGE, cor{ GREEN, 0, 1 }))
            {
                green_left(1);
                orange_left(1);
            }
            else if (compare_double(WHITE, ORANGE, cor{ RED, 0, 1 }))
            {
                red_left(1);
                green_right(1);
                yellow_left(1);
                orange_right(2);
            }
            else if (compare_double(WHITE, ORANGE, cor{ BLUE, 0, 1 }))
            {
                blue_right(1);
                orange_right(1);
            }
            else if (compare_double(WHITE, ORANGE, cor{ BLUE, 1, 2 }))
                orange_right(1);
            else if (compare_double(WHITE, ORANGE, cor{ ORANGE, 1, 0 }))
            {
                blue_right(1);
                yellow_right(1);
                orange_left(2);
            }
            else if (compare_double(WHITE, ORANGE, cor{ RED, 1, 2 }))
            {
                blue_left(1);
                yellow_right(1);
                orange_left(2);
            }
            else if (compare_double(WHITE, ORANGE, cor{ BLUE, 1, 0 }))
            {
                red_right(1);
                yellow_right(2);
                orange_left(2);
            }
            else if (compare_double(WHITE, ORANGE, cor{ GREEN,1 , 2 }))
            {
                red_left(1);
                yellow_left(2);
                orange_left(2);
            }
            else if (compare_double(WHITE, ORANGE, cor{ RED, 1, 0 }))
            {
                green_right(1);
                yellow_left(1);
                orange_left(2);
            }
            else if (compare_double(WHITE, ORANGE, cor{ ORANGE, 1, 2 }))
            {
                green_left(1);
                yellow_left(1);
                orange_left(2);
            }
            else if (compare_double(WHITE, ORANGE, cor{ GREEN, 1, 0 }))
            {
                green_left(1);
                yellow_left(1);
                orange_left(2);
            }
            else if (compare_double(WHITE, ORANGE, cor{ YELLOW, 1, 2 }))
            {
                orange_left(2);
            }
            else if (compare_double(WHITE, ORANGE, cor{ ORANGE, 2, 1 }))
            {
                orange_right(1);
                blue_right(1);
                yellow_right(1);
                orange_right(2);
            }
            else if (compare_double(WHITE, ORANGE, cor{ YELLOW, 2, 1 }))
            {
                yellow_left(1);
                orange_left(2);
            }
            else if (compare_double(WHITE, ORANGE, cor{ GREEN, 2, 1 }))
            {
                green_right(1);
                orange_left(1);
            }
            else if (compare_double(WHITE, ORANGE, cor{ YELLOW, 1, 0 }))
            {
                yellow_right(2);
                orange_left(2);
            }
            else if (compare_double(WHITE, ORANGE, cor{ RED, 2, 1 }))
            {
                red_left(1);
                blue_left(1);
                yellow_right(1);
                orange_left(2);
            }
            else if (compare_double(WHITE, ORANGE, cor{ YELLOW, 0, 1 }))
            {
                yellow_right(1);
                orange_left(2);
            }
            else if (compare_double(WHITE, ORANGE, cor{ RED, 2, 1 }))
            {
                blue_left(1);
                orange_right(1);
            }
        }

        if (!compare_double(WHITE, GREEN, cor{ WHITE, 0, 1 }))
        {
            if (compare_double(WHITE, GREEN, cor{ GREEN, 0, 1 }))
            {
                green_left(1);
                orange_right(1);
                yellow_right(1);
                orange_left(1);
                green_left(2);
            }
            else if (compare_double(WHITE, GREEN, cor{ WHITE, 2, 1 }))
            {
                blue_left(2);
                yellow_left(2);
                green_left(2);
            }
            else if (compare_double(WHITE, GREEN, cor{ BLUE, 0, 1 }))
            {
                blue_left(2);
                yellow_left(1);
                red_right(1);
                green_left(1);
            }
            else if (compare_double(WHITE, GREEN, cor{ WHITE, 1, 0 }))
            {
                red_left(2);
                yellow_left(1);
                green_left(2);
            }
            else if (compare_double(WHITE, GREEN, cor{ RED, 0, 1 }))
            {
                red_left(1);
                green_left(1);
            }
            //
            else if (compare_double(WHITE, GREEN, cor{ GREEN, 1, 0 }))
            {
                orange_left(1);
                white_right(1);
                orange_right(1);
            }
            else if (compare_double(WHITE, GREEN, cor{ ORANGE, 1, 2 }))
                green_right(1);
            else if (compare_double(WHITE, GREEN, cor{ RED, 1, 0 }))
                green_left(1);
            else if (compare_double(WHITE, GREEN, cor{ GREEN, 1, 2 }))
            {
                green_right(1);
                yellow_right(1);
                red_right(1);
                green_left(1);
            }
            else if (compare_double(WHITE, GREEN, cor{ BLUE, 1, 0 }))
            {
                red_right(1);
                yellow_left(1);
                green_right(2);
            }
            else if (compare_double(WHITE, GREEN, cor{ RED, 1, 2 }))
            {
                red_right(2);
                green_left(1);
            }
            else if (compare_double(WHITE, GREEN, cor{ ORANGE, 1, 0 }))
            {
                blue_right(1);
                yellow_right(2);
                green_left(2);
            }
            else if (compare_double(WHITE, GREEN, cor{ BLUE, 1, 2 }))
            {
                orange_left(1);
                yellow_right(1);
                orange_right(1);
                green_left(2);
            }
            //
            else if (compare_double(WHITE, GREEN, cor{ YELLOW, 2, 1 }))
                green_right(2);
            else if (compare_double(WHITE, GREEN, cor{ GREEN, 2, 1 }))
            {
                yellow_right(1);
                red_right(1);
                green_left(1);
            }
            else if (compare_double(WHITE, GREEN, cor{ YELLOW, 1, 0 }))
            {
                yellow_left(1);
                green_left(2);
            }
            else if (compare_double(WHITE, GREEN, cor{ RED, 2, 1 }))
            {
                red_right(1);
                green_left(1);
            }
            else if (compare_double(WHITE, GREEN, cor{ YELLOW, 0, 1 }))
            {
                yellow_left(2);
                green_left(2);
            }
            else if (compare_double(WHITE, GREEN, cor{ BLUE, 2, 1 }))
            {
                yellow_left(1);
                red_right(1);
                green_left(1);
                yellow_right(1);
                red_right(2);
            }
            else if (compare_double(WHITE, GREEN, cor{ YELLOW, 1, 2 }))
            {
                yellow_right(1);
                green_right(2);
            }
            else if (compare_double(WHITE, GREEN, cor{ ORANGE, 2, 1 }))
            {
                yellow_right(1);
                green_left(1);
                red_left(1);
                yellow_left(1);
                green_right(2);
            }
        }
        
        if (!compare_double(WHITE, RED, cor{ WHITE, 1, 0 }))
        {
            if (compare_double(WHITE, RED, cor{ RED, 0, 1 }))
            {
                red_right(1);
                blue_left(1);
                yellow_left(1);
                red_left(2);
            }
            if (compare_double(WHITE, RED, cor{ WHITE, 2, 1 }))
            {
                blue_left(2);
                yellow_left(1);
                green_left(2);
            }
            else if (compare_double(WHITE, RED, cor{ BLUE, 0, 1 }))
            {
                blue_left(1);
                red_left(1);
            }
            //
            else if (compare_double(WHITE, RED, cor{ ORANGE, 1, 0 }))
            {
                blue_right(1);
                yellow_left(1);
                red_left(2);
            }
            else if (compare_double(WHITE, RED, cor{ BLUE, 1, 2 }))
            {
                orange_left(1);
                yellow_left(2);
                orange_right(1);
                red_right(2);
            }
            else if (compare_double(WHITE, RED, cor{ GREEN, 0, 1 }))
            {
                orange_right(1);
                yellow_right(2);
                orange_left(1);
                red_left(2);
            }
            else if (compare_double(WHITE, RED, cor{ ORANGE, 1, 2 }))
            {
                green_left(1);
                yellow_right(1);
                green_right(1);
                red_right(2);
            }
            else if (compare_double(WHITE, RED, cor{ RED, 1, 0 }))
            {
                green_right(1);
                yellow_right(1);
                green_left(1);
                red_right(2);
            }
            else if (compare_double(WHITE, RED, cor{ GREEN, 1, 2 }))
                red_right(1);
            else if (compare_double(WHITE, RED, cor{ BLUE, 1, 0 }))
                red_left(1);
            else if (compare_double(WHITE, RED, cor{ RED, 1, 2 }))
            {
                blue_left(1);
                yellow_left(1);
                red_right(2);
            }
            else if (compare_double(WHITE, RED, cor{ ORANGE, 2, 1 }))
            {
                yellow_left(1);
                blue_right(1);
                red_left(1);
            }
            //
            else if (compare_double(WHITE, RED, cor{ YELLOW, 0, 1 }))
            {
                yellow_left(1);
                red_right(2);
            }
            else if (compare_double(WHITE, RED, cor{ BLUE, 2, 1 }))
            {
                blue_right(1);
                red_left(1);
            }
            else if (compare_double(WHITE, RED, cor{ YELLOW, 1, 2 }))
            {
                yellow_left(2);
                red_left(2);
            }
            else if (compare_double(WHITE, RED, cor{ ORANGE, 2, 1 }))
            {
                yellow_left(1);
                blue_right(1);
                red_left(1);
            }
            else if (compare_double(WHITE, RED, cor{ YELLOW, 2, 1 }))
            {
                yellow_right(1);
                red_left(2);
            }
            else if (compare_double(WHITE, RED, cor{ GREEN, 2, 1 }))
            {
                green_left(1);
                red_right(1);
                green_right(1);
            }
            else if (compare_double(WHITE, RED, cor{ YELLOW, 1, 0 }))
                red_right(2);

            else if (compare_double(WHITE, RED, cor{ RED, 2, 1 }))
            {
                red_left(1);
                blue_left(1);
                yellow_left(1);
                red_left(2);
            }
        }

        if (!compare_double(WHITE, BLUE, cor{ WHITE, 2, 1 }))
        {
            if (compare_double(WHITE, BLUE, cor{ BLUE, 0, 1 }))
            {
                blue_right(1);
                orange_left(1);
                yellow_left(1);
                orange_right(1);
                blue_left(2);
            }
            //
            else if (compare_double(WHITE, BLUE, cor{ ORANGE, 1, 0 }))
                blue_left(1);
            else if (compare_double(WHITE, BLUE, cor{ BLUE, 1, 2 }))
            {
                blue_right(1);
                yellow_right(1);
                orange_right(1);
                blue_left(1);
                orange_left(1);
            }
            else if (compare_double(WHITE, BLUE, cor{ GREEN, 1, 0 }))
            {
                orange_right(1);
                yellow_left(1);
                blue_left(2);
                orange_left(1);
            }
            else if (compare_double(WHITE, BLUE, cor{ ORANGE, 1, 2 }))
            {
                orange_right(2);
                blue_left(1);
                orange_right(2);
            }
            else if (compare_double(WHITE, BLUE, cor{ RED, 1, 0 }))
            {
                green_right(1);
                yellow_right(2);
                blue_right(2);
                green_left(1);
            }
            else if (compare_double(WHITE, BLUE, cor{ GREEN, 1, 2 }))
            {
                red_left(1);
                yellow_right(1);
                blue_right(2);
                red_right(1);
            }
            else if (compare_double(WHITE, BLUE, cor{ BLUE, 1, 0 }))
            {
                blue_left(1);
                yellow_right(1);
                orange_right(1);
                blue_left(1);
                orange_left(1);
            }
            else if (compare_double(WHITE, BLUE, cor{ RED, 1, 2 }))
                blue_right(1);
            //

            else if (compare_double(WHITE, BLUE, cor{ YELLOW,0 , 1 }))
                blue_right(2);
            else if (compare_double(WHITE, BLUE, cor{ BLUE, 2, 1 }))
            {
                yellow_right(1);
                orange_right(1);
                blue_left(1);
                orange_left(1);
            }
            else if (compare_double(WHITE, BLUE, cor{ YELLOW, 1, 2 }))
            {
                yellow_left(1);
                blue_right(2);
            }
            else if (compare_double(WHITE, BLUE, cor{ YELLOW, 2, 1 }))
            {
                yellow_left(2);
                blue_left(2);
            }
            else if (compare_double(WHITE, BLUE, cor{ YELLOW, 1, 0 }))
            {
                yellow_right(1);
                blue_left(2);
            }
            else if (compare_double(WHITE, BLUE, cor{ ORANGE, 2, 1 }))
            {
                orange_right(1);
                blue_left(1);
                orange_left(1);
            }
            else if (compare_double(WHITE, BLUE, cor{ GREEN, 2, 1 }))
            {
                green_right(1);
                orange_right(1);
                yellow_left(1);
                blue_left(2);
                orange_left(1);
                green_left(1);
            }
            else if (compare_double(WHITE, BLUE, cor{ RED, 2, 1 }))
            {
                red_left(1);
                blue_right(1);
                red_right(1);
            }
        }

        //Верхние углы

        if (!compare_triple(WHITE, BLUE, ORANGE, cor{ WHITE, 2, 2 }))
        {
            if (compare_triple(WHITE, BLUE, ORANGE, cor{ORANGE, 0, 0})
                || compare_triple(WHITE, BLUE, ORANGE, cor{ BLUE, 0, 2 }))
            {
                blue_right(1);
                yellow_right(1);
                blue_left(1);
                yellow_left(1);
            }
            else if (compare_triple(WHITE, BLUE, ORANGE, cor{ WHITE, 0, 2 })
                || compare_triple(WHITE, BLUE, ORANGE, cor{ ORANGE, 0, 2 })
                || compare_triple(WHITE, BLUE, ORANGE, cor{ GREEN, 0, 0 }))
            {
                orange_right(1);
                yellow_right(1);
                orange_left(1);
                yellow_left(2);
            }
            else if (compare_triple(WHITE, BLUE, ORANGE, cor{ WHITE, 0, 0 })
                || compare_triple(WHITE, BLUE, ORANGE, cor{ GREEN, 0, 2 })
                || compare_triple(WHITE, BLUE, ORANGE, cor{ RED, 0, 0 }))
            {
                green_right(1);
                yellow_right(1);
                green_left(1);
                yellow_right(1);
            }
            else if (compare_triple(WHITE, BLUE, ORANGE, cor{ WHITE, 2, 0 })
                || compare_triple(WHITE, BLUE, ORANGE, cor{ RED, 0, 2 })
                || compare_triple(WHITE, BLUE, ORANGE, cor{ BLUE, 0, 0 }))
            {
                red_right(1);
                yellow_right(1);
                red_left(1);
            }
            else if (compare_triple(WHITE, BLUE, ORANGE, cor{ YELLOW, 2, 2 })
                || compare_triple(WHITE, BLUE, ORANGE, cor{ ORANGE, 2, 2 })
                || compare_triple(WHITE, BLUE, ORANGE, cor{ GREEN, 2, 0 }))
            {
                yellow_left(1);
            }
            else if (compare_triple(WHITE, BLUE, ORANGE, cor{ YELLOW, 2, 0 })
                || compare_triple(WHITE, BLUE, ORANGE, cor{ GREEN, 2, 2 })
                || compare_triple(WHITE, BLUE, ORANGE, cor{ RED, 2, 0 }))
            {
                yellow_right(2);
            }
            else if (compare_triple(WHITE, BLUE, ORANGE, cor{ YELLOW, 0, 0 })
                || compare_triple(WHITE, BLUE, ORANGE, cor{ RED, 2, 2 })
                || compare_triple(WHITE, BLUE, ORANGE, cor{ BLUE, 2, 0 }))
            {
                yellow_right(1);
            }


            while (true)
            {
                blue_right(1);
                yellow_right(1);
                if (compare_triple(WHITE, BLUE, ORANGE, cor{ ORANGE, 2, 0 }))
                    break;
                yellow_right(1);
                blue_left(1);
                yellow_left(1);
            }
            blue_left(1);
        }
;

        if (!compare_triple(WHITE, GREEN, ORANGE, cor{ WHITE, 0, 2 }))
        {
            if (compare_triple(WHITE, GREEN, ORANGE, cor{ GREEN, 0, 0 })
                || compare_triple(WHITE, GREEN, ORANGE, cor{ ORANGE, 0, 2 }))
            {
                orange_right(1);
                yellow_right(1);
                orange_left(1);
                yellow_left(1);
            }
            //
            else if (compare_triple(WHITE, GREEN, ORANGE, cor{ WHITE, 0, 0 })
                || compare_triple(WHITE, GREEN, ORANGE, cor{ GREEN, 0, 2})
                || compare_triple(WHITE, GREEN, ORANGE, cor{ RED, 0, 0 }))
            {
                red_left(1);
                yellow_left(1);
                red_right(1);
            }
            //
            else if (compare_triple(WHITE, GREEN, ORANGE, cor{WHITE, 2, 2})
                || compare_triple(WHITE, GREEN, ORANGE, cor{ BLUE, 0, 2})
                || compare_triple(WHITE, GREEN, ORANGE, cor{ ORANGE, 0, 0 }))
            {
                blue_right(1);
                yellow_right(1);
                blue_left(1);
            }
            //
            else if (compare_triple(WHITE, GREEN, ORANGE, cor{ WHITE, 2, 0 })
                || compare_triple(WHITE, GREEN, ORANGE, cor{ BLUE, 0, 0 })
                || compare_triple(WHITE, GREEN, ORANGE, cor{ RED, 0, 2 }))
            {
                red_right(1);
                yellow_right(2);
                red_left(1);
            }
            ///
            else if (compare_triple(WHITE, GREEN, ORANGE, cor{ YELLOW, 0, 2 })
                || compare_triple(WHITE, GREEN, ORANGE, cor{ BLUE, 2, 2 })
                || compare_triple(WHITE, GREEN, ORANGE, cor{ ORANGE, 2, 0 }))
            {
                yellow_right(1);
            }
            //
            else if (compare_triple(WHITE, GREEN, ORANGE, cor{ YELLOW, 2, 0 })
                || compare_triple(WHITE, GREEN, ORANGE, cor{ GREEN, 2, 2 })
                || compare_triple(WHITE, GREEN, ORANGE, cor{ RED, 2, 0 }))
            {
                yellow_left(1);
            }
            //
            else if (compare_triple(WHITE, GREEN, ORANGE, cor{ YELLOW, 0, 0 })
                || compare_triple(WHITE, GREEN, ORANGE, cor{ RED, 2, 2 })
                || compare_triple(WHITE, GREEN, ORANGE, cor{ BLUE, 2, 0 }))
            {
                yellow_right(2);
            }


            while (true)
            {
                orange_right(1);
                yellow_right(1);
                if (compare_triple(WHITE, GREEN, ORANGE, cor{ GREEN, 2, 0 }))
                    break;
                yellow_right(1);
                orange_left(1);
                yellow_left(1);
            }
            orange_left(1);

        }

        
        if (!compare_triple(WHITE, GREEN, RED, cor{ WHITE, 0, 0 }))
        {
            if (compare_triple(WHITE, GREEN, RED, cor{ RED, 0, 0 })
                || compare_triple(WHITE, GREEN, RED, cor{ GREEN, 0, 2 }))
            {
                red_left(1);
                yellow_left(1);
                red_right(1);
                yellow_right(1);
            }

            else if (compare_triple(WHITE, GREEN, RED, cor{ WHITE, 2, 0 })
                || compare_triple(WHITE, GREEN, RED, cor{ BLUE, 0, 0 })
                || compare_triple(WHITE, GREEN, RED, cor{ RED, 0, 2 }))
            {
                red_right(1);
                yellow_left(1);
                red_left(1);
                yellow_left(1);
            }
            ///
            else if (compare_triple(WHITE, GREEN, RED, cor{ YELLOW, 0, 2 })
                || compare_triple(WHITE, GREEN, RED, cor{ BLUE, 2, 2 })
                || compare_triple(WHITE, GREEN, RED, cor{ ORANGE, 2, 0 }))
            {
                yellow_left(2);
            }

            else if (compare_triple(WHITE, GREEN, RED, cor{ YELLOW, 2, 2 })
                || compare_triple(WHITE, GREEN, RED, cor{ ORANGE, 2, 2 })
                || compare_triple(WHITE, GREEN, RED, cor{ GREEN, 2, 0 }))
            {
                yellow_right(1);
            }

            else if (compare_triple(WHITE, GREEN, RED, cor{ YELLOW, 0, 0 })
                || compare_triple(WHITE, GREEN, RED, cor{RED, 2, 2 })
                || compare_triple(WHITE, GREEN, RED, cor{ BLUE, 2, 0 }))
            {
                yellow_left(1);
            }


            while (true)
            {
                green_right(1);
                yellow_right(1);
                if (compare_triple(WHITE, GREEN, RED, cor{ RED, 2, 0 }))
                    break;
                yellow_right(1);
                green_left(1);
                yellow_left(1);
            }
            green_left(1);
        }

        if (!compare_triple(WHITE, BLUE, RED, cor{ WHITE, 2, 0 }))
        {

            if (compare_triple(WHITE, BLUE, RED, cor{ RED, 0, 2 })
                || compare_triple(WHITE, BLUE, RED, cor{ BLUE, 0, 0 }))
            {
                red_right(1);
                yellow_right(1);
                red_left(1);
                yellow_left(1);
            }

            if (compare_triple(WHITE, BLUE, RED, cor{ YELLOW, 0, 2 })
                || compare_triple(WHITE, BLUE, RED, cor{ BLUE, 2, 2 })
                || compare_triple(WHITE, BLUE, RED, cor{ ORANGE, 2, 0 }))
            {
                yellow_left(1);
            }

            if (compare_triple(WHITE, BLUE, RED, cor{ YELLOW, 2, 2 })
                || compare_triple(WHITE, BLUE, RED, cor{ ORANGE, 2, 2 })
                || compare_triple(WHITE, BLUE, RED, cor{ GREEN, 2, 0 }))
            {
                yellow_left(2);
            }


            if (compare_triple(WHITE, BLUE, RED, cor{ YELLOW, 2, 0 })
                || compare_triple(WHITE, BLUE, RED, cor{ GREEN, 2, 2 })
                || compare_triple(WHITE, BLUE, RED, cor{ RED, 2, 0 }))
            {
                yellow_right(1);
            }

            while (true)
            {
                red_right(1);
                yellow_right(1);
                if (compare_triple(WHITE, BLUE, RED, cor{ BLUE, 2, 0 }))
                    break;
                yellow_right(1);
                red_left(1);
                yellow_left(1);
            }
            red_left(1);
        }

        // Вторая строка
        
        for (int i = ORANGE; i <= BLUE; i++)
        {
            short f_consid;
            short s_consid;

            f_consid = i;
            i == BLUE ? s_consid = ORANGE : s_consid = i + 1;

            if (!compare_double(f_consid, s_consid, cor{ f_consid, 1, 2 }))
            {
                short f_color = -1;
                short s_color = -1;
            
                for (int j =i ; j <= i+3; j++)
                {
                    int ch=0;
                    j - ch > BLUE  ? ch = 4 : false ;
                    
                    f_color = j-ch;
                    j - ch + 1 > BLUE ? s_color = ORANGE : s_color = j - ch + 1;

                    if (compare_double(f_consid, s_consid, cor{f_color, 1, 2})
                        || compare_double(f_consid, s_consid, cor{s_color, 1, 0}))
                    {
                        yellow_right(1);
                        protate(f_color, RIGHT, 1);
                        yellow_left(1);
                        protate(f_color, LEFT, 1);
                        yellow_left(1);
                        protate(s_color, LEFT, 1);
                        yellow_right(1);
                        protate(s_color, RIGHT, 1);
                        yellow_right(2);

                        break;
                    }
                }

                for (short j = ORANGE; j <= BLUE; j++)
                {
                    if (compare_double(f_consid, s_consid, cor{ f_consid, 2, 1 }))
                    {
                        while (!compare_double(f_consid, s_consid , cor{f_consid, 2, 1}))
                            yellow_right(1);
                        
                        yellow_left(1);
                        protate(s_consid, LEFT, 1);
                        yellow_right(1);
                        protate(s_consid, RIGHT, 1);
                        yellow_right(1);
                        protate(f_consid, RIGHT, 1);
                        yellow_left(1);
                        protate(f_consid, LEFT, 1);
                        
                        break;
                    }

                    if (compare_double(s_consid, f_consid, cor{ f_consid, 2, 1 }))
                    {
                        while (!compare_double(s_consid, f_consid, cor{ f_consid, 2, 1 }))
                            yellow_right(1);

                        yellow_right(2);
                        protate(f_consid, RIGHT, 1);
                        yellow_left(1);
                        protate(f_consid, LEFT, 1);
                        yellow_left(1);
                        protate(s_consid, LEFT, 1);
                        yellow_right(1);
                        protate(s_consid, RIGHT, 1);
                        yellow_right(2);

                        break;
                    }
                    yellow_right(1);
                }
            }
        }

        //собираю нижнюю крестовину
            //ставлю кубики на своё место

        bool coins[4] = { false, false, false, false };
        short right_det;

        for (int i = 0; i < 4; i++)
        {

            int c = 0;
            for (short j = ORANGE; j <= BLUE; j++)
                if (compare_double(j, YELLOW, cor{ j, 2, 1 })
                    || compare_double(YELLOW, j, cor{ j, 2, 1 }))
                {
                    c++;
                    coins[j - 1] = true;
                }
            if (c >= 2)
                break;
            for (int j = 0; j < 4; j++)
                coins[j] = false;
            yellow_right(1);
        }

        for (short i = ORANGE; i <=BLUE; i++)
        {
            if (coins[i - 1])
                continue;

            short first;
            short second;
            short third;

            i + 1 > BLUE ? first = ORANGE : first = i+1;
            i - 1 < ORANGE ? second = BLUE : second = i - 1;
            first + 1 > BLUE ? third = ORANGE : third = first + 1;

            if (!coins[first - 1])
            {
                yellow_right(1);
                protate(i, RIGHT, 1);
                protate(second, RIGHT, 1);
                yellow_right(1);
                protate(second, LEFT, 1);
                yellow_left(1);
                protate(i, LEFT, 1);
                break;
            }
            else if (!coins[second - 1])
            {
                yellow_right(1);
                protate(second, RIGHT, 1);
                protate(third, RIGHT, 1);
                yellow_right(1);
                protate(third, LEFT, 1);
                yellow_left(1);
                protate(second, LEFT, 1);
                break;
            }
            else if (!coins[third - 1])
            {
                yellow_right(1);
                protate(second, RIGHT, 1);
                protate(third, RIGHT, 1);
                yellow_right(1);
                protate(third, LEFT, 1);
                yellow_left(1);
                protate(second, LEFT, 1);

                yellow_right(1);
                protate(third, RIGHT, 1);
                protate(first, RIGHT, 1);
                yellow_right(1);
                protate(first, LEFT, 1);
                yellow_left(1);
                protate(third, LEFT, 1);

                yellow_right(1);
                protate(second, RIGHT, 1);
                protate(third, RIGHT, 1);
                yellow_right(1);
                protate(third, LEFT, 1);
                yellow_left(1);
                protate(second, LEFT, 1);
                break;
            }
        }
            //переворачиваю кубики

        for (short i = ORANGE; i < BLUE; i++)
        {
            if (compare_double(i, YELLOW, cor{ i, 2, 1 }))
                continue;

            short first=i;

            for (int j = 0; j < 4; j++)
            {
                protate(first, RIGHT, 1);
                yellow_right(1);
                white_left(1);
                first + 1 > BLUE ? first = ORANGE : first++;
            }

            short second;
            i + 1 > BLUE ? second = ORANGE : second = i+1;

            for (int j = 0; j < 3; j++)
            {
                if (compare_double(second, YELLOW, cor{ second, 2, 1 }))
                {
                    second + 1 > BLUE ? second = ORANGE : second++;
                    continue;
                }
                break;
            }

            short number = 0;

            while (!compare_double(YELLOW, second, cor{ i, 2, 1 }))
            {
                yellow_left(1);
                number++;
            }

            first = i;

            for (int j = 0; j < 4; j++)
            {
                protate(first, RIGHT, 1);
                yellow_right(1);
                white_left(1);
                first + 1 > BLUE ? first = ORANGE : first++;
            }

            yellow_right(number);

        }

        if (is_building())
            return;

        //вставляю нижние углы на место

        for (int i = 0; i < 4; i++)
            coins[i] = false;

        short number;
        bool is_right_dot = false;
        for (short i = ORANGE; i <= BLUE; i++)
        {
            short next;
            i + 1 > BLUE ? next = ORANGE : next = i + 1;
            if (compare_triple(i, next, YELLOW, cor{ i, 2, 2 })
                || compare_triple(YELLOW, i, next, cor{ i, 2, 2 })
                || compare_triple(next, YELLOW, i, cor{ i, 2, 2 }))
            {
                coins[i-1]=true;
                is_right_dot = true;
            }

            if (i == BLUE && !is_right_dot)
            {
                protate(ORANGE, LEFT, 1);
                protate(GREEN, LEFT, 1);
                protate(RED, LEFT, 1);
                protate(GREEN, RIGHT, 1);
                protate(ORANGE, RIGHT, 1);
                protate(GREEN, LEFT, 1);
                protate(RED, RIGHT, 1);
                protate(GREEN, RIGHT, 1);
                i = ORANGE;
            }

        }

        for (int i = ORANGE; i <= BLUE; i++)
        {
            if (!coins[i - 1])
                continue;

            right_det = i;
            break;
        }

        short det=right_det;

        for (int j = 0; j < 2; j++)
            det + 1 > BLUE ? det = ORANGE : det++;

        short next;
        det + 1 > BLUE ? next = ORANGE : next = det + 1;

        if (!compare_triple(det, next, YELLOW, cor{det, 2, 2})
        && ! compare_triple(next, YELLOW, det, cor{det, 2, 2})
        && ! compare_triple(YELLOW, det, next, cor{det, 2, 2}))
            if (_cube[det][2][2] == color[next]
                || _cube[next][2][0] == color[next]
                || _cube[det][2][2] == color[right_det])
            {
                protate(det, LEFT, 1);
                protate(next, LEFT, 1);
                protate(right_det, LEFT, 1);
                protate(next, RIGHT, 1);
                protate(det, RIGHT, 1);
                protate(next, LEFT, 1);
                protate(right_det, RIGHT, 1);
                protate(next, RIGHT, 1);
            }
            else
            {
                protate(next, LEFT, 1);
                protate(right_det, LEFT, 1);
                protate(next, RIGHT, 1);
                protate(det, LEFT, 1);
                protate(next, LEFT, 1);
                protate(right_det, RIGHT, 1);
                protate(next, RIGHT, 1);
                protate(det, RIGHT, 1);
            }
        
        if (is_building())
            return;

        //переворачиваю углы
        for (int k = 0; k < 4; k++)
        {
            short first, prev, up;
            int number=0;

            for (short i=ORANGE; i<=BLUE; i++)
            {
                i + 1 > BLUE ? next = ORANGE : next = i + 1;
                first = i;
                if (compare_triple(i, next, YELLOW, cor{ i, 2, 2 }))
                    continue;
                break;
            }

            for (short i = first+1; i <= BLUE; i++)
            {
                number++;
                i + 1 > BLUE ? next = ORANGE : next = i + 1;
                if (compare_triple(i, next, YELLOW, cor{ i, 2, 2 }))
                    continue;
                break;
            }
            first + 1 > BLUE ? next = ORANGE : next = first + 1;
            first - 1 < ORANGE ? prev = BLUE : prev = first - 1;
            next + 1 > BLUE ? up = ORANGE : up = next + 1;
        
            for (int i = 0; i < 6; i++)
            {
                if (i == 2)
                    yellow_left(number);
                protate(first, RIGHT, 1);
                protate(next, LEFT, 1);
                protate(first, LEFT, 1);
                protate(next, RIGHT, 1);
            }
            yellow_right(number);
        }

    } 

    void return_change()
    {
        next_line;
        std::cout << "Start:\n";
        std::cout << start << std::endl;
        next_line;
        std::cout << "Finish:\n";
        std::cout << finish << std::endl;
    }
}; 

std::istream& operator>> (std::istream& input, cub& my_class)
{
    for (int i = 2; i >= 0; i--)
        for (int j = 2; j >= 0; j--)
            input >> my_class._cube[GREEN][i][j];

    for (int k = 0; k < 3; k++)
    {
        for (int i = 2; i >= 0; i--)
            input >> my_class._cube[RED][i][k];
        for (int i = 0; i < 3; i++)
            input >> my_class._cube[WHITE][k][i];
        for (int i = 0; i < 3; i++)
            input >> my_class._cube[ORANGE][i][2 - k];
    }
     
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            input >> my_class._cube[BLUE][i][j];

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            input >> my_class._cube[YELLOW][i][j];

    return input;
}
std::ostream& operator<< (std::ostream & output, cub& my_class)
{
    for (int i = 2; i >= 0; i--)
    {
        output << "     ";
        for (int j = 2; j >= 0; j--)
            output <<" "<< my_class._cube[GREEN][i][j];
        output << '\n';
    }

    for (int k = 0; k < 3; k++)
    {
        for (int i = 2; i >= 0; i--)
            output << my_class._cube[RED][i][k] << " ";
        for (int i=0; i<3; i++)
            output << my_class._cube[WHITE][k][i] << " ";
        for (int i = 0; i < 3; i++)
            output << my_class._cube[ORANGE][i][2-k] << " ";
        output << '\n';
    }

    for (int i = 0; i < 3; i++)
    {
        output << "     ";
        for (int j = 0; j < 3; j++)
            output << " " << my_class._cube[BLUE][i][j];
        output << "\n";
    }

    for (int i = 0; i < 3; i++)
    {
        output << "     ";
        for (int j = 0; j < 3; j++)
            output << " " << my_class._cube[YELLOW][i][j];
        output << '\n';
    }
    return output;
}


#define contur_size 5
#define contur_color 85, 52, 45

#define pos 80

#define rec_size 70, 70

#define back_size 1100, 1100
#define back_color 255, 185, 141

void cell(std:: vector<std::vector<std::vector<char>>> cube, sf::RenderWindow& window)
{
    int coor_x;
    int coor_y;
    for (int k = WHITE; k <= YELLOW; k++)
    {
        switch (k)
        {
        case(WHITE):
            coor_x = 430;
            coor_y = 310;
            break;
        case(ORANGE):
            coor_x = 670;
            coor_y = 310;
            break;
        case(GREEN):
            coor_x = 430;
            coor_y = 70;
            break;
        case(RED):
            coor_x = 190;
            coor_y = 310;
            break;
        case(BLUE):
            coor_x = 430;
            coor_y = 550;
            break;
        case(YELLOW):
            coor_x = 430;
            coor_y = 790;
            break;
        default:
            break;
        }
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                char color;
                switch (k)
                {
                case(ORANGE):
                    color = cube[k][j][2 - i];
                    break;
                case(GREEN):
                    color = cube[k][2 - i][2 - j];
                    break;
                case(RED):
                    color = cube[k][2 - j][i];
                    break;
                default:
                    color = cube[k][i][j];
                    break;
                }

                sf::RectangleShape rectangle;
                rectangle.setSize(sf::Vector2f(rec_size));
                rectangle.setOutlineColor(sf::Color(contur_color));
                rectangle.setOutlineThickness(contur_size);
                rectangle.setPosition(coor_x + j * pos, coor_y + i *pos);

                switch (color)
                {
                case('w'):
                    rectangle.setFillColor(sf::Color(255, 236, 222));
                    break;
                case('o'):
                    rectangle.setFillColor(sf::Color(255, 172, 104));
                    break;
                case('g'):
                    rectangle.setFillColor(sf::Color(167, 237, 165));
                    break;
                case('r'):
                    rectangle.setFillColor(sf::Color(246, 137, 129));
                    break;
                case('b'):
                    rectangle.setFillColor(sf::Color(135, 151, 233));
                    break;
                case('y'):
                    rectangle.setFillColor(sf::Color(245, 241, 138));
                    break;
                default:
                    break;
                }

                window.draw(rectangle);
            }
        }
    }
}

void grafix_on(cub& my_class, int time_1, int time_2)
{
    std::vector <std::string> start;
    start = divide_string(my_class.start);
    std::vector <std::string> finish;
    finish = divide_string(my_class.finish);

    sf::RenderWindow window(sf::VideoMode(back_size), "SFMLworks");
    sf::RectangleShape rectangle;
    
    rectangle.setSize(sf::Vector2f(back_size));
    rectangle.setFillColor(sf::Color(back_color));
    rectangle.setPosition(0, 0);

    for (int k = 0; k < faceds; k++)
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                my_class._cube[k][i][j] = my_class.color[k];

    bool is_build = false;
    bool grafixing = true;
    int it_1=0;
    int it_2 = 0;

    std::string duing;


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(rectangle);

        cell(my_class._cube, window);


//повторяю повороты
        if (grafixing)
            {
            if (duing == "U")
                my_class.white_right(1);
            else if (duing == "U2")
                my_class.white_right(2);
            else if (duing == "U'")
                my_class.white_left(1);
            else if (duing == "R")
                my_class.orange_right(1);
            else if (duing == "R2")
                my_class.orange_right(2);
            else if (duing == "R'")
                my_class.orange_left(1);
            else if (duing == "B")
                my_class.green_right(1);
            else if (duing == "B2")
                my_class.green_right(2);
            else if (duing == "B'")
                my_class.green_left(1);
            else if (duing == "L")
                my_class.red_right(1);
            else if (duing == "L2")
                my_class.red_right(2);
            else if (duing == "L'")
                my_class.red_left(1);
            else if (duing == "F")
                my_class.blue_right(1);
            else if (duing == "F2")
                my_class.blue_right(2);
            else if (duing == "F'")
                my_class.blue_left(1);
            else if (duing == "D")
                my_class.yellow_right(1);
            else if (duing == "D2")
                my_class.yellow_right(2);
            else if (duing == "D'")
                my_class.yellow_left(1);

            }

        if (!is_build)
        {
            duing = start[it_1];

            it_1++;
            if (it_1 >= start.size())
                is_build = true;

            wait(time_1);
        }
        else if (it_2 < finish.size())
        {
            duing = finish[it_2];
            it_2++;
            wait(time_2);
        }
        else
        {
            grafixing = false;
        }
        /**/
        
        window.display();
    }
}