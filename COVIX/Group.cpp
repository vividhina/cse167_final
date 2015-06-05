#include "Group.h"
#include "Window.h"

Group::Group()
{
	//this->toWorld.identity();
}

Group::~Group()
{
	//
}

void Group::draw(Matrix4 data)
{
	//std::cout << "Warning: draw() is not implemented" << std::endl;
	for (int i = 1; i <= children.size(); i++){
		children[i - 1]->draw(data);
	}
}

void Group::update(Matrix4 data)
{
	std::cout << "Warning: update() is not implemented" << std::endl;
}