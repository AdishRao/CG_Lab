#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <stdlib.h>

float x1,x2,x3,x4,y1,y2,y3,y4;
int choice = 0;

void edgedetect (float x1,float y1,float x2,float y2, int *le, int *re)
{
    float mx,x,temp;
    int i;
    if((y2-y1)<0)
    {
        temp = y1;
        y1 = y2;
        y2 = temp;
        temp = x1;
        x1 = x2;
        x2 = temp;
    }
    if((y2-y1)!=0)
    {
        mx = (x2-x1)/(y2-y1);
    }
    else
    {
        mx = x2-x1;
    }
    x=x1;
    for(i=y1;i<=y2;i++)
    {   printf("x %f! ",x);
        printf("le %d:: re %d\n",le[i],re[i]);
        if(x<(float)le[i])
        {
            le[i]=(int)x;
        }
        if(x>(float)re[i])
        {
            re[i]=(int)x;
        }
        x+=mx;
    }
}

void drawpixel(int x,int y)
{
    glColor3f(1.0,0.0,1.0);
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
    glFlush();
}

void scanfill(float x1,float y1,float x2,float y2,float x3,float y3,float x4,float y4)
{
    int le[500],re[500];
    int i,y;
    for(i=0;i<500;i++)
    {
        le[i]=500;
        re[i]=0;
    }
    printf("x1,y1,x2,y2\n");
    edgedetect(x1,y1,x2,y2,le,re);
    printf("x2,y2,x3,y3\n");
    edgedetect(x2,y2,x3,y3,le,re);
    printf("x3,y3,x4,y4\n");
    edgedetect(x3,y3,x4,y4,le,re);
    printf("x4,y4,x1,y1\n");
    edgedetect(x4,y4,x1,y1,le,re);
    for(y=0;y<500;y++)
    {
        if(le[y]<=re[y])
        {
            for(i=(int)le[y];i<=(int)re[y];i++)
            {
                drawpixel(i,y);
            }
        }
    }
}

void display()
{
    x1=200.0, y1=200.0, x2=100.0, y2=300.0, x3=200.0, y3=400.0, x4=300.0, y4=300.0;
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,1.0,0.0);
    if (choice==1) 
    {
        glBegin(GL_LINE_LOOP);
            glVertex2f(x1,y1);
            glVertex2f(x2,y2);
            glVertex2f(x3,y3);
            glVertex2f(x4,y4);
        glEnd();
    }
    if(choice==2)
    {
        scanfill(x1,y1,x2,y2,x3,y3,x4,y4);
    }
    glFlush();
}

void myinit()
{
    glClearColor(1.0,1.0,1.0,1.0);
    glColor3f(1.0,0.0,0.0);
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,500.0,0.0,500.0);
}

void mymenu(int id)
{
    glClear(GL_COLOR_BUFFER_BIT);
    switch(id)
    {
        case 1: exit(0);
        case 2: choice=1;
                break;
        case 3: choice=2;
                break;
    }
    printf("%d\n",choice);
    glutPostRedisplay();
}

void main(int argc, char ** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500,500);
    glutCreateWindow("Prog 5 - Adish");
    myinit();
    glutDisplayFunc(display);
    glutCreateMenu(mymenu);
    glutAddMenuEntry("Exit",1);
    glutAddMenuEntry("Outter edge",2);
    glutAddMenuEntry("Fill Polygon",3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutMainLoop();
}