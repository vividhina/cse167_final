#include <iostream>

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include "Window.h"
#include "Cube.h"
#include "Matrix4.h"
#include "Globals.h"

int Window::width  = 512;   //Set window width in pixels here
int Window::height = 512;   //Set window height in pixels here
int flag = 0; 
int Window::r_flag = 0;
int Window::light_type = 0;
Matrix4 idty;
Matrix4 walk;
float x_posi[] = { 0,1,2,3,4,5,5,5,5,5 };
float z_posi[] = { 0,0,0,0,0,0,1,2,3,4 };


void Window::initialize(void)
{
	Globals::particle.init(10);
	Globals::camera.set(Globals::camera.e, Globals::camera.d, Globals::camera.up);
	Globals::floor.init(x_posi, z_posi);

	idty.identity();
	walk.makeTranslate(0, 0, 0.01);
	Matrix4 T_sphere;
	Matrix4 T_cone;
	Globals::Skybox.back = Texture("Skybox_Water222_back.ppm");
	Globals::Skybox.base = Texture("Skybox_Water222_base.ppm");
	Globals::Skybox.front = Texture("Skybox_Water222_front.ppm");
	Globals::Skybox.top = Texture("Skybox_Water222_top.ppm");
	Globals::Skybox.left = Texture("Skybox_Water222_left.ppm");
	Globals::Skybox.right = Texture("Skybox_Water222_right.ppm");
	//Globals::head.head = Texture("head.ppm");

	//Globals::particle.LoadGLTextures();


    //Setup the light
    Vector4 lightPos0(0.0, 10.0, 15.0, 1.0);
	Vector4 lightPos(7.0, 7.0, 0.0, 1.0);
	Vector4 lightPos1(0.0, 0.0, 1.0, 0.0);
    Globals::light.position = lightPos0;
    Globals::light.quadraticAttenuation = 0.00;

	Globals::directional.position = lightPos1;
	Globals::directional.quadraticAttenuation = 0.02;

	Globals::point.position = lightPos;
	Globals::point.quadraticAttenuation = 0.02;

	Globals::spot.position = lightPos;
	Globals::spot.quadraticAttenuation = 0.02;
    
    //Initialize cube matrix:
    Globals::cube.toWorld.identity();

	//Globals::bunny.material.ambientColor = Color(0.0,0.0,0.0,1.0) ;
	//Globals::bunny.material.diffuseColor = Color(0.5, 0.5, 0.5, 1.0);
	//Globals::bunny.material.specularColor = Color(1.0, 0.0, 0.0, 1.0);
	//Globals::bunny.material.shininess = 100;

	T_sphere.makeTranslate(Globals::point.position.toVector3());
	Globals::sphere.toWorld = T_sphere*Globals::sphere.toWorld;

	T_sphere.makeTranslate(lightPos0.toVector3());
	Globals::lightposi.toWorld = T_sphere*Globals::lightposi.toWorld;

	Vector3 Z(0.0, 0.0, -1.0);
	float angle = Globals::spot.position.toVector3().angle(Z);
	Vector3 axis = Globals::spot.position.toVector3().cross(Z);
	T_cone.makeRotateArbitrary(axis, angle);
	Globals::cone.toWorld = T_cone*Globals::cone.toWorld;

	T_cone.makeTranslate(Globals::spot.position.toVector3());
	Globals::cone.toWorld = T_cone*Globals::cone.toWorld;


    //Setup the cube's material properties
    Color color(0x23ff27ff);
    Globals::cube.material.color = color;

	Globals::Android.init();
	for (int i = -50; i <= 50; i += 10){
		for (int j = -50; j <= 50; j += 10){
			MatrixTransform* operation = new MatrixTransform();
			(*operation).M.makeTranslate(i, -10, j);
			(*operation).children.push_back(&Globals::Android.root);
			Globals::Army_scale.children.push_back(operation);
		}
	}
	Globals::Army_rota.children.push_back(&Globals::Army_scale);
	Globals::Army_trans.children.push_back(&Globals::Army_rota);

}

