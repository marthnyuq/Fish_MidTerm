#include "Menu.h"
#include "Guide.h"

#define WIDTH 1520
#define HEIGHT 855

#define INTERVAL 15
#define SCALE 2

#define F1_SCORE 5
#define F2_SCORE 10
#define F3_SCORE 15

int F1_count = 0;
int F2_count = 0;
int F3_count = 0;
//float BOUNDARY_LEFT = 0.0f, BOUNDARY_RIGHT = WIDTH;
int LEVEL = 1, Score = 0, live = 3;
bool isLiving = true;

int win1, win2, winGuide;
int x = 100;
int y = HEIGHT - 100;

Rect Rect_Background = { 0,WIDTH, 0, HEIGHT };
Image Img_Background;

string a[3] = { "Image/player_lv1.png", "Image/player_lv2.png", "Image/player_lv3.png" };
#pragma region Fish_Lv1
class Fish_Lv1 {
public:
	struct FishPos {
		float x, y;
		float dir = -1;
	}f;
	static Image Img_save[2][2]; //[dir(l/r:0/1)][eat]

	Rect rect;
	Image* Img;

	int level;
	int Drt = 0.0, Timer, Anim;

	void Init(int _level, int x, int y)
	{
		level = _level;
		Drt = 0;
		Anim = 0;
		f.x = x;
		f.y = y;
		//isEating = false;
		Update_Image();
		Update_Rect(); //105, 107
		//112, 113.5
	}

	void Update_Image() { Img = &Img_save[Drt][Anim]; }
	void Update_Rect() {
		rect.Left = f.x - Img->w / 2;
		rect.Right = rect.Left + Img->w;
		rect.Bottom = f.y;
		rect.Top = rect.Bottom + Img->h;
		//cout << "RECT: " << rect.Left << ", " << rect.Right << ", " << rect.Bottom << ", " << rect.Top << endl;
	}

	void Draw() {
		Map_Texture(Img);
		Draw_Rect(&rect);
	}


	static bool Check_Boundary_Left(float x) { return x < -50; }
	static bool Check_Boundary_Right(float x) { return x > WIDTH + 50; }
	static bool Check_Boundary_Bottom(float y) { return y < 0 - 50; }
	static bool Check_Boundary_Top(float y) { return y > HEIGHT + 50; }
	void move() {
		Update_Image();
		Update_Rect();
	}

	float offsetX = 1, offsetY = 0.5;
	void setPos(FishPos& f)
	{
		if (Check_Boundary_Left(f.x))
		{
			Drt = 1;
			f.dir = 1;
		}
		else if (Check_Boundary_Right(f.x))
		{
			Drt = 0;
			f.dir = -1;
		}
		if (Check_Boundary_Bottom(f.y))
		{
			offsetY = 1;
		}
		else if (Check_Boundary_Top(f.y))
		{
			offsetY = -1;
		}
		f.x += f.dir;
		f.y += offsetY;
	}

