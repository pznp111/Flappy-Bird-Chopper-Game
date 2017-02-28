#include "Draw.h"
#include "bird.h"
#include "main.h"



//#include "Draw.h"







//****************************************************************basic texture mapping
GLuint loadMyTextures(char *filename, int mode)
{
	GLuint myTexture;
	FILE *file;
	unsigned char *tex, *tex2;


	// texture data
	int width = 256;
	int height = 256;

	// allocate buffer
	tex = (unsigned char *)malloc(width * height * 3);
	tex2 = (unsigned char *)malloc(width * height * 3);

	// open and read texture data
	//file = fopen(filename, "rb");
	fopen_s(&file, filename, "rb");
	if (file == NULL)
		cout << "Error! Missing texture!\n";
	else
		cout << "texture successfully loaded\n";

	fread(tex, width * height * 3, 1, file);
	fclose(file);

	for (int i = 0; i<width*height; i++)
	{
		tex2[i * 3] = tex[i * 3 + 2];
		tex2[i * 3 + 1] = tex[i * 3 + 1];
		tex2[i * 3 + 2] = tex[i * 3];
	}

	// allocate a texture name
	glGenTextures(1, &myTexture);
	glBindTexture(GL_TEXTURE_2D, myTexture);

	// select modulate to mix texture with color for shading
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	if (mode == 0) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_DECAL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_DECAL);
	}
	else {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	// when texture area is small, bilinear filter the closest mipmap
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	// when texture area is large, bilinear filter the first mipmap
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// texture should tile
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// build texture mipmaps
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, tex2);

	// free buffers
	free(tex);
	free(tex2);
	return myTexture;
}




void drawStarting() {
	
	glColor3f(0.302, 0.753, 0.792);
	//glColor3f(1,0,0);
	glBegin(GL_POLYGON);
	glVertex2f(-50, -300);
	glVertex2f(600, -300);
	glVertex2f(600, 300);
	glVertex2f(-50, 300);
	glEnd();
	

	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texSet[8]);
	glBegin(GL_QUADS);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-300, -200, 0.0f);

	glTexCoord2f(1.1f, 0.0f);
	glVertex3f(600, -200, 0.0f);

	glTexCoord2f(1.1f, 1.0f);
	glVertex3f(600, 200, 0.0f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-300, 200, 0.0f);
	glEnd();
	
	/*
	char mss[50];
	sprintf_s(mss, "Press   \"Space\"   To   Start");

	glColor3f(1.0, 0.0, 0.0);  //set font color  //set font color
	glRasterPos2i(150, 250);    //set font start position
	for (int i = 0; i < strlen(mss); i++)  glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, mss[i]);


	sprintf_s(mss, "\"A\" to go left, \"D\" to go right, \"space\" to jump");

	glColor3f(1.0, 1.0, 0.0);  //set font color   //set font color
	glRasterPos2i(100, 220);    //set font start position
	for (int i = 0; i < strlen(mss); i++)  glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, mss[i]);

	sprintf_s(mss, "Press \"P\" to Pause");

	glColor3f(1.0, 1.0, 0.0);  //set font color   //set font color
	glRasterPos2i(150, 190);    //set font start position
	for (int i = 0; i < strlen(mss); i++)  glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, mss[i]);

	sprintf_s(mss, "Press \"R\" to Restart");

	glColor3f(1.0, 1.0, 0.0);  //set font color   //set font color
	glRasterPos2i(150, 160);    //set font start position
	for (int i = 0; i < strlen(mss); i++)  glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, mss[i]);

	glFlush();
	*/
}

std::list<Blockers*> Blockerss = std::list<Blockers*>();
Bird* bird;

