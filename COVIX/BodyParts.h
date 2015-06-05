#ifndef CSE167_BodyParts_h
#define CSE167_BodyParts_h

#include "Geode.h"
#include "Texture.h"

class BodyParts : public Geode
{

public:

	//Texture face;

	BodyParts(void);
	virtual ~BodyParts(void);

	//void LoadTexture();

	virtual void draw(Matrix4);
	virtual void update(Matrix4);

};

#endif