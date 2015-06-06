#ifndef CSE167_Globals_h
#define CSE167_Globals_h

#include "Camera.h"
#include "Cube.h"
#include "House.h"
#include "Light.h"
#include "DrawData.h"
#include "UpdateData.h"
#include "Sphere.h"
#include "Texture.h"
#include "Cylinder.h"
#include "Robot.h"
#include "BodyParts.h"
#include "Particle.h"
#include "Floor.h"

class Globals
{
    
public:
    
    static Camera camera;
    static Cube cube;
	static Floor floor;
	//static Cube cube1;
	//static Cube cube2;
	static Cube Skybox;
	//static Cylinder head;
	static House house;
	static Sphere sphere;
	static Sphere lightposi;
	static Sphere cone;
    static Light light;
	static Light directional;
	static Light point;
	static Light spot;
    static DrawData drawData;
    static UpdateData updateData;
    //Feel free to add more member variables as needed
	static bool toggle_direction;

	static Particle particle;


	static Robot Android;
	//static MatrixTransform Army;
	static MatrixTransform Army_scale;
	static MatrixTransform Army_trans;
	static MatrixTransform Army_rota;
};

#endif
