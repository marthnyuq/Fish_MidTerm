#pragma once
#include "Menu.h"

Image imgScore;
Rect score = { w / 2 -400 , w / 2 + 400, h / 2 - 100, 800 };
Rect Play = { w / 2 + 200, w / 2 + 300, h / 2 - 150, 100 };
Rect Exit = { w / 2 - 200, w / 2 - 100, h / 2 - 150, 100 };

class Guide
{

public:
	void loadImg();
	void init();
};

void display3()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	Map_Texture(&imgBG);
	Draw_Rect(&Rct_BG);
	Map_Texture(&imgPlay);
	Draw_Rect(&Play);
	Map_Texture(&imgExit);
	Draw_Rect(&Exit);
	Map_Texture(&imgScore);
	Draw_Rect(&score);

	glutSwapBuffers();
}

void Guide::loadImg()
{

	Load_Texture_Swap(&imgBG, "Image/background1.png");
	Zoom_Image(&imgBG, 3);
	Load_Texture_Swap(&imgPlay, "Image/playBt.png");
	Zoom_Image(&imgPlay, 1);
	Load_Texture_Swap(&imgExit, "Image/exitBt.png");
	Zoom_Image(&imgExit, 1);
	Load_Texture_Swap(&imgScore, "Image/guide.png");
	Zoom_Image(&imgScore, 1);

}

void Guide::init()
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


	Guide::loadImg();
}
