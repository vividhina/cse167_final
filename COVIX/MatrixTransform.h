#ifndef CSE167_MatrixTransform_h
#define CSE167_MatrixTransform_h

#include "Group.h"

class MatrixTransform : public Group
{

public:

	Matrix4 M;
	//Material material;
	//std::vector<Node*> children;

	MatrixTransform(void);
	~MatrixTransform(void);

	virtual void draw(Matrix4);
	virtual void update(Matrix4);

};

#endif