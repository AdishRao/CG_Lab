#include <math.h>
#include<stdlib.h>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include<stdio.h>
#define PI 3.1416

GLsizei winWidth = 600, winHeight=600;
GLfloat xwcMin =0.0, xwcMax = 130.0;
GLfloat ywcMin =0.0, ywcMax = 130.0;
int choice=0;
typedef struct wcPt3D
{
    GLfloat x,y,z;
}wcPt3D;

void bino(GLint n, GLint *c)
{
    GLint k,j;
    for(k=0;k<=n;k++)
    {
        c[k]=1;
        for(j=n;j>=k+1;j--)
        {
            c[k]*=j;
        }
        for(j=n-k;j>=2;j--)
        {
            c[k]/=j;
        }
    }
}
void computeBezPt(GLfloat u, wcPt3D *bezPt, GLint nCtrlPts,wcPt3D *ctrlPts, GLint *c)
{
    GLint k, n=nCtrlPts-1;
    GLfloat bezBlendFcn;
    bezPt->x=bezPt->y=bezPt->z=0.0;
    for(k=0;k<nCtrlPts;k++)
    {
        bezBlendFcn = c[k]*pow(u,k)*pow(1-u,n-k);
        bezPt->x+=ctrlPts[k].x*bezBlendFcn;
        bezPt->y+=ctrlPts[k].y*bezBlendFcn;
        bezPt->z+=ctrlPts[k].z*bezBlendFcn;
    }
}

void bezier(wcPt3D *ctrlPts, GLint nCtrlPts,GLint nBezCurvePts)
{
    wcPt3D bezCurvePt;
    GLfloat u;
    GLint *c,k;
    c = new GLint [nCtrlPts];
    bino(nCtrlPts-1,c);
    glBegin(GL_LINE_STRIP);
        for(k=0;k<=nBezCurvePts;k++)
        {
            u=GLfloat(k)/GLfloat(nBezCurvePts);
            computeBezPt(u,&bezCurvePt,nCtrlPts,ctrlPts,c);
            glVertex2f(bezCurvePt.x,bezCurvePt.y);
        }
    glEnd();
    delete []c;
}

void displayFcn()
{
    glClear(GL_COLOR_BUFFER_BIT);
    if(choice==2||choice==3)
    {
        GLint nCtrlPts=4,nBezCurvePts=20;
        static float theta=0;
        wcPt3D ctrlPts[4]=
        {
            {20,100,0},
            {30,110,0},
            {50,90,0},
            {60,100,0}
        };
        ctrlPts[1].x+=10*sin(theta*PI/180.0);
        ctrlPts[1].y+=5*sin(theta*PI/180.0);
        ctrlPts[2].x-=10*sin((theta+30)*PI/180.0);
        ctrlPts[2].y-=10*sin((theta+30)*PI/180.0);
        ctrlPts[3].x-=4*sin(theta*PI/180.0);
        ctrlPts[3].y+=sin((theta-30)*PI/180.0);
        if(choice==3) theta+=1.0;
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1.0,1.0,1.0);
        glPointSize(5);
        glPushMatrix();
        glLineWidth(5);
        glColor3f(255/255.0,153.0/255.0,51.0/255.0);
        for(int i=0;i<8;i++)
        {
            glTranslatef(0,-0.8,0);
            bezier(ctrlPts,nCtrlPts,nBezCurvePts);
        }
        glColor3f(1,1,1);
        for(int i=0;i<8;i++)
        {
            glTranslatef(0,-0.8,0);
            bezier(ctrlPts,nCtrlPts,nBezCurvePts);
        }
        glColor3f(19.0/255.0,136.0/255.0,8.0/255.0);
        for(int i=0;i<8;i++)
        {
            glTranslatef(0,-0.8,0);
            bezier(ctrlPts,nCtrlPts,nBezCurvePts);
        }
        glPopMatrix();
        glColor3f(0.7,0.5,0.3);
        glLineWidth(5);
        glBegin(GL_LINES);
        glVertex2f(20,100);
        glVertex2f(20,40);
        glEnd();
        glFlush();
    }
    glutPostRedisplay();
    glutSwapBuffers();
}
void demo_menu(int id)
{
    switch(id)
    {
        case 1: exit(0);
                break;
        case 2: choice=2;
                break;
        case 3: choice=3;
                break;
    }
    glutPostRedisplay();
}

void winReshapeFun(GLint newWidth,GLint newHeight)
{
    glViewport(0,0,newWidth,newHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(xwcMin,xwcMax,ywcMin,ywcMax);
    glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowPosition(50,50);
    glutInitWindowSize(winWidth,winHeight);
    glutCreateWindow("FLAGGGGGY");
    int sub_menu = glutCreateMenu(demo_menu);
    glutAddMenuEntry("Draw",2);
    glutAddMenuEntry("Start animation",3);
    glutAddMenuEntry("Stop",2);
    glutCreateMenu(demo_menu);
    glutAddMenuEntry("Exit",1);
    glutAddSubMenu("Flag",sub_menu);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    choice=0;
    glClearColor(1,1,1,0);
    glutDisplayFunc(displayFcn);
    glutReshapeFunc(winReshapeFun);
    glutMainLoop();
}