///Basic Libs
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <map>
#include <time.h>

#include<windows.h>    
#include<fstream>
#pragma comment (lib, "winmm.lib")

//OpenGL Libs
#include <glew.h>
#include <glfw3.h>
#include <ext.hpp>


//FREETYPE 
#include <ft2build.h>
#include FT_FREETYPE_H

//Project Libs
#include "Drawings.h"
#include "Writer.h"
#include "Player.h"
#include "Block.h"
#include "piece.h"
#include "Board.h"
#include "GameController.h"
#include "Controller.h"




Controller  controller;



//Function with all the necessary procedures to start a screen.
int InitWindow(GLfloat *width, GLfloat*heigth)
{
    
    // Initialize the library
    if (!glfwInit()) return -1;

    // Getting monitor parameters
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    *width = mode->width*0.9;
    *heigth = mode->height*0.9;
    
    return 0;

}


//Function with all the necessary procedures to configure inputs(keyboar,mouse)
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
  
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
    {
        double X, Y;
        glfwGetCursorPos(window, &X, &Y);
        controller.Mouse(X, Y, window);

    }

}

void character_callback(GLFWwindow* window, unsigned int codepoint)
{
    controller.character_callback(window, codepoint);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    controller.keyCallback(window, key, scancode, action, mods);
}

void SetInputs(GLFWwindow* window)
{
    
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, 1);
    glfwSetCharCallback(window, character_callback);

    glfwSetKeyCallback(window,keyCallback);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);
}


int main()
{
    
    
    //Starting window and screen
    GLfloat width;   // will store the screen size
    GLfloat height ; // will store the screen size
    InitWindow(&width, &height);// getting screen size
    GLFWwindow* Window = glfwCreateWindow(width, height, "TETRIS3D", nullptr, nullptr);

    //Verifying that the window was created correctly
    if (!Window)
    {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(Window);
    
    // specifies the part of the window to which OpenGL will draw (in pixels), convert from normalised to pixels
    glViewport(0.0f, 0.0f, width, height);
    glMatrixMode(GL_PROJECTION); // projection matrix defines the properties of the camera that views the objects in the world coordinate frame. Here you typically set the zoom factor, aspect ratio and the near and far clipping planes
    glLoadIdentity(); // replace the current matrix with the identity matrix and starts us a fresh because matrix transforms such as glOrpho and glRotate cumulate, basically puts us at (0, 0, 0)
    glOrtho(0, width, 0, height, 0, 3000); // essentially set coordinate system
    glMatrixMode(GL_MODELVIEW); // (default matrix mode) modelview matrix defines how your objects are transformed (meaning translation, rotation and scaling) in your world
    glLoadIdentity(); // same as above comment

    //Configuring necessary parameters to get input data (mouse and keyboard)
    SetInputs(Window);

    
    //Configuring the object that manage the things that are write in the screen
    Writer writer = Writer(width, height);

 

   //Object that will control all the game;
    controller = Controller(Window, width, height, &writer);


    
    // Loop until the user closes the window
    while (!glfwWindowShouldClose(Window) && !controller.CheckExit())
    {
        glClear(GL_COLOR_BUFFER_BIT);
        int width_;   
        int height_;
        glfwGetWindowSize(Window, &width_, &height_);
        if (width != width_ || height != height_)
        {
            width = width_;
            height = height_;
            controller.updatewindow(width, height);
        }
        

        //writing
        writer.DrawText();

        // drawing
        controller.ControllerDrawObjects();
        
        glfwSwapBuffers(Window);
        glfwPollEvents();
 
    }

   

    glfwTerminate();

    return 0;
}







