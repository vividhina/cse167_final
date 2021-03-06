#ifndef CSE167_Cube_h
#define CSE167_Cube_h

#include "Drawable.h"
#include "Texture.h"

class Cube : public Drawable
{
    
public:
    
    float size;
	float alpha;
	Texture back;
	Texture base;
	Texture front;
	Texture left;
	Texture right;
	Texture top;


    Cube(float);
	Cube(float,float);
    virtual ~Cube(void);
    
    virtual void draw(DrawData&);
	virtual void drawTex(DrawData&);
    virtual void update(UpdateData&);
    
    void spin(float);
	void test_pingyi(void);
	void rotate(int);

	float test_pingyi_length;
	float rotate_num;

	float toWorld_m30;
	float toWorld_m31;
	float toWorld_m32;
	//void get_current_toWorld();
};

#endif

