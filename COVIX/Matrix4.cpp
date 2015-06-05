#include <math.h>
#include <iostream>
#include <iomanip>
#include <cstring>
#include "Matrix4.h"
#include "Vector4.h"
#include "Vector3.h"

#define M_PI 3.14159265358979323846

Matrix4::Matrix4()
{
    std::memset(m, 0, sizeof(m));
}

Matrix4::Matrix4(
                 float m00, float m01, float m02, float m03,
                 float m10, float m11, float m12, float m13,
                 float m20, float m21, float m22, float m23,
                 float m30, float m31, float m32, float m33 )
{
    this->set(m00, m01, m02, m03,
              m10, m11, m12, m13,
              m20, m21, m22, m23,
              m30, m31, m32, m33);
}

void Matrix4::set(float m00, float m01, float m02, float m03,
                  float m10, float m11, float m12, float m13,
                  float m20, float m21, float m22, float m23,
                  float m30, float m31, float m32, float m33)
{
    m[0][0] = m00;
    m[0][1] = m01;
    m[0][2] = m02;
    m[0][3] = m03;
    m[1][0] = m10;
    m[1][1] = m11;
    m[1][2] = m12;
    m[1][3] = m13;
    m[2][0] = m20;
    m[2][1] = m21;
    m[2][2] = m22;
    m[2][3] = m23;
    m[3][0] = m30;
    m[3][1] = m31;
    m[3][2] = m32;
    m[3][3] = m33;
}

float Matrix4::get(int vector,int element)
{
    return m[vector][element];
}

Matrix4& Matrix4::operator=(Matrix4 a)
{
    std::memcpy(m, a.m, sizeof(m));
    return *this;
}

float* Matrix4::ptr()
{
    return &m[0][0];
}

void Matrix4::identity()
{
    static const float ident[4][4]={{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
    std::memcpy(m, ident, sizeof(m));
}

Matrix4 Matrix4::multiply(Matrix4 a)
{
	Matrix4 b;

	//The current implementation below is not very efficient:
	//It allocates an additional 8 vectors on the stack and calls their constructors
	//It also calls off to additional functions (which create even more vectors!)
	//Which results in a lot of time being wasted on memory operations
	//This is bad, really bad, ultra bad D:

	//Implement a more performant Matrix * Matrix multiplication
	//Hint: Loops!
	//Hint for the ambitious: SIMD!

	/*Original
	Vector4 row1(m[0][0], m[1][0], m[2][0], m[3][0]);
	Vector4 row2(m[0][1], m[1][1], m[2][1], m[3][1]);
	Vector4 row3(m[0][2], m[1][2], m[2][2], m[3][2]);
	Vector4 row4(m[0][3], m[1][3], m[2][3], m[3][3]);

	Vector4 col1(a.m[0][0], a.m[0][1], a.m[0][2], a.m[0][3]);
	Vector4 col2(a.m[1][0], a.m[1][1], a.m[1][2], a.m[1][3]);
	Vector4 col3(a.m[2][0], a.m[2][1], a.m[2][2], a.m[2][3]);
	Vector4 col4(a.m[3][0], a.m[3][1], a.m[3][2], a.m[3][3]);

	b.set(row1.dot(col1), row2.dot(col1), row3.dot(col1), row4.dot(col1),
	row1.dot(col2), row2.dot(col2), row3.dot(col2), row4.dot(col2),
	row1.dot(col3), row2.dot(col3), row3.dot(col3), row4.dot(col3),
	row1.dot(col4), row2.dot(col4), row3.dot(col4), row4.dot(col4) );

	return b;
	}
	*/
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			b.m[i][j] = m[0][j] * a.m[i][0] + m[1][j] * a.m[i][1] + m[2][j] * a.m[i][2] + m[3][j] * a.m[i][3];
		}
	}
	return b;
}

Matrix4 Matrix4::operator * (Matrix4 a)
{
    return multiply(a);
}

