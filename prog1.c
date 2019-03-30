#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <stdio.h>

int x1,x2,y1,y2;

void myInit()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0,0.0,0.0,1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0,500,0,500);
}

void draw_pixel(int x, int y)
{
    glPointSize(10);
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
    sleep(1);
    glFlush();
}

void draw_line(int x1, int x2, int y1, int y2)
{
    int dx,dy,i,pk;
    int incx,incy,inc1,inc2;
    int x,y;
    dx=x2-x1;
    dy=y2-y1;
    if(dx<0) dx = -dx;
    if(dy<0) dy = -dy;
    incx = 1;
    if(x2<x1) incx = -1; //For left to right scanning
    incy = 1;
    if(y2<y1) incy = -1; //For left to right scanning
    x=x1;
    y=y1;
    if(dx>dy) //Slope is less than 1
    {
        draw_pixel(x,y);
        pk = 2*(dy)-dx;
        inc1 = 2*(dy-dx);
        inc2 = 2*dy;
        for(i=0;i<dx;i++)
        {
            if(pk>=0)
            {
                y+=incy;
                pk+=inc1;
            }
            else
            {
                pk+=inc2;
            } 
            x+=incx;
            draw_pixel(x,y);
        }
    }
    else //Slope is greater than 1
    {
        draw_pixel(x,y);
        pk = 2*(dx)-dy;
        inc1 = 2*(dx-dy);
        inc2 = 2*dx;
        for(i=0;i<dy;i++)
        {
            if(pk>=0)
            {
                x+=incx;
                pk+=inc1;
            }
            else
            {
                pk+=inc2;
            } 
            y+=incy;
            draw_pixel(x,y);
        }
    }     
}

void myDisplay()
{
    draw_line(x1,x2,y1,y2);
}

void main(int argc,char **argv)
{
    printf("Enter (x1,y1,x2,y2)\n");
    scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(0,0);
    glutCreateWindow("prog 1");
    myInit();
    glutDisplayFunc(myDisplay);
    glutMainLoop();
}