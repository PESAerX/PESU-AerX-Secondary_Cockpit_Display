#include<iostream>
#include<GL/glut.h>
#include<GL/freeglut.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<sstream>

#define PI 3.141592            // defining PI = 3.141592

using namespace std;

// calls InitialDisplay and renders the static object
void Display(void);
// Drawing all the lines and displaying texts in specific co-ordinates and is later used by KeyBoardFunction
void InitialDisplay(void);
// drawing white shade
void DrawWhiteShade(void);
// drawing green shade
void DrawGreenShade(void);
// drawing yellow shade
void DrawYellowShade(void);
// drawing lines around the airspeed
void DrawLines(void);
// displays all the texts required in the AIRSPEED
void DisplayAllTexts(void);
// takes in a string and returns an integer
int StringToInteger(const char *);
// takes in the string,x-coordinate,y-coordinate and displays it in those specified coordinates
void DisplayIncomingText(string,float,float);
// when keyboard event happens , this function is called
void KeyBoardFunction(int,int,int);
// displays the needle 
void DisplayNeedle(void);

// setting number of vertices for 180 degrees , for 360 degrees it would be double the number
int NumOfVertices = 20;
// setting the Radius of AIRSPEED 
float Radius = 0.25;


void Display()
{
	glClearColor(0.0,0.0,0.0,0.0); // setting the window background to black
	glClear(GL_COLOR_BUFFER_BIT);  // using GL_COLOR_BUFFER_BIT mode of displaying
	glMatrixMode(GL_PROJECTION);   // using PROJECTION matrix
	glLoadIdentity();              // loading the identity matrix
	
	InitialDisplay();	       // calling InitialDisplay function
	
	DisplayNeedle();
	
	glFlush();	// display onto the screen
}


