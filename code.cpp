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
#define PI 3.141592;
vector<float> vertices;
int VerticesCnt = 0;
float orgX=0,orgY=0;
float rotX=0,rotY=0;
float preRotX=0,preRotY=0;
float sumX=0,sumY=0,sumZ=0;
float centroidX=0,centroidY=0,centroidZ=0;
int vertCount=0;
float z_max=0;
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
void keyPressed(int key,int x,int y)
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
        sumX+=vertices[VerticesCnt];
		cin >> vertex;vertices[VerticesCnt+1] = gen_vertex(vertex);
        sumY+=vertices[VerticesCnt+1];
		cin >> vertex;vertices[VerticesCnt+2] = gen_vertex(vertex);
        sumZ+=vertices[VerticesCnt+2];
        z_max=max(z_max, vertices[VerticesCnt+2]);
		vertices[VerticesCnt+3] = 0.3f;
		vertices[VerticesCnt+4] = 0.4f;
		vertices[VerticesCnt+5] = 0.5f;//Set vertex color
		VerticesCnt += 6;
        vertCount+=1;
		////////////////////////////////Read in the second vertex
		cin >> word;
        cin >> vertex;vertices[VerticesCnt] = gen_vertex(vertex);
        sumX+=vertices[VerticesCnt];
		cin >> vertex;vertices[VerticesCnt+1] = gen_vertex(vertex);
        sumY+=vertices[VerticesCnt+1];
		cin >> vertex;vertices[VerticesCnt+2] = gen_vertex(vertex);
        sumZ+=vertices[VerticesCnt+2];
        z_max=max(z_max, vertices[VerticesCnt+2]);
		vertices[VerticesCnt+3] = 0.3f;
		vertices[VerticesCnt+4] = 0.4f;
		vertices[VerticesCnt+5] = 0.5f;//Set vertex color
		VerticesCnt += 6;
        vertCount+=1;
		///////////////////////////////////////////// read the third Vertex
		cin >> word;
        cin >> vertex;vertices[VerticesCnt] = gen_vertex(vertex);
        sumX+=vertices[VerticesCnt];
		cin >> vertex;vertices[VerticesCnt+1] = gen_vertex(vertex);
        sumY+=vertices[VerticesCnt+1];
		cin >> vertex;vertices[VerticesCnt+2] = gen_vertex(vertex);
        sumZ+=vertices[VerticesCnt+2];
        z_max=max(z_max, vertices[VerticesCnt+2]);
		vertices[VerticesCnt+3] = 0.3f;
		vertices[VerticesCnt+4] = 0.4f;
		vertices[VerticesCnt+5] = 0.5f;//Set vertex color
		VerticesCnt += 6;
        vertCount+=1;
		////////////////////////////////////
		cin >> word;//endloop
		cin >> word;//endfacet

    }
    centroidX=sumX/vertCount;
    centroidY=sumY/vertCount;
    centroidZ=sumZ/vertCount;
    fclose(stdin);
}
std::vector< int > points;
bool isFirstDown=true;
void mouse( int button, int state, int x, int y )
{
    cout<<button<<" "<<state<<endl;
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
float valX=0,valY=0;
float x_1,y_1,z_1,x2,x3,y2,y3,z2,z3;
float a,b,c,d;
float angle;
float sa,sb,sc;
float angle1;
float a1,a2,a3,b1,b2,b3,c1,c2,c3,d1,d2,d3;
float p1,p2,p3,p4,q1,q2,q3,q4,r1,r2,r3,r4;
float k1,k2,k3;
float theta1=0,theta2=0;
float distance(float x1, float y1,float z1, float x2, float y2, float z2)
{
    // Calculating distance
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0 + pow(z2-z1, 2));
}
float distance2(float x1,float y1, float x2, float y2){
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0);
}
void motion( int x, int y )
{
    x_1=centroidX;
    y_1=centroidY;
    z_1=centroidZ;
    x2=orgX;
    y2=orgY;
    z3=10;
    x3=x;
    y3=y;
    z3=10;
    a=(y2-y2)*(z3-z_1)-(y3-y_1)*(z2-z_1);
    b=(z2-z_1)*(x3-x_1)-(x2-x_1)*(z3-z_1);
    c=(x2-x_1)*(y3-y_1)-(x3-x_1)*(y2-y2);
    d= -1*(a*x_1 +b*y_1 + c*z_1);


    sa=distance(x_1,y_1,z_1, x2,y2,z2);
    sb= distance(x_1,y_1,z_1, x3,y3,z3);
    sc= distance(x2,y2,z2, x3,y3,z3);

    float sa1= distance2(x_1,z_1,x2,z2);
    float sb1= distance2(x_1,z_1, x3,z3);
    float sc1= distance2(x2,z2, x3,z3);
    float ang1= acos( (sa1*sa1 +sb1*sb1 - (sc1*sc1))/(2*sa1*sb1));
    if(x3<x2){
        ang1*=-1;
    }
    theta1+=ang1*180/PI;

    float sa2= distance2(x_1,y_1,x2,y2);
    float sb2= distance2(x_1,y_1, x3,y3);
    float sc2= distance2(x2,y2, x3,y3);
    float ang2= acos( (sa2*sa2 +sb2*sb2 - (sc2*sc2))/(2*sa2*sb2));
    if(y3<y2){
        ang2*=-1;
    }
    theta2+=ang2*180/PI;

    angle = acos( (sa*sa +sb*sb - (sc*sc))/(2*sa*sb));  //----------sign matters here
    float L= sqrt(a*a+b*b+c*c);
    float V= sqrt(b*b+c*c);
    float cosTheta =cos(angle);
    float sinTheta =sin(angle);
    if(!(x3>x2 && y3==y2 || x3==x2 && y3>y2 || x3>x2 && y3>y2)){
        cosTheta*=-1;
        sinTheta*=-1;
        angle*=-1;
    }
    angle1+= angle*180/PI;

    cout<<angle<<" "<<(sa*sa +sb*sb - (sc*sc))/(2*sa*sb)<<endl;
    //angle=angle;
    
    

    a1= (V/L)*cosTheta; a2= (c/V)*sinTheta- ((a*b)/(V*L))*cosTheta; a3=(b/V)*sinTheta - ((a*c)/(V*L))*cosTheta;
    b1= (V/L)*sinTheta; a2= -1*(c/V)*cosTheta- ((a*b)/(V*L))*sinTheta; a3=-1*(b/V)*cosTheta - ((a*c)/(V*L))*cosTheta;
    c1= (a/L); c2= (b/L); c3= (c/L);
    d1= -1*(a1*x_1+a2*y_1+a3*z_1);
    d2= -1*(b1*x_1+b2*y_1+b3*z_1);
    d3= -1*(c1*x_1+c2*y_1+c3*z_1);
    
    cout<< a<<" "<<b<<" "<<c<<" "<<a1<<" "<<b1<<" "<<c1<<" "<<d1<<" "<<d2<<" "<<d3<<L<<" "<<V<<endl;
    p1= (a1*V+a*c1)/L; p2= (a2*V+a*c2)/L; p3= (a3*V+a*c3)/L; p4= -1*((d1*V)/L+(d2*a)/L-x_1);
    q1= ((-1*a*b*a1)/(V*L)+(c*b1)/V+(b*c1)/L); q2= ((-1*a*b*a2)/(V*L)+(c*b2)/V+(b*c2)/L); q3= ((-1*a*b*a2)/(V*L)+(c*b3)/V+(b*c3)/L); q4= ((a*b*d1)/(V*L)-(c*d2)/V-(b*d3)/L+y_1);
    r1= ((-1*a*c*a1)/(V*L)-(b*b1)/V+(c*c1)/L); r2= ((-1*a*c*a2)/(V*L)-(b*b2)/V+(c*c2)/L); r3= ((-1*a*c*a3)/(V*L)-(b*b3)/V+(c*c3)/L); r4= ((a*c*d1)/(V*L)+(b*d2)/V-(c*d3)/L+z_1);

    /*for(int i=0;i<VerticesCnt;i+=6){
        k1=vertices[i];
        k2=vertices[i+1];
        k3=vertices[i+2];
        vertices[i]= p1*k1+p2*k2+p3*k3+p4;
        vertices[i+1]= q1*k1+q2*k2+q3*q3+q4;
        vertices[i+2]= r1*k1+r2*k2+r3*k3+r4;
        
    }*/

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
    glTranslatef(800.0f,500.0f,0);
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
            glVertex3f(0, 0, 0);
    }
    glEnd();
    glutSwapBuffers();
}

int main( int argc, char** argv )
{

    STL_Read();
    for(int i=0;i<VerticesCnt;i+=6){
        vertices[i]-=centroidX;
        vertices[i+1]-=centroidY;
        vertices[i+2]-=centroidZ;
        
    }
    centroidX=0;
    centroidY=0;
    centroidZ=0;
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
