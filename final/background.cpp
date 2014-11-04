#include <iostream>
#include "gl_framework.hpp"
#include "image.hpp"
#include "background.hpp"
#include "transformer.hpp"


transformer t;


void background::load_textures() { 
    glEnable(GL_TEXTURE_2D);

    //texture for torso
    glGenTextures(1, &texture[0]);
    Texture t0(texture[0], "Data/lesson6/face1light1.bmp");
    t0.generate();

    glGenTextures(1, &texture[1]);
    Texture t1(texture[1], "Data/lesson6/face1light2.bmp");
    t1.generate();

    glGenTextures(1, &texture[2]);
    Texture t2(texture[2], "Data/lesson6/lightgrey.bmp");
    t2.generate();

    glGenTextures(1, &texture[3]);
    Texture t3(texture[3], "Data/lesson6/index.bmp");
    t3.generate();

    glGenTextures(1, &texture[4]);
    Texture t4(texture[4], "Data/lesson6/helipad.bmp");
    t4.generate();

    glGenTextures(1, &texture[5]);
    Texture t5(texture[5], "Data/lesson6/building.bmp");
    t5.generate();

    glGenTextures(1, &texture[6]);
    Texture t6(texture[6], "Data/lesson6/wall.bmp");
    t6.generate();

    glGenTextures(1, &texture[7]);
    Texture t7(texture[7], "Data/lesson6/sky.bmp");
    t7.generate();

    glGenTextures(1, &texture[8]);
    Texture t8(texture[8], "Data/lesson6/birdview.bmp");
    t8.generate();

    glDisable(GL_TEXTURE_2D);
};


void background::draw_ground(void){
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,texture[6]);
	glBegin(GL_POLYGON);
		vertex_vec v1,v2,res;
    v1.x = -2.0;
    v1.y = 0.0;
    v1.z = 0.0;
    v2.x = -2.0;
    v2.y = -2.0;
    v2.z = 0.0;
    res = t.CalcNormal(v1,v2);
    glNormal3d(res.x,res.y,res.z);
    glTexCoord2f(0,0);
		glVertex3f(-1 , -1, -1);
		glTexCoord2f(1,0);
		glVertex3f(1 , -1 , -1);
		glTexCoord2f(1,1);
		glVertex3f(1, 1, -1);
		glTexCoord2f(0,1);
		glVertex3f(-1, 1, -1);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D,texture[4]);
	glBegin(GL_POLYGON);
    v1.x = -2.0;
    v1.y = 0.0;
    v1.z = 0.0;
    v2.x = -2.0;
    v2.y = 0.0;
    v2.z = -2.0;
    res = t.CalcNormal(v1,v2);
    glNormal3d(res.x,res.y,res.z);
    glTexCoord2f(0,0);
		glVertex3f(-1 , 1, -1);
		glTexCoord2f(1,0);
		glVertex3f(1 , 1, -1);
		glTexCoord2f(1,1);
		glVertex3f(1, 1, 1);
		glTexCoord2f(0,1);
		glVertex3f(-1, 1, 1);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}



