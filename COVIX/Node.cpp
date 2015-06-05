#include "Node.h"
#include "Window.h"

Node::Node()
{
	//this->toWorld.identity();
}

Node::~Node()
{
	//
}

void Node::draw(Matrix4 data)
{
	std::cout << "Warning: draw() is not implemented" << std::endl;
}

void Node::update(Matrix4 data)
{
	std::cout << "Warning: update() is not implemented" << std::endl;
}