//----------------------------------------------------------------------------
// Callback method called when system is idle.
// This is called at the start of every new "frame" (qualitatively)
void Window::idleCallback()
{
    //Set up a static time delta for update calls
    Globals::updateData.dt = 1.0/60.0;// 60 fps
    
    //Rotate cube; if it spins too fast try smaller values and vice versa
	//if (Globals::toggle_direction)
	//	Globals::cube.spin(0.0005);
	//else
	//	Globals::cube.spin(-0.0005);
    
    //Call the update function on cube
    Globals::cube.update(Globals::updateData);
    
    //Call the display routine to draw the cube
    displayCallback();
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when graphics window is resized by the user
void Window::reshapeCallback(int w, int h)
{
    width = w;                                                       //Set the window width
    height = h;                                                      //Set the window height
    glViewport(0, 0, w, h);                                          //Set new viewport size
    glMatrixMode(GL_PROJECTION);                                     //Set the OpenGL matrix mode to Projection
    glLoadIdentity();                                                //Clear the projection matrix by loading the identity
    gluPerspective(60.0, double(width)/(double)height, 1.0, 1000.0); //Set perspective projection viewing frustum
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when window readraw is necessary or when glutPostRedisplay() was called.
void Window::displayCallback()
{
    //Clear color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //Set the OpenGL matrix mode to ModelView
    glMatrixMode(GL_MODELVIEW);
    
    //Push a matrix save point
    //This will save a copy of the current matrix so that we can
    //make changes to it and 'pop' those changes off later.
    glPushMatrix();
    
    //Replace the current top of the matrix stack with the inverse camera matrix
    //This will convert all world coordiantes into camera coordiantes
    glLoadMatrixf(Globals::camera.getInverseMatrix().ptr());
	
    //Bind the light to slot 0.  We do this after the camera matrix is loaded so that
    //the light position will be treated as world coordiantes
    //(if we didn't the light would move with the camera, why is that?)
    Globals::light.bind(0);
	Globals::directional.bind(1);
	Globals::point.bind(2);
	Globals::spot.bind(3);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHT1);
	glDisable(GL_LIGHT2);
	glDisable(GL_LIGHT3);
	glEnable(GL_LIGHTING);
	if (light_type == 0)
		glEnable(GL_LIGHT0);
	if (light_type == 1)
		glEnable(GL_LIGHT1);
	if (light_type == 2)
		glEnable(GL_LIGHT2);
	if (light_type == 3)
		glEnable(GL_LIGHT3);
    //Draw the cube!
	glDisable(GL_LIGHTING);
	if (flag == 0){
		//glDisable(GL_LIGHT0);
		//glEnable(GL_LIGHT0);

		Globals::particle.draw(Globals::drawData);
		Globals::cube.draw(Globals::drawData);
		glDisable(GL_LIGHTING);
		Globals::lightposi.draw(Globals::drawData);
		//Globals::cube1.draw(Globals::drawData);
		//Globals::floor.draw(Globals::drawData);
		//Globals::head.draw(Globals::drawData);


		//Globals::Skybox.drawTex(Globals::drawData);
		//Globals::Army_trans.draw(idty);
		//if (light_type == 2)
		//	Globals::sphere.draw(Globals::drawData);
		//if (light_type == 3)
		//	Globals::cone.drawc(Globals::drawData);

		//Globals::Skybox.update(Globals::updateData);
		//Globals::Android.update();

		//idty = walk*idty;
	}
	if (r_flag != 0)
		Globals::cube.rotate(r_flag);
	//else if (flag == 1){
	//	//glDisable(GL_LIGHTING);
	//	Globals::house.draw(Globals::drawData);
	//}


    //Pop off the changes we made to the matrix stack this frame
    glPopMatrix();
    
    //Tell OpenGL to clear any outstanding commands in its command buffer
    //This will make sure that all of our commands are fully executed before
    //we swap buffers and show the user the freshly drawn frame
    glFlush();
    
    //Swap the off-screen buffer (the one we just drew to) with the on-screen buffer
    glutSwapBuffers();
}



//TODO: Keyboard callbacks!
void Window::keyboard(unsigned char key, int x, int y){
	Matrix4 T;
	Matrix4 R;
	Matrix4 S;
	Vector3 v3(0,0,1);
	float len = 2.5;
	float a = Globals::cube.toWorld.m[3][0];
	float b = Globals::cube.toWorld.m[3][1];
	float c = Globals::cube.toWorld.m[3][2];
	switch (key)
	{
	case 'q':case 'Q' :
		exit(0);
		break;
	case '1':
		if (light_type == 1)
			light_type = 0;
		else
			light_type = 1;
		break;
	case '2':
		if (light_type == 2)
			light_type = 0;
		else
			light_type = 2;
		break;
	case '3':
		if (light_type == 3)
			light_type = 0;
		else
			light_type = 3;
		break;
	case 't' : 
		glutIdleFunc(Window::idleCallback);
		Globals::toggle_direction = !Globals::toggle_direction;
		break;
	case 'x' :
		T.makeTranslate(-0.1, 0, 0);
		Globals::particle.initial_position(-0.1, 0, 0);
		if (flag == 0)
			Globals::cube.toWorld = T * Globals::cube.toWorld;
		break;
	case 'X':
		T.makeTranslate(0.1, 0, 0);
		Globals::particle.initial_position(0.1, 0, 0);
		if (flag == 0)
			Globals::cube.toWorld = T * Globals::cube.toWorld;
		break;
	case 'y':
		T.makeTranslate(0, -0.1, 0);
		Globals::particle.initial_position(0, -0.1, 0);
		if (flag == 0)
			Globals::cube.toWorld = T * Globals::cube.toWorld;
		break;
	case 'Y':
		T.makeTranslate(0, 0.1, 0);
		Globals::particle.initial_position(0, 0.1, 0);
		if (flag == 0)
			Globals::cube.toWorld = T * Globals::cube.toWorld;
		break;
	case 'z':
		T.makeTranslate(0, 0, -0.1);
		Globals::particle.initial_position(0, 0, -0.1);
		if (flag == 0)
			Globals::cube.toWorld = T * Globals::cube.toWorld;
		break;
	case 'Z':
		T.makeTranslate(0, 0, 0.1);
		Globals::particle.initial_position(0, 0, 0.1);
		if (flag == 0)
			Globals::cube.toWorld = T * Globals::cube.toWorld;
		break;
	case'r':
		Globals::particle.set_initial_position(0, 0, 0);
		if (flag == 0)
			Globals::cube.toWorld.identity();
		break;
	case 'o':
		R.makeRotateZ(0.05);
		if (flag == 0)
			Globals::cube.toWorld = R * Globals::cube.toWorld;
		break;
	case 'O':
		R.makeRotateZ(-0.05);
		if (flag == 0)
			Globals::cube.toWorld = R * Globals::cube.toWorld;
		break;
	case 'd':
		R.makeRotateY(0.05);
		if (flag == 0)
			Globals::cube.toWorld = R * Globals::cube.toWorld;
		break;
	case 'a':
		R.makeRotateY(-0.05);
		if (flag == 0)
			Globals::cube.toWorld = R * Globals::cube.toWorld;
		break;
	case 'b':
		T.makeTranslate(-len, +len, 0);
		Globals::cube.toWorld = T * Globals::cube.toWorld;
		break;
	case 'v':
		R.makeRotateArbitrary(v3,PI / 4.0);
		Globals::cube.toWorld = R * Globals::cube.toWorld;
		break;
	case 'n':
		R.makeRotateZ(PI / 4.0);
		Globals::cube.toWorld = R * Globals::cube.toWorld;
		break;
	case 'm':
		T.makeTranslate(+len, - len, 0);
		Globals::cube.toWorld = T * Globals::cube.toWorld;
		break;
	case 's':
		S.makeScale(0.9);
		T.makeTranslate(-a, -b, -c);
		if (light_type == 2){
			Globals::point.position = S * Globals::point.position;
			Globals::sphere.toWorld = S * Globals::sphere.toWorld;
		}

		else if (light_type == 3){
			Globals::spot.position = S * Globals::spot.position;
			Globals::cone.toWorld = S * Globals::cone.toWorld;
		}
		else if (flag == 0){
			Globals::cube.toWorld = T * Globals::cube.toWorld;
			Globals::cube.toWorld = S * Globals::cube.toWorld;
			T.makeTranslate(a, b, c);
			Globals::cube.toWorld = T * Globals::cube.toWorld;
			idty = T*idty;
			Globals::Skybox.toWorld = T * Globals::Skybox.toWorld;
		}


		break;
	case 'S':
		S.makeScale(1.1);
		T.makeTranslate(-a, -b, -c);
		if (light_type == 2){
			Globals::point.position = S * Globals::point.position;
			Globals::sphere.toWorld = S * Globals::sphere.toWorld;
		}

		else if (light_type == 3){
			Globals::spot.position = S * Globals::spot.position;
			Globals::cone.toWorld = S * Globals::cone.toWorld;
		}
		
		else if (flag == 0){
			Globals::cube.toWorld = T * Globals::cube.toWorld;
			Globals::cube.toWorld = S * Globals::cube.toWorld;
			T.makeTranslate(a, b, c);
			Globals::cube.toWorld = T * Globals::cube.toWorld;
			idty = T*idty;
			Globals::Skybox.toWorld = T * Globals::Skybox.toWorld;
		}
		break;
	}
	Vector3 position(Globals::cube.toWorld.m[3][0], Globals::cube.toWorld.m[3][1], Globals::cube.toWorld.m[3][2]);
	position.print("New cube position");
}

void Window::specialkey(int key, int x, int y){
	Vector3 e;   //Center of Projection
	Vector3 d;   //Look At
	Vector3 up;  //Up Vector ^
	//Globals::cube.get_current_toWorld();
	switch (key) {
	//case GLUT_KEY_F1:
	//	e.set(0.0, 0.0, 20.0);
	//	Globals::camera.ci.set(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, -e[0], -e[1], -e[2], 1);
	//	//Globals::camera.update();
	//	flag = 0;
	//	//idleCallback();
	//	break;
	//case GLUT_KEY_F2:
	//	e.set(0, 24.14, 24.14);
	//	d.set(0, 0, 0);
	//	up.set(0, 1, 0);
	//	Globals::camera.set(e, d, up);
	//	flag = 1;
	//	//idleCallback();
	//	break;
	case GLUT_KEY_RIGHT:
		//e.set(-28.33, 11.66, 23.33);
		//d.set(-5, 0, 0);
		//up.set(0, 1, 0.5);
		//Globals::camera.set(e, d, up);
		r_flag = 1;
		//idleCallback();
		break;
	case GLUT_KEY_LEFT:
		//e.set(0.0, 0.0, 20.0);
		//Globals::camera.ci.set(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, -e[0], -e[1], -e[2], 1);
		r_flag = 2;
		//idleCallback();
		break;
	case GLUT_KEY_UP:
		//e.set(0.0, 0.0, 20.0);
		//Globals::camera.ci.set(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, -e[0], -e[1], -e[2], 1);
		r_flag = 3;
		//idleCallback();
		break;
	case GLUT_KEY_DOWN:
		//e.set(0.0, 0.0, 20.0);
		//Globals::camera.ci.set(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, -e[0], -e[1], -e[2], 1);
		r_flag = 4;
		//idleCallback();
		break;
	}



	//TODO: Function Key callbacks!

	//TODO: Mouse callbacks!

	//TODO: Mouse Motion callbacks!
}

bool Rotate = false;
bool Move = false;
bool Zoom = false;
Vector3 lastPoint;


Vector3 trackBallMapping(int x, int y)
{
	Vector3 v;
	float d;
	v[0] = (2.0*x - Window::width) / Window::width;
	v[1] = (Window::height - 2.0*y) / Window::height;
	v[2] = 0.0;
	d = v.magnitude();
	d = (d<1.0) ? d : 1.0;
	v[2] = sqrtf(1.001 - d*d);
	v = v.normalize(); // Still need to normalize, since we only capped d, not v.
	return v;
}

void Window::mouse(int button, int state, int x, int y){
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		if (glutGetModifiers() == GLUT_ACTIVE_ALT){

			lastPoint = trackBallMapping(x, y);
			Rotate = false;
			Zoom = true;
			return;
		}
		Zoom = false;
		Move = false;
		Rotate = true;
		
		lastPoint = trackBallMapping(x, y);
		//glMatrixMode(GL_MODELVIEW);// Make sure we are modifying the MODELVIEW matrix.
		
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
		lastPoint = trackBallMapping(x, y);
		Rotate = false;
		Zoom = false;
		Move = true;
	}
	else {
		//lastPoint = trackBallMapping(x, y);
		Zoom = false;
		Rotate = false;
		Move = false;
	}


}



