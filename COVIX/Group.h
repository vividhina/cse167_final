#ifndef CSE167_Group_h
#define CSE167_Group_h

#include "Node.h"

class Group : public Node
{

public:

	//Matrix4 toWorld;
	//Material material;
	std::vector<Node*> children;

	Group(void);
	~Group(void);

	virtual void draw(Matrix4);
	virtual void update(Matrix4);

};

#endif