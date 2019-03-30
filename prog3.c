#include <OpenGL/gl.h>
#include <GLUT/glut.h>

GLfloat verticies[8][3] = { 
    {-1.0,-1.0,1.0}, {-1.0,1.0,1.0}, {1.0,1.0,1.0}, {1.0,-1.0,1.0}, {-1.0,-1.0,-1.0}, {-1.0,1.0,-1.0}, {1.0,1.0,-1.0},{1.0,-1.0,-1.0}
};
GLfloat color[][3] = {
    {0.0,0.0,0.0},{1.0,0.0,0.0},{1.0,1.0,0.0},{1.0,0.0,1.0},{0.0,1.0,1.0},{1.0,1.0,1.0},{0.0,1.0,0.0},{0.0,0.0,1.0}
};

void polygon(int a,int b,int c,int d)
{
    glBegin(GL_POLYGON);
        glColor3fv(color[a]);
        glVertex3fv(verticies[a]);
        glColor3fv(color[b]);
        glVertex3fv(verticies[b]);
        glColor3fv(color[c]);
        glVertex3fv(verticies[c]);
        glColor3fv(color[d]);
        glVertex3fv(verticies[d]);
    glEnd();
}
void colorcube()
{
    polygon(0,3,2,1);
    polygon(2,3,7,6);
    polygon(0,4,7,3);
    polygon(1,2,6,5);
    polygon(4,5,6,7);
    polygon(0,1,5,4);
}

static GLfloat theta[] = {0.0,0.0,0.0};
static GLint axis = 2;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0,1.0,1.0,1.0);
    glLoadIdentity();
    glRotatef(theta[0],1.0,0.0,0.0);
    glRotatef(theta[1],0.0,1.0,0.0);
    glRotatef(theta[2],0.0,0.0,1.0);
    colorcube();
    glFlush();
    glutSwapBuffers();
}

void spinCube()
{
    theta[axis]+=1.0;
    if(theta[axis]>360.0)
        theta[axis]-=360.0;
    glutPostRedisplay();
}

void mouse(int btn,int state, int x, int y)
{
    if(btn==GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        axis = 0;
    if(btn==GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
        axis = 1;
    if(btn==GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
        axis = 2;    
}

void myReshape(int w,int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(w<=h)
        glOrtho(-2.0,2.0,-2.0*(GLfloat)h/(GLfloat)w,2.0*(GLfloat)h/(GLfloat)w,-10.0,10.0);
    else
        glOrtho(-2.0*(GLfloat)w/(GLfloat)h,2.0*(GLfloat)w/(GLfloat)h,-2.0,2.0,-10.0,10.0);
    glMatrixMode(GL_MODELVIEW);
    
}

void keypressed(unsigned char key, int x, int y)
{
    axis = 1;
}

void main(int argc, char ** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(500,500);
    glutCreateWindow("Prog 3 - Adish");
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glutIdleFunc(spinCube);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keypressed);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
}