#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <math.h>

GLfloat input[3][3]={
    {100,150,250},
    {100,250,100},
    {1,1,1}
};
GLfloat result[3][3];
GLfloat m[3][3];
GLfloat xf,yf;
GLfloat theta;

void calM()
{
    m[0][0] = cos(theta);
    m[0][1] = -sin(theta);
    m[0][2] = xf*(1-cos(theta)) + yf*sin(theta);
    m[1][0] = sin(theta);
    m[1][1] = cos(theta);
    m[1][2] = yf*(1-cos(theta)) - xf*sin(theta);
    m[2][0] = 0;
    m[2][1] = 0;
    m[2][2] = 1;
}
void mulmat()
{
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            result[i][j] = 0;
            for(int k=0;k<3;k++)
            {
                result[i][j]+= m[i][k]*input[k][j];
            }
        }
    }
}
void calres()
{
  calM();
  mulmat();
}

void drawtriangle(GLfloat input[3][3], int i)
{
    glBegin(GL_TRIANGLES);
        glVertex2f(input[0][0],input[1][0]);
        glVertex2f(input[0][1],input[1][1]);
        glVertex2f(input[0][2],input[1][2]);
    glEnd();
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,0.0,0.0);
    drawtriangle(input,1);
    calres();
    glColor3f(0.0,1.0,0.0);
    drawtriangle(result,2);
    glFlush();
}

void myinit()
{
    gluOrtho2D(0.0,500.0,0.0,500.0);
    glMatrixMode(GL_PROJECTION);
    glClearColor(1.0,1.0,1.0,1.0);
}

void main(int argc,char **argv)
{
    printf("Enter xf,yf,theta\n");
    scanf("%f%f%f",&xf,&yf,&theta);
    theta*=(3.14)/180; 
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500,500);
    glutCreateWindow("Prog 2");
    myinit();
    glutDisplayFunc(display);
    glutMainLoop();
}