#include "Robot.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Window.h"
#include "math.h"

#define PI 3.14159265

Robot::Robot()
{
	//this->size = size;
	head = Cylinder(18);
	angle1 = 0;
	angle2 = 0;
	increment1 = PI / 1000;
	increment2 = -PI / 1000;
}

Robot::~Robot()
{
	//Delete any dynamically allocated memory/objects here
}

void Robot::init(){
	head.LoadTexture();
	Matrix4 HR;
	Htrans.M.makeTranslate(0, 2, 0);
	HR.makeRotateY(PI);
	Htrans.M = HR*Htrans.M;

	Tscale.M.makeScale(1.5, 2.5, 1);

	LAscale.M.makeScale(0.5, 1, 0.5);
	LAtrans1.M.makeTranslate(0, -0.5, 0);
	LAtrans2.M.makeTranslate(-2, 1.5, 0);

	RAscale.M.makeScale(0.5, 1, 0.5);
	RAtrans1.M.makeTranslate(0, -0.5, 0);
	RAtrans2.M.makeTranslate(2, 1.5, 0);

	LLscale.M.makeScale(0.5, 1, 0.5);
	LLtrans1.M.makeTranslate(0, -0.5, 0);
	LLtrans2.M.makeTranslate(-1.5, -2, 0);

	RLscale.M.makeScale(0.5, 1, 0.5);
	RLtrans1.M.makeTranslate(0, -0.5, 0);
	RLtrans2.M.makeTranslate(1.5, -2, 0);

	Htrans.children.push_back(&head);
	root.children.push_back(&Htrans);

	Tscale.children.push_back(&torso);
	root.children.push_back(&Tscale);

	LAscale.children.push_back(&leftarm);
	LAtrans1.children.push_back(&LAscale);
	LArota.children.push_back(&LAtrans1);
	LAtrans2.children.push_back(&LArota);
	root.children.push_back(&LAtrans2);

	RAscale.children.push_back(&rightarm);
	RAtrans1.children.push_back(&RAscale);
	RArota.children.push_back(&RAtrans1);
	RAtrans2.children.push_back(&RArota);
	root.children.push_back(&RAtrans2);

	LLscale.children.push_back(&leftleg);
	LLtrans1.children.push_back(&LLscale);
	LLrota.children.push_back(&LLtrans1);
	LLtrans2.children.push_back(&LLrota);
	root.children.push_back(&LLtrans2);

	RLscale.children.push_back(&rightleg);
	RLtrans1.children.push_back(&RLscale);
	RLrota.children.push_back(&RLtrans1);
	RLtrans2.children.push_back(&RLrota);
	root.children.push_back(&RLtrans2);
}

void Robot::update(){
	angle1 += increment1;
	LArota.M.makeRotateX(angle1);
	RLrota.M.makeRotateX(angle1);
	//RArota.M.makeRotateX(-angle);
	//LLrota.M.makeRotateX(-angle);
	//LArota.M.print("LA");
	//RArota.M.print("RA");
	if (angle1 > PI / 3){
		angle1 = PI / 3;
		increment1 = -increment1;
	}
	else if (angle1 < -PI / 3){
		angle1 = -PI / 3;
		increment1 = -increment1;
	}

	angle2 += increment2;
	RArota.M.makeRotateX(angle2);
	LLrota.M.makeRotateX(angle2);
	if (angle2 > PI / 3){
		angle2 = PI / 3;
		increment2 = -increment2;
	}
	else if (angle2 < -PI / 3){
		angle2 = -PI / 3;
		increment2 = -increment2;
	}
}