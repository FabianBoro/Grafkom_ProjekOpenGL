/******************
File utama menggambar truck
******************/

#include <GL/glut.h> 
#include "draw.cpp"
using namespace std;

namespace{
	float headx = 2;
	float headz = -3;
	float roth = 180;
	
	void drawHead(){
		glPushMatrix();	//Depan
			glTranslatef(headx,0,headz);
			glRotatef(180-roth, 0, 1, 0);
			glTranslatef(-2, 1.0, 0.0);
			glPushMatrix();
				glTranslatef(0.0, 0.0, 1.2);
				glRotatef(90, 1, 0, 0);
				glScalef(1.0, 0.4, 1.0);
				glColor3f(0.1,0.1,0.1);
				cylinder();
				glScalef(0.5, 1.2, 0.5);
				glColor3f(0.5,0.5,0.5);
				cylinder();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0.0, 0.0, -1.2);
				glRotatef(90, 1, 0, 0);
				glScalef(1.0, 0.4, 1.0);
				glColor3f(0.1,0.1,0.1);
				cylinder();
				glScalef(0.5, 1.2, 0.5);
				glColor3f(0.5,0.5,0.5);
				cylinder();
			glPopMatrix();
			glTranslatef(0, 2, 0);
			glPushMatrix();	//Kaca depan
				glTranslatef(-1.0, 0.0, 0.0);
				glRotatef(90, 1, 0, 0);
				glScalef(0.9, 1.6, 1.4);
				glColor3f(1,1,1);
				cylinder();
			glPopMatrix();
			glPushMatrix();	//Badan belakang
				glTranslatef(0.5, -0.2, 0.0);
				glScalef(1.5, 1.8, 1.8);
				glColor3f(0.35, 0.04, 0.08);
				glutSolidCube(2);
			glPopMatrix();
			glPushMatrix();	//Badan bawah
				glTranslatef(-1.5, -1.0, 0.0);
				glScalef(0.5, 1.0, 1.8);
				glColor3f(0.35, 0.04, 0.08);
				glutSolidCube(2);
			glPopMatrix();
			glPushMatrix();	//Lampu
				glTranslatef(-2.0, -1.3, 1.0);
				glRotatef(90, 1, 0, 0);
				glScalef(0.1, 0.4, 0.3);
				glColor3f(1,1,0.5);
				cylinder();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(-2.0, -1.3, -1.0);
				glRotatef(90, 1, 0, 0);
				glScalef(0.1, 0.4, 0.3);
				glColor3f(1,1,0.5);
				cylinder();
			glPopMatrix();
			glPushMatrix(); //Bumper depan
				glTranslatef(-2.0, -1.9, 0.0);
				glRotatef(90, 1, 0, 0);
				glScalef(0.1, 1.9, 0.1);
				glColor3f(0.5,0.5,0.5);
				cylinder();
			glPopMatrix();
		glPopMatrix();
	}
	
	float cont1x = 2;
	float cont1z = -3;
	float cont2x = 11;
	float cont2z = -3;
	
	float rot1 = 180;
	float rot2 = 180;
	
  	GLuint containtex;
	
	void drawCont(float x, float z, float rot){
		glPushMatrix();	//Container 1
			glTranslatef(x, 1.0, z);
			glRotatef(180+rot, 0, 1.0, 0);
			glPushMatrix();
				glPushMatrix();	//Sambungan
					glTranslatef(0.5, 0.5, 0);
					glScalef(0.5, 0.2, 0.5);
					glColor3f(0.3,0.3,0.3);
					glutSolidCube(2);
				glPopMatrix();
				glPushMatrix();	//Container
					glTranslatef(5.0, 2.0, 0);
					glScalef(4.0, 2.0, 2.0);
					glColor3f(5.0,0.0,0.0);
					texbox(containtex);
				glPopMatrix();
			glPopMatrix();
			glTranslatef(2.0, 0, 0);
			glPushMatrix();
				glTranslatef(0.0, 0.0, 1.4);
				glRotatef(90, 1, 0, 0);
				glScalef(1.0, 0.4, 1.0);
				glColor3f(0.1,0.1,0.1);
				cylinder();
				glScalef(0.5, 1.2, 0.5);
				glColor3f(0.5,0.5,0.5);
				cylinder();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0.0, 0.0, -1.4);
				glRotatef(90, 1, 0, 0);
				glScalef(1.0, 0.4, 1.0);
				glColor3f(0.1,0.1,0.1);
				cylinder();
				glScalef(0.5, 1.2, 0.5);
				glColor3f(0.5,0.5,0.5);
				cylinder();
			glPopMatrix();
			glTranslatef(5.6, 0.0, 0.0);
			glPushMatrix();
				glTranslatef(0.0, 0.0, 1.4);
				glRotatef(90, 1, 0, 0);
				glScalef(1.0, 0.4, 1.0);
				glColor3f(0.1,0.1,0.1);
				cylinder();
				glScalef(0.5, 1.2, 0.5);
				glColor3f(0.5,0.5,0.5);
				cylinder();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0.0, 0.0, -1.4);
				glRotatef(90, 1, 0, 0);
				glScalef(1.0, 0.4, 1.0);
				glColor3f(0.1,0.1,0.1);
				cylinder();
				glScalef(0.5, 1.2, 0.5);
				glColor3f(0.5,0.5,0.5);
				cylinder();
			glPopMatrix();
		glPopMatrix();
	}
}
