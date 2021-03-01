
#include <glew.h>
#include <glfw3.h>
#include "cDisplay.h"




Display::Display(int width, int height, const std::string & title, Mouse &dmouse)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(WIDTH, HEIGHT, "VACCUM", nullptr, nullptr);
	
	//MOUSE
	
	glfwSetCursorPosCallback(window, mouse.cursorPositionCallback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glfwSetCursorEnterCallback(window, mouse.cursorEnterCallback);
	glfwSetMouseButtonCallback(window, mouse.mouseButtonCallback);
	glfwSetScrollCallback(window, mouse.scrollCallback);
	glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, 1);

	//new mouse image
	GLFWimage image; //= mouse.CreateMouseImage(10, 10);
	unsigned char pixels[16 * 16 * 4];
	memset(pixels, 0xff, sizeof(pixels));
	image.width = 10;
	image.height = 10;
	image.pixels = pixels;

	GLFWcursor *cursor = glfwCreateCursor(&image, 0, 0);
	glfwSetCursor(window, cursor);

	//CHECK ERRORS
	int screenWidth = width;
	int screenHeight = height;

	if (nullptr == window)
	{
		std::cout << "FAILED\n";
		glfwTerminate();
	}
	else
	{
		cout << "\WINDOW CREATED";
	}

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;

	if (GLEW_OK != glewInit())
	{
		std::cout << "\nFAILED TO GLEW\n";
	}

	glViewport(0, 0, screenWidth, screenHeight);

}

Display::~Display()
{
	glfwTerminate();
}

void Display::SwapBuffers()
{
	//cout << "SWAPING BUFFER";
	glfwSwapBuffers(window);
}

void Display::Update()
{
	//cout << "UPDATING";
	glfwPollEvents();
}

void Display::UpdateMouse(double & x, double & y, int &b)
{
	glfwGetCursorPos(window, &x, &y);
	glfwGetMouseButton(window, b);

}

//void mouseClick(int button, int buttonState, int x, int y) 
//{
//
//
//		GLint viewport[4]; //var to hold the viewport info
//		GLdouble modelview[16]; //var to hold the modelview info
//		GLdouble projection[16]; //var to hold the projection matrix info
//		GLfloat winX, winY, winZ; //variables to hold screen x,y,z coordinates
//		GLdouble worldX, worldY, worldZ; //variables to hold world x,y,z coordinates
//
//		glGetDoublev(GL_MODELVIEW_MATRIX, modelview); //get the modelview info
//		glGetDoublev(GL_PROJECTION_MATRIX, projection); //get the projection matrix info
//		glGetIntegerv(GL_VIEWPORT, viewport); //get the viewport info
//
//		winX = (float)x;
//		winY = (float)viewport[3] - (float)y;
//		winZ = 0;
//
//		//get the world coordinates from the screen coordinates
//		gluUnProject(winX, winY, winZ, modelview, projection, viewport, &amp; worldX, &amp; worldY, &amp; worldZ);
//
//
//}