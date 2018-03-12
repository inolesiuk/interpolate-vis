#include <cmath>

#include "Visualisation.h"

Visualisation::Visualisation()
{
    tapped = false;
    m_tapped = false;
}

Visualisation::Visualisation(Visualisation const & v)
{
    if (&v != this)
    {
        m = v.m_();
        lagrange = v.lagrange_();
        least_mean = v.least_mean_();
        tapped = v.tapped_();
        m_tapped = v.m_tapped_();
    }
}

Visualisation const & Visualisation::operator = (Visualisation const & v)
{
    if (this != &v)
    {
        m = v.m_();
        lagrange = v.lagrange_();
        least_mean = v.least_mean_();
        tapped = v.tapped_();
        m_tapped = v.m_tapped_();
    }
    return *this;
}

void Visualisation::Display()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear( GL_COLOR_BUFFER_BIT );       //clear display
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    draw_axes();
    if (m_tapped)
    {
        show_legend();
    }
    if (tapped)
    {
        draw_button(0.21, 0.2, 0.4);
        tapped = false;
    }
    else
    {
        draw_button(0.8, 0.8, 0.8);
    }

    const double w = glutGet( GLUT_WINDOW_WIDTH );
    const double h = glutGet( GLUT_WINDOW_HEIGHT );
    gluOrtho2D(0.0, w, 0.0, h);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glPointSize(5.0f);
    glLineWidth(3.0f);

    glEnable( GL_LINE_SMOOTH );
    glEnable( GL_POLYGON_SMOOTH );
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
    glHint( GL_POLYGON_SMOOTH_HINT, GL_NICEST );
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < lagrange.size(); ++i)
    {
        glColor3f(0.3, 0.9, 0.1);
        Point x;
        x.xy(lagrange[i].first, lagrange[i].second);
        glLineWidth(10.0f);
        glVertex2i(x.win_x(), x.win_y());
    }
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(3.0f);
    for (int i = 0; i < least_mean.size(); ++i)
    {
        glColor3f(0.9, 0.1, 0.4);
        Point x;
        x.xy(least_mean[i].first, least_mean[i].second);
        glVertex2i(x.win_x(), x.win_y());
    }
    glEnd();
    glLineWidth(1.0f);
    glBegin(GL_POINTS);
    auto it = m.begin();
    for (it; it != m.end(); ++it)
    {
        int x = it -> second.win_x();
        int y = it -> second.win_y();
        glColor3f(0.3, 0.3, 0.3);
        glVertex2i(x, h - y);
    }

    glEnd();

    glFlush();
}

void Visualisation::draw_triangles(double x1, double x2, double y, bool choose)
{
    glBegin( GL_TRIANGLES );
    glColor3f(0, 0, 0);
    if (choose)
    {
        glVertex2f(x1, 0.8);
        glVertex2f(x2, 0.8);
        glVertex2f(-0.8, y);
    }
    else
    {
        glVertex2f(0.8, x1);
        glVertex2f(0.8, x2);
        glVertex2f(y, -0.8);
    }
    glEnd();
}

void Visualisation::draw_axes()
{
    glColor3f(0.0, 0.0, 0.0);  //draw lines
    glBegin(GL_LINES);
    glVertex3f(0.8, -0.8, 0.0);
    glVertex3f(-0.8, -0.8, 0);
    glVertex3f(-0.8, 0.8, 0);
    glVertex3f(-0.8,-0.8,0);
    glEnd();

    draw_triangles(-0.785, -0.815, 0.835, false);
    draw_triangles(-0.79, -0.81, 0.86, true);

    int x_lines = 7;
    int y_lines = 10;
    double x = -0.6;
    double y = -0.655;
    double y_step = 0.145;
    double x_step = 0.2;
    double x_height = 0.03;
    double y_height = 0.02;

    markdown(x_lines, x, x_step, x_height, true);
    markdown(y_lines, y, y_step, y_height, false);

    numbers(x, x_step, x_lines, true);
    numbers(y, y_step, y_lines, false);
}

void Visualisation::draw_button(double x, double y, double z)
{
    glBegin( GL_QUADS );
    glColor3d(x, y, z);
    glVertex3f(0.65,0.75,0.2);
    glColor3d(x, y, z);
    glVertex3f(0.9, 0.75, 0.2);
    glColor3d(x, y, z);
    glVertex3f(0.9, 0.85, 0.2);
    glColor3d(x, y, z);
    glVertex3f(0.65, 0.85, 0.2);
    glEnd();
    glColor3f(0, 0, 0);
    glLineWidth(1.0f);
    glBegin(GL_LINES);
    glVertex3f(0.9, 0.75, 0.2);
    glVertex3f(0.9, 0.85, 0.2);;
    glVertex3f(0.65, 0.75, 0.2);
    glVertex3f(0.65, 0.85, 0.2);
    glVertex3f(0.65, 0.75, 0.2);
    glVertex3f(0.9, 0.75, 0.2);
    glVertex3f(0.65, 0.85, 0.2);
    glVertex3f(0.9, 0.85, 0.2);
    glEnd();

    printtext(0.73, 0.8, "Start");
}

