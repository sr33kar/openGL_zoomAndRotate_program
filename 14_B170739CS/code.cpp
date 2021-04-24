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

#define PI 3.141592;
vector<float> vertices;
int VerticesCnt = 0;
float orgX=0,orgY=0;
float sumX=0,sumY=0,sumZ=0;
float centroidX=0,centroidY=0,centroidZ=0;
int vertCount=0;
float z_max=0;
float valX=0,valY=0;
float x_1,y_1,z_1,x2,x3,y2,y3,z2,z3;
float theta1=0,theta2=0;

void initRendering()
{
    glEnable(GL_DEPTH_TEST);
}
/*
 * zoomIn function multiplies the coordinates of each vertex to make a bigger projection when scrolled up
 *
*/
void zoomIn(){
    for(int i=0;i<VerticesCnt;i++){
            vertices[i]=vertices[i]*1.10;
        }
}
/*
 * zoomOut function diminishes the coordinates of each vertex to make a smaller projection when scrolled down
 *
*/
void zoomOut(){
    for(int i=0;i<VerticesCnt;i++){
            vertices[i]=vertices[i]*0.90;
        }
}
/*
 * user can rotate the object by using keyboard arrow keys
 * up arrow key increases the angle of projection with X-axis by a value of 5deg on each stroke
 * down arrow key decreases the angle of projection with X-axis by a value of 5deg on each stroke
 * left arrow key decreases the angle of projection with Y-axis by a value of 5deg on each stroke
 * right arrow key increases the angle of projection with Y-axis by a value of 5deg on each stroke
*/
void keyPressed(int key,int x,int y)
{
    if(key==GLUT_KEY_UP)
    {
        theta2+=5;
        glutPostRedisplay();
    }
    if(key==GLUT_KEY_DOWN)
    {
        theta2-=5;
        glutPostRedisplay();
    }
    if(key==GLUT_KEY_LEFT)
    {
        theta1+=5;
        glutPostRedisplay();
    }
    if(key==GLUT_KEY_RIGHT)
    {
        theta1-=5;
        glutPostRedisplay();
    }
}
/*
 *below three functions are used for data processing incase of the STL file having scientific notation
 * two are for making prior part and post part of number (example. 230e-10) to decimal numbers 
 * then the gen_vertex is used to generate the float value by combining the both produced above
*/

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
}
/*
 * reading the stl files
 * i ignored the first line as most of the stl files doesn't have it same( we will lose some important data but now for us it is not needed)
 * read data one after the other vertex and append it to the vertices vector.
 * each 6 consecutive numbers in a stl file refers to a vertex, where first 3 are the coordinates and other 3 corresponds to the color data
 * each 3 consecutive vertices make up a triangle and all these triangles make up the object we have to render.
 * while reading the vertices we also calculate the centroid of the object around which i restricted the movement(rotation). 
 * reading stops when we reach the word that starts with 'e' on the first line of a vertex

*/
void STL_Read(char* s)
{
	char word[15];
    freopen(s,"r",stdin);
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
        getline(cin,str);
        cin >> word;cin >> word;
        //---------------------------------------Read in the first vertex
        cin >> word;
        //cout << i;
        cin >> vertex;vertices[VerticesCnt] = gen_vertex(vertex);
        sumX+=vertices[VerticesCnt];
		cin >> vertex;vertices[VerticesCnt+1] = gen_vertex(vertex);
        sumY+=vertices[VerticesCnt+1];
		cin >> vertex;vertices[VerticesCnt+2] = gen_vertex(vertex);
        sumZ+=vertices[VerticesCnt+2];
        z_max=min(z_max, vertices[VerticesCnt+2]);
		vertices[VerticesCnt+3] = 0.3f;
		vertices[VerticesCnt+4] = 0.4f;
		vertices[VerticesCnt+5] = 0.5f;//Set vertex color
		VerticesCnt += 6;
        vertCount+=1;
		//---------------------------------------Read in the second vertex
		cin >> word;
        cin >> vertex;vertices[VerticesCnt] = gen_vertex(vertex);
        sumX+=vertices[VerticesCnt];
		cin >> vertex;vertices[VerticesCnt+1] = gen_vertex(vertex);
        sumY+=vertices[VerticesCnt+1];
		cin >> vertex;vertices[VerticesCnt+2] = gen_vertex(vertex);
        sumZ+=vertices[VerticesCnt+2];
        z_max=min(z_max, vertices[VerticesCnt+2]);
		vertices[VerticesCnt+3] = 0.3f;
		vertices[VerticesCnt+4] = 0.4f;
		vertices[VerticesCnt+5] = 0.5f;//Set vertex color
		VerticesCnt += 6;
        vertCount+=1;
		//--------------------------------------Read the third Vertex
		cin >> word;
        cin >> vertex;vertices[VerticesCnt] = gen_vertex(vertex);
        sumX+=vertices[VerticesCnt];
		cin >> vertex;vertices[VerticesCnt+1] = gen_vertex(vertex);
        sumY+=vertices[VerticesCnt+1];
		cin >> vertex;vertices[VerticesCnt+2] = gen_vertex(vertex);
        sumZ+=vertices[VerticesCnt+2];
        z_max=min(z_max, vertices[VerticesCnt+2]);
		vertices[VerticesCnt+3] = 0.3f;
		vertices[VerticesCnt+4] = 0.4f;
		vertices[VerticesCnt+5] = 0.5f;//Set vertex color
		VerticesCnt += 6;
        vertCount+=1;
        //------------------------------------
		cin >> word;//endloop
		cin >> word;//endfacet

    }
    centroidX=sumX/vertCount;
    centroidY=sumY/vertCount;
    centroidZ=sumZ/vertCount;
    fclose(stdin);
}
/*
 * mouse function is invoked by glut as we have given 'mouse' to be executed when there is a movement in mouse
 * button gives us which button of the mouse it is beign pressed
 * button:
 *      0- left click, 3- scroll up, 4- scroll down 
 * state:
 *      0- pressed down, 1- released
 * 
 * when the user scrolls up zoomIn function is called and projection get bigger
 * when the user scrolls down zoomOut function is called and projection get smaller
 * when the user tries to drag:
 *      - when the left click is pressed down we record the coordinates of mouse pointer when pressed down
 *      - when the user moves the mouse keeping the left click pressed, we tract the motion using motion()
 *  

*/
void mouse( int button, int state, int x, int y )
{
    if(button==0){
        if(state==0){
                orgX = x;
                orgY = y;
        }
    }
    else if(button==3){
        zoomIn();
    }
    else if(button==4){
        zoomOut();
    }
    glutPostRedisplay();
}
// function to calculate the distance between two 3D points
float distance3(float x1, float y1,float z1, float x2, float y2, float z2)
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0 + pow(z2-z1, 2));
}
// function to calculate the distance between two 2D points
float distance2(float x1,float y1, float x2, float y2){
    return sqrt(pow(x2 - x1, 2)*1.0 + pow(y2 - y1, 2) * 1.0);
}
/*
 * now we have the centroid of the object and the coordinates of mouse when it is first pressed down
 * and now with this motion tracker we get the current coordinates of the mouse
 * method 1: now our job is to rotate the object based on the angle that is formed by the current point, the started point with the centroid
 *      - this seems to be right fit for this but when we find the angles it has to be calculated by the cosine rule and that gives a not-defined (nan) when it encouters a 90deg.
 * methoed 2: project the triangle formed by those 3 points on to XZ plane and YZ plane to get the angles formed in each of the planes and transform the projection by that angle
 *      - this also proved to be wrong as here also there is a chance of getting nan for cosine inverse and the program misbehaves
 * methoed 3: 
 *      - get the difference between x-coordinates and if that is positive increase the transform angle around Y-axis by 1 else decrease by 1
 *      - get the difference between y-coordinates and if that is positive increase the amout of transformation around X-axis by 1 else decrease by 1.
 *      - and also to smoothen the user interface, if the difference between x-coordinates over dominates that of y-coordinates, make the transformation around x-axis to zero
 *      - in the same way if the difference between y-coordinates over dominates that of x-coordinates, make the transformation around y-axis to zero
 * we are using method 3.
 * NOTE: after each call of motion function we call glutPostRedisplay() to re-render by calling the display function
 * 
 * also we put a sleep of 5ms to smoothen the user interaction
*/
void motion( int x, int y )  //--------------insert a bit of delay in rendering to make this work properly
{
    x_1=centroidX;
    y_1=centroidY;
    z_1=centroidZ;
    x2=orgX;
    y2=orgY;
    z3=z_max;
    x3=x*1.0f;
    y3=y*1.0;
    z3=z_max;
    float ang1=0,ang2=0;
    if(x3<x2){
        //ang1*=-1;
        ang1-=1;
    }
    else{
        ang1+=1;
    }
    if(y3<y2){
        ang2-=1;
    }
    else{
        ang2+=1;
    }
    if((abs(x2-x3)/abs(y3-y2))>5){
        ang2=0;
    }
    else if((abs(y2-y3)/abs(x3-x2))>5){
        ang1=0;
    }
    theta1+=ang1;
    theta2+=ang2;
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
    glutPostRedisplay();
}

