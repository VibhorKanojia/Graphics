#include <iostream>
#include "gl_framework.hpp"
#include "image.hpp"
#include "background.hpp"
#include "transformer.hpp"

#define NUM_BUILDING 10
transformer t;

#define GRND_LEVEL -0.9
#define ROAD_LEVEL -0.8

background::background(){
  for (int i = 0 ; i < NUM_BUILDING ; i++){
    float randomNumber = (float)(rand() %200 + 100)/ 100;
    heights.push_back(randomNumber);
    cout<<randomNumber<<endl;
    building.push_back(rand()%2);
  }
}

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
    Texture t5(texture[5], "Data/lesson6/buildingtype1.bmp");
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

    glGenTextures(1, &texture[9]);
    Texture t9(texture[9], "Data/lesson6/buildingtype1.bmp");
    t9.generate();

    glGenTextures(1, &texture[10]);
    Texture t10(texture[10], "Data/lesson6/buildingtype2.bmp");
    t10.generate();

    glGenTextures(1, &texture[11]);
    Texture t11(texture[11], "Data/lesson6/road.bmp");
    t11.generate();

    glDisable(GL_TEXTURE_2D);
};


void background::draw_ground(void){
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,texture[2]);
    glColor4f(0,0.4,0.04,1);
    glBegin(GL_POLYGON);
     glTexCoord2f(0,0);
     glVertex3f(-6,GRND_LEVEL,-20);
     glTexCoord2f(7,0);
     glVertex3f(6,GRND_LEVEL,-20);
     glTexCoord2f(7,7);
     glVertex3f(6,GRND_LEVEL,20);
     glTexCoord2f(0,7);
     glVertex3f(-6,GRND_LEVEL,20);
    glEnd();

  glDisable(GL_TEXTURE_2D);
}


void background::draw_road(void){
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,texture[11]);
  glColor4f(0.5,0.5,0.5,1);
  for (int i = -20 ; i < 20 ; i++){
    glBegin(GL_POLYGON);
      glTexCoord2f(0,0);
      glVertex3f(0,ROAD_LEVEL,-i);
      glTexCoord2f(1,0);
      glVertex3f(1,ROAD_LEVEL,-i);
      glTexCoord2f(1,1);
      glVertex3f(1,ROAD_LEVEL,-(i+1));
      glTexCoord2f(0,1);
      glVertex3f(0,ROAD_LEVEL,-(i+1));
  glEnd();
  }

  glDisable(GL_TEXTURE_2D);
}


/*
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
    glBindTexture(GL_TEXTURE_2D,texture[7]);
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
    glBindTexture(GL_TEXTURE_2D,texture[8]);
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
*/


void background::draw_building(int text_num){ 
  float s = 0.5;
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture[text_num]);
  //glColor4f(0.8,0.8,1.0,1.0);
  glBegin(GL_POLYGON);
    glTexCoord2f(0,1);
    glVertex3f(0.0,s,0.0);
    glTexCoord2f(0,0);
    glVertex3f(0.0,0.0,0.0);
    glTexCoord2f(1,0);
    glVertex3f(s,0.0,0.0);
    glTexCoord2f(1,1);
    glVertex3f(s,s,0.0);
  glEnd();

  glBegin(GL_POLYGON);
    glTexCoord2f(0,1);
    glVertex3f(s,s,-s);
    glTexCoord2f(0,0);
    glVertex3f(s,0.0,-s);
    glTexCoord2f(1,0);
    glVertex3f(0.0,0.0,-s);
    glTexCoord2f(1,1);
    glVertex3f(0.0,s,-s);
  glEnd();


  glBegin(GL_POLYGON);
    glTexCoord2f(0,1);
    glVertex3f(s,s,-s);
    glTexCoord2f(0,0);
    glVertex3f(s,0.0,-s);
    glTexCoord2f(1,0);
    glVertex3f(s,0,0);
    glTexCoord2f(1,1);
    glVertex3f(s,s,0);
  glEnd();

  glBegin(GL_POLYGON);
    glTexCoord2f(0,1);
    glVertex3f(0,s,-s);
    glTexCoord2f(0,0);
    glVertex3f(0,0,-s);
    glTexCoord2f(1,0);
    glVertex3f(0.0,0.0,0);
    glTexCoord2f(1,1);
    glVertex3f(0.0,s,0);
  glEnd();
  
  glBegin(GL_POLYGON);
    glVertex3f(0.0,s,0.0);
    glVertex3f(s,s,0.0);
    glVertex3f(s,s,-s);
    glVertex3f(0,s,-s);
  glEnd();

  glBegin(GL_QUAD_STRIP);
    glVertex3f(0.0,0.0,0.0);
    glVertex3f(s,0.0,0.0);
    glVertex3f(s,0.0,-s);
    glVertex3f(0.0,0.0,-s);
  glEnd();
  glDisable(GL_TEXTURE_2D);
}



void background::struct_ground(void){
	glNewList(grnd,GL_COMPILE); 
		draw_ground();
	glEndList();
}


void background::struct_road(void){
  glNewList(rd,GL_COMPILE); 
    draw_road();
  glEndList();
}

void background::struct_building(int text_num){
	if (text_num == 9){
    glNewList(blding1,GL_COMPILE); 
	   draw_building(text_num);
	 glEndList();
  } 
  else {
    glNewList(blding2,GL_COMPILE); 
     draw_building(text_num);
   glEndList();
  } 
}


void background::createRoom(){
	
}

void background::createScene(){
    glPushMatrix();
      glCallList(grnd);
      glCallList(rd);
      glPushMatrix();
        glTranslatef(2,GRND_LEVEL,2);
        for (int i = 0 ; i < NUM_BUILDING ; i++){
          glTranslatef(0,0,-1);
          glPushMatrix();
            glScalef(2,heights[i],1);
            if (building[i]){
              glCallList(blding1);
            }
            else{
              glCallList(blding2);
            }
          glPopMatrix();
        }
      glPopMatrix();

      glPushMatrix();
        glTranslatef(-2,GRND_LEVEL,2);
        for (int i = 0 ; i < NUM_BUILDING ; i++){
          glTranslatef(0,0,-1);
          glPushMatrix();
            glScalef(2,heights[i],1);
            if (!building[i]){
              glCallList(blding1);
            }
            else{
              glCallList(blding2);
            }
          glPopMatrix();
        }
      glPopMatrix();


    glPopMatrix();
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
  if (cam_pos == 3){
    gluLookAt(0,3,0.7,0 , 0 , 6 , 0, 1, 0);
  }
}

