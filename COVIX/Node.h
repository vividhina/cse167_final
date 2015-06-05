#ifndef CSE167_Node_h
#define CSE167_Node_h

#include <iostream>
#include "Matrix4.h"
#include "Material.h"
#include <float.h>
#include <math.h>
#include <vector>


class Node
{

public:

	//Matrix4 toWorld;
	//Material material;

	Node(void);
	~Node(void);

	virtual void draw(Matrix4);
	virtual void update(Matrix4);

};

#endif