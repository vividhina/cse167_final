#ifndef CSE167_Floor_h
#define CSE167_Floor_h


#include "Drawable.h"
#include "Texture.h"

#define MAX_FLOOR 10

class Floor : public Drawable
{

public:

	float size;
	float alpha;
	float x[MAX_FLOOR];
	float z[MAX_FLOOR];

	Texture back;
	Texture base;
	Texture front;
	Texture left;
	Texture right;
	Texture top;


	Floor(float);
	void init(float*, float*);
	virtual ~Floor(void);

	virtual void draw(DrawData&);
	//virtual void drawGlow(DrawData&);
	//virtual void drawTex(DrawData&);

};




#endif