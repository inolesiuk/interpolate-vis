#include <iostream>
#include <vector>
#include <map>

#include "Point.h"

#ifndef INTERPOLATE_TRAIN_H
#define INTERPOLATE_TRAIN_H

typedef std::pair <double, double> pt;
typedef std::vector <std::vector <double> > Matrix;

class Train
{
    std::vector <pt> i_state;
    std::vector <pt> marks;

    Matrix const find_inverse(Matrix const &);
    Matrix const minor_(Matrix const &, int);
    Matrix const cofactor (Matrix const &, double);
    Matrix const transpose (Matrix const &);
    Matrix const LS_matrix();
    Matrix const multiply(Matrix const &, Matrix const &);
    Matrix const & make_null (Matrix &, int, int);
    Matrix const & normalize(Matrix &, double);

    double det_(Matrix, int);
    void print_matrix(Matrix);
    std::vector <pt> multiply_v(Matrix const & m, std::vector<pt>);
    std::vector <pt> coef(Matrix);
    std::vector <pt> i_state_() const;
    std::vector <pt> marks_() const;
public:
        Train();
        Train (std::map <int, Point>);
        Train(Train const &);
        Train const & operator = (Train const &);
        ~Train();
        void make_coef();
        double LS (double);
        double lagrange_interpolate (double);
};

#endif //INTERPOLATE_TRAIN_H
