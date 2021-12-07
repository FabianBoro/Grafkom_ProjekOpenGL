/******************
File utama fungsi-fungsi
komponen menggambar
******************/

#ifndef DRAW_CPP
#define DRAW_CPP
#include <math.h> 
#include <GL/glut.h> 
#include "imageloader.h"
#include "decorcross.h"
using namespace std;

namespace{
	int slices = 30;	//Potongan pada silinder
	
	GLuint loadTexture(Image* image) {
		GLuint textureId;
		glGenTextures(1, &textureId);
		glBindTexture(GL_TEXTURE_2D, textureId);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 
		0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
		return textureId;
	}
	void texplane(GLuint texid){
	//Membuat papan sumbu x-y dengan ukuran 1
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texid);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glColor3f(1.0f, 1.0f, 1.0f);
		glScalef(1.0, -1.0, 1.0);
		glBegin(GL_QUADS); 
		glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-1.0f,-1.0f,0.0f); 
	    glTexCoord2f(0.0f, 1.0f);
			glVertex3f(1.0f,-1.0f,0.0f); 
	    glTexCoord2f(1.0f, 1.0f);
			glVertex3f(1.0f,1.0f,0.0f); 
	    glTexCoord2f(1.0f, 0.0f);
			glVertex3f(-1.0f,1.0f,0.0f); 
	    glEnd(); 
	    glDisable(GL_TEXTURE_2D);
	}
	
	void repeatedtexplane(GLuint texid, float col, float row){
	//Membuat papan sumbu x-y dengan ukuran 1
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texid);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT);
		glColor3f(1.0f, 1.0f, 1.0f);
		glScalef(1.0, -1.0, 1.0);
		glRotatef(-90, 0, 0, 1);
		glBegin(GL_QUADS); 
		glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-1.0f,-1.0f,0.0f); 
	    glTexCoord2f(0.0f, row);
			glVertex3f(1.0f,-1.0f,0.0f); 
	    glTexCoord2f(col, row);
			glVertex3f(1.0f,1.0f,0.0f); 
	    glTexCoord2f(col, 0.0f);
			glVertex3f(-1.0f,1.0f,0.0f); 
	    glEnd(); 
	    glDisable(GL_TEXTURE_2D);
	}
	
	void plane(){
	//Membuat papan sumbu x-y dengan ukuran 2
		glBegin(GL_QUADS); 
	      glVertex3f(-1.0f,-1.0f,0.0f); 
	      glVertex3f(1.0f,-1.0f,0.0f); 
	      glVertex3f(1.0f,1.0f,0.0f); 
	      glVertex3f(-1.0f,1.0f,0.0f); 
	    glEnd(); 
	}
	
	void cylinder(){
	//Membuat silinder dengan radius 1 dan tinggi 2 
	//berpusat di tengah mengarah ke atas
		float rot;
		
		const float inc = 360.0/slices;
		const float aft = 2.0*M_PI/slices;
		const float leng = sin(aft/2.0);
		const float dist = cos(aft/2.0);
		
		//Selimut
		glPushMatrix();
		glRotated(90, 0, 1, 0);
		for(rot = inc/2.0; rot < 360.0; rot += inc){
			glPushMatrix();
			glRotated(rot, 0, 1, 0);
			glTranslatef(0,0,dist); 
			glScalef(leng, 1.0, 1.0);
			plane();
			glPopMatrix();
		}
		glPopMatrix();
		
		//Alas
		glPushMatrix();
	    glRotated(-90, 1, 0, 0); 
	    glTranslatef(0,0,1); 
		glBegin(GL_POLYGON);
		for(rot = 0.0; rot < 2*M_PI; rot += aft){
			glVertex3f(cos(rot),sin(rot),0.0); 
		}
		glEnd();
		glPopMatrix();
		
		//Tutup
		glPushMatrix();
	    glRotated(90, 1, 0, 0); 
	    glTranslatef(0,0,1); 
		glBegin(GL_POLYGON);
		for(rot = 0.0; rot < 2*M_PI; rot += aft){
			glVertex3f(cos(rot),sin(rot),0.0); 
		}
		glEnd();
		glPopMatrix();
	}
	
	void texbox(GLuint image){
		glPushMatrix();
			glRotatef(90, 1, 0, 0);
			glTranslatef(0, 0, -1);
			glScalef(1, 1, 1);
			texplane(image);
		glPopMatrix();
		glPushMatrix();
			glRotatef(0, 0, 1, 0);
			glTranslatef(0, 0, 1);
			glScalef(1, 1, 1);
			glRotatef(90, 0, 0, 1);
			texplane(image);
		glPopMatrix();
		glPushMatrix();
			glRotatef(90, 0, 1, 0);
			glTranslatef(0, 0, 1);
			glScalef(1, 1, 1);
			glRotatef(90, 0, 0, 1);
			texplane(image);
		glPopMatrix();
		glPushMatrix();
			glRotatef(180, 0, 1, 0);
			glTranslatef(0, 0, 1);
			glScalef(1, 1, 1);
			glRotatef(90, 0, 0, 1);
			texplane(image);
		glPopMatrix();
		glPushMatrix();
			glRotatef(270, 0, 1, 0);
			glTranslatef(0, 0, 1);
			glScalef(1, 1, 1);
			glRotatef(90, 0, 0, 1);
			texplane(image);
		glPopMatrix();
		glPushMatrix();
			glRotatef(-90, 1, 0, 0);
			glTranslatef(0, 0, -1);
			glScalef(1, 1, 1);
			texplane(image);
		glPopMatrix();
	}
	
	void drawAdBoard(GLuint image, float x, float y, float z, float w, float h, float r){
		glPushMatrix();
			glTranslatef(x, y, z);
			glPushMatrix();
			glScalef(0.2, y, 0.2);
			glColor3f(0.4, 0.4, 0.4);
			cylinder();
			glPopMatrix();
			glTranslatef(0, y+h, 0);
			glRotatef(r, 0, 1, 0);
			glScalef(w, h, 1);
			glRotatef(90, 0, 0, 1);
			texplane(image);
		glPopMatrix();
	}
	
	void addTexture(const char *filename, GLuint *id){
		Image *image = loadBMP(filename);
  		*id = loadTexture(image);
		delete image;
	}
	
	GLuint eE[4];
	
	void ee(){
		addTexture("Ee1.bmp", &eE[0]);
		addTexture("Ee2.bmp", &eE[1]);
		addTexture("Ee3.bmp", &eE[2]);
		addTexture("Ee4.bmp", &eE[3]);
	}
	void EE(){
		glPushMatrix();
		glTranslatef(-500, 9, -400);
		glScalef(16, 9, 16);
		glPushMatrix();
			glRotatef(0, 0, 1, 0);
			glTranslatef(0, 0, 1);
			glScalef(1, 1, 1);
			glRotatef(90, 0, 0, 1);
			texplane(eE[0]);
		glPopMatrix();
		glPushMatrix();
			glRotatef(90, 0, 1, 0);
			glTranslatef(0, 0, 1);
			glScalef(1, 1, 1);
			glRotatef(90, 0, 0, 1);
			texplane(eE[1]);
		glPopMatrix();
		glPushMatrix();
			glRotatef(180, 0, 1, 0);
			glTranslatef(0, 0, 1);
			glScalef(1, 1, 1);
			glRotatef(90, 0, 0, 1);
			texplane(eE[2]);
		glPopMatrix();
		glPushMatrix();
			glRotatef(270, 0, 1, 0);
			glTranslatef(0, 0, 1);
			glScalef(1, 1, 1);
			glRotatef(90, 0, 0, 1);
			texplane(eE[3]);
		glPopMatrix();
		glPopMatrix();
	}
}

#endif