void Window::OnMouseMove(int x, int y)
{

	// 
	// Handle any necessary mouse movements
	//
	//Vector3 direction;
	//float pixel_diff;
	float rot_angle, zoom_factor;
	Vector3 curPoint;
	Matrix4 T;

	

	if (Rotate == true){
		curPoint = trackBallMapping(x, y); // Map the mouse position to a logical
		Vector3 rotAxis;
		rotAxis = lastPoint.cross(curPoint); //Attention! Maybe need to normalized here!
		rot_angle = lastPoint.angle(curPoint);
		T.identity();
		T.makeRotateArbitrary(rotAxis, rot_angle);

		if (light_type == 0){
			if (flag == 0){
				Globals::cube.toWorld = T*Globals::cube.toWorld;
				
				//Globals::cube1.toWorld = T*Globals::cube.toWorld;
				//Globals::cube2.toWorld = T*Globals::cube.toWorld;
				//Globals::Skybox.toWorld = T*Globals::Skybox.toWorld;
				//idty = T*idty;
				//Globals::head.toWorld = T*Globals::head.toWorld;
			}

		}
		if (light_type == 1)
			Globals::directional.position = T*Globals::directional.position;
		if (light_type == 2){
			Globals::sphere.toWorld = T*Globals::sphere.toWorld;
			
			Globals::point.position = T*Globals::point.position;
		}

		if (light_type == 3){
			Globals::cone.toWorld = T*Globals::cone.toWorld;
			Globals::spot.position = T*Globals::spot.position;
		}
			
		lastPoint = curPoint;
	}
		
	else if (Move == true){
		curPoint = trackBallMapping(x, y); // Map the mouse position to a logical
		Vector3 Trans;
		curPoint.set(curPoint[0], curPoint[1], 0);
		lastPoint.set(lastPoint[0], lastPoint[1], 0);
		Trans = (curPoint - lastPoint) * 10;
		if (light_type == 3){
			Light::angle = Light::angle - (curPoint[1] - lastPoint[1])/5;
			Light::exp = Light::exp - (curPoint[0] - lastPoint[0]);
			std::cout << "Exp:"<< Light::exp << std::endl;
			return;
		}
		T.identity();
		T.makeTranslate(Trans);
		if (flag == 0)
			Globals::cube.toWorld = T*Globals::cube.toWorld;
			//Globals::Skybox.toWorld = T*Globals::Skybox.toWorld;
			idty = T*idty;
		lastPoint = curPoint;
	}
	else if (Zoom == true){

		curPoint = trackBallMapping(x, y); // Map the mouse position to a logical
		float zoom = 10*(curPoint[1] - lastPoint[1]);
		T.identity();
		T.makeTranslate(0, 0, zoom);
		if (flag == 0)
			Globals::cube.toWorld = T*Globals::cube.toWorld;
			Globals::Skybox.toWorld = T*Globals::Skybox.toWorld;
			idty = T*idty;
		lastPoint = curPoint;
	}

	}