#include "Draw.h"
//all drawing functions are here


void drawTexture(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double r, double g, double b) {
	glBindTexture(GL_TEXTURE_2D, texSet[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0); glVertex3f(x1, y1, 0);
	glTexCoord2d(4, 0); glVertex3f(x2, y2, 0);
	glTexCoord2d(4, 4); glVertex3f(x3, y3, 0);
	glTexCoord2d(0, 4); glVertex3f(x4, y4, 0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}


void drawSquare(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double r, double g, double b) {
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, texSet[6]);
	glColor3f(r, g, b);
	glBegin(GL_POLYGON);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glVertex2f(x3, y3);
	glVertex2f(x4, y4);
	glEnd();
	glDisable(GL_TEXTURE_2D);

}
void drawArc(double cx, double cy, float r,
	int startDeg, int endDeg)
{
	int i;
	//int M_PI=3.1415927;
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_STRIP);
	for (i = startDeg; i <= endDeg; i++)
		glVertex2f(cx + r*sin(2.0*PI*i / 360.0),
			cy + r*cos(2.0*PI*i / 360.0));
	glEnd();
}

void drawArcColor(double cx, double cy, float r,
	int startDeg, int endDeg, double c1, double c2, double c3)
{
	int i;
	//int M_PI=3.1415927;
	glColor3f(c1, c2, c3);
	glBegin(GL_POLYGON);
	for (i = startDeg; i <= endDeg; i++) {

		//glColor3f(0,0,0);
		glVertex2f(cx + r*sin(2.0*PI*i / 360.0),
			cy + r*cos(2.0*PI*i / 360.0));

	}
	glEnd();
	glFlush();
}

void drawEllipseColor(double cx, double cy, float rx, float ry,
	int startDeg, int endDeg, double c1, double c2, double c3)
{
	int i;
	//int M_PI=3.1415927;
	glColor3f(c1, c2, c3);
	glBegin(GL_POLYGON);
	for (i = startDeg; i <= endDeg; i++) {

		//glColor3f(0,0,0);
		glVertex2f(cx + rx*sin(2.0*PI*i / 360.0),
			cy + ry*cos(2.0*PI*i / 360.0));

	}
	glEnd();
	glFlush();
}
void drawSquareO(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double r, double g, double b) {
	glColor3f(r, g, b);
	glBegin(GL_POLYGON);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glVertex2f(x3, y3);
	glVertex2f(x4, y4);
	glEnd();
	glFlush();

}
void drawCurve(double cx, double cy, float rx, float ry,
	int startDeg, int endDeg)
{
	int i;
	//int M_PI=3.1415927;
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_STRIP);
	for (i = startDeg; i <= endDeg; i++)
		glVertex2f(cx + rx*sin(2.0*PI*i / 360.0),
			cy + ry*cos(2.0*PI*i / 360.0));
	glEnd();
}

void drawArc1(double cx, double cy, float r,
	int startDeg, int endDeg)
{
	int i;
	//int M_PI=3.1415927;
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_STRIP);
	for (i = startDeg; i <= endDeg; i++)
		glVertex2f(cx + r*sin(2.0*PI*i / 360.0),
			cy + r*cos(2.0*PI*i / 360.0));
	glEnd();
}

