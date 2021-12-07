/********************************************
Vandicco Maris Siregar		24060119130126
M. Bahri Hussein Almaroqy	24060119120017
Kenny Anaga					24060119130098
Tsaqif Muhammad Arkan		24060119120026
*********************************************/	

/******************************************
Program Truk Gandeng dengan interaksi++

Gunakan tombol:
-> WASD untuk bergerak
-> panah (arrow key) untuk memutar arah kamera
-> spasi untuk melompat
-> 'e' untuk berinteraksi dengan objek

Kecepatan bergerak dipengaruhi kecepatan PC
*/
const float speed = 

/*************     Atur ini jika Kecepatan/Kelambatan     **************/
/**/                                                                 /**/
                                  0.1                                
/**/                                                                 /**/
/***********************************************************************/
//default speed 0.7
;

#include <math.h> 
#include <GL/glut.h> 
#include <stdio.h> 
#include <stdlib.h> 

#include "vector2.h"
#include "hook.h"
#include "circle.h"
#include "rect.h"
#include "movecoll.h"
#include "staticcoll.h"
#include "pickable.h"
#include "imageloader.h"
#include "imageloader.cpp"

#include "draw.cpp" 
#include "truck.cpp"

using namespace std;

const float ground = 1.75;							//Letak tanah menurut kamera
const float minrot = -M_PI/4.0, maxrot = M_PI/4.0;	//min-max rotasi ke atas-bawah

const float gravity = 0.01;		//Gravitasi
const float jumpPower = 1.4;	//Kekuatan lompat
const float rotSpeed = 0.012f;	//Kecepatan memutar kamera

float angle=0.0, deltaAngle = 0.0, anglup = 0.0, deltaAnglup = 0.0, ratio; 
float x=0.0f,y=ground,z=5.0f; // posisi awal kamera 
float lx=0.0f,ly=0.0f,lz=-1.0f;
float rx=1.0f,rz=0.0f; 
int deltaMove = 0, deltaCrab = 0, h,w; 
float deltaFly = 0.0;
int bitmapHeight=12; 
float deltaDrive = 0; 
float phi = 0;

static bool isJump = false;
static bool isDriving = false;
static bool isOpen = false;

MoveColl player(Rect(0,15,1,1));

//Variabel penyimpan gambar
GLuint road1, sand, building, barr, rock1, rock2, rock3;
GLuint bg[5], bg0, bg5;
GLuint ads1, ads3;
GLuint crate1, crate2;

void DecorCross::draw(){
	for(int c = 0; c < DecorCross::counter; c++){
		DecorCross *d = DecorCross::container[c];
		for(int i = 0; i < d->position.size(); i++){
			glPushMatrix();
				glTranslatef(d->position[i].x, d->h, d->position[i].y);
				glPushMatrix();
					glRotatef(90, 1, 0, 0);
					glTranslatef(0, 0, -(d->h));
					glScalef(d->w, d->w, 1);
					texplane(d->image);
				glPopMatrix();
				for(int i = 0; i < 4; i++){
					glPushMatrix();
						glRotatef(90*i, 0, 1, 0);
						glTranslatef(0, 0, d->w);
						glScalef(d->w, d->h, 1);
						glRotatef(90, 0, 0, 1);
						texplane(d->image);
					glPopMatrix();
				}
			glPopMatrix();
		}
	}
}

void Pickable::draw(){
	for(int i = 0; i < Pickable::counter; i++){
		Pickable *p = Pickable::container[i];
		glPushMatrix();
		if(Pickable::isHold && Pickable::hold == p){
			p->setPos(x+4*lx, z+4*lz);
			glTranslatef(0, y+4*ly, 0);
		}
		glTranslatef(p->coll->rect.center.x, p->coll->rect.size.x, p->coll->rect.center.y);
		glScalef(p->coll->rect.size.x, p->coll->rect.size.x, p->coll->rect.size.x);
		texbox(p->image);
		glPopMatrix();
	}
}

