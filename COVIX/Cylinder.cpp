#include "Cylinder.h"
#include "Globals.h"
#include <vector>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Window.h"
#include "math.h"

Cylinder::Cylinder() : Geode()
{
	//
}

Cylinder::~Cylinder()
{
	//Delete any dynamically allocated memory/objects here
}

void Cylinder::LoadTexture(){
	head = Texture("head.ppm");
}

Cylinder::Cylinder(int n)
{
	float h = 1;
	height = 2;
	float r = 1;
	float theta = 0.0;
	//the least tessellation factor for the cylinder we will allow is 3
	if (n < 3)
		n = 3;
	
	//make some fixed points and a container for the circumference points
	fixedPT = Vector3(0, 2, 0);
	fixedPB = Vector3(0, 0, 0);

	//get the angle interval
	float angle = 3.1415926 / n;
	Vector3 n1 = Vector3(r*sin(theta), fixedPB[1], r*cos(theta));
	circumPoints.push_back(n1);
	//begin with the top and bottom
	for (float theata = 0; theta < 2 * 3.1415926; theta += 3.1415926 / n)
	{
		//create 2 circumference points and add it to the container
		
		Vector3 n2 = Vector3(r*sin(theta + angle), fixedPB[1], r*cos(theta + angle));

		circumPoints.push_back(n2);
	}

}

		//iterate through to make the top and the bottom
	//while i < n
	//	create 2 triangles using the fixed points and the circumference points

	//	//now make squares for each circumference point all the way down the side
	//for each face of the cylinder
	//	grab 2 circumference points
	//while i < m
	//	create a square made up of 2 triangles



void Cylinder::draw(Matrix4 C)
{

	//Apply the material properties
	//From here forward anything drawn will be drawn with these material
	

	//Se the OpenGL Matrix mode to ModelView (used when drawing geometry)
	glMatrixMode(GL_MODELVIEW);

	//Push a save state onto the matrix stack, and multiply in the toWorld matrix
	glPushMatrix();
	glMultMatrixf(&C.m[0][0]);
	glColor3f(1, 1, 1);
	glDisable(GL_LIGHTING);
	//Make cube!
	//Note: The glBegin, and glEnd should always be as close to the glNormal/glVertex calls as possible
	//These are special calls that 'freeze' many internal states of OpenGL.
	//Once the glBegin state is active many of the calls made to OpenGL (like glMultMatrixf) will be IGNORED!
	//As a good habit, only call glBegin just before you need to draw, and call end just after you finish
	head.bind();
	for (float i = 0; i <36 ; i = i + 1){
		glBegin(GL_TRIANGLES);
		//glColor3f(0, 1, 1);
		glVertex3f(circumPoints[i][0], circumPoints[i][1],circumPoints[i][2]);
		glVertex3f(circumPoints[i+1][0], circumPoints[i+1][1], circumPoints[i+1][2]);
		glVertex3f(fixedPB[0], fixedPB[1], fixedPB[2]);

		glVertex3f(circumPoints[i][0], circumPoints[i][1]+height, circumPoints[i][2]);
		glVertex3f(circumPoints[i + 1][0], circumPoints[i + 1][1]+height, circumPoints[i + 1][2]);
		glVertex3f(fixedPT[0], fixedPB[1]+height, fixedPT[2]);
		glEnd();

	
		glBegin(GL_QUADS);
		//glColor3f(1, 1, 0);
		
		glTexCoord2f(i/36, 1);
		glVertex3f(circumPoints[i][0], circumPoints[i][1], circumPoints[i][2]);
		glTexCoord2f((i + 1) / 36, 1);
		glVertex3f(circumPoints[i + 1][0], circumPoints[i + 1][1], circumPoints[i + 1][2]);
		glTexCoord2f((i+1) /36, 0);
		glVertex3f(circumPoints[i + 1][0], circumPoints[i + 1][1] + height, circumPoints[i + 1][2]);
		glTexCoord2f(i / 36, 0);
		glVertex3f(circumPoints[i][0], circumPoints[i][1] + height, circumPoints[i][2]);
		glEnd();
		
	}
	head.unbind();


	glEnable(GL_LIGHTING);
	glPopMatrix();
}
