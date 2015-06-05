#include "Cube.h"
#include "Globals.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include "Window.h"
#include "math.h"



Cube::Cube(float size) : Drawable()
{
    this->size = size;

}

Cube::Cube(float size, float alpha) : Drawable()
{
	this->size = size;
	this->alpha = alpha;

}

Cube::~Cube()
{
    //Delete any dynamically allocated memory/objects here
}


void Cube::draw(DrawData& data)
{
    float halfSize = size/2.0;
    
    //Apply the material properties
    //From here forward anything drawn will be drawn with these material
	//if (Window::light_type == 0)
	//	material.apply();
	//else{
		//Color white(0.0, 1.0, 1.0, alpha);
		//glColor4fv(white.ptr());
	//}

		

    //Se the OpenGL Matrix mode to ModelView (used when drawing geometry)
    glMatrixMode(GL_MODELVIEW);
    
    //Push a save state onto the matrix stack, and multiply in the toWorld matrix
    glPushMatrix();
    glMultMatrixf(toWorld.ptr());
	material.apply();
	float temp = 20.0;
	for (float i = 0; i < temp; i++){
		//GLUquadricObj *quadratic;
		//quadratic = gluNewQuadric();
		//gluQuadricNormals(quadratic, GLU_SMOOTH);
		float a = 1-i/temp;
		double s = 5 + 5 * (i / temp);
		glColor4f(0.0, 1.0, 1.0, a);
		//glutSolidCube(s);
		glutSolidSphere(s, 100, 100);
	}



    ////Make cube!
    ////Note: The glBegin, and glEnd should always be as close to the glNormal/glVertex calls as possible
    ////These are special calls that 'freeze' many internal states of OpenGL.
    ////Once the glBegin state is active many of the calls made to OpenGL (like glMultMatrixf) will be IGNORED!
    ////As a good habit, only call glBegin just before you need to draw, and call end just after you finish
    //glBegin(GL_QUADS);
    //
    //// Draw front face:
    //glNormal3f(0.0, 0.0, 1.0);
    //glVertex3f(-halfSize,  halfSize,  halfSize);
    //glVertex3f( halfSize,  halfSize,  halfSize);
    //glVertex3f( halfSize, -halfSize,  halfSize);
    //glVertex3f(-halfSize, -halfSize,  halfSize);
    //
    //// Draw left side:
    //glNormal3f(-1.0, 0.0, 0.0);
    //glVertex3f(-halfSize,  halfSize,  halfSize);
    //glVertex3f(-halfSize,  halfSize, -halfSize);
    //glVertex3f(-halfSize, -halfSize, -halfSize);
    //glVertex3f(-halfSize, -halfSize,  halfSize);
    //
    //// Draw right side:
    //glNormal3f(1.0, 0.0, 0.0);
    //glVertex3f( halfSize,  halfSize,  halfSize);
    //glVertex3f( halfSize,  halfSize, -halfSize);
    //glVertex3f( halfSize, -halfSize, -halfSize);
    //glVertex3f( halfSize, -halfSize,  halfSize);
    //
    //// Draw back face:
    //glNormal3f(0.0, 0.0, -1.0);
    //glVertex3f(-halfSize,  halfSize, -halfSize);
    //glVertex3f( halfSize,  halfSize, -halfSize);
    //glVertex3f( halfSize, -halfSize, -halfSize);
    //glVertex3f(-halfSize, -halfSize, -halfSize);
    //
    //// Draw top side:
    //glNormal3f(0.0, 1.0, 0.0);
    //glVertex3f(-halfSize,  halfSize,  halfSize);
    //glVertex3f( halfSize,  halfSize,  halfSize);
    //glVertex3f( halfSize,  halfSize, -halfSize);
    //glVertex3f(-halfSize,  halfSize, -halfSize);
    //
    //// Draw bottom side:
    //glNormal3f(0.0, -1.0, 0.0);
    //glVertex3f(-halfSize, -halfSize, -halfSize);
    //glVertex3f( halfSize, -halfSize, -halfSize);
    //glVertex3f( halfSize, -halfSize,  halfSize);
    //glVertex3f(-halfSize, -halfSize,  halfSize);
    //
    //glEnd();
    
    //The above glBegin, glEnd, glNormal and glVertex calls can be replaced with a glut convenience function
    //glutSolidCube(size);
    
    //Pop the save state off the matrix stack
    //This will undo the multiply we did earlier
    glPopMatrix();
}