void Reshape(int w1, int h1){ 
//	Fungsi reshape 
	if(h1 == 0) h1 = 1; 
	w = w1; 
	h = h1; 
	ratio = 1.0f * w / h; 
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 
	glViewport(0, 0, w, h); 
	gluPerspective(45, ratio, 0.1, 1000); 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); 
	gluLookAt(x, y, z, 
			  x+lx, y+ly, z+lz, 
			  0.0f, 1.0f, 0.0f); 
} 

void orientMe(float ang, float angup){ 
//	Fungsi ini untuk memutar arah kamera
	lx = sin(ang); lz = -cos(ang); 
	rz = sin(ang); rx = cos(ang);
	ly = tan(angup);
	glLoadIdentity();
	gluLookAt(x, y, z, 
  			  x+lx, y+ly, z+lz, 
			  0.0f, 1.0f, 0.0f); 
} 

void moveMeFlat(float i, float j, float k){ 
//	Fungsi ini untuk maju mundur kamera 
	x = x + i*(lx)*speed + j*(rx)*speed; 
	z = z + i*(lz)*speed + j*(rz)*speed; 
	y = y + k*speed;
	if(y < ground){
		y = ground;
		isJump = false;
	}
	player.setPos(x,z);
	x = player.rect.center.x;
	z = player.rect.center.y;
	glLoadIdentity();
	gluLookAt(x, y, z, 
			  x+lx, y+ly, z+lz, 
			  0.0f,1.0f,0.0f); 
}

/**********Konstruktor Objek**********/
Vector2 orienter;
Vector2 helper;
Vector2 position;
Vector2 pmove;
Hook hc1(cont1x, cont1z, cont2x, cont2z);
Hook hc2(cont2x, cont2z, cont2x+11, cont2z);
Circle enterTruck(headx, headz, 8);
Circle tombol(-200, 10, 4);
MoveColl truck(Rect(headx, headz, 2, 2));
StaticColl block(Rect(0, 10, 1010, 0.2));
StaticColl block2(Rect(0, -30, 1010, 0.2));
StaticColl palang(Rect(-200, -10, 1, 20));
Pickable crate[6];
Rect nutup1(-300, -10, 2, 20);
Rect nutup2(-100, -10, 2, 20);

DecorCross dbuild;
DecorCross drock1, drock2, drock3;

