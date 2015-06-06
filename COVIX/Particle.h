#ifndef CSE167_Particle_h
#define CSE167_Particle_h

#include "Drawable.h"
#include "Texture.h"
#include "bmp.h"
#include <stdlib.h>
#include <stdio.h>
#define	MAX_PARTICLES	1000		// Number Of Particles To Create

class Particle : public Drawable
{

public:

	bool	active;					// Active (Yes/No)
	float	life[MAX_PARTICLES];					// Particle Life
	float	fade[MAX_PARTICLES];					// Fade Speed
	float	r[MAX_PARTICLES];						// Red Value
	float	g[MAX_PARTICLES];						// Green Value
	float	b[MAX_PARTICLES];						// Blue Value
	float	x[MAX_PARTICLES];						// X Position
	float	y[MAX_PARTICLES];						// Y Position
	float	z[MAX_PARTICLES];						// Z Position
	float	x_init[MAX_PARTICLES];						// X Position
	float	y_init[MAX_PARTICLES];						// Y Position
	float	z_init[MAX_PARTICLES];						// Z Position
	float	xi[MAX_PARTICLES];						// X Direction
	float	yi[MAX_PARTICLES];						// Y Direction
	float	zi[MAX_PARTICLES];						// Z Direction
	float	xg[MAX_PARTICLES];						// X Gravity
	float	yg[MAX_PARTICLES];						// Y Gravity
	float	zg[MAX_PARTICLES];						// Z Gravity


	Particle(void);
	//Particle(float, float);
	virtual ~Particle(void);
	void initial_position(float x0, float y0, float z0);
	void set_initial_position(float x0, float y0, float z0);
	void init(int);

	AUX_RGBImageRec *LoadBMP(char*);
	int LoadGLTextures(void);

	virtual void draw(DrawData&);
	//virtual void drawTex(DrawData&);
	//virtual void update(UpdateData&);

	//void spin(float);

};



















#endif