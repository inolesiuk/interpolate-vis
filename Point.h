#include<GL/gl.h>
#include <GL/glut.h>

#ifndef INTERPOLATE_POINT_H
#define INTERPOLATE_POINT_H

class Point
{
    double Xvalue;
    double Yvalue;

public:
    Point() : Xvalue(0), Yvalue(0) {};
    Point (Point const & p) { Xvalue = p.x(); Yvalue = p.y(); }
    Point& operator = (Point const & p)
    {
        if (&p != this)
        {
            Xvalue = p.x();
            Yvalue = p.y();
        }
        return *this;
    }
    void xy(double x, double y)
    {
        Xvalue = x;
        Yvalue = y;
    }

    //return individual x y value
    double x() const { return Xvalue; }
    double y() const { return Yvalue; }

    int win_x() { return (int)((Xvalue + 1) / 2 * glutGet( GLUT_WINDOW_WIDTH ));}
    int win_y() { return (int)((Yvalue + 1) / 2 * glutGet( GLUT_WINDOW_HEIGHT ));}

    void set_y(double y)
    {
        Yvalue = y;
    }
};

#endif //INTERPOLATE_POINT_H