void display(){ 
	//Jika mengendarai, letakkan kamera ke atas truk, jika tidak letakkan di sudut pertama
	if(isDriving){
		glLoadIdentity();
		gluLookAt(headx - 28*cos(roth*M_PI/180), 15, headz - 28*sin(roth*M_PI/180), 
  		headx + 15*cos(roth*M_PI/180), 0, headz + 15*sin(roth*M_PI/180), 
  		0.0f, 1.0f, 0.0f); 
  		//Kondisional maju/mundur
		if(deltaMove > 0){
			deltaDrive += 0.01;		//def 0.0001
			if(deltaDrive > 3.5) deltaDrive = 3.5;
		}
		else if(deltaMove < 0){
			if(deltaDrive > 0) deltaDrive -= 0.03;		
			else{
				deltaDrive -= 0.002;
				if(deltaDrive < -1.5) deltaDrive = -1.5;
			}
		}
		else{
			if(deltaDrive > 0){
				deltaDrive -= 0.01;
				if(deltaDrive < 0) deltaDrive = 0;
			}
			else{
				deltaDrive += 0.01;
				if(deltaDrive > 0) deltaDrive = 0;
			}
		}
		//Kondisional berbelok/berputar
		if(deltaCrab != 0){
			phi += deltaCrab*(0.01+(((phi<0?-1:1)!=deltaCrab))*0.04);
			if(phi > 1 || phi < -1) phi = phi < 0 ? -1 : 1;
		}
		else{
			if(phi > 0){
				phi -= 0.01;
				if(phi < 0) phi = 0;
			}
			else if(phi < 0){
				phi += 0.01;
				if(phi > 0) phi = 0;
			}
		}
		
		//Menggerakkan kepala truck
		roth += phi*3.5*deltaDrive*speed;
		orienter.rad2Vec((roth/180)*M_PI);
		deltaDrive = (deltaDrive < 0 ? -1 : 1)*
		truck.setPos(headx+deltaDrive*orienter.x*speed, 
		headz+deltaDrive*orienter.y*speed)/speed;
		headx = truck.rect.center.x;
		x = headx;
		headz = truck.rect.center.y;
		z = headz;
		enterTruck.center.setPos(headx, headz);
		
		//Kedua kontainer
		hc1.setPos(headx, headz, &helper);
		cont1x = hc1.pos.x;
		cont1z = hc1.pos.y;
		rot1 = (M_PI-hc1.dir)*180/M_PI;
		hc2.setPos(hc1.tpos.x, hc1.tpos.y, &helper);
		cont2x = hc2.pos.x;
		cont2z = hc2.pos.y;
		rot2 = (M_PI-hc2.dir)*180/M_PI;
	}
	else{
		if (deltaMove || deltaCrab || isJump){
			if(isJump){	//Jika sedang melompat, maka kecepatan y dipengaruhi gravitasi
	  			deltaFly -= gravity*speed*20;
	  			block.isEnabled = false;
	  			block2.isEnabled = false;
			}
			else{
				block.isEnabled = true;
				block2.isEnabled = true;
			}
			pmove.setPos(deltaMove, deltaCrab);
			pmove.normalize();
			moveMeFlat(pmove.x, pmove.y, deltaFly);
	  	}
		if (deltaAngle || deltaAnglup) { 
			angle += deltaAngle*speed*10;
	    	anglup += deltaAnglup*speed*10;
	    	if(anglup < minrot || anglup > maxrot){
	    		anglup -= deltaAnglup*speed*10;
	    	}
	    	orientMe(angle, anglup);
		} 
	}
	
	//Kondisional untuk endless
	if(x < -1000 || x > 1000){
		int msgn = x < 0? 1 : -1;
		x += msgn*2000;
		headx += msgn*2000;
		cont1x += msgn*2000;
		cont2x += msgn*2000;
		hc1.pos.x += msgn*2000;
		hc1.tpos.x += msgn*2000;
		hc2.pos.x += msgn*2000;
		hc2.tpos.x += msgn*2000;
	}
	
	position.setPos(x,z);
	glClearColor(0.53, 0.81, 0.92, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glMatrixMode(GL_MODELVIEW);

	/*Gambar objek di sini...*/
	glPushMatrix();
	glTranslatef(x, 100+y, z);
  	
  	/*Gambar Background/SkyBox*/
  	glDisable(GL_LIGHTING); 
	//bg 0 (sb y+)
	glPushMatrix();
		glRotatef(-90, 1.0, 0.0, 0.0);
		glRotatef(180, 0.0, 0.0, 1.0);
		glTranslatef(0.0, 0.0, 500.0);
		glScalef(500.0, 500.0, 1.0);
  		texplane(bg0);
  	glPopMatrix();
  	//bg all
  	for(int i = 1; i <= 4; i++){
  		glPushMatrix();
			glRotatef((i-1)*90, 0.0, 1.0, 0.0);
			glRotatef(90, 0.0, 0.0, 1.0);
			glTranslatef(0.0, 0.0, 500.0);
			glScalef(500.0, 500.0, 1.0);
	  		texplane(bg[i]);
	  	glPopMatrix(); 
  	}
  	//bg 5 (sb y-)
	glPushMatrix();
		glRotatef(90, 1.0, 0.0, 0.0);
		glRotatef(0, 0.0, 0.0, 1.0);
		glTranslatef(0.0, 0.0, 500.0);
		glScalef(500.0, 500.0, 1.0);
  		texplane(bg5);
  	glPopMatrix();
	glPopMatrix();
	glEnable(GL_LIGHTING); 
	
	/*Looping Highway / Gambar Environment Utama*/
	for(int i = -1; i <= 1; i++){
		glPushMatrix();
		glTranslatef(i*2000, 0, 0);
		
		glDisable(GL_LIGHTING); 
		//sand_left-side of highway
		glPushMatrix();
			glTranslatef(0.0, 0.0, 1010.0);
			glRotatef(90, 1, 0, 0);
			glScalef(1000.0, 1000.0, 1.0);
			repeatedtexplane(sand, 20, 20);
		glPopMatrix();
		
		//sand_right-side of highway
		glPushMatrix();
			glTranslatef(0.0, 0.0, -1030.0);
			glRotatef(90, 1, 0, 0);
			glScalef(1000.0, 1000.0, 1.0);
			repeatedtexplane(sand, 20, 20);
		glPopMatrix();
		glEnable(GL_LIGHTING);
		 
		/*Main-Highway*/
		glPushMatrix();
		glTranslatef(-495,0,-10);
		glRotatef(90, 0, 0, 1);
		glRotatef(90, 0, 1, 0);
		glScalef(20, 1000, 1);
		repeatedtexplane(road1, 2, 100);
		glPopMatrix();
		
		//Objek Dekorator
		DecorCross::draw();
		
		Pickable::draw();
	  	
	  	//gambar iklan
	  	drawAdBoard(ads3, -283, 7, -53, 20, 10, 50); //untuk r, z+ ke x+
	  	drawAdBoard(ads1, -810, 2, 33, 15, 10, -50);
	  	
	    //batas jalan bag kiri (sb z+)
	    glPushMatrix();
			glTranslatef(0, 0.5, 10);
			glScalef(1000, 0.5, 0.2);
			glColor3f(0.5, 0.5, 0.5);
	    	glutSolidCube(2);
	    glPopMatrix();
	    //batas jalan bag kanan (sb z-)
	    glPushMatrix();
			glTranslatef(0, 0.5, -30);
			glScalef(1000, 0.5, 0.2);
			glColor3f(0.5, 0.5, 0.5);
	    	glutSolidCube(2);
	    glPopMatrix();
	    
	    /*Barrier/Palang Jalan*/
	    static float rotpol = 0;
	    if(!isOpen){
		    rotpol -= speed;
		    if(rotpol < 0) rotpol = 0;
		}
		else{
			rotpol += speed;
		    if(rotpol > 90) rotpol = 90;
		}
		glPushMatrix();
			glTranslatef(-200, 1, -10);
			glTranslatef(0, 0, 20);
			glRotatef(rotpol, 1, 0, 0);
			glTranslatef(0, 0, -20);
			glRotatef(90, 1, 0, 0);
			glRotatef(90, 0, 1, 0);
			glScalef(0.6, 20, 1);
			texplane(barr);
		glPopMatrix();
	    glPushMatrix();
			glTranslatef(-200, 1, 10);
			glScalef(0.7, 1, 0.7);
			glColor3f(1, 1, 1);
	    	glutSolidCube(2);
	    glPopMatrix();
	    glPushMatrix();
			glTranslatef(-200, 1.4, 10);
			glScalef(1, 0.3, 0.3);
			if(isOpen) glColor3f(0, 1, 0);
			else glColor3f(1, 0, 0);
	    	glutSolidCube(2);
	    glPopMatrix();
	    glPopMatrix();
	    if(nutup1.isInside(truck.rect.center) || 
		nutup2.isInside(truck.rect.center)){
			isOpen = false;
			palang.isEnabled = true;
		}
	}
    
	/*Main-Truck*/
	drawHead();
	drawCont(cont1x, cont1z, rot1);
	drawCont(cont2x, cont2z, rot2);
	
	EE();
	glutSwapBuffers();
	glFlush(); 
}  

void pressKey(int key, int x, int y) { 
//	Fungsi ini akan dijalankan saat tombol keyboard ditekan dan belum dilepas.
//	Selama tombol ditekan, variabel angle dan move diubah => kamera bergerak.
	switch (key) { 
		case GLUT_KEY_LEFT : deltaAngle = -rotSpeed; break; 
		case GLUT_KEY_RIGHT : deltaAngle = rotSpeed; break;
		case GLUT_KEY_UP : deltaAnglup = rotSpeed; break;
		case GLUT_KEY_DOWN : deltaAnglup = -rotSpeed; break;
	}
} 

void pressKeyReg(unsigned char key, int a, int b) { 
//	Fungsi ini dijalankan saat keyboard ditekan yang bisa diterima ASCII.
	switch (key){
		case 'w' : 
		case 'W' : deltaMove = 1; break; 
		case 's' :
	    case 'S' : deltaMove = -1; break;  
	    case 'a' : 
		case 'A' : deltaCrab = -1; break; 
		case 'd' :
	    case 'D' : deltaCrab = 1; break;  
	    case ' ' :
			if(!isJump && !isDriving){
				isJump = true;
				deltaFly = jumpPower;
			}
			break;
		case 'e' :
		case 'E' :
			if(isDriving){
				isDriving = false;
				x = headx + 5*cos(((roth+90)/180)*M_PI);  //def 10
				z = headz + 5*sin(((roth+90)/180)*M_PI);  //def 10
				orientMe(angle, anglup);
				deltaDrive = 0;
			}
			else if(Pickable::togglePick(&(player.rect.center)));
			else if(tombol.isInside(player.rect.center)){
				isOpen = !isOpen;
				palang.isEnabled = !palang.isEnabled;
			}
			else{
				if(Pickable::togglePick(&(player.rect.center)));
				else if(enterTruck.isInside(position)) {
					isJump = false;
					block.isEnabled = true;
					block2.isEnabled = true;
					isDriving = true;
				}
			}
			break;
	}
}

void releaseKey(int key, int x, int y) { 
//	Fungsi ini akan dijalankan saat tekanan tombol keyboard dilepas.
//	Saat tombol dilepas, variabel angle dan move diset nol => kamera berhenti. 
	switch (key) { 
		case GLUT_KEY_LEFT : if (deltaAngle < 0.0f) 
        	deltaAngle = 0.0f; break; 
		case GLUT_KEY_RIGHT : if (deltaAngle > 0.0f) 
    		deltaAngle = 0.0f; break; 
		case GLUT_KEY_UP : if (deltaAnglup > 0.0f) 
    		deltaAnglup = 0.0f; break; 
		case GLUT_KEY_DOWN : if (deltaAnglup < 0.0f) 
    		deltaAnglup = 0.0f; break; 
	} 
}

void releaseKeyReg(unsigned char key, int x, int y) { 
//	Fungsi ini dijalankan saat keyboard dilepas yang bisa diterima ASCII.
	switch (key){
		case 'w' : 
		case 'W' : if (deltaMove > 0) deltaMove = 0; break;
		case 's' :
	    case 'S' : if (deltaMove < 0) deltaMove = 0; break;
	    case 'a' : 
		case 'A' : if (deltaCrab < 0) deltaCrab = 0; break;
		case 'd' :
	    case 'D' : if (deltaCrab > 0) deltaCrab = 0; break;
	}
}

/*******Variable untuk Pencahayaan*******/
const GLfloat light_ambient[] = { 0.5f, 0.5f, 0.5f, 0.0f }; 
const GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f }; 
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; 
const GLfloat light_position[] = { 0.0f, 20.0f, 10.0f, 1.0f }; 
const GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f }; 
const GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f }; 
const GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; 
const GLfloat high_shininess[] = { 100.0f }; 