/*
 * this is called whenever openGL has to render the output image on screen
 * we draw using the GL primitive 'GL_LINES' to draw all the triangles of each 3 consequent points(a,b,c) as lines ab, bc,ca
 * give pink colour for drawing
 * rotate the object projection by theta2 around X-axis and theta1 around Y-axis by using glRotatef() function
 * 
 * NOTE: The angles theta1 and theta2 are generated in motion() function 
 * 
 * 
 * 
*/
void display()
{
    glClearColor( 1, 1, 1, 1 );
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    double w = glutGet( GLUT_WINDOW_WIDTH );
    double h = glutGet( GLUT_WINDOW_HEIGHT );
    glOrtho( 0, w, h, 0, -1, 1 );
    glTranslatef(w/2,h/2,0);  //-----------translate the origin to center of the window each time
    glScalef(2,2,0);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glRotatef(theta2, 1.0, 0.0, 0.0);
    glRotatef(theta1, 0.0, 1.0, 0.0);
    glBegin( GL_LINES );
    glPointSize(10.0);
    glColor3ub( 255, 0, 255 );
	for(int qiuzili = 0;qiuzili<=VerticesCnt;qiuzili+=18)
	{
		glVertex3f( vertices[qiuzili+0], vertices[qiuzili+1] , vertices[qiuzili+2]); glVertex3f( vertices[qiuzili+6], vertices[qiuzili+7] , vertices[qiuzili+8]);
		glVertex3f( vertices[qiuzili+6], vertices[qiuzili+7] , vertices[qiuzili+8]); glVertex3f( vertices[qiuzili+12], vertices[qiuzili+13] , vertices[qiuzili+14]);
		glVertex3f( vertices[qiuzili+12], vertices[qiuzili+13] , vertices[qiuzili+14]); glVertex3f( vertices[qiuzili+0], vertices[qiuzili+1] , vertices[qiuzili+2]);
	}
    glEnd();
    glColor3f(0.0, 0.0, 1.0);
    glPointSize(10.0);
    glBegin(GL_POINTS);
    {
            glVertex3f(0, 0, 0);        //display the origin
    }
    glEnd();
    glutSwapBuffers();
}
//----------------------main function------------------------------------------------------------
/*
 * take input file name by command line argument and pass it to STL_Read function
 * translate the object so that it's centroid moves to origin
 * calling glutInit()
 * setting window size
 * creating window with name "B170739CS"
 * initiating mouse function by using glutMouseFunc
 * initiating motion capture function by using glutMotionFunc
 * initiating display function using glutDisplayFunc
 * start rendering with initRendering function
 * giving display function as the idle function, this runs display function whenever the program is idle
 * starting the main loop 
*/
int main( int argc, char** argv )
{

    STL_Read(argv[1]);
    for(int i=0;i<VerticesCnt;i+=6){  //-----translate the object to origin
        vertices[i]-=centroidX;
        vertices[i+1]-=centroidY;
        vertices[i+2]-=centroidZ;
    }
    centroidX=0;
    centroidY=0;
    centroidZ=0;
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
    glutInitWindowSize(800, 500);
    glutCreateWindow( "B170739CS" );

    glutMouseFunc( mouse );
    glutMotionFunc( motion );
    glutDisplayFunc( display );
    initRendering();
    
    glutDisplayFunc(display);
    
    glutIdleFunc(display);
    
    glutSpecialFunc(keyPressed);
    
    glutMainLoop();

    return 0;
}
