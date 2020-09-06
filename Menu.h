#pragma once
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <gl\glut.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <iostream>
#include <string>
using namespace std;

#include "Linking\LIBABRY\loadpng.h"
#include "Linking\LIBABRY\process_image.h"
#include "Linking\LIBABRY\gl_texture.h"


struct Point {
	int x, y;
};
int w = 1520, h = 855;
Image imgBG, imgPlay, imgExit, imgGuide, imgLogo;
Rect Rct_BG = { 0, w, 0, h };
Rect Play_Button = { w / 2 - 50, w / 2 + 50, h / 2, 250 };
Rect Exit_Button = { w / 2 - 200, w / 2 - 100, h / 2 - 150, 100 };
Rect Guide_Button = { w / 2 + 100, w / 2 + 200, h / 2 - 150, 100 };
class menu
{

public:
	void loadImg();
	void init();
};

void display2()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	Map_Texture(&imgBG);
	Draw_Rect(&Rct_BG);
	Map_Texture(&imgPlay);
	Draw_Rect(&Play_Button);
	Map_Texture(&imgExit);
	Draw_Rect(&Exit_Button);
	Map_Texture(&imgGuide);
	Draw_Rect(&Guide_Button);

	glutSwapBuffers();
}

void menu::loadImg()
{

	Load_Texture_Swap(&imgBG, "Image/background1.png");
	Zoom_Image(&imgBG, 3);
	Load_Texture_Swap(&imgPlay, "Image/playBt.png");
	Zoom_Image(&imgPlay, 1);
	Load_Texture_Swap(&imgExit, "Image/exitBt.png");
	Zoom_Image(&imgExit, 1);
	Load_Texture_Swap(&imgGuide, "Image/guideBt.png");
	Zoom_Image(&imgGuide, 1);

}

void menu::init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluOrtho2D(0, w, 0, h);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_LINE_SMOOTH);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glutIgnoreKeyRepeat(GL_TRUE);
	glEnable(GL_TEXTURE_2D);


	menu::loadImg();
}



//void myMouse(int button, int state, int x, int y) {
//	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
//	{
//		if (x <  810 && x > 709 && y < 580 && y > 416)
//		{
//			cout << "            Play          " << endl;
//			win2 = glutCreateWindow("Hungry Fish");
//			glutSetCursor(GLUT_CURSOR_NONE);
//			init();
//			glutDisplayFunc(display);
//			glutTimerFunc(0, Timer, 0);
//			glutPassiveMotionFunc(mouseHover);
//
//			glutDestroyWindow(win1);
//		}
//		if (x < 660 && x > 560 && y < 728 && y > 560)
//		{
//			/*exit(1);*/
//		}
//		if (x < 960 && x > 860 && y < 728 && y > 560)
//		{
//			cout << "            guide          " << endl;
//		}
//	}
//}