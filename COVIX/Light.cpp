#include "Light.h"
#include "Window.h"
#include <iostream>
#include "Globals.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

float Light::angle = 40;
float Light::exp = 50;
Light::Light()
{
	
    ambientColor = Color::ambientDefault();
    diffuseColor = Color::diffuseDefault();
    specularColor = Color::specularDefault();
    


    constantAttenuation = 1.0;
    linearAttenuation = 0.0;
    quadraticAttenuation = 0.05;
}

Light::~Light()
{
    //Delete any dynamically allocated memory/objects here
}

void Light::bind(int id)
{
	Matrix4 T_sphere;
    if(id < 0 || id > 7) {
        std::cout << "ERROR: The light bind ID " << id << " is not valid!" << std::endl;
        return;
    }

    
    //Set the bindID
    bindID = id;
    
    //Configure the light at the bindID
    glEnable(GL_LIGHT0 + bindID);
    //Configure the color of the light
	if (bindID == 0){
		glLightfv(GL_LIGHT0 + bindID, GL_AMBIENT, ambientColor.ptr());
		glLightfv(GL_LIGHT0 + bindID, GL_DIFFUSE, diffuseColor.ptr());
		glLightfv(GL_LIGHT0 + bindID, GL_SPECULAR, specularColor.ptr());
		
	}
	if (bindID == 1){
		glLightfv(GL_LIGHT0 + bindID, GL_AMBIENT, ambientColor.ptr());
		glLightfv(GL_LIGHT0 + bindID, GL_DIFFUSE, Color::yellow().ptr());
		glLightfv(GL_LIGHT0 + bindID, GL_SPECULAR, Color::yellow().ptr());
		//glLightfv(GL_LIGHT0 + bindID, GL_AMBIENT, directional_ambient);
		//glLightfv(GL_LIGHT0 + bindID, GL_DIFFUSE, directional_diffuse);
		//glLightfv(GL_LIGHT0 + bindID, GL_SPECULAR, directional_specular);
	}
	if (bindID == 2){
		glLightfv(GL_LIGHT0 + bindID, GL_AMBIENT, ambientColor.ptr());
		glLightfv(GL_LIGHT0 + bindID, GL_DIFFUSE, Color::red().ptr());
		glLightfv(GL_LIGHT0 + bindID, GL_SPECULAR, Color::red().ptr());
	}
	if (bindID == 3){
		glLightfv(GL_LIGHT0 + bindID, GL_AMBIENT, ambientColor.ptr());
		glLightfv(GL_LIGHT0 + bindID, GL_DIFFUSE, Color::blue().ptr());
		glLightfv(GL_LIGHT0 + bindID, GL_SPECULAR, Color::blue().ptr());
	}


    
    //Configure the attenuation properties of the light
    //Constant Attenuation
    //Linear Attenuation
	if (bindID == 0)
		glLightf(GL_LIGHT0 + bindID, GL_QUADRATIC_ATTENUATION, quadraticAttenuation);
	if (bindID == 1)
		glLightf(GL_LIGHT1 + bindID, GL_CONSTANT_ATTENUATION, 0);
	if (bindID == 2){
		glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 2.0);
		//T_sphere.identity();
		//T_sphere.makeTranslate(Globals::point.position.toVector3());
		//Globals::sphere.toWorld = T_sphere*Globals::sphere.toWorld;
		//Globals::sphere.draw(Globals::drawData);
		
		//glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 1.0);
		//glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.5);
	}
		
	if (bindID == 3){
		glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, 2.0);
		//glLightf(GL_LIGHT3, GL_LINEAR_ATTENUATION, 1.0);
		//glLightf(GL_LIGHT3, GL_QUADRATIC_ATTENUATION, 0.5);
		glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, angle);
		glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, exp);
		Vector3 temp(-position[0], -position[1], -position[2]);
		glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, temp.ptr());
	}
    
    //Position the light
    glLightfv(GL_LIGHT0 + bindID, GL_POSITION, position.ptr());
    
    //Setup spotlight direction, angle, and exponent here
}

void Light::unbind(void)
{
    glDisable(GL_LIGHT0 + bindID);
    bindID = -1;
}