	bool is_Caught(float _x, float _y, int scale, int w, int h) //player position
	{
		//cout << "IS_CAUGHT[LV1]: " << Img->w << " " << Img->h << endl;
		/*if (_x - (Img->w * scale) < f.x && _x + (Img->w * scale) > f.x && _y - (Img->h * scale) < f.y && _y + (Img->h * scale) > f.y)
			return true;
		return false;*/
		if (f.x > _x - (w * scale) / 2 && f.x < _x + (w * scale) / 2 && f.y > _y - (h * scale) / 2 && f.y < _y + (h * scale) / 2)
			return true;
		return false;
	}
	void update()
	{

		setPos(f);
		Timer++;
		if (Timer == 10)
		{
			Timer = 0;
			Anim = 1 - Anim;
			//cout << "Anim: " << Anim << endl;
			Img = &Img_save[Drt][Anim];
		}
		//f.y += offsetY;
		Update_Image();
		Update_Rect();
	}
	static void Load_Image(int level) {
		Image Img;
		Load_Texture(&Img, "Image/fish1.png");
		Crop_Image(&Img, &Img_save[0][0], 0, 0, 46.5, 48);
		Crop_Image(&Img, &Img_save[0][1], 0, 46.5, 46.5, 48);
		Crop_Image(&Img, &Img_save[1][0], 46.5, 0, 46.5, 48);
		Crop_Image(&Img, &Img_save[1][1], 46.5, 48, 46.5, 48);
		/*Swap_Image(Img_save[0][0][level].img, 46.5, 48);
		Swap_Image(Img_save[0][1][level].img, 46.5, 48);
		Swap_Image(Img_save[1][0][level].img, 46.5, 48);
		Swap_Image(Img_save[1][1][level].img, 46.5, 48);*/
		Zoom_Image(&Img_save[0][0], level);
		Zoom_Image(&Img_save[0][1], level);
		Zoom_Image(&Img_save[1][0], level);
		Zoom_Image(&Img_save[1][1], level);

		Delete_Image(&Img);
	}
};
Image Fish_Lv1::Img_save[2][2];
Fish_Lv1 f1;
vector<Fish_Lv1> F_level1;
#pragma endregion

#pragma region Fish_Lv2
class Fish_Lv2 { //350, 216
public:
	struct FishPos {
		float x, y;
		float dir = -1;
	}f;
	static Image Img_save[2][2];
	Rect rect;
	Image* img;
	int Drt = 0.0, Timer, Anim;
	void init(int x, int y)
	{
		Drt = 0;
		Anim = 0;
		f.x = x;
		f.y = y;
		Update_Image();
		Update_Rect();
	}
	void Update_Image() { img = &Img_save[Drt][Anim]; }
	void Update_Rect()
	{
		rect.Left = f.x - img->w / 2;
		rect.Right = rect.Left + img->w;
		rect.Bottom = f.y;
		rect.Top = rect.Bottom + img->h;
	}
	void Draw() {
		Map_Texture(img);
		Draw_Rect(&rect);
	}
	static bool Check_Boundary_Left(float x) { return x < -50; }
	static bool Check_Boundary_Right(float x) { return x > WIDTH + 50; }
	static bool Check_Boundary_Bottom(float y) { return y < 0 - 50; }
	static bool Check_Boundary_Top(float y) { return y > HEIGHT + 50; }

	float offsetX = 1, offsetY = 0.5;
	void setPos(FishPos& f)
	{
		if (Check_Boundary_Left(f.x))
		{
			Drt = 1;
			f.dir = 1;
		}
		else if (Check_Boundary_Right(f.x))
		{
			Drt = 0;
			f.dir = -1;
		}
		if (Check_Boundary_Bottom(f.y))
		{
			offsetY = 1;
		}
		else if (Check_Boundary_Top(f.y))
		{
			offsetY = -1;
		}
		f.x += f.dir;
		f.y += offsetY;
	}
	void update()
	{
		setPos(f);
		/*Timer++;
		if (Timer == 20)
		{
			Timer = 0;
			Anim = 1 - Anim;
			//cout << "Anim: " << Anim << endl;
			img = &Img_save[Drt][Anim];
		}*/
		vector<Fish_Lv1>::iterator it = F_level1.begin();
		while (it != F_level1.end()) {
			if (it->is_Caught(f.x, f.y, 1, img->w, img->h)) {
				//cout << "CATCHED[LV2]: " << img->w << " " << img->h << endl;
				it = F_level1.erase(it);
				//update score
			}
			else
			{
				it++;
			}
		}
		Update_Image();
		Update_Rect();
	}
	bool is_Caught(float _x, float _y, int scale, int w, int h) //player position
	{
		//cout << "IS_CAUGHT[LV1]: " << Img->w << " " << Img->h << endl;
		/*if (_x - (Img->w * scale) < f.x && _x + (Img->w * scale) > f.x && _y - (Img->h * scale) < f.y && _y + (Img->h * scale) > f.y)
			return true;
		return false;*/
		if (f.x > _x - (w * scale) / 2 && f.x < _x + (w * scale) / 2 && f.y > _y - (h * scale) / 2 && f.y < _y + (h * scale) / 2)
			return true;
		return false;
	}
	static void Load_Image(int level) {
		Image Img;
		Load_Texture(&Img, "Image/fish2.png");
		Crop_Image(&Img, &Img_save[0][0], 0, 0, 150, 86);
		Crop_Image(&Img, &Img_save[0][1], 0, 86, 150, 86);
		Crop_Image(&Img, &Img_save[1][0], 150, 0, 150, 86);
		Crop_Image(&Img, &Img_save[1][0], 150, 86, 150, 86);
		Zoom_Image(&Img_save[0][0], level);
		Zoom_Image(&Img_save[0][1], level);
		Zoom_Image(&Img_save[1][0], level);
		Zoom_Image(&Img_save[1][1], level);

		Delete_Image(&Img);
	}
};
Image Fish_Lv2::Img_save[2][2];
Fish_Lv2 f2;
vector<Fish_Lv2> F_level2;
#pragma endregion