void Visualisation::printtext(double x, double y, std::string String)
{
    glRasterPos2f(x, y);
    for (int i = 0; i < String.size(); ++i)
    {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, String[i]);
    }
}

void Visualisation::numbers(double start, double step, int lines, bool horiz)
{
    for (int i = 0; i < lines; ++i)
    {
        if (horiz)
        {
            printtext(start, -0.9, std::to_string(i + 1) );
            start += step;
        }
        else
        {
            printtext(-0.9, start, std::to_string(i + 1) );
            start += step;
        }
    }

}

void Visualisation:: markdown(int lines, double start, double step, double height, bool horiz)
{
    glBegin(GL_LINES);
    for (int i = 0; i < lines; ++i)
    {
        if (horiz)
        {
            glVertex3f(start, -0.8 + height, 0);
            glVertex3f(start, -0.8 - height, 0);
            start += step;
        }
        else
        {
            glVertex3f(-0.8 + height, start, 0);
            glVertex3f(-0.8 - height, start, 0);
            start += step;
        }
    }
    glEnd();
}

void Visualisation:: mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (norm_y(y) < - 0.75 && norm_y(y) > -0.85 && norm_x(x) > 0.65 && norm_x(x) < 0.9)
        {
            if (!m_tapped && !m.empty())
            {
                Train t(m);
                t.make_coef();
                plot(t);
                tapped = true;
                m_tapped = true;
            }
        }
        int temp = pos(x);
        if (y_is_bounded(y))
            if (1 <= temp && temp <= 5)
            {
                if (m_tapped)
                {
                    m.clear();
                    lagrange.clear();
                    least_mean.clear();
                    m_tapped = false;
                }
                auto i = m.find(temp);
                Point p;
                p.xy(inv_pos(temp), norm_y(y));
                if (i != m.end())
                {
                    i -> second = p;
                }
                else
                {
                    m.insert(std::pair<int,Point> (temp,p));
                }
                last_point = temp;
            }
    }
    glutPostRedisplay();
}

double Visualisation::norm_y(int y)
{
    return 2 / (double) glutGet( GLUT_WINDOW_HEIGHT ) * y - 1;
}

double Visualisation::norm_x(int x)
{
    return 2 / (double) glutGet( GLUT_WINDOW_WIDTH ) * x - 1;
}

bool Visualisation::y_is_bounded(int y)
{
    double norm = norm_y(y);
    return -0.8 + 0.145 <= norm && norm <= 0.8;
}

void Visualisation::mouse_move(int x, int y)
{
    if (y_is_bounded(y))
    {
        m.find(last_point) -> second.set_y(norm_y(y));
        glutPostRedisplay();
    }
}

void Visualisation::plot(Train& train)
{
    double x = -0.8;
    double delta_x = 0.01;
    while (x <= 0.8)
    {
        double y = -(train.lagrange_interpolate((x + 0.8) / 0.2) * 0.145 + 0.8);
        if (y > -1 && y < 0.8)
        {
            lagrange.push_back(pt(x, y));
        }
        x += delta_x;
    }

    x = -0.8;
    while (x <= 0.8)
    {
        double y = -(train.LS((x + 0.8) / 0.2) * 0.145 + 0.8);
        if (y > -1 && y < 0.8)
        {
            least_mean.push_back(pt(x, y));
        }
        x += delta_x;
    }
}

int Visualisation::pos (int x)
{
    return (int)round((norm_x(x) + 0.8) / 0.2);
}

double Visualisation::inv_pos (int x)
{
    return x * 0.2 - 0.8;
}

void Visualisation::show_legend()
{
    glColor3f(0.9, 0.1, 0.4);
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glVertex3f(0.65, 0.55, 0);
    glVertex3f(0.9, 0.55, 0);
    glColor3f(0.3, 0.9, 0.1);
    glVertex3f(0.65, 0.35, 0.2);
    glVertex3f(0.9, 0.35, 0.2);
    glEnd();
    std::string s1 = "Lagrange";
    std::string s2 = "LSQ";
    glRasterPos2f(0.7, 0.4);
    for (int i = 0; i < s1.size(); ++i)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s1[i]);
    }
    glColor3f(0.9, 0.1, 0.4);
    glRasterPos2d(0.7, 0.6);

    for (int i = 0; i < s2.size(); ++i)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s2[i]);
    }
}

Visualisation::~Visualisation() {}
