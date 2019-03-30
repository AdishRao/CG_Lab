#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <math.h>

void circlecaller(float cx, float cy, float rad)
{
    glBegin(GL_LINE_LOOP);
    for(int i=0;i<3000;i++)
    {
        double angle = 2*3.14*i/3000;
        double x = cos(angle)*10;
        double y = sin(angle)*10;
        glVertex2d(x+100,y+100);
    }
    glEnd();
}

void drawlines()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,0.0,0.0);
    circlecaller(180.0,15.0,15.0);
    glFlush();
}

void init()
{
    glClearColor(1.0,1.0,1.0,1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0,200.0,0.0,150.0);

}


int main(int argc, char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(50,100);
    glutInitWindowSize(500,500);
    glutCreateWindow("test");
    init();
    glutDisplayFunc(drawlines);
    glutMainLoop();
}