void KeyboardFunc(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'p':
	case 'P':
		if (bird->Alive())
			TogglePause();
		break;
	case 'r':
	case 'R':
		Restart();
		break;
	case '`':
	case '~':
		exit(0);
	case 'd':
	case 'D':
		if (!isPaused) {
			bird->x += 5;
			break;
		}
	case 'a':
	case 'A':
		//if (true) {
		if (!isPaused) {
			bird->x -= 5;
			break;
		}
	case '1':
		diffIndex = 1;
			break;

	case '2':
		diffIndex = 2;
		break;

	case '3':
		diffIndex = 3;
		break;
	case '4':
		diffIndex = 4;
		break;
	case '5':
		diffIndex = 5;
		break;
	case ' ':
		//if(true){
		if (!isStarted) {
			isStarted = true;
		}
	
			bird->Jump();
		
		if (!isPaused) {
			PlaySoundA((LPCSTR) "jump.WAV", NULL, SND_FILENAME | SND_ASYNC);
		}
	default:
		//bird->Jump();
		break;
	}
}

//Update Game
void Update(int useless)
{
	if (!isPaused && bird->Alive()) {
		bird->Update();
		/*
		if (diffIndex == 1) {
			if (frame % 2700 == 0)
			{
				Blockerss.insert(Blockerss.end(), new Blockers());
			}
		}
		if (diffIndex == 2) {
			if (frame % 1350 == 0)
			{
				Blockerss.insert(Blockerss.end(), new Blockers());
			}
		}
		if (diffIndex == 3) {
			if (frame % 900 == 0)
			{
				Blockerss.insert(Blockerss.end(), new Blockers());
			}
		}
		if (diffIndex == 4) {
			if (frame % 675 == 0)
			{
				Blockerss.insert(Blockerss.end(), new Blockers());
			}
		}
		if (diffIndex == 5) {
			if (frame % 540 == 0)
			{
				Blockerss.insert(Blockerss.end(), new Blockers());
			}
		}
		*/
		if (frame == 1) {
			Blockerss.insert(Blockerss.end(), new Blockers());
		}
		for (std::list<Blockers*>::iterator it = Blockerss.begin(); it != Blockerss.end(); ++it)
		{
			if ((*it)->isLastBlk() && (*it)->xPosIs() <= 300) {
				(*it)->changeLast(false);
				Blockerss.insert(Blockerss.end(), new Blockers());
				cout << "inserted";
			}
			(*it)->changeDiff(diffIndex);
			(*it)->Update();
			//remove the blockers
			if (!(*it)->isAlive()) {
				delete *it;
				it = Blockerss.erase(it);
			}
			//die if collide
			if ((*it)->Collide(bird)) {
				bird->Die();
			}
			if (bird->x > (*it)->x) {
				if (!(*it)->isScoredFunc()) {
					score++;
					PlaySoundA((LPCSTR) "smilling.WAV", NULL, SND_FILENAME | SND_ASYNC);
					(*it)->changeScore(true);
				}
			}
		}
		frame = frame + 1;
	}
	glutPostRedisplay();
	glutTimerFunc(5, Update, 0);
}



