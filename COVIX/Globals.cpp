#include "Globals.h"

Camera Globals::camera = Camera();

Cube Globals::cube = Cube(10.0,1.0);
//Cube Globals::cube1 = Cube(11.0,0.5);
Floor Globals::floor = Floor(5);

Cube Globals::Skybox = Cube(1000.0);

//Cylinder Globals::head = Cylinder(18);

Sphere Globals::sphere(1.0, 20, 16);

Sphere Globals::lightposi(1.0, 20, 16);

Sphere Globals::cone(1.0, 20, 16);

House Globals::house = House();

Light Globals::light = Light();

Light Globals::directional = Light();

Light Globals::point = Light();

Light Globals::spot = Light();

DrawData Globals::drawData = DrawData();
UpdateData Globals::updateData = UpdateData();

bool Globals::toggle_direction = false;

Particle Globals::particle = Particle();


Robot Globals::Android = Robot();
//MatrixTransform Globals::Army = MatrixTransform();
MatrixTransform Globals::Army_scale = MatrixTransform();
MatrixTransform Globals::Army_trans = MatrixTransform();
MatrixTransform Globals::Army_rota = MatrixTransform();