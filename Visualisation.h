#include <iostream>
#include <map>

#include "Point.h"
#include "Train.h"

#ifndef INTERPOLATE_VISUALISATION_H
#define INTERPOLATE_VISUALISATION_H

class Visualisation
{
    std::map <int, Point> m;
    std::vector <pt> lagrange;
    std::vector <pt> least_mean;

    int last_point;

    void draw_axes();
    void plot(Train&);
    void show_legend();
    void draw_button(double, double, double);
    void printtext(double, double, std::string);
    void numbers(double, double, int, bool);
    void markdown(int, double, double, double, bool);
    void draw_triangles(double, double, double, bool);
    int pos (int);
    double norm_y(int);
    double norm_x(int);
    double inv_pos (int);
    bool y_is_bounded(int);

public:

    Visualisation();
    Visualisation(Visualisation const &);
    Visualisation const & operator = (Visualisation const  &);
    ~ Visualisation();

    bool tapped;
    bool m_tapped = false;
    std::map <int, Point> const & m_() const { return m; };
    std::vector <pt> const & lagrange_() const { return  lagrange; };
    std::vector <pt> const & least_mean_() const { return least_mean; };
    bool tapped_ () const { return tapped; };
    bool m_tapped_ () const { return m_tapped; };

    void Display();
    void mouse(int, int, int, int);
    void mouse_move(int, int);
};

#endif //INTERPOLATE_VISUALISATION_H