#pragma region Fish_Lv3
class Fish_Lv3 {
public:
	struct FishPos {
		float x, y;
		float dir = -1;
	}f;
	static Image Img_save[2][2];
	Rect rect;
	Image* img;
	int Drt = 0.0, Timer, Anim;
	void init(int x, int y)
	{
		Drt = 0;
		Anim = 0;
		f.x = x;
		f.y = y;
		Update_Image();
		Update_Rect();
	}
	void Update_Image() { img = &Img_save[Drt][Anim]; }
	void Update_Rect()
	{
		rect.Left = f.x - img->w / 2;
		rect.Right = rect.Left + img->w;
		rect.Bottom = f.y;
		rect.Top = rect.Bottom + img->h;
	}
	void Draw() {
		Map_Texture(img);
		Draw_Rect(&rect);
	}
	static bool Check_Boundary_Left(float x) { return x < -50; }
	static bool Check_Boundary_Right(float x) { return x > WIDTH + 50; }
	static bool Check_Boundary_Bottom(float y) { return y < 0 - 50; }
	static bool Check_Boundary_Top(float y) { return y > HEIGHT + 50; }

	float offsetX = 1, offsetY = 0.5;
	void setPos(FishPos& f)
	{
		if (Check_Boundary_Left(f.x))
		{
			Drt = 1;
			f.dir = 1;
		}
		else if (Check_Boundary_Right(f.x))
		{
			Drt = 0;
			f.dir = -1;
		}
		/*if (Check_Boundary_Bottom(f.y))
		{
			offsetY = 1;
		}
		else if (Check_Boundary_Top(f.y))
		{
			offsetY = -1;
		}*/
		f.x += f.dir;
	}
	void update()
	{
		setPos(f);
		Timer++;
		if (Timer == 20)
		{
			Timer = 0;
			Anim = 1 - Anim;
			//cout << "Anim: " << Anim << endl;
			img = &Img_save[Drt][Anim];
		}
		vector<Fish_Lv1>::iterator it = F_level1.begin();
		while (it != F_level1.end()) {
			if (it->is_Caught(f.x, f.y, 1, img->w, img->h)) {
				//cout << "CATCHED[LV2]: " << img->w << " " << img->h << endl;
				it = F_level1.erase(it);
				//update score
			}
			else
			{
				it++;
			}
		}
		vector<Fish_Lv2>::iterator it2 = F_level2.begin();
		while (it2 != F_level2.end())
		{
			if (it2->is_Caught(f.x, f.y, 1, img->w, img->h)) {
				it2 = F_level2.erase(it2);
			}
			else
			{
				it2++;
			}
		}
		Update_Image();
		Update_Rect();
	}
	bool is_Caught(float _x, float _y, int scale, int w, int h) //player position
	{
		//cout << "IS_CAUGHT[LV1]: " << Img->w << " " << Img->h << endl;
		/*if (_x - (Img->w * scale) < f.x && _x + (Img->w * scale) > f.x && _y - (Img->h * scale) < f.y && _y + (Img->h * scale) > f.y)
			return true;
		return false;*/
		if (f.x > _x - (w * scale) / 2 && f.x < _x + (w * scale) / 2 && f.y > _y - (h * scale) / 2 && f.y < _y + (h * scale) / 2)
			return true;
		return false;
	}
	static void Load_Image(int level) {
		Image Img;
		int w, h;
		Load_Texture(&Img, "Image/shark.png");
		w = Img.w / 2; h = Img.h / 2;
		Crop_Image(&Img, &Img_save[0][0], 0, 0, w, h);
		Crop_Image(&Img, &Img_save[0][1], 0, h, w, h);
		Crop_Image(&Img, &Img_save[1][0], w, 0, w, h);
		Crop_Image(&Img, &Img_save[1][1], w, h, w, h);

		Zoom_Image(&Img_save[0][0], 1);
		Zoom_Image(&Img_save[0][1], 1);
		Zoom_Image(&Img_save[1][0], 1);
		Zoom_Image(&Img_save[1][1], 1);

		Delete_Image(&Img);
	}
};
Image Fish_Lv3::Img_save[2][2];
Fish_Lv3 f3;
vector<Fish_Lv3> F_level3;
#pragma endregion