void Display()
{
	glClear(GL_COLOR_BUFFER_BIT);


	///////////////
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texSet[7]);
	glBegin(GL_QUADS);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-300, -300, 0.0f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(600, -300, 0.0f);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(600, 300, 0.0f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-300, 300, 0.0f);
	glEnd();

	glDisable(GL_TEXTURE_2D);


	

	/////
	bird->Draw();
	for (std::list<Blockers*>::iterator it = Blockerss.begin(); it != Blockerss.end(); ++it)
		(*it)->Draw();
	if (!bird->Alive())
		DrawDeathScreen();
	if (!isStarted) {
		DrawDeathScreen();
	}
	//background
	glPushMatrix();
	{
		glTranslated(-50, 250, 0);
		glScaled(50, 50, 50);
		glColor3d(0, 1, 0);

	}
	glPopMatrix();
	if (isPaused)
	{


		//sample code to show words
		char mss[50];
		sprintf_s(mss, "PAUSED");

		glColor3f(1.0, 0.0, 0.0);  //set font color
		glRasterPos2i(150, 0);    //set font start position
		for (int i = 0; i < strlen(mss); i++)  glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, mss[i]);
	}
	if (!isStarted) {
		drawStarting();
		//isStarted = true;
	}
	glFlush();


	
	glutSwapBuffers();
}
void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glViewport(0, 0, 600, 600);
	gluOrtho2D(-50, 550, -300, 300);


	glutKeyboardFunc(KeyboardFunc);
	glutTimerFunc(5, Update, 0);
	srand(time(nullptr));
	bird = new Bird(posX+200, posY, 0, true);

	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);


	//load textures
	texSet[0] = loadMyTextures("bird1.bmp", 1);
	texSet[1] = loadMyTextures("brick1.bmp", 0);
	texSet[2] = loadMyTextures("brick2.bmp", 0);
	texSet[3] = loadMyTextures("brick3.bmp", 0);
	texSet[4] = loadMyTextures("background.bmp", 0);
	texSet[5] = loadMyTextures("Wood7.bmp", 0);
	texSet[6] = loadMyTextures("dragon.bmp", 0);
	texSet[7] = loadMyTextures("bg4.bmp", 0);
	texSet[8] = loadMyTextures("title.bmp", 0);
	




	//cout << texSet[0];
	//test();
}
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	//glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Floppy Bird");
	



	init();
	glutDisplayFunc(Display);
	glutMainLoop();
	return 0;


}


void TogglePause()
{
	isPaused = !isPaused;
}
void Restart()
{
	gravity = -0.01;
	isPaused = false;
	frame = 0;
	score = 0;
	Blockerss.clear();
	delete bird;
	//bird = new Bird();
	bird = new Bird(posX + 200, posY, 0, true);
	isStarted = false;
	isDrawn = false;
	isDeathDrawn = false;
	diffIndex = 3;
		
}

