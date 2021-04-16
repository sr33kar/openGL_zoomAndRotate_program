/*
 *   Created By Tushar
 *
 */
#ifdef __APPLE__
#include<GLUT/glut.h>
#include<openGL/openGL.h>

#else
#include<GL/glut.h>
#endif

float x1=-2.0,x2=2.0;
float x = 0.7;
float y = 0.7;
static int flag=1;
void initRendering()
{
    glEnable(GL_DEPTH_TEST);
}

void reshape(int w,int h)
{
    glViewport(0,0,w,h);
    
    glMatrixMode(GL_PROJECTION);
    
    glLoadIdentity();
    
    gluPerspective(45,w/h,1,200);
    
}

void keyPressed(int key,int x1,int y1)
{
    if(key==GLUT_KEY_UP)
    {
        x = x * 1.10;
        y = y * 1.10;
        glutPostRedisplay();
    }
    if(key==GLUT_KEY_DOWN)
    {
        x = x * 0.90;
        y = y * 0.90;
        glutPostRedisplay();
    }
}

void drawShape(float x, float y){
    
    glColor3f(0.0, 0.0, 1.0);
    int k = 1;
    
    while(x >= 0.0125){
        if(k%2){
            glBegin(GL_LINES);
            glVertex2f(x, y);
            glVertex2f(x, -y);
            glEnd();
            glBegin(GL_LINES);
            glVertex2f(x, -y);
            glVertex2f(-x, -y);
            glEnd();
            glBegin(GL_LINES);
            glVertex2f(-x, -y);
            glVertex2f(-x, y);
            glEnd();
            glBegin(GL_LINES);
            glVertex2f(-x, y);
            glVertex2f(x, y);
            glEnd();
            //x = x/2;
            //y = y/2;
        }
        else{
            glBegin(GL_LINES);
            glVertex2f(x, 0.0);
            glVertex2f(0.0, -y);
            glEnd();
            glBegin(GL_LINES);
            glVertex2f(0.0, -y);
            glVertex2f(-x, 0.0);
            glEnd();
            glBegin(GL_LINES);
            glVertex2f(-x, 0.0);
            glVertex2f(0.0, y);
            glEnd();
            glBegin(GL_LINES);
            glVertex2f(0.0, y);
            glVertex2f(x, 0.0);
            glEnd();
            x = x/2;
            y = y/2;
        }
        k++;
        
    }
    
    
    
    
//    glVertex3f(-10.0f,-10.0f,0.0f);
//    glVertex3f(-10.0f,10.0f,0.0f);
//    glVertex3f(10.0f,10.0f,0.0f);
//    glVertex3f(10.0f,-10.0f,0.0f);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    
    glLoadIdentity();
    
    //glShadeModel(GL_SMOOTH);
    drawShape(x, y);
    
    glutSwapBuffers();
}

int main(int argc,char **argv)
{
    glutInit(&argc,argv);
    
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    
    glutInitWindowSize(800,800);
    
    glutCreateWindow("QWERTY");
    
    initRendering();
    
    glutDisplayFunc(display);
    
    glutIdleFunc(display);
    
    //glutReshapeFunc(reshape);
    
    glutSpecialFunc(keyPressed);
    
    glutMainLoop();
    
    return(0);
}