#pragma region Urchin
class Urchin {
public:
	struct Pos {
		float x, y;
	}p;
	static Image Img_save[2]; //[dir(l/r:0/1)][eat]

	Rect rect;
	Image* Img;


	void Init(int x, int y)
	{
		p.x = x;
		p.y = y;
		//isEating = false;
		Update_Image();
		Update_Rect(); //105, 107
		//112, 113.5
	}

	void Update_Image() { Img = &Img_save[1]; }
	void Update_Rect() {
		rect.Left = p.x - Img->w / 2;
		rect.Right = rect.Left + Img->w;
		rect.Bottom = p.y;
		rect.Top = rect.Bottom + Img->h;
	}

	void Draw() {
		Map_Texture(Img);
		Draw_Rect(&rect);
	}

	bool is_Caught(float _x, float _y, int scale, int w, int h) //player position
	{
		if (p.x > _x - (w * scale) / 2 && p.x < _x + (w * scale) / 2 && p.y > _y - (h * scale) / 2 && p.y < _y + (h * scale) / 2)
			return true;
		return false;
	}
	static bool Check_Boundary_Bottom(float y) { return y < 0 - 50; }
	static bool Check_Boundary_Top(float y) { return y > HEIGHT + 50; }
	int offsetY = 1;
	void setPos(Pos &f)
	{
		if (Check_Boundary_Bottom(f.y))
		{
			offsetY = 1;
		}
		else if (Check_Boundary_Top(f.y))
		{
			offsetY = -1;
		}
		f.y += offsetY;
	}
	void update()
	{
		setPos(p);
		Update_Image();
		Update_Rect();
	}
	static void Load_Image(int level) {
		Image Img;
		Load_Texture(&Img, "Image/urchin.png");
		Crop_Image(&Img, &Img_save[0], 0, 0, 100, 100);
		Crop_Image(&Img, &Img_save[1], 100, 0, 100, 100);

		Zoom_Image(&Img_save[0], 1);
		Zoom_Image(&Img_save[1], 1);

		Delete_Image(&Img);
	}
};
Image Urchin::Img_save[2];
Urchin u;
vector<Urchin> Urchins;
#pragma endregion