Vector4 Matrix4::multiply(Vector4 a)
{
    Vector4 b;
    
    //Implement Matrix * Vector4 multiplication
	int i;
	float temp[4];

	for (i = 0; i < 4; i++)
	{
		Vector4 b_temp = Vector4(m[0][i], m[1][i], m[2][i], m[3][i]);
		//a.print("a:");
		//b_temp.print("b_temp:");
		//std::cout << "b_temp.dot(a) = " << b_temp.dot(a) << std::endl;
		temp[i] = b_temp.dot(a);
	}
	b = Vector4(temp[0], temp[1], temp[2], temp[3]);
	//b.print("b:");
	return b;
}

Vector4 Matrix4::operator * (Vector4 a)
{
    return multiply(a);
}

Vector3 Matrix4::multiply(Vector3 a)
{
    Vector3 b;
    
    //Implement Matrix * Vector3 multiplication
    //Assume the 4th component is 0
	int i;
	float temp[3];

	for (i = 0; i < 3; i++)
	{
		Vector3 b_temp = Vector3(m[0][i], m[1][i], m[2][i]);
		temp[i] = b_temp.dot(a);
	}
	b = Vector3(temp[0], temp[1], temp[2]);

    return b;
}

Vector3 Matrix4::operator * (Vector3 a)
{
    return multiply(a);
}

Matrix4 Matrix4::makeRotateX(float angle)
{
    identity();
    
    //Configure this matrix to be a rotation about the X-Axis by 'angle' radians
	m[1][2] = sin(angle);
	m[2][1] = -sin(angle);
	m[1][1] = cos(angle);
	m[2][2] = cos(angle);
    return *this;
}

Matrix4 Matrix4::makeRotateY(float angle)
{
    identity();
    
	m[0][0] = cos(angle);
	m[0][2] = -sin(angle);
	m[2][0] = sin(angle);
	m[2][2] = cos(angle);
    
    return *this;
}

Matrix4 Matrix4::makeRotateZ(float angle)
{
    identity();
	m[0][0] = cos(angle);
	m[1][0] = -sin(angle);
	m[0][1] = sin(angle);
	m[1][1] = cos(angle);
    //Configure this matrix to be a rotation about the Z-Axis by 'angle' radians
    
    return *this;
}

Matrix4 Matrix4::makeRotateArbitrary(Vector3 a, float angle)
{
    identity();
	a = a.normalize();
	Vector3 x, y, z;
	x.set(1, 0, 0);
	y.set(0, 1, 0);
	z.set(0, 0, 1);
	m[0][0] = 1 + (1 - cos(angle))*(a.dot(x) * a.dot(x) - 1);
	m[1][1] = 1 + (1 - cos(angle))*(a.dot(y) * a.dot(y) - 1);
	m[2][2] = 1 + (1 - cos(angle))*(a.dot(z) * a.dot(z) - 1);
	m[0][1] = a.dot(z)*sin(angle) + (1 - cos(angle))*a.dot(y)*a.dot(x);
	m[0][2] = -a.dot(y)*sin(angle) + (1 - cos(angle))*a.dot(z)*a.dot(x);
	m[1][0] = -a.dot(z)*sin(angle) + (1 - cos(angle))*a.dot(x)*a.dot(y);
	m[1][2] = a.dot(x)*sin(angle) + (1 - cos(angle))*a.dot(z)*a.dot(y);
	m[2][0] = a.dot(y)*sin(angle) + (1 - cos(angle))*a.dot(x)*a.dot(z);
	m[2][1] = -a.dot(x)*sin(angle) + (1 - cos(angle))*a.dot(y)*a.dot(z);
    //Configure this matrix to be a rotation about the 'a' axis by 'angle' radians
    
    return *this;
}

Matrix4 Matrix4::makeScale(float s)
{
    return makeScale(s, s, s);
}

Matrix4 Matrix4::makeScale(float sx, float sy, float sz)
{
    identity();
    
    //Configure this matrix to be a sclaing by sx, sy, sz
	m[0][0] = sx;
	m[1][1] = sy;
	m[2][2] = sz;
	m[3][3] = 1;
    return *this;
}

