#include <cmath>

#include "Train.h"

Train::Train()
{
    pt p_1(0, -4.59512);
    pt p_2(0.2, -3.17805);
    pt p_3(0.3, -2.31363);
    pt p_4(0.4, -1.65823);
    pt p_5(0.5, -1.09861);

    i_state.push_back(p_1);
    i_state.push_back(p_2);
    i_state.push_back(p_3);
    i_state.push_back(p_4);
    i_state.push_back(p_5);
}

Train::Train(std::map <int, Point> m)
{
    auto it = m.begin();
    for (it; it != m.end(); ++it)
    {
        i_state.emplace_back(pt((it -> second.x() + 0.8) / 0.2,
                             (it -> second.y() - 0.8) / 0.145));
    }
}

Train::Train(Train const & m)
{
    i_state = m.i_state_();
    marks = m.marks_();
}

Train const & Train::operator = (Train const & m)
{
    if (this != &m)
    {
        i_state = m.i_state_();
        marks = m.marks_();
    }
}

double Train::lagrange_interpolate(double x)
{
    double result = 0;
    double w1, w2;
    for (int i = 0; i < i_state.size(); ++i)
    {
        w1 = 1;
        w2 = 1;
        for (int j = 0;j < i_state.size(); ++j)
            if (j != i)
            {
                w1 *= (x - i_state[j].first);
                w2 *= (i_state[i].first - i_state[j].first);
            }
        result += i_state[i].second * w1 / w2;
    }
    return result;
}

//Matrix proedures

Matrix const & Train::make_null(Matrix & m, int rsize, int csize)
{
    std::vector <double> temp;
    for (int i = 0; i < csize; ++i)
    {
        for (int j = 0; j < rsize; ++j)
        {
            temp.push_back(0);
        }
        m.push_back(temp);
        temp.clear();
    }
    return m;
}

void Train::print_matrix(Matrix m)
{
    for (int i = 0; i < m.size(); ++i)
    {
        for (int j = 0; j < m[0].size(); ++j)
        {
            std::cout << m[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

Matrix const Train::minor_(Matrix const & m, int n)
{
    int a = 0;
    int k = 0;
    Matrix temp;
    temp = make_null(temp, m.size(), m.size());
    for (int i = 1; i < m.size(); ++i)
        for (int j = 0; j < m.size(); ++j)
        {
            if (j == n) continue;
            temp[a][k] = m[i][j];
            ++k;
            if (k == m.size() - 1)
            {
                ++a;
                k = 0;
            }
        }
    return temp;
}

double Train::det_ (Matrix m, int size)
{
    double det = 0;
    Matrix temp;
    if(size == 1)
    {
        det = m[0][0];
    }
    else if(size == 2)
    {
        det = m[0][0] * m[1][1] - m[0][1] * m[1][0];
    }
    else
    {
        for (int i = 0; i < size; ++i)
        {
            for (int j = 0; j < size - 1; ++j)
            {
                if (j < i) temp.push_back(m[j]);
                else temp.push_back(m[j+1]);
            }
            det += pow((double)-1, (i + size - 2)) * det_(temp, size - 1) * m[i][size - 1];
            temp.clear();
        }
    }
    return det;
}

Matrix const Train::cofactor(Matrix const & m, double det)
{
    int i1, i2;
    Matrix temp;
    temp = make_null(temp, m.size(), m.size());
    Matrix cof;
    cof = make_null(cof, m.size(), m.size());
    for (int k = 0; k < m.size(); ++k)
        for (int l = 0; l < m.size(); ++l)
        {
            i1 = 0;
            i2 = 0;
            for (int i = 0; i < m.size(); ++i)
                for (int j = 0; j < m.size(); ++j)
                    if (i != k && j != l)
                    {
                        temp[i1][i2] = m[i][j];
                        if (i2 < m.size() - 2) i2++;
                        else
                        {
                            i2 = 0;
                            ++i1;
                        }

                     }
                    if (l % 2 != 0)
                    cof[k][l] = -(pow (-1, (k + 1)) * det_(temp,temp.size()-1));
                    else cof[k][l] = pow (-1, (k + 1)) * det_(temp,temp.size()-1);
        }
    cof = transpose(cof);
    return normalize(cof, det);
}

Matrix const Train::transpose(Matrix const & m)
{
    Matrix result;
    result = make_null(result,m.size(), m[0].size());
    for (int i = 0; i < m[0].size(); ++i)
        for (int j = 0; j < m.size(); ++j)
            result[i][j] = m[j][i];
    return result;
}

Matrix const & Train::normalize(Matrix & m, double det)
{
    for (int i = 0; i < m.size(); ++i)
    {
        for (int j = 0; j < m.size(); j++ )
        {
            m[i][j] = m[i][j] / det;
        }
    }
    return m;
}

Matrix const Train::find_inverse(Matrix const & m)
{
    return cofactor(m, det_(m, m.size()));
}

Matrix const Train::LS_matrix()
{
    Matrix temp;
    temp = make_null(temp, 4, 5);
    for (int i = 0; i < temp.size(); ++i)
        for (int j = 0; j < temp[0].size(); ++j)
        {
            temp[i][j] = pow (i_state[i].first, j);
        }
    return temp;
}

Matrix const Train::multiply (Matrix const & m1, Matrix const & m2)
{
    Matrix result;
    result  = make_null(result, m1.size(), m1.size());
    for (int i = 0; i < m1.size(); ++i)
        for (int j = 0; j < m1.size(); ++j)
        {
            for (int k = 0; k < m1[0].size(); ++k)
            result [i][j] += m1[i][k] * m2[k][j];
        }
    return result;
}

std::vector <pt> Train::multiply_v(Matrix const & m, std::vector<pt> p)
{
    std::vector<pt> result;
    pt p_(0,0);
    for (int l = 0; l < m.size(); ++l)
    {
        result.push_back(p_);
    }
    for (int i = 0; i < m.size(); ++i)
        for (int j = 0; j < m[0].size(); ++j)
            result[i].second += m[i][j] * p[j].second;
    return result;
}

std::vector <pt> Train:: coef(Matrix m)
{
    return multiply_v(find_inverse(multiply(transpose(m), m)), multiply_v(transpose(m), i_state));
}

void Train::make_coef()
{
    marks = coef(LS_matrix());
}

std::vector<pt> Train::i_state_() const
{
    return i_state;
}

std::vector<pt> Train::marks_() const
{
    return marks;
}

double Train::LS(double x)
{
    double result  = 0;
    for (int i = 0; i < marks.size(); ++i)
    {
        result += marks[i].second * pow (x,i);
    }
    return result;
}

Train::~Train() {};