#pragma region Spawn_Fish
class Spawn_Fish {
public:
	void update_lv1()
	{
		for (int i = 0; i < 10; i++)
		{
			f1.Init(1, rand() % WIDTH, rand() % HEIGHT);
			F_level1.push_back(Fish_Lv1(f1));
		}
	}
	void update_lv2()
	{
		for (int i = 0; i < 3; i++)
		{
			f2.init(rand() % WIDTH, rand() % HEIGHT);
			F_level2.push_back(Fish_Lv2(f2));
		}
	}
	void update_lv3()
	{
		f3.init(0, rand() % HEIGHT);
		F_level3.push_back(Fish_Lv3(f3));
		f3.init(WIDTH, rand() % HEIGHT);
		F_level3.push_back(Fish_Lv3(f3));
	}
	void update_urchin()
	{
		u.Init(rand() % WIDTH, HEIGHT);
		Urchins.push_back(Urchin(u));
		u.Init(rand() % WIDTH, 0);
		Urchins.push_back(Urchin(u));
	}
};
Spawn_Fish s;
#pragma endregion

#pragma region Fish_Player
class Fish {
public:
	struct FishPos {
		float x, y;
		float dir = -1;
	}f;
	static Image Img_Save[2][2]; //[dir(l/r:0/1)][eat]

	Rect rect;
	Image* Img;

	int level = 1;
	int Drt = 0.0, Anim;
	//int Score;

	void Init(int _level, int x, int y)
	{
		level = _level;
		Drt = 0;
		Anim = 0;
		f.x = x;
		f.y = y;
		Update_Image();
		Update_Rect(); //105, 107
		//112, 113.5
		//Score = 0;

	}

	void Update_Image() { Img = &Img_Save[Drt][Anim]; }
	void Update_Rect() {
		rect.Left = f.x - (Img->w / 2);
		rect.Right = rect.Left + Img->w;
		rect.Bottom = f.y;
		rect.Top = rect.Bottom + Img->h;
	}

	void Draw() {
		Map_Texture(Img);
		Draw_Rect(&rect);
	}
	bool is_Caught(float _x, float _y, int scale, int w, int h) //player position
	{
		if (f.x > _x - (w * scale) / 2 && f.x < _x + (w * scale) / 2 && f.y > _y - (h * scale) / 2 && f.y < _y + (h * scale) / 2)
			return true;
		return false;
	}


