#ifndef CSE167_Geode_h
#define CSE167_Geode_h

#include "Node.h"

class Geode : public Node
{

public:

	//Matrix4 toWorld;
	Material material;

	Geode(void);
	~Geode(void);

	virtual void draw(Matrix4);
	virtual void update(Matrix4);

};

#endif