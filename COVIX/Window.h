#ifndef CSE167_Window_h
#define CSE167_Window_h

class Window	  // OpenGL output window related routines
{
    
public:
    
    static int width, height; 	            // window size
	static int light_type;
    
    static void initialize(void);
    static void idleCallback(void);
    static void reshapeCallback(int, int);
    static void displayCallback(void);
	static void keyboard(unsigned char, int, int);
	static void specialkey(int, int, int);
	static void mouse(int, int, int, int);
//	static Vector3 trackBallMapping(int, int);
	static void OnMouseMove(int, int);

    
};

#endif

