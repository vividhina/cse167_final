#include "MatrixTransform.h"
#include "Window.h"

MatrixTransform::MatrixTransform()
{
	this->M.identity();
}

MatrixTransform::~MatrixTransform()
{
	//
}

void MatrixTransform::draw(Matrix4 data)
{
	//std::cout << "Warning: draw() is not implemented" << std::endl;
	Matrix4 C_new = data*M;
	for (int i = 1; i <= children.size(); i++){
		children[i - 1]->draw(C_new);
	}
}

void MatrixTransform::update(Matrix4 data)
{
	std::cout << "Warning: update() is not implemented" << std::endl;
}