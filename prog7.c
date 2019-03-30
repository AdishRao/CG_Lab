#include <OpenGL/gl.h>
#include <GLUT/glut.h>


GLfloat v[4][3]= {
    {0.0,0.0,1.0},
    {0.0,0.942,-0.33},
    {-0.816,-0.47,-.033},
    {0.816,-0.47,-0.33}
};
int n;

void triangle(GLfloat *a,GLfloat *b,GLfloat *c)
{
    glBegin(GL_POLYGON);
        glVertex3fv(a);
        glVertex3fv(b);
        glVertex3fv(c);
    glEnd();
}

void divide_triangle(GLfloat *a,GLfloat *b,GLfloat *c, int m)
{
    GLfloat v1[3], v2[3], v3[3]; //Mid points of one side [3] for x,y,z
    int j;
    if(m>0)
    {
        for(j=0;j<3;j++) v1[j] = (a[j]+b[j])/2; //v1 x,y,z val calc
        for(j=0;j<3;j++) v2[j] = (a[j]+c[j])/2; //v2 x,y,z val calc
        for(j=0;j<3;j++) v3[j] = (b[j]+c[j])/2; //v3 x,y,z val calc
        divide_triangle(a,v1,v2,m-1);
        divide_triangle(c,v2,v3,m-1);
        divide_triangle(b,v3,v1,m-1);
    }
    else (triangle(a,b,c));
}

void tetrahedron(int m)
{
    glColor3f(1.0,0.0,0.0);
    divide_triangle(v[0],v[1],v[2],m);
    glColor3f(0.0,1.0,0.0);
    divide_triangle(v[3],v[2],v[1],m);
    glColor3f(0.0,0.0,1.0);
    divide_triangle(v[0],v[3],v[1],m);
    glColor3f(0.0,0.0,0.0);
    divide_triangle(v[0],v[2],v[3],m);
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    tetrahedron(n);
    glFlush();
}

void myinit()
{
    glOrtho(-2.0,2.0,-2.0,2.0,-10.0,10.0);
    //gluLookAt(2.0,2.0,2.0,10.0,10.0,10.0,2.0,2.0,2.0);
    glClearColor(1.0,1.0,1.0,1.0);
}

void main(int argc,char **argv)
{
    printf("No of divisions\n");
    scanf("%d",&n);
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(500,500);
    glutCreateWindow("Prog 7");
    glutDisplayFunc(display);
    myinit();
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
}