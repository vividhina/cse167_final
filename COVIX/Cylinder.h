#ifndef CSE167_Cylinder_h
#define CSE167_Cylinder_h

#include "Geode.h"
#include "Texture.h"
#include "Vector3.h"


class Cylinder : public Geode
{

public:

	float height;
	Texture head;
	std::vector<Vector3> circumPoints;
	Vector3 fixedPT;
	Vector3 fixedPB;

	Cylinder(void);
	virtual ~Cylinder(void);

	void LoadTexture();

	Cylinder(int);
	//virtual ~Cylinder(void);

	//virtual void draw(DrawData&);
	virtual void draw(Matrix4);
	//virtual void update(UpdateData&);

	

};

#endif
