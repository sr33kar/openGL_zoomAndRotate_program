#include <GL/glut.h>
#include <vector>

std::vector< int > points;
void mouse( int button, int state, int x, int y )
{

    points.push_back( x );
    points.push_back( y );
    glutPostRedisplay();
}

void motion( int x, int y )
{
    points.push_back( x );
    points.push_back( y );
    glutPostRedisplay();
}

void display()
{
    glClearColor( 1, 1, 1, 1 );
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    double w = glutGet( GLUT_WINDOW_WIDTH );
    double h = glutGet( GLUT_WINDOW_HEIGHT );
    glOrtho( 0, w, h, 0, -1, 1 );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    glBegin( GL_POINTS );
    glPointSize(10.0);
    glColor3ub( 0, 0, 0 );
    for( size_t i = 0; i < points.size(); i += 2 )
    {
        glVertex2i( points[i+0], points[i+1] );
    }
    glEnd();

    glutSwapBuffers();
}

int main( int argc, char** argv )
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );

    glutCreateWindow( "GLUT" );
    glutInitWindowSize(500, 500);
    glutMouseFunc( mouse );
    glutMotionFunc( motion );
    glutDisplayFunc( display );
    glutMainLoop();
    return 0;
}
