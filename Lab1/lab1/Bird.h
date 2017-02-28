#pragma once
#include "Draw.h"
class Objects
{
public:
	Objects() {
		x = 0;
		y = 0;
	};
	Objects(double a, double b) {
		x = a;
		y = b;
	}
	double x, y;
	virtual void Draw() = 0;
	virtual void Update() = 0;
};

void static ResetJump(int voidNumber)
{
	gravity -= jumpHigh;
}

class Bird : public Objects
{
	double speed;
	bool isAlive;
public:
	Bird() : Bird(0, 0, 0, true) {}
	//Bird(double a, double b) :Bird(a, b, 0, true) {}
	//Bird(double a, double b, double s) :Bird(a, b, s, true) {}
	Bird(double a, double b, double s, bool livingStatus)
	{
		x = a;
		y = b;
		speed = s;
		isAlive = livingStatus;
	}
	void Draw() {
		double displaceX = x - posX;
		double displaceY = y - posX;
		glPushMatrix();
		glTranslatef(displaceX, displaceY, 0);
		chopper(1);
		glPopMatrix();
	}

	bool Alive() { return isAlive; }
	void Update()
	{
		if (isStarted) {
			if (!isAlive) return;
		/*	if (isBounceBack) {
				y -= speed;
				if (y< 200) {
					isBounceBack = false;
				}
			}
			else {*/
			//	if (y < -300) {
					if (y > 300 || y < -300) {
					Die();
				}
			//	if (y >= 250) {
			//		isBounceBack = true;
			//		y -= speed;
			//		speed -= gravity;
			//	}
				//else {
					y += speed;
					speed += gravity;
			//	}
			//}
		}
	}
	void Jump()
	{
		if (!isAlive) {
			return;
		}
		else {

			gravity += jumpHigh;
			
			glutTimerFunc(20, ResetJump, 0);

		}
	}
	void Die()
	{
		isAlive = false;
	}
};





class Blockers : public Objects
{
	double speed;
	bool isScored;
	bool isLast;

public:
	Blockers() : Blockers(550, rand() % (200 - 10) + 10) {}
	Blockers(double a, double b)
	{
		cout << a;
		cout << "/n";
		cout << b;
		cout << "/n";
		if ((rand() % (200 - 10) + 10) % 3 == 1) {
			b = b * -1;
		}
		isScored = false;
		x = a; y = b;
		speed = 0.1 * diffIndex;
		isLast = true;
	}

	void changeLast(bool lastValue) {
		this->isLast = lastValue;
	}

	bool isLastBlk() {
		return isLast;
	}
	double xPosIs() {
		return x;
	}
	void Draw()
	{

		
		
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texSet[5]);
		glBegin(GL_QUADS);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		//glBegin(GL_POLYGON);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(x - 20, y - 50, 0.0f);

		glTexCoord2f(0.4f, 0.0f);
		glVertex3f(x + 20, y - 50, 0.0f);

		glTexCoord2f(0.4f, 6.5f);
		glVertex3f(x + 20, y - 600, 0.0f);

		glTexCoord2f(0.0f, 6.5f);
		glVertex3f(x - 20, y - 600, 0.0f);
		glEnd();
		
		
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texSet[5]);
		glBegin(GL_QUADS);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		//glBegin(GL_POLYGON);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(x - 20, y + 50, 0.0f);

		glTexCoord2f(0.4f, 0.0f);
		glVertex3f(x + 20, y + 50, 0.0f);

		glTexCoord2f(0.4f, 6.5f);
		glVertex3f(x + 20, y + 600, 0.0f);

		glTexCoord2f(0.0f, 6.5f);
		glVertex3f(x - 20, y + 600, 0.0f);
		glEnd();

		

		glDisable(GL_TEXTURE_2D);


		char mss[50];

		sprintf_s(mss, "Difficulty :");

		glColor3f(1.0, 0.0, 0.0);  //set font color
		glRasterPos2i(100, 250);    //set font start position
		for (int i = 0; i < strlen(mss); i++)  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, mss[i]);



		sprintf_s(mss, "%d", diffIndex);

		glColor3f(1.0, 1.0, 0.0);  //set font color
		glRasterPos2i(150, 250);    //set font start position
		for (int i = 0; i < strlen(mss); i++)  glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, mss[i]);


		sprintf_s(mss, "Press 1-5 to change the difficulty");

		glColor3f(1.0, 0.0, 1.0);  //set font color
		glRasterPos2i(60, 220);    //set font start position
		for (int i = 0; i < strlen(mss); i++)  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, mss[i]);



		sprintf_s(mss, "SCORE");

		glColor3f(1.0, 0.0, 0.0);  //set font color
		glRasterPos2i(0, 250);    //set font start position
		for (int i = 0; i < strlen(mss); i++)  glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, mss[i]);






		sprintf_s(mss, "%d", score);

		glColor3f(1.0, 0.0, 0.0);  //set font color
		glRasterPos2i(0, 220);    //set font start position
		for (int i = 0; i < strlen(mss); i++)  glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, mss[i]);

	}
	void Update()
	{
		//cout << x<<"\n";
		if (isStarted) {
			x -= speed;
		}
	}
	void changeDiff(int newDiff) {
		this->speed = 0.1 * newDiff;
	}
	bool Collide(Bird* p)
	{
		if (p->x > x - 25 && p->x < x + 50 )
			if (p->y-32   < y - 50 || p->y-13  > y + 50)
				p->Die();
		//cout << "x is" << p->x << " " << x << "\n";
		//cout << "y is" << p->y << " " << y << "\n";
		return false;

	

	}
	bool isAlive()
	{
		return x > -50;
	}
	bool isScoredFunc()
	{
		return isScored;
	}
	void changeScore(bool value) {
		this->isScored = value;
	}

};