	void move()
	{
		#pragma region Urchin
		vector<Urchin>::iterator it_u = Urchins.begin();
		while (it_u != Urchins.end()) {
			if (it_u->is_Caught(f.x, f.y, 1, Img->w, Img->h)) {
				//Load_Image1(1);
				//system("pause");
				exit(1);
			}
			else
			{
				it_u++;
			}
		}
		#pragma endregion

		#pragma region Fish_LV1_Caught
		vector<Fish_Lv1>::iterator it = F_level1.begin();
		while (it != F_level1.end()) {
			if (it->is_Caught(f.x, f.y, 1, Img->w, Img->h)) {
				it = F_level1.erase(it);
				F1_count += 1;
				//cout << F1_count;
				//update score
				Score += 10;
			}
			else
			{
				it++;
			}
		}
		#pragma endregion

		#pragma region Fish_LV2_BeingCaught_Caught
		vector<Fish_Lv2>::iterator it2 = F_level2.begin();
		while (it2 != F_level2.end()) {
			if (LEVEL < 2) //being caught
			{
				if (it2->is_Caught(f.x, f.y, 1, it2->img->w, it2->img->h))
				{
					Init(LEVEL, WIDTH / 2, HEIGHT / 2);
					Score = 0;
				}
				else
				{
					it2++;
				}
			}
			else
			{
				//cout << "upLevel()\n";
				if (it2->is_Caught(f.x, f.y, 1, it2->img->w, it2->img->h))
				{
					it2 = F_level2.erase(it2);
					F2_count += 1;
					Score += 20;
				}
				else
				{
					it2++;
				}
			}
		}
		#pragma endregion

		#pragma region Fish_LV3_BeingCaught_Caught
		vector<Fish_Lv3>::iterator it3 = F_level3.begin();
		while (it3 != F_level3.end()) {
			if (LEVEL < 3)
			{
				if (it3->is_Caught(f.x, f.y, 1, it3->img->w, it3->img->h))
				{
					F2_count = 0;
					//Load_Image(LEVEL);
					Init(LEVEL, WIDTH / 2, HEIGHT / 2);
					if (LEVEL < 2)
						Score = 0;
					else
						Score = 200;
					//live -= 1;
				}
				else
				{
					it3++;
				}
			}
			else
			{
				//cout << "upLevel()\n";
				if (it3->is_Caught(f.x, f.y, 1, it3->img->w, it3->img->h))
				{
					it3 = F_level3.erase(it3);
					F3_count += 1;
					Score += 50;
				}
				else
				{
					it3++;
				}
			}
		}
		#pragma endregion

		#pragma region Update
		if (F_level1.size() == 0)
		{
			s.update_lv1();
		}
		if (F_level2.size() == 0)
		{
			s.update_lv2();
		}
		if (F_level3.size() == 0)
		{
			s.update_lv3();
		}
		#pragma endregion

		#pragma region Up_Level
		if (Score == 200)
		{
			LEVEL = 2;
			Load_Image(LEVEL);
		}
		if (Score >= 500 && Score <= 510)
		{
			LEVEL = 3;
			Load_Image(LEVEL);
		}
		if (Score == 1000)
		{
			cout << "You Win\n";
		}
		#pragma endregion

		Update_Image();
		Update_Rect();
	}
	static void Load_Image(int level) {
		//cout << "Float level: " << level << endl;
		Image Img;
		int w, h;
		Load_Texture(&Img, a[level - 1].c_str());
		w = Img.w / 2; h = Img.h / 2;
		Crop_Image(&Img, &Img_Save[0][0], 0, 0, w, h);
		Crop_Image(&Img, &Img_Save[0][1], 0, h, w, h);
		Crop_Image(&Img, &Img_Save[1][0], w, 0, w, h);
		Crop_Image(&Img, &Img_Save[1][1], w, h, w, h);

		Zoom_Image(&Img_Save[0][0], 1);
		Zoom_Image(&Img_Save[0][1], 1);
		Zoom_Image(&Img_Save[1][0], 1);
		Zoom_Image(&Img_Save[1][1], 1);

		Delete_Image(&Img);
	}
	static void Load_Image1(int level) {
		//cout << "Float level: " << level << endl;
		Image Img;
		int w, h;
		Load_Texture(&Img, "Image/boom.png");
		w = Img.w; h = Img.h;
		Crop_Image(&Img, &Img_Save[0][0], 0, 0, w, h);
		Crop_Image(&Img, &Img_Save[0][1], 0, h, w, h);

		Delete_Image(&Img);
	}
};
Image Fish::Img_Save[2][2];
//vector<Fish>::iterator Player;
Fish Player;
vector<Fish> player;
#pragma endregion


string convert(int Score)
{
	return "Score: " + to_string(Score);
}

void output(int x, int y, const char* string)
{
	//cout << string << endl;
	int len, i;
	glRasterPos2f(x, y);
	len = (int)strlen(string);
	for (i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}

int mouse = WIDTH / 2;
void mouseHover(int x, int y)
{
	if (mouse < x)
	{
		Player.Drt = 1;
	}
	else
	{
		Player.Drt = 0;
	}
	mouse = x;
	Player.f.x = x;// +Player.Img->w;
	Player.f.y = y;// +Player.Img->h;

	Player.move();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	Map_Texture(&Img_Background);
	Draw_Rect(&Rect_Background);

	output(x, y, convert(Score).c_str());
	//player
	Player.Draw();
	//F1
	int size = F_level1.size();
	for (int i = 0; i < size; i++)
	{
		F_level1[i].Draw();
	}
	//F2
	size = F_level2.size();
	for (int i = 0; i < size; i++)
	{
		F_level2[i].Draw();
	}
	//F3
	size = F_level3.size();
	for (int i = 0; i < size; i++)
	{
		F_level3[i].Draw();
	}
	size = Urchins.size();
	for (int i = 0; i < size; i++)
	{
		Urchins[i].Draw();
	}
	glutSwapBuffers();

}

void init_Game()
{
	Load_Texture_Swap(&Img_Background, "Image/ocean3.png");
	Zoom_Image(&Img_Background, SCALE);

	output(x, y, convert(Score).c_str());

	//fish
	Fish::Load_Image(LEVEL);
	Urchin::Load_Image(1);
	Fish_Lv1::Load_Image(1);
	Fish_Lv2::Load_Image(1);
	Fish_Lv3::Load_Image(1);

	Player.Init(1, WIDTH / 2, HEIGHT / 2);
	//init
	s.update_lv1();
	s.update_lv2();
	s.update_lv3();
	s.update_urchin();

}

void init()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, WIDTH, HEIGHT);
	gluOrtho2D(0, WIDTH, HEIGHT, 0);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_LINE_SMOOTH);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glEnable(GL_TEXTURE_2D);

	init_Game();
}