void chopper(double x) {

	drawSquareO(0 / x, 0 / x, 0 / x, -3 / x, -4 / x, -8 / x, -6 / x, -10 / x, 0.91, 0.7144, 0.5187);//arm
	drawSquareO(0, 0, 0, -3 / x, 4 / x, -8 / x, 6 / x, -10 / x, 0.91, 0.7144, 0.5187);//arm
																					  //leg 2

	drawSquareO(-1.5 / x, -13 / x, -1 / x, -13 / x, -1.5 / x, -15 / x, -2.5 / x, -15 / x, 0.91, 0.7144, 0.5187);
	drawSquareO(1.5 / x, -13 / x, 1 / x, -13 / x, 1.5 / x, -15 / x, 2.5 / x, -15 / x, 0.91, 0.7144, 0.5187);

	//body
	drawEllipseColor(0, -10 / x, 4 / x, 4 / x, 90, 270, 0.3535, 0.1974, 0.42);
	drawEllipseColor(0, -10 / x, 4 / x, 7 / x, -90, 90, 0.91, 0.7144, 0.5187);
	drawEllipseColor(0, -14 / x, 1 / x, 1 / x, -90, 90, 0, 0, 0.3);

	//leg 1
	drawEllipseColor(-2 / x, -15 / x, 1 / x, 1 / x, -90, 90, 0, 0, 0);
	drawEllipseColor(2 / x, -15 / x, 1 / x, 1 / x, -90, 90, 0, 0, 0);



	//horn

	drawEllipseColor(-10 / x, 10 / x, 4 / x, 3 / x, 70, 250, 0.45, 0.3818, 0.2925);
	drawEllipseColor(-9.5 / x, 11 / x, 1 / x, 3 / x, 70, 250, 0, 0, 0.3);
	drawEllipseColor(10 / x, 10 / x, 4 / x, 3 / x, 110, 290, 0.45, 0.3818, 0.2925);
	drawEllipseColor(9.5 / x, 11 / x, 1 / x, 3 / x, 70, 250, 0, 0, 0.3);
	drawSquareO(-5 / x, 6 / x, -4 / x, 7 / x, -10 / x, 8 / x, -11 / x, 7 / x, 0.45, 0.3818, 0.2925);
	drawSquareO(5 / x, 6 / x, 4 / x, 7 / x, 10 / x, 8 / x, 11 / x, 7 / x, 0.45, 0.3818, 0.2925);

	//hat
	drawSquareO(-5 / x, 5 / x, 5 / x, 5 / x, 7 / x, 10 / x, -7 / x, 10 / x, 0.84, 0.4032, 0.527);//hat
	drawSquareO(1 / x, 6 / x, 2 / x, 7 / x, -1 / x, 9 / x, -2 / x, 8 / x, 1, 1, 1);//cross
	drawSquareO(-1 / x, 6 / x, -2 / x, 7 / x, 1 / x, 9 / x, 2 / x, 8 / x, 1, 1, 1);//cross
	drawEllipseColor(0, 3 / x, 10 / x, 3 / x, 0, 360, 0.84, 0.4032, 0.527);//hat
	drawCurve(0 / x, 3 / x, 10 / x, 3 / x, -31, 31);
	drawCurve(0, 0, 10 / x, 4.5 / x, -66.97, 66.97);
	drawEllipseColor(0, -1 / x, 5 / x, 3 / x, 90, 270, 0.91, 0.7144, 0.5187);
	drawSquareO(-5 / x, -1 / x, -5.5 / x, 1.5 / x, 5.5 / x, 1.5 / x, 5 / x, -1 / x, 0.91, 0.7144, 0.5187);
	drawEllipseColor(0, 1.5 / x, 5.5 / x, 2 / x, -90, 90, 0.91, 0.7144, 0.5187);

	drawEllipseColor(0, 10 / x, 7 / x, 2 / x, -90, 90, 0.84, 0.4032, 0.527);
	drawArcColor(2.5 / x, 0.8 / x, 1 / x, 0, 360, 1, 1, 1);//right eye
	drawArcColor(2.5 / x, 0.8 / x, 0.7 / x, 0, 360, 0, 0, 0);

	//drawArc(-3,2,2,-90,90);
	drawArcColor(-2.5 / x, 0.8 / x, 1 / x, 0, 360, 1, 1, 1);//left eye
	drawArcColor(-2.5 / x, 0.8 / x, 0.7 / x, 0, 360, 0, 0, 0);



	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex2f(3 / x, 2.5 / x);
	glVertex2f(1 / x, 1.5 / x);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex2f(-3 / x, 2.5 / x);
	glVertex2f(-1 / x, 1.5 / x);
	glEnd();

	drawArcColor(0, 0, 0.5 / x, 90, 270, 0, 0, 1);//nose
	drawArc1(-1 / x, -1 / x, 1 / x, 90, 270);
	drawArc1(1 / x, -1 / x, 1 / x, 90, 270);

	//line in the nose
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(0, -0.5 / x);
	glVertex2f(0, -1 / x);
	glEnd();


	//mouse
	drawArcColor(0, -2 / x, 1 / x, 90, 270, 1, 0, 0);

}







void DrawEllipticArc(double x, double y, double theta_min, double theta_max, double internal_x, double internal_y, double external_x, double external_y)
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLE_STRIP);
	for (; theta_min < theta_max; theta_min += 0.1)
	{
		glVertex2d(x + internal_x*cos(theta_min*PI / 180), y + internal_y*sin(theta_min*PI / 180));
		glVertex2d(x + external_x*cos(theta_min*PI / 180), y + external_y*sin(theta_min*PI / 180));
	}
	glEnd();
	glPopAttrib();
}
void DrawCircularArc(double x, double y, double theta_min, double theta_max, double internal_radius, double external_radius)
{
	DrawEllipticArc(x, y, theta_min, theta_max, internal_radius, internal_radius, external_radius, external_radius);
}
void DrawEllipse(float WingX, float WingY, float CenterX, float CenterY)
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glPolygonMode(GLenum(GL_FRONT), GLenum(GL_FILL));
	glBegin(GL_POLYGON);
	{
		float a = sqrt(pow((WingX - CenterX), 2) + pow((WingY - CenterY), 2));   
		float b = 0.02;
		float phiDEG; float phiRAD;
		float x; float y;
		for (phiDEG = 0.0; phiDEG < 360; phiDEG++)
		{
			phiRAD = phiDEG*PI / 180.0;
			x = a*cos(phiRAD);
			y = b*sin(phiRAD);
			glVertex2f(x + CenterX, y + CenterY);

		}
	}
	glPopAttrib();
	glEnd();
}
void RotatedEllipse(GLfloat Ang, GLfloat X, GLfloat Y, GLfloat Z)
{
	glPushMatrix();
	glTranslated(X, Y, Z);
	glRotatef(Ang, 0.0, 0.0, 1.0);
	DrawEllipse(0.25, 0.0, 0.0, 0.0);
	glPopMatrix();
}
void DRotatedEllipse(GLfloat Ang, GLfloat X, GLfloat Y, GLfloat Z)     //Diagonal Rotated Ellipse
{
	glPushMatrix();
	glTranslated(X, Y, Z);
	glRotatef(Ang, 0.0, 0.0, 1.0);
	DrawEllipse(0.25, 0.25, 0.0, 0.0);
	glPopMatrix();
}