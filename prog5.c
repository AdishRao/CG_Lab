#include <stdio.h>
#include <stdbool.h>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>

#define outcode int
#define true 1
#define false 0
double xmin=50,ymin=50,xmax=100,ymax=100;
double xvmin=200,yvmin=200,xvmax=300,yvmax=300;
float X0,Y0,X1,Y1;
int n;
const int RIGHT = 2;
const int LEFT = 1;
const int TOP = 8;
const int BOTTOM = 4;

outcode computecode(double x, double y);

void cohensutterland(double x0,double y0,double x1, double Y1)
{
    outcode outcode0,outcode1,outcodeout;
    bool accept = false;
    bool done = false;
    outcode0 = computecode(x0,y0);
    outcode1 = computecode(x1,Y1);
    do
    {
        if(!(outcode0|outcode1))
        {
            accept=true;
            done=true;
        }
        else if(outcode0&outcode1)
        {
            done = true;
        }
        else
        {
            double x,y;
            outcodeout=outcode0?outcode0:outcode1;
            if(outcodeout&TOP)
            {
                x=x0+(ymax-y0)*(x1-x0)/(Y1-y0);
                y=ymax;
            }
            else if(outcodeout&BOTTOM)
            {
                x=x0+(ymin-y0)*(x1-x0)/(Y1-y0);
                y=ymin;
            }
            else if(outcodeout&RIGHT)
            {
                y=y0+(xmax-x0)*(Y1-y0)/(x1-x0);
                x=xmax;
            }
            else
            {
                y=y0+(Y1-y0)*(xmin-x0)/(x1-x0);
                x=xmin;
            }
            if(outcodeout==outcode0)
            {
                x0=x;
                y0=y;
                outcode0=computecode(x0,y0);
            }
            else
            {
                x1=x;
                Y1=y;
                outcode1=computecode(x1,Y1);
            }
        }
    } while (!done);
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(xvmin,yvmin);
        glVertex2f(xvmax,yvmin);
        glVertex2f(xvmax,yvmax);
        glVertex2f(xvmin,yvmax);
    glEnd();
    if(accept)
    {
        double sx = (xvmax-xvmin)/(xmax-xmin);
        double sy = (yvmax-yvmin)/(ymax-ymin);
        double vx0 = xvmin +(x0-xmin)*sx;
        double vy0 = yvmin +(y0-ymin)*sy;
        double vx1 = xvmin +(x1-xmin)*sx;
        double vY1 = yvmin +(Y1-ymin)*sy;
        glColor3f(0.0,0.0,1.0);
        glBegin(GL_LINES);
            glVertex2d(vx0,vy0);
            glVertex2d(vx1,vY1);
        glEnd();
    }
}

outcode computecode(double x,double y)
{
    outcode code=0;
    if (y>ymax)  code|=TOP;
    else if (y<ymin)    code|=BOTTOM;
    if (x>xmax) code|=RIGHT;
    else if (x<xmin)    code|=LEFT;
    return code;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_LINES);
        glVertex2d(X0,Y0);
        glVertex2d(X1,Y1);
    glEnd();
    glColor3f(0.0,0.0,1.0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(xmin,ymin);
        glVertex2f(xmax,ymin);
        glVertex2f(xmax,ymax);
        glVertex2f(xmin,ymax);
    glEnd();
    cohensutterland(X0,Y0,X1,Y1);
    glFlush();
}

void myInit()
{
    glClearColor(1.0,1.0,1.0,1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,499.0,0.0,499.0);
}

void main(int argc, char ** argv)
{
    printf("Enter line coordinates");
    scanf("%f%f%f%f",&X0,&Y0,&X1,&Y1);
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Prog 5 - Adish");
    glutDisplayFunc(display);
    myInit();
    glutMainLoop();
}