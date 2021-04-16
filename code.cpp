#include <GL/glut.h>
#include <vector>
#include <bits/stdc++.h>
using namespace std;
#ifdef __APPLE__
#include<GLUT/glut.h>
#include<openGL/openGL.h>

#else
#include<GL/glut.h>
#endif

//float vertices[10000000];//Vertex array
vector<float> vertices;
int VerticesCnt = 0;
void initRendering()
{
    glEnable(GL_DEPTH_TEST);
}
void zoomIn(){
    for(int i=0;i<VerticesCnt;i++){
            vertices[i]=vertices[i]*1.10;
        }
}
void zoomOut(){
    for(int i=0;i<VerticesCnt;i++){
            vertices[i]=vertices[i]*0.90;
        }
}
void keyPressed(int key,int x1,int y1)
{
    if(key==GLUT_KEY_UP)
    {
        zoomIn();
        glutPostRedisplay();
    }
    if(key==GLUT_KEY_DOWN)
    {
        zoomOut();
        glutPostRedisplay();
    }
}

float pow0_1(int a)
{
    float pow = 1.0;
    for(;a>=0;a--)
        pow *= 0.1;
    return pow;
}
float pow10(int a)
{
    float pow = 1.0;
    for(;a>=0;a--)
        pow *= 10.0;
    return pow;
}
float gen_vertex(char input[15])
{
    int temp1,temp2;float v;float multipler=0.0000001;
    if(input[0]=='-')
    {
        temp1=(input[1]-48)*1000000+(input[3]-48)*100000+(input[4]-48)*10000+(input[5]-48)*1000+(input[6]-48)*100+(input[7]-48)*10+(input[8]-48)*1;
        temp2=(input[11]-48)*10+(input[12]-48);
        if(input[10]=='-')
            multipler *= pow0_1(temp2);
        else
            multipler *= pow10(temp2);
        v = (float)temp1 * multipler * (-1.0);
    }
    else
    {
        temp1=(input[0]-48)*1000000+(input[2]-48)*100000+(input[3]-48)*10000+(input[4]-48)*1000+(input[5]-48)*100+(input[6]-48)*10+(input[7]-48)*1;
        temp2=(input[10]-48)*10+(input[11]-48);
        if(input[9]=='-')
            multipler *= pow0_1(temp2);
        else
            multipler *= pow10(temp2);
        v = (float)temp1 * multipler;
    }
    return v;
}//////////////////////////// These three functions return the floating point value of a component of the vertex
void STL_Read()
{
	char word[15];
    freopen("bottle.stl","r",stdin);
    string str;
    getline(cin,str);
    int i;
    char vertex[15];
    for(i=1;;i++)
    {
        cin >> word;
        if(word[0]=='e')
        {
            break;
        }//If endsolid is read, the vertex input is ended
        vertices.push_back(0);
        vertices.push_back(0);
        vertices.push_back(0);
        vertices.push_back(0);
        vertices.push_back(0);
        vertices.push_back(0);
        vertices.push_back(0);
        vertices.push_back(0);
        vertices.push_back(0);
        vertices.push_back(0);
        vertices.push_back(0);
        vertices.push_back(0);
        vertices.push_back(0);
        vertices.push_back(0);
        vertices.push_back(0);
        vertices.push_back(0);
        vertices.push_back(0);
        vertices.push_back(0);
        getline(cin,str);//cin >> word;cin >> word;cin >> word;cin >> word;/////////facet normal
        cin >> word;cin >> word;/////////outer loop
        ///////////////////Read in the first vertex
        cin >> word;
        //cout << i;
        cin >> vertex;vertices[VerticesCnt] = gen_vertex(vertex);
		cin >> vertex;vertices[VerticesCnt+1] = gen_vertex(vertex);
		cin >> vertex;vertices[VerticesCnt+2] = gen_vertex(vertex);
		vertices[VerticesCnt+3] = 0.3f;
		vertices[VerticesCnt+4] = 0.4f;
		vertices[VerticesCnt+5] = 0.5f;//Set vertex color
		VerticesCnt += 6;
		////////////////////////////////Read in the second vertex
		cin >> word;
        cin >> vertex;vertices[VerticesCnt] = gen_vertex(vertex);
		cin >> vertex;vertices[VerticesCnt+1] = gen_vertex(vertex);
		cin >> vertex;vertices[VerticesCnt+2] = gen_vertex(vertex);
		vertices[VerticesCnt+3] = 0.5f;
		vertices[VerticesCnt+4] = 0.5f;
		vertices[VerticesCnt+5] = 1.0f;//Set vertex color
		VerticesCnt += 6;
		///////////////////////////////////////////// read the third Vertex
		cin >> word;
        cin >> vertex;vertices[VerticesCnt] = gen_vertex(vertex);
		cin >> vertex;vertices[VerticesCnt+1] = gen_vertex(vertex);
		cin >> vertex;vertices[VerticesCnt+2] = gen_vertex(vertex);
		vertices[VerticesCnt+3] = 0.5f;
		vertices[VerticesCnt+4] = 0.4f;
		vertices[VerticesCnt+5] = 0.0f;//Set vertex color
		VerticesCnt += 6;
		////////////////////////////////////
		cin >> word;//endloop
		cin >> word;//endfacet

    }
    fclose(stdin);
}
std::vector< int > points;
void mouse( int button, int state, int x, int y )
{
    //cout<<button;
    if(button==3){
        zoomIn();
    }
    else if(button==4){
        zoomOut();
    }
    glutPostRedisplay();
}

void motion( int x, int y )
{
    //zoomOut();
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
    glTranslatef(120.0f,80.0f,0.0f);
    glScalef(2,2,0);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    glBegin( GL_LINES );
    glPointSize(10.0);
    glColor3ub( 255, 0, 255 );
	for(int qiuzili = 0;qiuzili<=VerticesCnt;qiuzili+=6)
	{
		glVertex3f( vertices[qiuzili+0], vertices[qiuzili+1] , vertices[qiuzili+2]); glVertex3f( vertices[qiuzili+6], vertices[qiuzili+7] , vertices[qiuzili+8]);
		glVertex3f( vertices[qiuzili+6], vertices[qiuzili+7] , vertices[qiuzili+8]); glVertex3f( vertices[qiuzili+12], vertices[qiuzili+13] , vertices[qiuzili+14]);
		glVertex3f( vertices[qiuzili+12], vertices[qiuzili+13] , vertices[qiuzili+14]); glVertex3f( vertices[qiuzili+0], vertices[qiuzili+1] , vertices[qiuzili+2]);
	}
    glEnd();

    glutSwapBuffers();
}

int main( int argc, char** argv )
{
    STL_Read();
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
    glutCreateWindow( "B170739CS" );
    glutInitWindowSize(1000, 1000);

    glutMouseFunc( mouse );
    glutMotionFunc( motion );
    glutDisplayFunc( display );
    initRendering();
    
    glutDisplayFunc(display);
    
    glutIdleFunc(display);
    
    //glutReshapeFunc(reshape);
    
    glutSpecialFunc(keyPressed);
    
    glutMainLoop();

    return 0;
}