void Cube::drawTex(DrawData& data)
{
	//float halfSize = size / 2.0;

	////Apply the material properties
	////From here forward anything drawn will be drawn with these material

	////Color white(1.0, 1.0, 1.0);
	////glColor3fv(white.ptr());

	////Se the OpenGL Matrix mode to ModelView (used when drawing geometry)
	//glMatrixMode(GL_MODELVIEW);

	////Push a save state onto the matrix stack, and multiply in the toWorld matrix
	//glPushMatrix();
	//glMultMatrixf(toWorld.ptr());


	////Make cube!
	////Note: The glBegin, and glEnd should always be as close to the glNormal/glVertex calls as possible
	////These are special calls that 'freeze' many internal states of OpenGL.
	////Once the glBegin state is active many of the calls made to OpenGL (like glMultMatrixf) will be IGNORED!
	////As a good habit, only call glBegin just before you need to draw, and call end just after you finish
	//
	//front.bind();
	//glBegin(GL_QUADS);
	//// Draw front face:
	//glNormal3f(0.0, 0.0, -1.0);
	//glTexCoord2f(0, 1); glVertex3f(-halfSize, halfSize, halfSize);
	//glTexCoord2f(1, 1); glVertex3f(halfSize, halfSize, halfSize);
	//glTexCoord2f(1, 0); glVertex3f(halfSize, -halfSize, halfSize);
	//glTexCoord2f(0, 0); glVertex3f(-halfSize, -halfSize, halfSize);
	//glEnd();
	//front.unbind();

	//left.bind();
	//glBegin(GL_QUADS);
	//// Draw left side:
	//glNormal3f(1.0, 0.0, 0.0);
	//glTexCoord2f(0, 1); glVertex3f(-halfSize, halfSize, halfSize);
	//glTexCoord2f(1, 1); glVertex3f(-halfSize, halfSize, -halfSize);
	//glTexCoord2f(1, 0); glVertex3f(-halfSize, -halfSize, -halfSize);
	//glTexCoord2f(0, 0); glVertex3f(-halfSize, -halfSize, halfSize);
	//glEnd();
	//left.unbind();

	//right.bind();
	//glBegin(GL_QUADS);
	//// Draw right side:
	//glNormal3f(-1.0, 0.0, 0.0);
	//glTexCoord2f(0, 1); glVertex3f(halfSize, halfSize, halfSize);
	//glTexCoord2f(1, 1); glVertex3f(halfSize, halfSize, -halfSize);
	//glTexCoord2f(1, 0); glVertex3f(halfSize, -halfSize, -halfSize);
	//glTexCoord2f(0, 0); glVertex3f(halfSize, -halfSize, halfSize);
	//glEnd();
	//right.unbind();

	//back.bind();
	//// Draw back face:
	//glBegin(GL_QUADS);
	//glNormal3f(0.0, 0.0, 1.0);
	//glTexCoord2f(0, 1); glVertex3f(-halfSize, halfSize, -halfSize);
	//glTexCoord2f(1, 1); glVertex3f(halfSize, halfSize, -halfSize);
	//glTexCoord2f(1, 0); glVertex3f(halfSize, -halfSize, -halfSize);
	//glTexCoord2f(0, 0); glVertex3f(-halfSize, -halfSize, -halfSize);
	//glEnd();
	//back.unbind();

	//top.bind();
	//glBegin(GL_QUADS);
	//// Draw top side:
	//glNormal3f(0.0, -1.0, 0.0);
	//glTexCoord2f(0, 1); glVertex3f(-halfSize, halfSize, halfSize);
	//glTexCoord2f(1, 1); glVertex3f(halfSize, halfSize, halfSize);
	//glTexCoord2f(1, 0); glVertex3f(halfSize, halfSize, -halfSize);
	//glTexCoord2f(0, 0); glVertex3f(-halfSize, halfSize, -halfSize);
	//glEnd();
	//top.unbind();

	//base.bind();
	//glBegin(GL_QUADS);
	//// Draw bottom side:
	//glNormal3f(0.0, 1.0, 0.0);
	//glTexCoord2f(0, 1); glVertex3f(-halfSize, -halfSize, -halfSize);
	//glTexCoord2f(1, 1); glVertex3f(halfSize, -halfSize, -halfSize);
	//glTexCoord2f(1, 0); glVertex3f(halfSize, -halfSize, halfSize);
	//glTexCoord2f(0, 0); glVertex3f(-halfSize, -halfSize, halfSize);
	//glEnd();
	//base.unbind();

	////The above glBegin, glEnd, glNormal and glVertex calls can be replaced with a glut convenience function
	////glutSolidCube(size);

	////Pop the save state off the matrix stack
	////This will undo the multiply we did earlier
	//glPopMatrix();



	float halfSize = size / 2.0;

	//Apply the material properties
	//From here forward anything drawn will be drawn with these material
	material.apply();

	//Se the OpenGL Matrix mode to ModelView (used when drawing geometry)
	glMatrixMode(GL_MODELVIEW);

	//Push a save state onto the matrix stack, and multiply in the toWorld matrix
	glPushMatrix();
	glMultMatrixf(toWorld.ptr());

	glColor3f(1, 1, 1);

	//Make cube!
	//Note: The glBegin, and glEnd should always be as close to the glNormal/glVertex calls as possible
	//These are special calls that 'freeze' many internal states of OpenGL.
	//Once the glBegin state is active many of the calls made to OpenGL (like glMultMatrixf) will be IGNORED!
	//As a good habit, only call glBegin just before you need to draw, and call end just after you finish
	glDisable(GL_LIGHTING);

	front.bind();
	glBegin(GL_QUADS);
	// Draw front face:
	glNormal3f(0.0, 0.0, -1.0);
	glTexCoord2f(1, 0); glVertex3f(-halfSize, halfSize, halfSize);
	glTexCoord2f(0, 0); glVertex3f(halfSize, halfSize, halfSize);
	glTexCoord2f(0, 1); glVertex3f(halfSize, -halfSize, halfSize);
	glTexCoord2f(1, 1); glVertex3f(-halfSize, -halfSize, halfSize);
	glEnd();
	front.unbind();

	right.bind();
	// Draw left side:
	glBegin(GL_QUADS);
	glNormal3f(1.0, 0.0, 0.0);
	glTexCoord2f(0, 0); glVertex3f(-halfSize, halfSize, halfSize);
	glTexCoord2f(1, 0); glVertex3f(-halfSize, halfSize, -halfSize);
	glTexCoord2f(1, 1); glVertex3f(-halfSize, -halfSize, -halfSize);
	glTexCoord2f(0, 1); glVertex3f(-halfSize, -halfSize, halfSize);
	glEnd();
	right.unbind();

	left.bind();
	// Draw right side:
	glBegin(GL_QUADS);
	glNormal3f(-1.0, 0.0, 0.0);
	glTexCoord2f(1, 0); glVertex3f(halfSize, halfSize, halfSize);
	glTexCoord2f(0, 0); glVertex3f(halfSize, halfSize, -halfSize);
	glTexCoord2f(0, 1); glVertex3f(halfSize, -halfSize, -halfSize);
	glTexCoord2f(1, 1); glVertex3f(halfSize, -halfSize, halfSize);
	glEnd();
	left.unbind();

	back.bind();
	// Draw back face:
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2f(0, 0); glVertex3f(-halfSize, halfSize, -halfSize);
	glTexCoord2f(1, 0); glVertex3f(halfSize, halfSize, -halfSize);
	glTexCoord2f(1, 1); glVertex3f(halfSize, -halfSize, -halfSize);
	glTexCoord2f(0, 1); glVertex3f(-halfSize, -halfSize, -halfSize);
	glEnd();
	back.unbind();

	top.bind();
	// Draw top side:
	glBegin(GL_QUADS);
	glNormal3f(0.0, -1.0, 0.0);
	glTexCoord2f(1, 1); glVertex3f(-halfSize, halfSize, halfSize);
	glTexCoord2f(0, 1); glVertex3f(halfSize, halfSize, halfSize);
	glTexCoord2f(0, 0); glVertex3f(halfSize, halfSize, -halfSize);
	glTexCoord2f(1, 0); glVertex3f(-halfSize, halfSize, -halfSize);
	glEnd();
	top.unbind();

	base.bind();
	// Draw bottom side:
	glBegin(GL_QUADS);
	glNormal3f(0.0, 1.0, 0.0);
	glTexCoord2f(1, 1); glVertex3f(-halfSize, -halfSize, -halfSize);
	glTexCoord2f(0, 1); glVertex3f(halfSize, -halfSize, -halfSize);
	glTexCoord2f(0, 0); glVertex3f(halfSize, -halfSize, halfSize);
	glTexCoord2f(1, 0); glVertex3f(-halfSize, -halfSize, halfSize);
	glEnd();
	base.unbind();

	glEnable(GL_LIGHTING);

	//The above glBegin, glEnd, glNormal and glVertex calls can be replaced with a glut convenience function
	//glutSolidCube(size);

	//Pop the save state off the matrix stack
	//This will undo the multiply we did earlier
	glPopMatrix();





}


void Cube::update(UpdateData& data)
{
    //
}

void Cube::spin(float radians)
{
    Matrix4 rotation;
    rotation.makeRotateY(radians);
    
    toWorld = toWorld * rotation;
}





