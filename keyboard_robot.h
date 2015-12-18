
#ifndef KEYBOARD_ROBOT_H
#define KEYBOARD_ROBOT_H

#define GLFW_DLL

#include "GL/glfw.h"

#include <math.h>
#include <stdio.h>

#pragma comment( lib, "glu32.lib" )
#pragma comment( lib, "opengl32.lib" )
#pragma comment( lib, "glfw.lib" )
#pragma comment( lib, "glfwdll.lib" )


#define MAXFRAME 300.0

void makebox(double width, double height, double length, GLenum type=GL_LINE_LOOP);
void makeboxB(double width, double height, double length, GLenum type);
void makeboxROBOT( double width, double height, double length, GLenum type=GL_LINE_LOOP);
void makeGear(double radius, double thick, double cog_height, int cog_num, double hole=0);

int randN();

#endif	/* KEYBOARD_ROBOT_H */