void InitialDisplay()
{
	glColor3f(0.0,0.0,0.0);     // setting the color to be black 
	
	glBegin(GL_POLYGON);        // start to draw a black circle
	
	glVertex2f(0,0);	    	
	for(int i=0;i<=NumOfVertices;i++)
	{       
		glVertex2f(Radius*cosf(i*PI/NumOfVertices),Radius*sinf(i*PI/NumOfVertices));
	}
	
	glEnd(); // ends the drawn black circle
	
	DrawWhiteShade();
	
	DrawGreenShade();
	
	DrawYellowShade();
	
	DrawLines();
	
	DisplayAllTexts();
 	
}
 
 // draws white shades
 void DrawWhiteShade()
{
 	//white shade from 45 to 85 
	glColor3f(1.0,1.0,1.0);      // setting color of the white shade
	glBegin(GL_QUAD_STRIP);	     // begin to draw the white shade
	for(int i=(3*NumOfVertices/2)+6;i<=(3*NumOfVertices/2)+15;i++)  // setting the specific i values
	{       
	// joining these two points to make a line
		glVertex2f((Radius+0.01)*cosf(i*PI/NumOfVertices),(Radius+0.01)*sinf(i*PI/NumOfVertices));       
		glVertex2f((Radius+0.01)*cosf((i+1)*PI/NumOfVertices),(Radius+0.01)*sinf((i+1)*PI/NumOfVertices));

	// joining these two points to make a line
		glVertex2f((Radius-0.01)*cosf(i*PI/NumOfVertices),(Radius-0.01)*sinf(i*PI/NumOfVertices));
		glVertex2f((Radius-0.01)*cosf((i+1)*PI/NumOfVertices),(Radius-0.01)*sinf((i+1)*PI/NumOfVertices));
	}
	glEnd(); // finally the white shade is ready
	
	//white shade from 85 to 130 . Same procedure but the i values are different
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_QUAD_STRIP);
	
	for(int i=(3*NumOfVertices/2)-3;i<=(3*NumOfVertices/2)+4;i++)
	{       
		glVertex2f((Radius+0.025)*cosf(i*PI/NumOfVertices),(Radius+0.025)*sinf(i*PI/NumOfVertices));
		glVertex2f((Radius+0.025)*cosf((i+1)*PI/NumOfVertices),(Radius+0.025)*sinf((i+1)*PI/NumOfVertices));
		
		glVertex2f((Radius-0.01)*cosf(i*PI/NumOfVertices),(Radius-0.01)*sinf(i*PI/NumOfVertices));
		glVertex2f((Radius-0.01)*cosf((i+1)*PI/NumOfVertices),(Radius-0.01)*sinf((i+1)*PI/NumOfVertices));
	}
	glEnd();
 
}
 
 
void DrawGreenShade()
{
	// green shade
	glColor3f(0.0,0.75,0.0);
	glBegin(GL_QUAD_STRIP);
	for(int i=(3*NumOfVertices/2)-3;i<(2*NumOfVertices)+(NumOfVertices/4)-1;i++)
	{       
		glVertex2f((Radius-0.01)*cosf(i*PI/NumOfVertices),(Radius-0.01)*sinf(i*PI/NumOfVertices));
		glVertex2f((Radius-0.01)*cosf((i+1)*PI/NumOfVertices),(Radius-0.01)*sinf((i+1)*PI/NumOfVertices));
		
		glVertex2f((Radius-0.05)*cosf(i*PI/NumOfVertices),(Radius-0.05)*sinf(i*PI/NumOfVertices));
		glVertex2f((Radius-0.05)*cosf((i+1)*PI/NumOfVertices),(Radius-0.05)*sinf((i+1)*PI/NumOfVertices));
	}
	glEnd();
}
 
 
void DrawYellowShade()
{
 	// yellow shade
	glColor3f(1.0,1.0,0.0);
	glBegin(GL_QUAD_STRIP);
	for(int i=(3*NumOfVertices/2)-9;i<=(3*NumOfVertices/2)-4;i++)
	{       
		glVertex2f((Radius-0.01)*cosf(i*PI/NumOfVertices),(Radius-0.01)*sinf(i*PI/NumOfVertices));
		glVertex2f((Radius-0.01)*cosf((i+1)*PI/NumOfVertices),(Radius-0.01)*sinf((i+1)*PI/NumOfVertices));
		
		glVertex2f((Radius-0.05)*cosf(i*PI/NumOfVertices),(Radius-0.05)*sinf(i*PI/NumOfVertices));
		glVertex2f((Radius-0.05)*cosf((i+1)*PI/NumOfVertices),(Radius-0.05)*sinf((i+1)*PI/NumOfVertices));
		
	}
	glEnd();
}
 
 
void DrawLines()
{
 	int count = 0; // to keep track of the size of the line
	glLineWidth(1.0); // setting the line width to 1.
	
	glBegin(GL_LINES);

	for(int i=(NumOfVertices/4)+8;i<=(2*NumOfVertices)+(NumOfVertices/4);i++)
	{      
		// draw a big line
	if(count % 2==0 && i!=(3*NumOfVertices/4)+6)
	{	
			glColor3f(1.0,1.0,1.0);
			glVertex2f((Radius+0.05)*cosf(i*PI/NumOfVertices),(Radius+0.05)*sinf(i*PI/NumOfVertices));
			glVertex2f((Radius-0.07)*cosf(i*PI/NumOfVertices),(Radius-0.07)*sinf(i*PI/NumOfVertices));
	}
	else{
		// draw a small line
		if(i!=(3*NumOfVertices/4)+6)
		   {
			glColor3f(1.0,1.0,1.0);
			glVertex2f((Radius+0.03)*cosf(i*PI/NumOfVertices),(Radius+0.03)*sinf(i*PI/NumOfVertices));
			glVertex2f((Radius-0.04)*cosf(i*PI/NumOfVertices),(Radius-0.04)*sinf(i*PI/NumOfVertices));
		   }
		// draw the red line
		else
		   {
			
			glColor3f(1.0,0.0,0.0);
			glVertex2f((Radius+0.05)*cosf(i*PI/NumOfVertices),(Radius+0.05)*sinf(i*PI/NumOfVertices));
			glVertex2f((Radius-0.07)*cosf(i*PI/NumOfVertices),(Radius-0.07)*sinf(i*PI/NumOfVertices));
		   }
	   }
		count++; // incrementing count
	}
	
	glEnd();
}
 
 
void DisplayAllTexts()
{
 	string textToDisplay = "40"; // initial text to be displayed
 	
 	// display numbers in specific co-ordinates
 	int IntegerFromString = 0;
    for(int i=(3*NumOfVertices/8)+1;i<(4*NumOfVertices/3)-1;i+=2)
      {       glColor3f(1.0,1.0,1.0);
	DisplayIncomingText(textToDisplay,-(Radius-0.1)*cosf(2*(i-0.53)*PI/NumOfVertices),(Radius-0.1)*sinf(2*(i-0.53)*PI/NumOfVertices)); 
	
		IntegerFromString = StringToInteger(textToDisplay.c_str()); 
	
		ostringstream IntegerToString;
		IntegerFromString+=20;   // incrementing converted string to int by 20.
		IntegerToString <<IntegerFromString;
		textToDisplay = IntegerToString.str(); // converting incremented integer by 20 to string.
      }
	
	DisplayIncomingText("KNOTS",-0.03,-0.09); // display text knots and airspeed in specific co-ordinates
	DisplayIncomingText("AIRSPEED",-0.05,0.03);
}
 
 
 // converts string to int and returns the integer
  int StringToInteger(const char *str)
{
  int result;
  int puiss;

  result = 0;
  puiss = 1;
  while (('-' == (*str)) || ((*str) == '+'))
    {
      if (*str == '-')
        puiss = puiss * -1;
      str++;
    }
  while ((*str >= '0') && (*str <= '9'))
    {
      result = (result * 10) + ((*str) - '0');
      str++;
    }
  return (result * puiss);
}


