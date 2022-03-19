class dot
{
protected:
    int x_=0, y_=0;
public:
    dot ()
    {}
    dot (int x, int y)
    : x_(x)
    , y_(y)
    {}
    dot (const dot &other)
    : x_(other.x_)
    , y_(other.y_)
    {}
    void operator = (const dot &other)
    {
        x_=other.x_;
        y_=other.y_;
    }
    void set_O (int x, int y)
    {
        x_=x;
        y_=y;
    }
    int get_x ()
    {
        return x_;
    }
    int get_y ()
    {
        return y_;
    }

};