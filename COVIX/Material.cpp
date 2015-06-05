#include "Material.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

Material::Material()
{
    //Material setup goes hurr
    ambientColor = Color::ambientMaterialDefault();
    diffuseColor = Color::diffuseMaterialDefault();
    specularColor = Color::specularMaterialDefault();
    emissionColor = Color::emissionMaterialDefault();
    shininess = 100.0;
    
    //Set the initial color to a random pastel color
    //Can be removed once materials are implemented
    color = Color::randomPastel();
}

Material::~Material()
{
    //Delete any dynamically allocated memory/objects here
}

void Material::apply(void)
{

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambientColor.ptr());
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuseColor.ptr());
	//std::cout << diffuseColor[0] << diffuseColor[1] << diffuseColor[2]<<std::endl;
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specularColor.ptr());


	glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
    //Set the material properties for ambient, diffuse, specular, emission, and shininess
    //Hint: Lookup how glMaterialfv works
    
    //Set the color property (can be removed once materials are implemented)
    //Used for projects 1, 2, and 3
    //glColor3fv(color.ptr());
}