Matrix4 Matrix4::makeTranslate(float x, float y, float z)
{
    identity();
	m[0][0] = 1;
	m[1][1] = 1;
	m[2][2] = 1;
	m[3][3] = 1;
	m[3][0] = x;
	m[3][1] = y;
	m[3][2] = z;
    //Configure this matrix to be a translation by vector 'a'
    
    return *this;
}

Matrix4 Matrix4::makeTranslate(Vector3 a)
{
    return makeTranslate(a[0], a[1], a[2]);
}

Matrix4 Matrix4::transpose(void)
{
    Matrix4 b;
    for(int x = 0; x < 4; ++x)
    {
        for(int y = 0; y < 4; ++y)
        {
            b.m[y][x] = m[x][y];
        }
    }
    return b;
}

//Hint: Try basing this on code by cool people on the internet
//In this class it is okay to use code from the internet
//So long as you fully understand the code and can clearly explain it if asked to
//http://stackoverflow.com/questions/2624422/efficient-4x4-matrix-inverse-affine-transform
Matrix4 Matrix4::inverse(void)
{
    Matrix4 b;
    
    //Calculate the inverse of this matrix
    
    return b;
}

Matrix4 Matrix4::orthoNormalInverse(void)
{
    Matrix4 b;
    
    //Calculate the inverse of this matrix with the assumption that it is ortho-normal
    //This will be useful when implementing cameras!
    
    return b;
}

void Matrix4::print(std::string comment)
{
    //Width constants and variables
    static const int pointWidth = 1;
    static const int precisionWidth = 4;
    int integerWidth = 1;
    
    //Determine the necessary width to the left of the decimal point
    float* elementPtr = (float*)m;
    float maxValue = fabsf(*(elementPtr++));
    while(elementPtr++ < ((float*)m+16)) if(fabsf(*elementPtr) > maxValue) maxValue = fabsf(*elementPtr);
    while(maxValue >= 10.0) { ++integerWidth; maxValue /= 10.0; }
    
    //Sum up the widths to determine the cell width needed
    int cellWidth = integerWidth + pointWidth + precisionWidth;
    
    //Set the stream parameters for fixed number of digits after the decimal point
    //and a set number of precision digits
    std::cout << std::fixed;
    std::cout << std::setprecision(precisionWidth);
    
    //Print the comment
    std::cout << comment << std::endl;
    
    //Loop through the matrix elements, format each, and print them to screen
    float cellValue;
    for(int element = 0; element < 4; element++)
    {
        std::cout << std::setw(1) << (element == 0 ? "[" : " ");
        for(int vector = 0; vector < 4; vector++)
        {
            cellValue =  m[vector][element];
            std::cout << std::setw(cellWidth + (cellValue >= 0.0 ? 1 : 0)) << cellValue;
            std::cout << std::setw(0) << (vector < 3 ? " " : "");
        }
        std::cout << std::setw(1) << (element == 3 ? "]" : " ") << std::endl;
    }
}

void Matrix4::adjustProjection(double FOV, double aspect, double near, double far){
	//std::cout << "Adjusting perspective projection matrix:" << std::endl;
	identity();
	FOV = FOV / 180.0 * M_PI;  // convert from degrees to radians

	m[0][0] = (1.0) / (aspect * tan(FOV / 2));
	m[1][1] = (1.0) / tan(FOV / 2);
	m[2][2] = (near + far) / (near - far);
	m[3][3] = 0.0;

	m[2][3] = -1.0;
	m[3][2] = (2 * near*far) / (near - far);
}

void Matrix4::viewPortToWindowSize(double x0, double x1, double y0, double y1){
	//std::cout << "Adjusting viewport matrix:" << std::endl;
	identity();
	m[0][0] = (x1 - x0) / 2;
	m[1][1] = (y1 - y0) / 2;
	m[2][2] = 1.0 / 2.0;
	m[3][3] = 1.0;

	m[3][0] = (x0 + x1) / 2;
	m[3][1] = (y0 + y1) / 2;
	m[3][2] = 1.0 / 2.0;
}