// displays text txt in the co-ordinates of(x,y)
void DisplayIncomingText(string textToBeDisplayed,float x,float y)
{
	
	glRasterPos2f(x,y);	// specifying the coordinates on the window
	// glutBitmapString(font,(const unsigned char*)text)
	glutBitmapString(GLUT_BITMAP_HELVETICA_10, (const unsigned char*)textToBeDisplayed.c_str()); 
	
}


float angle=0.0f; // setting angle of the needle 
void KeyBoardFunction(int PressedKey,int x,int y)
{

	if(PressedKey==GLUT_KEY_UP && angle<=0 && angle>=-332)
	{
		
		glClear(GL_COLOR_BUFFER_BIT);
		glLoadIdentity();
		glMatrixMode(GL_PROJECTION);
		glEnable(GL_COLOR_LOGIC_OP);  // enabling logic operation
		
		angle--;           //decrementing angle to rotate needle clock-wise
		
		glLogicOp(GL_OR);	// performing logical OR operation
		glTranslatef(0.0f,0.0f,0.0f);	// translating it to 0,0 co-ordinate  
		glRotatef(angle,0.0f,0.0f,1.0f);    // rotating the needle to "angle" degrees
		glScalef(1.0,1.0,1.0);	// giving the size of the object in each direction

		DisplayNeedle();	// displays needle
		
		glTranslatef(0.0f,0.0f,0.0f); // translating it to 0,0 co-ordinate 
		glRotatef((360-angle),0.0f,0.0f,1.0f); // rotating outer display by "360-angle" degrees(rotates in anticlockwise direction)
		glScalef(1.0,1.0,1.0);  // giving the size of the object in each direction
	
		InitialDisplay();
			
	}
	
	if(PressedKey==GLUT_KEY_DOWN && angle<0 && angle>=-333 )
	{	
		glClear(GL_COLOR_BUFFER_BIT);
		glLoadIdentity();
		glMatrixMode(GL_PROJECTION);
		glEnable(GL_COLOR_LOGIC_OP);	
		
		angle++;    // incrementing angle to rotate in anti-clockwise direction
		
		glLogicOp(GL_OR);
		glTranslatef(0.0f,0.0f,0.0f);
		glRotatef(angle,0.0f,0.0f,1.0f);
		glScalef(1.0,1.0,1.0);

		DisplayNeedle();
		
		glTranslatef(0.0f,0.0f,0.0f);
		glRotatef((360-angle),0.0f,0.0f,1.0f);
		glScalef(1.0,1.0,1.0);
			
			InitialDisplay();	
			
			
	}
		glFlush();
}


void DisplayNeedle()
{
	
	glLineWidth(4.0);	       // setting width of the needle pointer
	glBegin(GL_POLYGON);	       // start to draw a Polygon
	
	glColor3f(1.0,1.0,1.0);        // specifying the color of the needle
				  
	glVertex2f(0,0);
	glVertex2f(0.015,0.015);
				      // Specifying all the coordinates
	glVertex2f(0.015,0.015);
	glVertex2f(0,0.27);
	
	glVertex2f(0,0.27);
	glVertex2f(-0.015,0.015);
	
	glVertex2f(-0.015,0.015);
	glVertex2f(0,0);
	
	glEnd();		     // ends the drawn polygon	
}


int main(int argc,char **argv)
{
	glutInit(&argc,argv);  
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_SINGLE);
	glutInitWindowSize(800,800);
	glutCreateWindow("Window");
	glutDisplayFunc(Display);
	glutSpecialFunc(KeyBoardFunction);
	glutInitWindowPosition(0,0);
	glutMainLoop();
}
