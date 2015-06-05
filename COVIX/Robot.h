#ifndef CSE167_Robot_h
#define CSE167_Robot_h

#include "MatrixTransform.h"
#include "Cylinder.h"
#include "BodyParts.h"

class Robot
{

public:
	float angle1;
	float angle2;
	float increment1;
	float increment2;

	Group root;
	Cylinder head;
	BodyParts torso;
	BodyParts leftarm;
	BodyParts rightarm;
	BodyParts leftleg;
	BodyParts rightleg;

	MatrixTransform Htrans;

	MatrixTransform Tscale;
	
	MatrixTransform LAscale;
	MatrixTransform LAtrans1;
	MatrixTransform LArota;
	MatrixTransform LAtrans2;

	MatrixTransform RAscale;
	MatrixTransform RAtrans1;
	MatrixTransform RArota;
	MatrixTransform RAtrans2;

	MatrixTransform LLscale;
	MatrixTransform LLtrans1;
	MatrixTransform LLrota;
	MatrixTransform LLtrans2;

	MatrixTransform RLscale;
	MatrixTransform RLtrans1;
	MatrixTransform RLrota;
	MatrixTransform RLtrans2;

	Robot(void);
	virtual ~Robot(void);

	void init();
	void update();

	//void LoadTexture();

	//virtual void draw(DrawData&);
	//virtual void update(UpdateData&);

};

#endif