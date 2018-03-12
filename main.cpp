
#include "Train.h"
#include "Visualisation.h"

Visualisation v;

void mouse (int button, int state, int x, int y)
{
    v.mouse(button, state, x, y);
}

void mouse_move(int x, int y)
{
    v.mouse_move(x,y);
}

void Display()
{
    v.Display();
}

int main(int argc,char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );
    glutInitWindowSize(1200, 800);
    glutCreateWindow("Approximation");
    glutMouseFunc(mouse);
    glutMotionFunc(mouse_move);
    glutDisplayFunc(Display);
    glutMainLoop();
    return 0;
}