void background::draw_building(void){
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,texture[5]);
	//front
	glBegin(GL_POLYGON);
	 vertex_vec v1,v2,res;
    v1.x = 12.0;
    v1.y = 0.0;
    v1.z = 0.0;
    v2.x = -12.0;
    v2.y = -12.0;
    v2.z = 0.0;
    res = t.CalcNormal(v1,v2);
    glNormal3d(res.x,res.y,res.z);
   glTexCoord2f(0,0);
	 glVertex3f(-6,-5,6);
	 glTexCoord2f(1,0);
	 glVertex3f(6,-5,6);
	 glTexCoord2f(1,1);
	 glVertex3f(6,7,6);
	 glTexCoord2f(0,1);
	 glVertex3f(-6,7,6);
    glEnd();
    
    //left
    glBegin(GL_POLYGON);
    v1.x = 0.0;
    v1.y = 0.0;
    v1.z = 12.0;
    v2.x = 0.0;
    v2.y = -12.0;
    v2.z = 12.0;
    res = t.CalcNormal(v1,v2);
    glNormal3d(res.x,res.y,res.z);
   glTexCoord2f(0,0);
	 glVertex3f(6,-5,6);
	 glTexCoord2f(2,0);
	 glVertex3f(6,-5,-6);
	 glTexCoord2f(2,1);
	 glVertex3f(6,7,-6);
	 glTexCoord2f(0,1);
	 glVertex3f(6,7,6);
    glEnd();
    
    //right
    glBegin(GL_POLYGON);
    v1.x = 0.0;
    v1.y = 0.0;
    v1.z = 12.0;
    v2.x = 0.0;
    v2.y = -12.0;
    v2.z = 12.0;
    res = t.CalcNormal(v1,v2);
    glNormal3d(res.x,res.y,res.z);
	 glTexCoord2f(0,0);
	 glVertex3f(-6,-5,6);
	 glTexCoord2f(3,0);
	 glVertex3f(-6,-5,-6);
	 glTexCoord2f(3,1);
	 glVertex3f(-6,7,-6);
	 glTexCoord2f(0,1);
	 glVertex3f(-6,7,6);
    glEnd();
    
    //back
	glBegin(GL_POLYGON);
    v1.x = -12.0;
    v1.y = 0.0;
    v1.z = 0.0;
    v2.x = -12.0;
    v2.y = -12.0;
    v2.z = 0.0;
    res = t.CalcNormal(v1,v2);
    glNormal3d(res.x,res.y,res.z);
	 glTexCoord2f(0,0);
	 glVertex3f(-6,-5,-6);
	 glTexCoord2f(1,0);
	 glVertex3f(6,-5,-6);
	 glTexCoord2f(1,1);
	 glVertex3f(6,7,-6);
	 glTexCoord2f(0,1);
	 glVertex3f(-6,7,-6);
    glEnd();
    
    //top
    glBindTexture(GL_TEXTURE_2D,texture[8]);
    glColor4f(0.01,0.55,0.9,1);
	glBegin(GL_POLYGON);
	  v1.x = -12.0;
    v1.y = 0.0;
    v1.z = 0.0;
    v2.x = -12.0;
    v2.y = 0.0;
    v2.z = -12.0;
    res = t.CalcNormal(v1,v2);
    glNormal3d(res.x,res.y,res.z);
   glTexCoord2f(0,0);
	 glVertex3f(-6,7,-6);
	 glTexCoord2f(1,0);
	 glVertex3f(6,7,-6);
	 glTexCoord2f(1,1);
	 glVertex3f(6,7,6);
	 glTexCoord2f(0,1);
	 glVertex3f(-6,7,6);
    glEnd();
    
     glClearColor(1,1,1,1);
     glColor4f(1,1,1,1);
    //bottom
    glBindTexture(GL_TEXTURE_2D,texture[7]);
    //glColor4f(0.01,0.55,0.9,1);
	glBegin(GL_POLYGON);
	  v1.x = -12.0;
    v1.y = 0.0;
    v1.z = 0.0;
    v2.x = -12.0;
    v2.y = 0.0;
    v2.z = -12.0;
    res = t.CalcNormal(v1,v2);
    glNormal3d(res.x,res.y,res.z);
   glTexCoord2f(0,0);
	 glVertex3f(-6,-5,-6);
	 glTexCoord2f(7,0);
	 glVertex3f(6,-5,-6);
	 glTexCoord2f(7,7);
	 glVertex3f(6,-5,6);
	 glTexCoord2f(0,7);
	 glVertex3f(-6,-5,6);
    glEnd();
     glClearColor(.043,0.62,0.75,1);

     glDisable(GL_TEXTURE_2D);
  }




void background::struct_ground(void){
	glNewList(grnd,GL_COMPILE); 
		draw_ground();
	glEndList();
}


void background::struct_building(void){
	glNewList(blding,GL_COMPILE); 
		draw_building();
	glEndList();
}

void background::createRoom(){
	
}
void background::setCamera(int cam_pos){
	if (cam_pos  == 1){
		gluLookAt(0,3,-0.7,0 , 0 , -6 , 0, 1, 0);
	}
	if (cam_pos == 0){
		gluLookAt(0,3.2,0,0 , 0 , -6 , 0, 1, 0);
	}
	if (cam_pos == 2){
		gluLookAt(0,3,-2.2,0 , 0 , -6 , 0, 1, 0);
	}
}

