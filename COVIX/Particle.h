#ifndef CSE167_Particle_h
#define CSE167_Particle_h

#include "Drawable.h"
#include "Texture.h"
#include "bmp.h"
#include <stdlib.h>
#include <stdio.h>

class Particle : public Drawable
{

public:

	bool	active;					// Active (Yes/No)
	float	life;					// Particle Life
	float	fade;					// Fade Speed
	float	r;						// Red Value
	float	g;						// Green Value
	float	b;						// Blue Value
	float	x;						// X Position
	float	y;						// Y Position
	float	z;						// Z Position
	float	xi;						// X Direction
	float	yi;						// Y Direction
	float	zi;						// Z Direction
	float	xg;						// X Gravity
	float	yg;						// Y Gravity
	float	zg;						// Z Gravity


	Particle(void);
	Particle(float, float);
	virtual ~Particle(void);

	void init(int);

	AUX_RGBImageRec *LoadBMP(char*);
	int LoadGLTextures(void);

	virtual void draw(DrawData&);
	//virtual void drawTex(DrawData&);
	//virtual void update(UpdateData&);

	void spin(float);

};



















#endif