void Timer(int value)
{
	
	//score

	output(x, y, convert(Score).c_str());
	int size = F_level1.size();
	for (int i = 0; i < size; i++)
	{
		F_level1[i].update();
	}
	size = F_level2.size();
	for (int i = 0; i < size; i++)
	{
		F_level2[i].update();
	}
	size = F_level3.size();
	for (int i = 0; i < size; i++)
	{
		F_level3[i].update();
	}
	size = Urchins.size();
	for (int i = 0; i < size; i++)
	{
		Urchins[i].update();
	}
	//demo.update();
	glutPostRedisplay();
	glutTimerFunc(INTERVAL, Timer, 0);

}

void myMouse2(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		cout << "Clicked at [" << x << "," << y << "]\n";

		if (x < 659 && x > 559 && y < 742 && y > 573)
		{
			exit(1);
		}
		if (x < 1057 && x > 958 && y < 742 && y > 573)
		{
			cout << "            Play          " << endl;
			win2 = glutCreateWindow("Hungry Fish");
			glutSetCursor(GLUT_CURSOR_NONE);
			init();
			glutDisplayFunc(display);
			glutTimerFunc(0, Timer, 0);
			glutPassiveMotionFunc(mouseHover);

			glutDestroyWindow(winGuide);
		}
	}
}

void myMouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		cout << "Clicked at [" << x << "," << y << "]\n";
		if (x < 810 && x > 709 && y < 580 && y > 416)
		{
			cout << "            Play          " << endl;
			win2 = glutCreateWindow("Hungry Fish");
			glutSetCursor(GLUT_CURSOR_NONE);
			init();
			glutDisplayFunc(display);
			glutTimerFunc(0, Timer, 0);
			glutPassiveMotionFunc(mouseHover);

			glutDestroyWindow(win1);
		}
		if (x < 660 && x > 560 && y < 728 && y > 560)
		{
			exit(1);
		}
		if (x < 960 && x > 860 && y < 728 && y > 560)
		{
			cout << "            Guide          " << endl;
			winGuide = glutCreateWindow("Guide");
			Guide g;
			g.init();
			glutDisplayFunc(display3);
			glutMouseFunc(myMouse2);
			glutDestroyWindow(win1);
		}
	}
}

int main(int argc, char** argv)
{
	srand(NULL);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	int POS_X = (glutGet(GLUT_SCREEN_WIDTH) - WIDTH) >> 1;
	int POS_Y = (glutGet(GLUT_SCREEN_HEIGHT) - HEIGHT) >> 1;
	glutInitWindowPosition(POS_X, POS_Y);
	glutInitWindowSize(WIDTH, HEIGHT);

	menu m;
	win1 = glutCreateWindow("Menu");
	m.init();
	glutDisplayFunc(display2);
	glutMouseFunc(myMouse);
	/*glutCreateWindow("Mid-term");
	glutSetCursor(GLUT_CURSOR_NONE);


	init();
	glutDisplayFunc(display);
	glutTimerFunc(0, Timer, 0);
	glutPassiveMotionFunc(mouseHover);*/

	glutMainLoop();
	return 0;
}