void lighting(){ 
//	Fungsi mengaktifkan pencahayaan 
	glEnable(GL_DEPTH_TEST); 
	glDepthFunc(GL_LESS); 
	glEnable(GL_LIGHT0); 
	glEnable(GL_NORMALIZE); 
	glEnable(GL_COLOR_MATERIAL); 
	glEnable(GL_LIGHTING); 
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient); 
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse); 
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular); 
	glLightfv(GL_LIGHT0, GL_POSITION, light_position); 
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient); 
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse); 
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); 
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess); 
}

void init(void){ 
	//Highway Texture
	addTexture("tol.bmp", &road1);
	
	//Building Texture
	addTexture("building4.bmp", &building);
	dbuild.set(building, 50, 80);
	dbuild.add(-500, -400);
	
	//Rocks Texture
	addTexture("rock1.bmp", &rock1);		
	addTexture("rock2.bmp", &rock2);
	addTexture("rock4.bmp", &rock3);
	drock1.set(rock1, 3, 4);
	drock2.set(rock2, 9, 5);
	drock3.set(rock3, 12, 6);	
	
	DecorCross *darr[] = {&drock1, &drock2, &drock3};
	float arrrock[][3] = {
	{-50, -42, 0},{15, -50, 1}, {-20, -61, 2}, {-9, 26, 1}, {9, 38, 0},
	{26, 50, 1}, {-90, 31, 2}, {-55, 21, 1}, {66, 60, 0}, {41, 24, 2},
	{-124, 38, 0}, {-75, -51, 1}, {-106, -44, 2}, {-154, 55, 2}, {-171, 69, 1},
	{-166, -74, 1}, {-190, -49, 0}, {-236, 85, 0}, {-215, -66, 2}, {-294, 56, 1},
	{-581, 60, 1}, {-688, 52, 0}, {-755, 31, 2}, {-821, -56, 1}, {129, 47, 0},
	{143, -57, 2}, {244, 37, 1}, {274, -96, 1}, {367, 85, 2}, {334, -69, 0},
	{482, 102, 0}, {514, -67, 1}, {552, 65, 2}, {597, -84, 0}, {642, -54, 1},
	{-555, -87, 0}, {-593, -64, 2}, {-669, -52, 1}, {-701, 47, 0}, {-725, -74, 1},
	{800, 94, 1}, {841, -44, 2}, {887, 54, 0}, {912, -57, 0}, {987, 40, 1}
						};
	
	for(int i = 0; i < 45; i++){
		darr[(int)arrrock[i][2]]->add(arrrock[i][0], arrrock[i][1]);
	}
	
	//Background/SkyBox Texture
	addTexture("bg0.bmp", &bg0);
	addTexture("bg1.bmp", &bg[1]);
	addTexture("bg2.bmp", &bg[2]);
	addTexture("bg3.bmp", &bg[3]);
	addTexture("bg4.bmp", &bg[4]);
	addTexture("bg5.bmp", &bg5);
	
	//sand_left/right-side of highway texture
	addTexture("sand.bmp", &sand);

	//barrier/palang texture
	addTexture("barrier.bmp", &barr);
	
	//container texture
	addTexture("container1.bmp", &containtex);
	
	//papan iklan
	addTexture("ads1.bmp", &ads1);
	addTexture("ads3.bmp", &ads3);
	
	//Crate
	addTexture("crate1.bmp", &crate1);
	addTexture("crate2.bmp", &crate2);
	crate[0].set(-20, 5, 1, crate1);
	crate[1].set(-15, 5, 1, crate2);
	crate[2].set(-25, 5, 1, crate1);
	crate[3].set(-30, 5, 1, crate2);
	crate[4].set(-12, 7, 0.7, crate1);
	crate[5].set(-8, 8, 0.5, crate2);
	
	ee();
	
} 

int main(int argc, char **argv){
	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA); 
	glutInitWindowPosition(100,100); 
	glutInitWindowSize(640,480); 
	glutCreateWindow("Advanced Truk Gandeng in Highway_Sandsea Environment"); 
	glutIgnoreKeyRepeat(1); // Mengabaikan key repeat (saat tombol keyboard dipencet terus) 
	glutSpecialFunc(pressKey);
	glutSpecialUpFunc(releaseKey);
	glutKeyboardFunc(pressKeyReg);
	glutKeyboardUpFunc(releaseKeyReg);
	glutDisplayFunc(display); 
	glutIdleFunc(display); // Fungsi display-nya dipanggil terus menerus
	glutReshapeFunc(Reshape);
	lighting();
	init();
	glutMainLoop();
	return(0);
}
