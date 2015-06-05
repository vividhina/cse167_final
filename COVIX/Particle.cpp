#include "Particle.h"
#include "Globals.h"

//#include <gl\gl.h>					// Header File For The OpenGL32 Library
//#include <gl\glu.h>					// Header File For The GLu32 Library
#include "bmp.h"		     		// Header File For Read .bmp file
//#include <gl\GL.h>
#include <gl\glut.h>
#include "Window.h"
#include "math.h"
#include <iostream>

#define	MAX_PARTICLES	1000		// Number Of Particles To Create
float	slowdown = 2.0f;				// Slow Down Particles
float	xspeed;						// Base X Speed (To Allow Keyboard Direction Of Tail)
float	yspeed;						// Base Y Speed (To Allow Keyboard Direction Of Tail)
float	zoom = -40.0f;				// Used To Zoom Out
GLuint	col;						// Current Color Selection
GLuint	texture[1];					// Storage For Our Particle Texture


static GLfloat colors[12][3] =		// Rainbow Of Colors
{
	{ 1.0f, 0.5f, 0.5f }, { 1.0f, 0.75f, 0.5f }, { 1.0f, 1.0f, 0.5f }, { 0.75f, 1.0f, 0.5f },
	{ 0.5f, 1.0f, 0.5f }, { 0.5f, 1.0f, 0.75f }, { 0.5f, 1.0f, 1.0f }, { 0.5f, 0.75f, 1.0f },
	{ 0.5f, 0.5f, 1.0f }, { 0.75f, 0.5f, 1.0f }, { 1.0f, 0.5f, 1.0f }, { 1.0f, 0.5f, 0.75f }
};

AUX_RGBImageRec* Particle::LoadBMP(char *Filename)				// Loads A Bitmap Image
{
	FILE *File = NULL;								// File Handle
	if (!Filename)									// Make Sure A Filename Was Given
	{
		return NULL;							// If Not Return NULL
	}
	File = fopen(Filename, "r");						// Check To See If The File Exists
	if (File)										// Does The File Exist?
	{
		fclose(File);								// Close The Handle
		return auxDIBImageLoad(Filename);			// Load The Bitmap And Return A Pointer
	}
	return NULL;									// If Load Failed Return NULL
}

int Particle::LoadGLTextures(){
	int Status = FALSE;								// Status Indicator
	AUX_RGBImageRec *TextureImage[1];				// Create Storage Space For The Textures
	memset(TextureImage, 0, sizeof(void *) * 1);		// Set The Pointer To NULL

	if (TextureImage[0] = LoadBMP("Particle.bmp"))	// Load Particle Texture
	{
		Status = TRUE;								// Set The Status To TRUE
		glGenTextures(1, &texture[0]);				// Create One Texture

		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
	}

	if (TextureImage[0])							// If Texture Exists
	{
		if (TextureImage[0]->data)					// If Texture Image Exists
		{
			free(TextureImage[0]->data);			// Free The Texture Image Memory
		}
		free(TextureImage[0]);						// Free The Image Structure
	}
	return Status;									// Return The Status
}


Particle::Particle(){}

Particle::~Particle(){}

void Particle::init(int loop)
{
	LoadGLTextures();
	active = true;								// Make All The Particles Active
	life = 1.0f;								// Give All The Particles Full Life
	fade = float(rand() % 100) / 1000.0f + 0.003f;	// Random Fade Speed
	r = colors[loop*(12 / MAX_PARTICLES)][0];	// Select Red Rainbow Color
	g = colors[loop*(12 / MAX_PARTICLES)][1];	// Select Red Rainbow Color
	b = colors[loop*(12 / MAX_PARTICLES)][2];	// Select Red Rainbow Color
	xi = float((rand() % 50) - 26.0f)*10.0f;		// Random Speed On X Axis
	yi = float((rand() % 50) - 25.0f)*10.0f;		// Random Speed On Y Axis
	zi = float((rand() % 50) - 25.0f)*10.0f;		// Random Speed On Z Axis
	xg = 0.0f;									// Set Horizontal Pull To Zero
	yg = -0.8f;								// Set Vertical Pull Downward
	zg = 0.0f;									// Set Pull On Z Axis To Zero

}

void Particle::draw(DrawData& data)
{
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear Screen And Depth Buffer
	//glLoadIdentity();										// Reset The ModelView Matrix
	//Se the OpenGL Matrix mode to ModelView (used when drawing geometry)
	glMatrixMode(GL_MODELVIEW);

	//Push a save state onto the matrix stack, and multiply in the toWorld matrix
	glPushMatrix();
	glMultMatrixf(toWorld.ptr());

	if (active)							// If The Particle Is Active
	{
		//float x = x;						// Grab Our Particle X Position
		//float y = y;						// Grab Our Particle Y Position
		//float z = z;					// Particle Z Pos + Zoom

		// Draw The Particle Using Our RGB Values, Fade The Particle Based On It's Life
		glColor4f(r, g, b, life);
		//glBindTexture(GL_TEXTURE_2D, texture[0]);			// Select Our Texture
		glBegin(GL_TRIANGLE_STRIP);						// Build Quad From A Triangle Strip
		glTexCoord2d(1, 1); glVertex3f(x + 0.5f, y + 0.5f, z); // Top Right
		glTexCoord2d(0, 1); glVertex3f(x - 0.5f, y + 0.5f, z); // Top Left
		glTexCoord2d(1, 0); glVertex3f(x + 0.5f, y - 0.5f, z); // Bottom Right
		glTexCoord2d(0, 0); glVertex3f(x - 0.5f, y - 0.5f, z); // Bottom Left
		glEnd();										// Done Building Triangle Strip

		x += xi / (slowdown * 1000);// Move On The X Axis By X Speed
		y += yi / (slowdown * 1000);// Move On The Y Axis By Y Speed
		z += zi / (slowdown * 1000);// Move On The Z Axis By Z Speed

		xi += xg;			// Take Pull On X Axis Into Account
		yi += yg;			// Take Pull On Y Axis Into Account
		zi += zg;			// Take Pull On Z Axis Into Account
		life -= fade;		// Reduce Particles Life By 'Fade'

		if (life < 0.0f)					// If Particle Is Burned Out
		{
			life = 1.0f;					// Give It New Life
			fade = float(rand() % 100) / 1000.0f + 0.003f;	// Random Fade Value
			x = 0.0f;						// Center On X Axis
			y = 0.0f;						// Center On Y Axis
			z = 0.0f;						// Center On Z Axis
			xi = xspeed + float((rand() % 60) - 32.0f);	// X Axis Speed And Direction
			yi = yspeed + float((rand() % 60) - 30.0f);	// Y Axis Speed And Direction
			zi = float((rand() % 60) - 30.0f);	// Z Axis Speed And Direction
			r = colors[2][0];			// Select Red From Color Table
			g = colors[2][1];			// Select Green From Color Table
			b = colors[2][2];			// Select Blue From Color Table
		}
	}
	glPopMatrix();

}