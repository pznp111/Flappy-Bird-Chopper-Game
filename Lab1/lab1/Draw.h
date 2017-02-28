#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
//#include "glew.h"
//#include "freeglut.h"
#define _USE_MATH_DEFINES
#include "math.h"
#include <list>
#include "ctime"
#include "string"
#include <GL/glut.h>
#include <iostream>
#include <ios>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <vector>
#include <fstream>
#include <algorithm>
#include <windows.h>
#include <mmsystem.h>


using namespace std;

//statics global variable
static float jumpHigh = 0.25;
static float gravity = -0.01;
static long score = 0;
static bool isPaused = false;
static int frame = 0;
static bool isStarted = false;
//static bool isBounceBack = false;
static int winWidth = 600;
static int winHeight = 600;
static GLfloat PI = 3.14;
static bool isDrawn = false;
static bool isDeathDrawn = false;
static int posX = 20;
static int posY = 20;
static GLuint texSet[9];
static int diffIndex = 3;

void chopper(double);