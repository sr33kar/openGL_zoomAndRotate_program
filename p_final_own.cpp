#include<GL/freeglut.h>
#include<GL/gl.h>
#include<bits/stdc++.h>
using namespace std;


//global varaibles
vector<float> points;
char title[] = "B170820CS";
int total_points = 0;


void initGL() {
   glClearColor(1.0f,1.0f,1.0f,0.0f); // Set background color to black and opaque
   glClearDepth(1.0f);                   // Set background depth to farthest
   glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
   glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
   glShadeModel(GL_SMOOTH);   // Enable smooth shading
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}
void renderFunction() {
	//printf("%d",total_points);
	//glClearColor(r,g,b,a);    //already put in initGL()
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glColor3f(0.0,0.0,1.0);   //this is for the points
	//glPointSize(5);			//this is for the points
	double w = GLUT_WINDOW_WIDTH;
	double h = GLUT_WINDOW_HEIGHT;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, w, h,0, -1, 1);
	//glTranslatef(1.5f, 0.0f, -7.0f);
    glScalef(10,10,0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    
	glBegin(GL_LINES);
		glColor3ub(0,0,200);
		int j = 0;
		glVertex3f(points[j],points[j+1],points[j+2]);
		glVertex3f(points[j+3],points[j+4],points[j+5]);
		glVertex3f(points[j+3],points[j+4],points[j+5]);
		glVertex3f(points[j+6],points[j+7],points[j+8]);
		glVertex3f(points[j+6],points[j+7],points[j+8]);
		glVertex3f(points[j],points[j+1],points[j+2]);
		/*for(int j=0;j<total_points;j+=9)
		{
			//cout<<points[j]<<" "<<points[j+1]<<" "<<points[j+2]<<endl;
			glVertex3f(points[j],points[j+1],points[j+2]);
			glVertex3f(points[j+3],points[j+4],points[j+5]);
			glVertex3f(points[j+3],points[j+4],points[j+5]);
			glVertex3f(points[j+6],points[j+7],points[j+8]);
			glVertex3f(points[j+6],points[j+7],points[j+8]);
			glVertex3f(points[j],points[j+1],points[j+2]);
		}*/
	glEnd();
	glutSwapBuffers();
}
void readInput() {
	char temp[15];
	string str;
	char content[15];
	char *end;
	freopen("bottle.txt","r",stdin);
	getline(cin,str);
	end=(char*)calloc(30,sizeof(char));
	while(true) {
		cin>>temp;
		if(temp[0]=='e') break;
		getline(cin,str);
		getline(cin,str);
		cin>>temp; //vertex1
		cin>>content;//first coordinate of vertex1
		points.push_back((float)strtod(content,&end)); //strtod is a function to convert string to double
		cin>>content;//second coordinate of vertex1
		points.push_back((float)strtod(content,&end));
		cin>>content;//third coordinate of vertex1
		points.push_back((float)strtod(content,&end));
		total_points+=3;
		cin>>temp; //vertex2
		cin>>content; //first coordinate of vertex2
		points.push_back((float)strtod(content,&end));
		cin>>content;//second coordinate of vertex2
		points.push_back((float)strtod(content,&end));
		cin>>content;//third coordinate of vertex2
		points.push_back((float)strtod(content,&end));
		total_points+=3;
		cin>>temp; //vertex3
		cin>>content; //first coordinate of vertex3
		points.push_back((float)strtod(content,&end));
		cin>>content;//second coordinate of vertex3
		points.push_back((float)strtod(content,&end));
		cin>>content;//third coordinate of vertex3
		points.push_back((float)strtod(content,&end));
		total_points+=3;
		getline(cin,str);//new line character
		getline(cin,str);//endloop
		getline(cin,str);//endfacet
	}
	fclose(stdin);
	/*
	FILE* wr = fopen("cube_out.txt","w+");
	for(int i=0;i<total_points;i=i+0) {
		fprintf(wr,"%f %f %f\n",points[i],points[i+1],points[i+2]);
		i+=3;
		fprintf(wr,"%f %f %f\n",points[i],points[i+1],points[i+2]);
		i+=3;
		fprintf(wr,"%f %f %f\n",points[i],points[i+1],points[i+2]);
		i+=3;
		fprintf(wr,"\n\n");
	}
	fclose(wr);*/
}
int main( int argc, char** argv )
{

    /*STL_Read();
    for(int i=0;i<VerticesCnt;i+=6){
        vertices[i]-=centroidX;
        vertices[i+1]-=centroidY;
        vertices[i+2]-=centroidZ;
        
    }
    centroidX=0;
    centroidY=0;
    centroidZ=0;*/
    readInput();
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE);
 	glutInitWindowSize(640,480);
 	glutInitWindowPosition(100,100);
	glutCreateWindow(title);
    //glutMouseFunc( mouse );
    //glutMotionFunc( motion );
    glutDisplayFunc(renderFunction);
    
    
    //glutDisplayFunc(display);
    //glutIdleFunc(renderFunction);    
    //glutSpecialFunc(keyPressed);
    initGL();
    glutMainLoop();

    return 0;
}
