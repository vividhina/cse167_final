#include "Sphere.h"
#include "Light.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif


Sphere::Sphere(double radius, int slices, int stacks) : Drawable()
{
    this->radius = radius;
    this->slices = slices;
    this->stacks = stacks;
}

void Sphere::draw(DrawData& data)
{
    //material.apply();
	Color white(1.0, 1.0, 1.0);
	glColor3fv(white.ptr());
    
    glMatrixMode(GL_MODELVIEW);
    
    glPushMatrix();
    glMultMatrixf(toWorld.ptr());
    
    glutSolidSphere(radius, slices, stacks);
    
    glPopMatrix();
}

void Sphere::drawc(DrawData& data)
{
	material.apply();

	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	glMultMatrixf(toWorld.ptr());

	glutSolidCone(1.0*tan(3.1415926/(180/Light::angle)), 1.0, slices, stacks);

	glPopMatrix();
}


void Sphere::update(UpdateData& data)
{
    //
}