void DrawDeathScreen()
{
	//cout << "start once" << '\n';


	if (isStarted) {
		glColor3f(0, 0, 0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glBegin(GL_POLYGON);
		glVertex2d(50, 150);
		glVertex2d(450, 150);
		glVertex2d(450, 100);
		glVertex2d(50, 100);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex2d(50, -150);
		glVertex2d(450, -150);
		glVertex2d(450, -100);
		glVertex2d(50, -100);
		glEnd();


		//high score board
		char *str = "";
		char mss[500];
		int append = 0;


		
		sprintf_s(mss, "Press \"R to Restart");

		glColor3f(1.0, 1.0, 0.0);  //set font color
		glRasterPos2i(150, -90);    //set font start position
		for (int i = 0; i < strlen(mss); i++)  glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, mss[i]);





			/*
			vector<string> vec;
			string line;
			ifstream myfile("example.txt");
			int count = 0;
			if (myfile.is_open())
			{
				while (getline(myfile, line) && count < 5)
				{
					//str = temp + line + "\n";
					sprintf_s(mss, "%s", line.c_str());

						glColor3f(1.0, 0.0, 0.0);  //set font color
						glRasterPos2i(150, 80-append);    //set font start position
						append += 20;
						for (int i = 0; i < strlen(mss); i++)  glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, mss[i]);
					
					//c.push_back(line);
						count++;
				}
				myfile.close();
				
			}

			else {
				cout << "Unable to open file";
			}
			*/

		
			vector<MyStruct> vec;
			string line;
			ifstream myfile("example.txt");
			int count = 0;
			if (myfile.is_open())
			{
				while (getline(myfile, line) )
				{
					string timeStr = line.substr(0,line.find(" "));
					string scoreStr = line.substr(line.find(" ")+1,line.size());
					vec.push_back(MyStruct(stoi(scoreStr), timeStr));
				}
				myfile.close();

			}


			else {
				cout << "Unable to open file";
			}



			
			if (!isDeathDrawn) {

				
				time_t t = time(0);
				

				time_t now = time(0);

				//cout << "Number of sec since January 1,1970:" << now << endl;

				tm *ltm = localtime(&now);

				// print various components of tm structure.
				//cout << "Year" << 1900 + ltm->tm_year << endl;
				//cout << "Month: " << 1 + ltm->tm_mon << endl;
				//cout << "Day: " << ltm->tm_mday << endl;
				//cout << "Time: " << 1 + ltm->tm_hour << ":";
				//cout << 1 + ltm->tm_min << ":";
				//cout << 1 + ltm->tm_sec << endl;

				//string timeString = to_string(1900 + ltm->tm_year)+"/"+to_string(1 + ltm->tm_mon) + "/" + to_string(ltm->tm_mday) + " " + to_string(1 + ltm->tm_hour) + ":" +to_string( 1 + ltm->tm_min) +":" + to_string(1 + ltm->tm_sec);
				string timeString = to_string(1 + ltm->tm_hour) + ":" + to_string(1 + ltm->tm_min) + ":" + to_string(1 + ltm->tm_sec);
				cout << "timeString\n";
				cout << timeString + "\n";
				//struct tm *aTime = localtime(&t);
				cout << score + "\n";
				//int day = aTime->tm_mday;
				//int month = aTime->tm_mon + 1; // Month is 0 - 11, add 1 to get a jan-dec 1-12 concept
				//int year = aTime->tm_year + 1900; // Year is # years since 1900

				//string timeString = to_string(year) + " " + to_string(month) + " " + to_string(day);
				//cout << timeString;
				vec.push_back(MyStruct(score, timeString));
			}

			sort(vec.begin(), vec.end(), less_than_key());
			

			sprintf_s(mss, "%s", "time           score");

			glColor3f(1.0, 0.0, 0.0);  //set font color
			glRasterPos2i(150, 80 );    //set font start position
			append += 20;
			for (int i = 0; i < strlen(mss); i++)  glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, mss[i]);

			//int append = 0;
			string savingstr;
			if (vec.size()<5) {
				for (int i = 0; i < vec.size(); i++)
				{
					//str = temp + line + "\n";
					string tempstr = vec.at(vec.size() - 1 - i).stringValue + "    " + to_string(vec.at(vec.size() - 1 - i).key);
					savingstr += tempstr + "\n";
					sprintf_s(mss, "%s", tempstr.c_str());

					glColor3f(1.0, 0.0, 0.0);  //set font color
					glRasterPos2i(150, 80 - append);    //set font start position
					append += 20;
					for (int i = 0; i < strlen(mss); i++)  glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, mss[i]);

					//c.push_back(line);
					count++;
				}
				
			}
			else {
				for (int i = 0; i < 5; i++)
				{
					string tempstr = vec.at(vec.size()-1-i).stringValue + "    " + to_string(vec.at(vec.size() - 1 - i).key);
					savingstr = savingstr + tempstr + "\n";
					sprintf_s(mss, "%s", tempstr.c_str());

					glColor3f(1.0, 0.0, 0.0);  //set font color
					glRasterPos2i(150, 80 - append);    //set font start position
					append += 20;
					for (int i = 0; i < strlen(mss); i++)  glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, mss[i]);

					//c.push_back(line);
					count++;
				}
			}

			if (!isDeathDrawn) {
				cout << "once\n";
				isDeathDrawn = true;
				std::ofstream ofs("example.txt", std::ofstream::out);

				ofs << savingstr;
				cout << savingstr;

				ofs.close();
				PlaySoundA((LPCSTR) "screaming.WAV", NULL, SND_FILENAME | SND_ASYNC);
				
			}
		glPopMatrix();
		glFlush();

	}
	else {
		//sample code to show words
		char mss[50];
		sprintf_s(mss, "Press   \"Space\"   To   Start");

		glColor3f(1.0, 0.0, 0.0);  //set font color
		glRasterPos2i(150, 0);    //set font start position
		for (int i = 0; i < strlen(mss); i++)  glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, mss[i]);
	}
}


