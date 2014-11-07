#include "gl_framework.hpp"
#include "record_frames.hpp"
#include "image.hpp"
#include "transformer.hpp"
#include "background.hpp"
#include <math.h>
#include <string>
#include <fstream>
#include <vector>
#include <stdlib.h>

#define PI 3.14159265
#define INTERVAL 1.0
#define TOTAL_CAMERA 4
background myback;
transformer::transformer() {
  torso_x = 0.3;
  torso_y = 0.6;
  torso_z = 0.3;
  conn_x = 0.06;
  conn_y = 0.06;
  conn_z = 0.06;
  head_x = 0.1;
  head_y = 0.1;
  head_z = 0.1;
  upper_leg_x = 0.15;
  upper_leg_y = 0.25;
  upper_leg_z = 0.06;
  upper_leg_w1 = 0.15;
  upper_leg_w2 = 0.075;
  lower_leg_x = 0.075;
  lower_leg_y = 0.15;
  lower_leg_z = 0.06; 
  upper_hand_x = 0.2;
  upper_hand_y = 0.06;
  upper_hand_z = 0.06;
  lower_hand_x = 0.2;
  lower_hand_y = 0.06;
  lower_hand_z = 0.06;
}

vertex_vec transformer:: CalcNormal(vertex_vec v1, vertex_vec v2) {
  vertex_vec result;
  result.x = (v1.y*v2.z - v1.z*v2.y);
  result.y = (v1.z*v2.x - v1.x*v2.z);
  result.z = (v1.x*v2.y - v1.y*v2.x);
  return result;
}

void transformer::load_textures() { 
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

    glGenTextures(1, &texture[9]);
    Texture t9(texture[9], "Data/lesson6/bomb.bmp");
    t9.generate();

    glGenTextures(1, &texture[10]);
    Texture t10(texture[10], "Data/lesson6/head.bmp");
    t10.generate();

    glDisable(GL_TEXTURE_2D);
};


void transformer::DrawCircle(float r,float Z){
  glColor4f(0.2,0.2,0.3,1.0);
  float X = r;
  float Y = 0;
  float theta = 0;
  glBegin(GL_POLYGON);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,texture[0]);
  for (int i = 0 ; i < precision ; i++){
	  if (i == 0 ){
		glTexCoord2f(0.3,0.3);
	  }
	  if (i == (precision -1)/4){
		glTexCoord2f(1,0);
	  }
	  if (i == (precision -1)/2){
		glTexCoord2f(1,1);
	  }
	  if (i == precision -1){
		glTexCoord2f(0,1);
	  }
      glVertex3f(X,Y,Z);
      theta = theta + 2*3.1415926f/precision;
      X = r*cos(theta);
      Y = r*sin(theta);
  }
  glEnd();
  glDisable(GL_TEXTURE_2D);
}

void transformer::shearMatrix(int shearX, int shearY) {
  float m[] = { 
    1, shearY, 0, 0, 
      shearX, 1, 0, 0,
      0, 0, 1, 0,
      0, 0, 0, 1 };
  glMultMatrixf(m);
}


void transformer::DrawTyre(float r,float width,float z){
  DrawCircle(r,z);
  DrawCircle(r,width+z);
  DrawLayer(r,z,width+z,1,1);
}


void transformer::DrawSphere(float r,int flag)
{ 
	
	if (flag ==0){
		float z=0;
		for(int i=0; i<precision2; i++) {
			DrawLayer(r, z, z+r/precision2,0,1);
			z = z+r/precision2;
		}
		DrawTyre(r,0.1,-0.1);
	}
	
	else {
		float z=-r;
		for(int i=0; i<2*precision2; i++) {
			DrawLayer(r, z, z+r/precision2,0,0);
			z = z+r/precision2;
		}
	}
}

void transformer::DrawJoint(float r,float z){
  glColor4f(1,1,1,1);
  float X = r;
  float Y = 0.0;
  float Z = z;
  float theta = 0;  
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,texture[0]);
  glBegin(GL_TRIANGLES);
    vertex_vec v1,v2,res;
    v1.x = X;
    v1.y = Y+r;
    v1.z = Z-z;
    v2.x = X-r;
    v2.y = Y+r;
    v2.z = Z-z;
    res = CalcNormal(v1,v2);
    std::cout << res.x <<" "<< res.y << " "<< res.z << "normals" << std::endl;
    glNormal3d(res.x,res.y,res.z);
  	glTexCoord2f(1,1);
	  glVertex3f(X,Y,Z);
	  glTexCoord2f(0,0);
	  glVertex3f(0,-r,z);
	  glTexCoord2f(1,0);
	  glVertex3f(r,-r,z);
  glEnd();
  glDisable(GL_TEXTURE_2D);
}


void transformer::DrawLayer(float R, float z1, float z2,int flag,int texture_flag){
  
  float r2,r1;
  if (flag ==0){
    r2 = sqrt(R*R-z2*z2);
    r1 = sqrt(R*R - z1*z1);
  }
  else if (flag ==1){
    r2 = R;
    r1 = R;
  }
  float X = r1;
  float Y = 0;
  float x = r2;
  float y = 0;
  float theta = 0;
  if (texture_flag ==1){
	  glColor4f(0.1,0.1,0.2,1.0);
    glEnable(GL_TEXTURE_2D);
	  glBindTexture(GL_TEXTURE_2D, texture[2]);   // 2d texture (x and y size)
    
  }
  
  if (texture_flag ==0){
	glColor4f(0.2,0.2,0.2,1.0);
  glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[3]);   // 2d texture (x and y size)
  }
  for (int i = 0 ; i < precision ; i++){
    glBegin(GL_QUADS);
      vertex_vec v1,v2,res;
      v1.x = X - x;
      v1.y = Y-y;
      v1.z = z1-z2;
      float d = theta;
      d = d + 2*3.1415926f/precision;
      v2.x = X - r1*cos(d);
      v2.y = Y - r1*sin(d);
      v2.z = z1-z1;
      res = CalcNormal(v1,v2);
      glNormal3d(res.x,res.y,res.z);
		if (i % 2 == 0){
			glTexCoord2f(1,0);
		}
		else {
			glTexCoord2f(1,1);
		}
      glVertex3f(X,Y,z1);
		if (i%2 == 0){
			glTexCoord2f(0,0);
		}
		else {
			glTexCoord2f(1,0);
		}
      glVertex3f(x,y,z2);
      theta = theta + 2*3.1415926f/precision;
      X = r1*cos(theta);
      Y = r1*sin(theta);
      x = r2*cos(theta);
      y = r2*sin(theta);
      if (i % 2 == 0){
		glTexCoord2f(1,1);
	  }
	  else{
		glTexCoord2f(1,0);
	  }
      glVertex3f(x,y,z2);
      if (i % 2 == 0){
		glTexCoord2f(1,0);
	  }
	  else{
		glTexCoord2f(0,0);
	  }
      
      glVertex3f(X,Y,z1);
    glEnd();
  }
  glDisable(GL_TEXTURE_2D);
}

void transformer::DrawTail(float s1, float s2, float s3, float delta) {
	glColor4f(1,1,1,1);
  glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,texture[1]);
  glBegin(GL_QUAD_STRIP);
	  vertex_vec v1,v2,res;
    v1.x = 0.0;
    v1.y = s1;
    v1.z = 0.0;
    v2.x = -s1;
    v2.y = 0.0;
    v2.z = 0.0;
    res = CalcNormal(v1,v2);
    glNormal3d(res.x,res.y,res.z);
    glTexCoord2f(0,1);
    glVertex3f(0.0,s1,0.0);
    glTexCoord2f(0,0);
    glVertex3f(0.0,0.0,0.0);
    glTexCoord2f(1,1);
    glVertex3f(s1,s1,0.0);
    glTexCoord2f(1,0);
    glVertex3f(s1,0.0,0.0);
    glTexCoord2f(0,1);
    glVertex3f(s1,s1,-s1);
    glTexCoord2f(0,0);
    glVertex3f(s1,0.0,-s1);
    glTexCoord2f(1,1);
    glVertex3f(0.0,s1,-s1);
    glTexCoord2f(1,0);
    glVertex3f(0.0,0.0,-s1);
    glTexCoord2f(0,1);
    glVertex3f(0.0,s1,0.0);
    glTexCoord2f(0,0);
    glVertex3f(0.0,0.0,0.0);
  glEnd();
  glBindTexture(GL_TEXTURE_2D,texture[0]);
  glBegin(GL_TRIANGLES);
    v1.x = 0.0;
    v1.y = -s2;
    v1.z = 0.0;
    v2.x = s2;
    v2.y = -s2/2;
    v2.z = 0.0;
    res = CalcNormal(v1,v2);
    glNormal3d(res.x,res.y,res.z);
    glTexCoord2f(1,0);
    glVertex3f(0.0,0.0,0.0);
    glTexCoord2f(1,1);
    glVertex3f(0.0,s2,0.0);
    glTexCoord2f(0,1);
    glVertex3f(-s2,s2/2,0.0);
  glEnd();
  glBindTexture(GL_TEXTURE_2D,texture[0]);
  glBegin(GL_TRIANGLES);
    v1.x = 0.0;
    v1.y = delta;
    v1.z = s3;
    v2.x = 0.0;
    v2.y = -delta;
    v2.z = s3;
    res = CalcNormal(v1,v2);
    glNormal3d(res.x,res.y,res.z);
    glTexCoord2f(0,0);
    glVertex3f(-s2,s2/2,0.0);
    glTexCoord2f(1,0);
    glVertex3f(-s2,(s2/2)-delta,-s3);
    glTexCoord2f(1,1);
    glVertex3f(-s2,(s2/2)+delta,-s3);    
  glEnd();
  glBegin(GL_TRIANGLES);
    v1.x = 0.0;
    v1.y = delta;
    v1.z = -s3;
    v2.x = 0.0;
    v2.y = -delta;
    v2.z = -s3;
    res = CalcNormal(v1,v2);
    glNormal3d(res.x,res.y,res.z);
    glTexCoord2f(1,1);
    glVertex3f(-s2,s2/2,0.0);
    glTexCoord2f(0,1);
    glVertex3f(-s2,(s2/2)-delta,s3);
    glTexCoord2f(0,0);
    glVertex3f(-s2,(s2/2)+delta,s3);    
  glEnd();
  glDisable(GL_TEXTURE_2D);
}

void transformer::DrawCube(float s){
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture[0]);   // choose the texture to use.
  glColor4f(0.8,0.8,1.0,1.0);
  glBegin(GL_QUAD_STRIP);
    vertex_vec v1,v2,res;
    v1.x = 0.0;
    v1.y = s;
    v1.z = 0.0;
    v2.x = -s;
    v2.y = 0.0;
    v2.z = 0.0;
    res = CalcNormal(v1,v2);
    glNormal3d(res.x,res.y,res.z);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0.0,s,0.0);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0.0,0.0,0.0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(s,s,0.0);
	glTexCoord2f(1.0f, 0.0f);
    glVertex3f(s,0.0,0.0);
	
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(s,s,-s);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(s,0.0,-s);
    
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0.0,s,-s);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.0,0.0,-s);
    
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0.0,s,0.0);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0.0,0.0,0.0);
  glEnd();
  
  glBindTexture(GL_TEXTURE_2D, texture[1]);   // choose the texture to use.
  glBegin(GL_QUAD_STRIP);
    v1.x = -s;
    v1.y = 0.0;
    v1.z = 0.0;
    v2.x = 0.0;
    v2.y = 0.0;
    v2.z = s;
    res = CalcNormal(v1,v2);
    glNormal3d(res.x,res.y,res.z);
    glTexCoord2f(0,1);
    glVertex3f(0.0,s,0.0);
    glTexCoord2f(1,1);
    glVertex3f(s,s,0.0);
    glTexCoord2f(0,0);
    glVertex3f(0,s,-s);
	glTexCoord2f(1,0);
    glVertex3f(s,s,-s);
  glEnd();

  glBindTexture(GL_TEXTURE_2D, texture[1]);   // choose the texture to use.
  glBegin(GL_QUAD_STRIP);
    v1.x = -s;
    v1.y = 0.0;
    v1.z = 0.0;
    v2.x = 0.0;
    v2.y = 0.0;
    v2.z = s;
    res = CalcNormal(v1,v2);
    glNormal3d(res.x,res.y,res.z);
    glTexCoord2f(0,1);
    glVertex3f(0.0,0.0,0.0);
    glTexCoord2f(1,1);
    glVertex3f(s,0.0,0.0);
    glTexCoord2f(0,0);
    glVertex3f(0.0,0.0,-s);
    glTexCoord2f(1,0);
    glVertex3f(s,0.0,-s);
  glEnd();
  glDisable(GL_TEXTURE_2D);
  
}




void transformer::DrawBomb(void){
  float s = 0.5;
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture[9]);   // choose the texture to use.
  glColor4f(0.8,0.8,1.0,1.0);
  glBegin(GL_QUAD_STRIP);
    vertex_vec v1,v2,res;
    v1.x = 0.0;
    v1.y = s;
    v1.z = 0.0;
    v2.x = -s;
    v2.y = 0.0;
    v2.z = 0.0;
    res = CalcNormal(v1,v2);
    glNormal3d(res.x,res.y,res.z);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0.0,s,0.0);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0.0,0.0,0.0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(s,s,0.0);
  glTexCoord2f(1.0f, 0.0f);
    glVertex3f(s,0.0,0.0);
  
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(s,s,-s);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(s,0.0,-s);
    
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0.0,s,-s);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.0,0.0,-s);
    
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0.0,s,0.0);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0.0,0.0,0.0);
  glEnd();

  glBegin(GL_QUAD_STRIP);
    v1.x = -s;
    v1.y = 0.0;
    v1.z = 0.0;
    v2.x = 0.0;
    v2.y = 0.0;
    v2.z = s;
    res = CalcNormal(v1,v2);
    glNormal3d(res.x,res.y,res.z);
    glTexCoord2f(0,1);
    glVertex3f(0.0,s,0.0);
    glTexCoord2f(1,1);
    glVertex3f(s,s,0.0);
    glTexCoord2f(0,0);
    glVertex3f(0,s,-s);
  glTexCoord2f(1,0);
    glVertex3f(s,s,-s);
  glEnd();

  glBegin(GL_QUAD_STRIP);
    v1.x = -s;
    v1.y = 0.0;
    v1.z = 0.0;
    v2.x = 0.0;
    v2.y = 0.0;
    v2.z = s;
    res = CalcNormal(v1,v2);
    glNormal3d(res.x,res.y,res.z);
    glTexCoord2f(0,1);
    glVertex3f(0.0,0.0,0.0);
    glTexCoord2f(1,1);
    glVertex3f(s,0.0,0.0);
    glTexCoord2f(0,0);
    glVertex3f(0.0,0.0,-s);
    glTexCoord2f(1,0);
    glVertex3f(s,0.0,-s);
  glEnd();
  glDisable(GL_TEXTURE_2D);
  
}


void transformer::DrawHead(float s){
  //glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture[2]);   // choose the texture to use.
  //glColor4f(1,1,1,1.0);
  glBegin(GL_QUAD_STRIP);
    vertex_vec v1,v2,res;
    v1.x = 0.0;
    v1.y = s;
    v1.z = 0.0;
    v2.x = -s;
    v2.y = 0.0;
    v2.z = 0.0;
    res = CalcNormal(v1,v2);
    glNormal3d(res.x,res.y,res.z);
    //glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0.0,s,0.0);
    //glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0.0,0.0,0.0);
    //glTexCoord2f(1.0f, 1.0f);
    glVertex3f(s,s,0.0);
    //glTexCoord2f(1.0f, 0.0f);
    glVertex3f(s,0.0,0.0);
     

  
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(s,s,-s);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(s,0.0,-s);
    
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0.0,s,-s);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.0,0.0,-s);
    
    //glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0.0,s,0.0);
    //glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0.0,0.0,0.0);
  glEnd();

  glBindTexture(GL_TEXTURE_2D, texture[2]);   // choose the texture to use.
  glBegin(GL_QUAD_STRIP);
    v1.x = -s;
    v1.y = 0.0;
    v1.z = 0.0;
    v2.x = 0.0;
    v2.y = 0.0;
    v2.z = s;
    res = CalcNormal(v1,v2);
    glNormal3d(res.x,res.y,res.z);
    glTexCoord2f(0,1);
    glVertex3f(0.0,s,0.0);
    glTexCoord2f(1,1);
    glVertex3f(s,s,0.0);
    glTexCoord2f(0,0);
    glVertex3f(0,s,-s);
  glTexCoord2f(1,0);
    glVertex3f(s,s,-s);
  glEnd();

  glBegin(GL_QUAD_STRIP);
    v1.x = -s;
    v1.y = 0.0;
    v1.z = 0.0;
    v2.x = 0.0;
    v2.y = 0.0;
    v2.z = s;
    res = CalcNormal(v1,v2);
    glNormal3d(res.x,res.y,res.z);
    glTexCoord2f(0,1);
    glVertex3f(0.0,0.0,0.0);
    glTexCoord2f(1,1);
    glVertex3f(s,0.0,0.0);
    glTexCoord2f(0,0);
    glVertex3f(0.0,0.0,-s);
    glTexCoord2f(1,0);
    glVertex3f(s,0.0,-s);
  glEnd();
  glDisable(GL_TEXTURE_2D);
  
}



void transformer::DrawTrapezoid(float l1, float l2, float h){
	glColor4f(1,1,1,1);
  glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,texture[1]);
	glBegin(GL_QUAD_STRIP);
    vertex_vec v1,v2,res;
    v1.x = (l2-l1)/2;
    v1.y = h;
    v1.z = 0.0;
    v2.x = -l1;
    v2.y = 0.0;
    v2.z = 0.0;
    res = CalcNormal(v1,v2);
    glNormal3d(res.x,res.y,res.z);
		glTexCoord2f(1,0);
		glVertex3f(0.0,0.0,0.0);
		glTexCoord2f(0,0);
		glVertex3f((l1-l2)/2,-h,0.0);
		glTexCoord2f(1,1);
		glVertex3f(l1,0.0,0.0);
		glTexCoord2f(1,0);
		glVertex3f((l1 - (l1-l2)/2), -h ,0.0 );
		glTexCoord2f(0,1);
		glVertex3f(l1,0.0,l1);
		glTexCoord2f(0,0);
		glVertex3f((l1 - (l1-l2)/2), -h , l1);
		glTexCoord2f(1,1);
		glVertex3f(0.0,0.0,l1);
		glTexCoord2f(1,0);
		glVertex3f((l1-l2)/2,-h,l1);
		glTexCoord2f(0,1);
		glVertex3f(0.0,0.0,0.0);
		glTexCoord2f(0,0);
		glVertex3f((l1-l2)/2,-h,0.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    v1.x = -l1;
    v1.y = 0.0;
    v1.z = 0.0;
    v2.x = -l1;
    v2.y = 0.0;
    v2.z = -l1;
    res = CalcNormal(v1,v2);
    glNormal3d(res.x,res.y,res.z);
    glTexCoord2f(0,0);
		glVertex3f(0.0,0.0,0.0);
		glTexCoord2f(0,1);
		glVertex3f(l1,0.0,0.0);
		glTexCoord2f(1,1);
		glVertex3f(l1,0.0,l1);
		glTexCoord2f(1,0);
		glVertex3f(0.0,0.0,l1);		
	glEnd();
	
	glBegin(GL_POLYGON);
    v1.x = -l2;
    v1.y = 0.0;
    v1.z = 0.0;
    v2.x = -l2;
    v2.y = 0.0;
    v2.z = -l1;
    res = CalcNormal(v1,v2);
    glNormal3d(res.x,res.y,res.z);
		glTexCoord2f(0,0);
		glVertex3f((l1-l2)/2,-h,0.0);
		glTexCoord2f(0,1);
		glVertex3f((l1 - (l1-l2)/2), -h ,0.0 );
		glTexCoord2f(1,1);
		glVertex3f((l1 - (l1-l2)/2), -h , l1);
		glTexCoord2f(1,0);
		glVertex3f((l1-l2)/2,-h,l1);
	glEnd();
	glDisable(GL_TEXTURE_2D);

}

void transformer::struct_tyre(void){
	glColor4f(0,0,0,1);
	glNewList(tyre,GL_COMPILE);
		glCallList(connectors);
		glTranslatef(-(conn_y)/4,-0.13,(conn_y)/4);
		glScalef(0.3,1,0.3);
		glCallList(legs);
		glScalef(10/3,1,10/3);
		glTranslatef(0.0,-0.05,-0.015);
		glRotatef(90,0.0,1.0,0.0);
		DrawTyre(0.05,0.03,0.0);
	glEndList();
}

void transformer::struct_torso(void)
{
  glNewList(torso,GL_COMPILE); 

	// torso
	DrawSphere(0.3,0);
   
  glEndList();
}


void transformer::struct_connectors(void)
{
	glNewList(connectors,GL_COMPILE); 

	// connectors
	DrawSphere(0.03,1);
   
  glEndList();
}

void transformer::struct_head(void)
{
  glNewList(head,GL_COMPILE); 
	// head
	DrawHead(0.1);   
  glEndList();
}


void transformer::struct_legs(void)
{
  glNewList(legs,GL_COMPILE); 
  // legs
  DrawCube(0.1);   
  glEndList();
}

void transformer::struct_bomb(void)
{
  glNewList(bomb,GL_COMPILE);
    DrawBomb();
  glEndList();
}
void transformer::struct_blade(void)
{
  glNewList(blade,GL_COMPILE);
	
	glTranslatef(0.0,-(0.01)/2,(torso_z)/2);
	glScalef(0.5,0.1,1.8);
	glTranslatef(-0.05,0.0,0.0);
	DrawCube(0.1);   
  glEndList();
}

void transformer::struct_right_upper_leg(void)
{
  glNewList(ru_leg,GL_COMPILE); 
	// head
	DrawTrapezoid(0.1,0.05,0.1);   
  glEndList();
}

void transformer::struct_tail_fan(void)
{
  glNewList(tail,GL_COMPILE); 
	DrawTail(0.07,0.05,0.5,0.02);   
  glEndList();
}

void transformer::struct_right_lower_leg(void)
{
  glNewList(rl_leg,GL_COMPILE); 
	// head
	DrawCube(0.1);   
  glEndList();
}

void transformer::struct_right_upper_hand(void)
{
  glNewList(ru_hand,GL_COMPILE); 
	// head
	DrawCube(0.1);   
  glEndList();
}

void transformer::struct_right_lower_hand(void)
{
  glNewList(rl_hand,GL_COMPILE); 
	// head
  glColor4f(32,32,32,0);
	DrawCube(0.1);
  glEndList();
}

void transformer::struct_joint(void)
{
  glNewList(joint,GL_COMPILE); 
	glColor4f(1,1,1,1.0);
	DrawJoint(0.3,0.0);   
  glEndList();
}

void savePPM(int start_x,int start_y,int w,int h,const char *fname)
{
        FILE *f=fopen(fname,"wb");
        if (!f) return;
        std::vector<unsigned char> out(3*w*h);
        glPixelStorei(GL_PACK_ALIGNMENT,1); /* byte aligned output */
        glReadPixels(start_x,start_y,w,h, GL_RGB,GL_UNSIGNED_BYTE,&out[0]);
        fprintf(f,"P6\n%d %d\n255\n",w,h);
        for (int y=0;y<h;y++) { /* flip image bottom-to-top on output */
                fwrite(&out[3*(h-1-y)*w],1,3*w,f);
        }
        fclose(f);
}

int fmcount = 1;
void transformer::renderGL(void)
{
  //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
 rotate_ball = rotate_ball - 10;  
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 if(playback) {
  double end_time = glfwGetTime();
  while(glfwGetTime() <= end_time + (float)INTERVAL/(float)FPS) {
  }
  //float elapse = end_time - start_time;
  //float factor = INTERVAL/FPS;
  record r;    
  std::vector<float> i_params = r.parse_file_and_interpolate(end_time - start_time);
  r.set_intermediate_params(i_params, end_time - start_time);  
  
  DrawTransformer();
  std::string name = "frame";
  std::stringstream ss2;
  ss2 << fmcount;
  std::string str2 = ss2.str();
  name += str2;
  name += ".ppm";
  savePPM(0,0,800,800,name.c_str());
  fmcount++; 
 }
 else { 
  DrawTransformer();
 }
}

void transformer::DrawTransformer(){
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
	//glScalef(0.2,0.2,0.2);
	//glTranslatef(0,3.5,-3);
  //transformer
  //glRotatef(rotate_angle,0.0,1.0,0.0);
  
  myback.setCamera(camera_number%TOTAL_CAMERA);
 
  glRotatef(rotate_x,1.0,0.0,0.0);
	if (camera_number%TOTAL_CAMERA == 2){
		glRotatef(-tilt_down,1.0,0.0,0.0);
    glRotatef(-tilt_left,0.0,1.0,0.0);

	}
	if (camera_number%TOTAL_CAMERA !=0){

		if (movement_flag == 1){
			glTranslatef(-(pre_move_x+ 0.5*sin(tilt_left*PI/180)),-(pre_move_y + 0.5*cos(tilt_left*PI/180)*cos(tilt_down*PI/180)),-(pre_move_z+ 0.5*sin(tilt_down*PI/180)));
		}
		else if (movement_flag == 2){
			glTranslatef(-(pre_move_x -  0.5*sin(tilt_left*PI/180)),-(pre_move_y - 0.5*cos(tilt_left*PI/180)*cos(tilt_down*PI/180)),-(pre_move_z- 0.5*sin(tilt_down*PI/180)));
		}
		else{
			glTranslatef(-pre_move_x,-pre_move_y,-pre_move_z);
		}

	}

    //cout<<pre_move_x<<" "<<pre_move_y<<" "<<pre_move_z<<endl;
	
		glPushMatrix();
			glRotatef(-rotate_x,1.0,0.0,0.0);
			myback.createScene();
	glPopMatrix();

   /*================torso=================*/
    glPushMatrix();   
    //glTranslatef(0,-2,0);
		if (movement_flag == 1){
			glTranslatef(pre_move_x+ 0.5*sin(tilt_left*PI/180), pre_move_y + 0.5*cos(tilt_left*PI/180)*cos(tilt_down*PI/180),pre_move_z+ 0.5*sin(tilt_down*PI/180));
			pre_move_x = pre_move_x+ 0.5*sin(tilt_left*PI/180);
			pre_move_y = pre_move_y + 0.5*cos(tilt_left*PI/180)*cos(tilt_down*PI/180);
			pre_move_z = pre_move_z+ 0.5*sin(tilt_down*PI/180);
      //pre_move_z = pre_move_z + 0.05*cos(tilt_down*PI/180);
			//std::cout<<pre_move_x<<" "<<pre_move_y<<std::endl;
			movement_flag =0;
			
		}
		else if (movement_flag == 2){
			glTranslatef(pre_move_x -  0.5*sin(tilt_left*PI/180), pre_move_y - 0.5*cos(tilt_left*PI/180)*cos(tilt_down*PI/180),pre_move_z- 0.5*sin(tilt_down*PI/180));
			pre_move_x = pre_move_x - 0.5*sin(tilt_left*PI/180);
			pre_move_y = pre_move_y - 0.5*cos(tilt_left*PI/180)*cos(tilt_down*PI/180);
			pre_move_z = pre_move_z -  0.5*sin(tilt_down*PI/180);
			//pre_move_z = pre_move_z - 0.05*cos(tilt_down*PI/180);
      movement_flag =0;
		}
		else {
			glTranslatef(pre_move_x,pre_move_y,pre_move_z);
		}
	  
      //glTranslatef(move_back,0.0,0.0);
      glTranslatef(0,0,torso_move_z);
      glRotatef(tilt_left,0.0,1.0,0.0);
      glRotatef(tilt_down,1.0,0.0,0.0);
      glScalef(0.5,1.0,0.5);					//scaling the sphere to make an oval
	    glCallList(torso);
      glScalef(2.0,1.0,2.0);					// scaling back to normal coordinates
      glPushMatrix();
        glPushMatrix();
          glScalef(0.1,0.1,3);
          glCallList(legs);
        glPopMatrix();
        glTranslatef(-0.05,-0.05,-0.3);
          glScalef(0.3,0.3,0.3);
        glCallList(bomb);
      glPopMatrix();
        GLfloat  lightPos[] = { 0.0f, 0.0f, 0.2f, 1.0f };
        GLfloat  specular[] = { 1.0f, 1.0f, 1.0f, 1.0f};
        GLfloat  specref[] =  { 1.0f, 1.0f, 1.0f, 1.0f };
        GLfloat  ambientLight[] = { 0.5f, 0.5f, 0.5f, 1.0f};
        GLfloat  spotDir[] = { 0.0f, 0.0f, -1.0f };
  
        // Set up and enable light 0
        // Supply a slight ambient light so the objects can be seen
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
  
        glLightfv(GL_LIGHT0,GL_DIFFUSE,ambientLight);
        glLightfv(GL_LIGHT0,GL_SPECULAR,specular);
      glPushMatrix();
        glTranslatef(pre_move_x,pre_move_y,0.0);
        glRotatef(tilt_left,0.0,1.0,0.0);
        glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
        
        // Specific spot effects
        // Cut off angle is 30 degrees
        float fov = 30.0 + pre_move_x*10;
        glLightf(GL_LIGHT0,GL_SPOT_CUTOFF,fov);
  
        // Fairly shiny spot
        glLightf(GL_LIGHT0,GL_SPOT_EXPONENT,100.0f);
      glPopMatrix();
    /*===================Front tyre====================*/
	
			glPushMatrix();
				glTranslatef(0.0,0.0,-0.05);
				glRotatef(rotate_tyre,1.0,0.0,0.0);
				glRotatef(orient_tyre,0.0,1.0,0.0);
				glRotatef(90,0.0,1.0,0.0);
				glCallList(tyre);
			glPopMatrix();
      
      /*================blades===============*/
      glPushMatrix();
        glRotatef(rotate_ball,0.0,0.0,1.0);
				glTranslatef(0.0,0.0,translate_blades);
				glPushMatrix();
			    glTranslatef(0.0,0.0,-(conn_z)/2);
			    glCallList(connectors);
		    glPopMatrix();
				glPushMatrix();		
					glPushMatrix();
				    glTranslatef(0.0,0.0,-(conn_z)/2);
				    glRotatef(rotate_blades, 1.0, 0.0 , 0.0);
				    glTranslatef(0.0,0.0,(conn_z)/2);
						glPushMatrix();
					    glTranslatef(0.0,0.0,-(conn_z)/2);
					    glRotatef(-rotate_split,0.0,1.0,0.0);
					    glTranslatef(0.0,0.0,(conn_z)/2);
					    glCallList(blade);
				    glPopMatrix();
						glPushMatrix();
					    glTranslatef(0.0,0.01,0.0);
					    glTranslatef(0.0,0.0,-(conn_z)/2);
					    glRotatef(-2*rotate_split,0.0,1.0,0.0);
					    glTranslatef(0.0,0.0,(conn_z)/2);
					    glCallList(blade);
				    glPopMatrix();
          glPopMatrix();
					glPushMatrix();
				    glTranslatef(0.0,0.0,-(conn_z)/2);
				    glRotatef(-rotate_blades, 1.0, 0.0 , 0.0);
				    glTranslatef(0.0,0.0,(conn_z)/2);
		  			glPushMatrix();
			  		  glTranslatef(0.0,0.0,-(conn_z)/2);
					    glRotatef(rotate_split,0.0,1.0,0.0);
					    glTranslatef(0.0,0.0,(conn_z)/2);
					    glCallList(blade);
				    glPopMatrix();
  				  glPushMatrix();
					    glTranslatef(0.0,-0.01,0.0);
					    glTranslatef(0.0,0.0,-(conn_z)/2);
					    glRotatef(2*rotate_split,0.0,1.0,0.0);
					    glTranslatef(0.0,0.0,(conn_z)/2);
					    glCallList(blade);
				    glPopMatrix();
			    glPopMatrix();
	      glPopMatrix();
      glPopMatrix();
      
      /*================head=================*/
	    glPushMatrix();
			  glTranslatef(0.0,0.0,t_head_z);
		    glTranslatef(0.0,(torso_y/2 + conn_y/2),-(conn_z/2));			//translating the centre of the connector
		    glTranslatef(0.0,0.0,t_head_z);
		    glTranslatef(0.0,t_head_y,0.0);
        glRotatef(rotate_head, 1.0, 0.0, 0.0);
		 		glCallList(connectors);
		    glTranslatef(-(head_x/2),(conn_y/2),(head_z/2));			// translating the head so that its centre lies on top of connector
		    glCallList(head);
      glPopMatrix();
	  
      /*================supporting rectangle=================*/
			glPushMatrix();
				glPushMatrix();
				  glTranslatef(torso_x/2,0.0,0.0);
				  glRotatef(rotate_sides,0.0,0.0,1.0);
				  glTranslatef(-torso_x/2,0.0,0.0);
				  glScalef(0.5,1.0,0.5);						// scaling the supporting rectangle to fit the torso
					glCallList(joint);
			  glPopMatrix();
				glScalef(0.5,1.0,0.5);	
		    glRotatef(180,1.0,0.0,0.0);
		    glCallList(joint);
		    glRotatef(180,0.0,1.0,0.0);
		    glCallList(joint);
				glRotatef(180,1.0,0.0,0.0);
				glPushMatrix();
				  glScalef(2,1,2);
				  glTranslatef(torso_x/2,0.0,0.0);
				  glRotatef(rotate_sides,0.0,0.0,1.0);
				  glTranslatef(-torso_x/2,0.0,0.0);
				  glScalef(0.5,1,0.5);
				  glCallList(joint);
		    glPopMatrix();
			glPopMatrix();
	  
      /*================Right Upper Leg=================*/
			glPushMatrix();
			  glTranslatef(0.0,0.03,0.0);										
		    glTranslatef(torso_x/4, -(torso_y/2 + conn_y/2), -(conn_z/2)); 
		    glTranslatef(ur_x, 0.0, 0.0);
        glRotatef(rotate_ur_angle,0.0,0.0,1.0);
        glRotatef(rotate_ur_x,1.0,0.0,0.0);
        glRotatef(rotate_ur_angle_y,0.0,1.0,0.0);
    		glCallList(connectors);
    		glPushMatrix();		//origin is at the centre of the connector
		      glTranslatef(-(upper_leg_w1/2),-(conn_y/2),-(conn_z/2));		
		      glScalef(1.5,2.5,0.6);						
			    glCallList(ru_leg);
		    glPopMatrix();					
	      /*===================Side tyres====================*/
				glPushMatrix();
				  glTranslatef(upper_leg_w1/2+0.03/2+0.01,-2*(0.03),0.0);
				  glRotatef(rotate_tyre,1.0,0.0,0.0);
				  glCallList(tyre);
			  glPopMatrix();
	      /*================Right Lower Leg=================*/
	      glPushMatrix();				// origin at the centre of the connector
			    glTranslatef(0.0 , -(conn_y/2 + upper_leg_y + conn_y/2), 0.0);
			    glRotatef(rotate_lr_angle , 0.0 , 0.0 , 1.0);
			    glCallList(connectors);		//origin at the centre of the bottom connetor
    			glPushMatrix();
			      glTranslatef(-(lower_leg_x/2),-(conn_y/2 + lower_leg_y),(conn_z/2));
			      glScalef(0.75,1.5,0.6);
            glCallList(rl_leg);
          glPopMatrix();				
        glPopMatrix();				
      glPopMatrix();				
      
      /*================Left Upper Leg=================*/
			glPushMatrix();
			  glTranslatef(0.0,0.03,0.0);											
		    glTranslatef(-(torso_x/4), -(torso_y/2 + conn_y/2), -(conn_z/2)); 
		    glTranslatef(ul_x, 0.0, 0.0);
        glRotatef(rotate_ul_angle,0.0,0.0,1.0);
        glRotatef(rotate_ul_x,1.0,0.0,0.0);
        glRotatef(rotate_ul_angle_y,0.0,1.0,0.0);
	    	glCallList(connectors);
		    glPushMatrix();		//origin is at the centre of the connector
		      glTranslatef(-(upper_leg_w1/2),-(conn_y/2),-(conn_z/2));		//translating to the top left corner of the leg
		      glScalef(1.5,2.5,0.6);						//scaling the trapezium accordingly
		      glCallList(ru_leg);
		      glTranslatef(upper_leg_w1/6,-6*(conn_y/2),1.6*conn_z);
          glScalef(0.75,0.8,0.2);
          glCallList(tail);
		    glPopMatrix();					
		    /*===================Side tyres====================*/
				glPushMatrix();
					glTranslatef(-(upper_leg_w1/2+upper_leg_w1/10+0.01),-2*(upper_leg_w1/5),0.0);
				  glRotatef(rotate_tyre,1.0,0.0,0.0);
				  glCallList(tyre);
			  glPopMatrix();
	      /*================Left Lower Leg=================*/
	      glPushMatrix();				// origin at the centre of the connector
			    glTranslatef(0.0 , -(conn_y/2 + upper_leg_y + conn_y/2), 0.0);
			    glRotatef(rotate_ll_angle , 0.0 , 0.0 , 1.0);
    			glCallList(connectors);		//origin at the centre of the bottom connetor
    			glPushMatrix();
				    glTranslatef(-(lower_leg_x/2),-(conn_y/2 + lower_leg_y),(conn_z/2));
			      glScalef(0.75,1.5,0.6);
            glCallList(rl_leg);
          glPopMatrix();				
        glPopMatrix();				
      glPopMatrix();				
    
	    /*================Right Upper Hand=================*/
      glPushMatrix();
			  glTranslatef((torso_x/2 + conn_x/2) , (torso_y/2 - upper_hand_y/2) , -(conn_z/2));	
	      glTranslatef(0.0,rhand_y,0.0);
        glRotatef(rotate_ur_hand_x,1.0,0.0,0.0);
        glRotatef(rotate_ur_hand,0.0,0.0,1.0);
	      glCallList(connectors);
		    glPushMatrix();			// origin shifted to BOTTOM LEFT corner of the upper hand
          glTranslatef((conn_x/2),-(upper_hand_y/2),(conn_z/2));
			    glScalef(2,0.6,0.6);	
				  glCallList(ru_hand);
			  glPopMatrix();				
        /*================Right Lower Hand=================*/
        glPushMatrix();
		      glColor4f(32,32,32,1);
          glTranslatef((conn_x/2 + upper_hand_x + conn_x/2) ,0.0, 0.0);
          glRotatef(rotate_lr_hand,0.0,0.0,1.0);
    	    glCallList(connectors);
          glPushMatrix();					// need to shift origin to the BOTTOM LEFT corner of the lower hand
            glTranslatef((conn_x/2) ,-(lower_hand_y/2), (conn_z/2));
		        glScalef(2.0,0.6,0.6);
		        //rl_hand part-1
            glPushMatrix();
              glScalef(1.0,0.33,1.0);
              glTranslatef(0.0,gun_rotate,0.0);
		          glCallList(rl_hand);
            glPopMatrix();
            //rl_hand part-2
            glPushMatrix();
              glScalef(1.0,0.33,1.0);
		          glTranslatef(0.0,0.1,0.0);
              glCallList(legs);
            glPopMatrix();
            //rl_hand part-3
            glPushMatrix();
              glScalef(1.0,0.33,1.0);
              glTranslatef(0.0,0.2,0.0);
              glTranslatef(0.0,-gun_rotate,0.0);
		          glCallList(rl_hand);
            glPopMatrix();
    	    glPopMatrix();	
	  	  glPopMatrix();		
      glPopMatrix();			

		  /*================Left Upper Hand=================*/
			glPushMatrix();
			  glTranslatef(-(torso_x/2 + conn_x/2) , (torso_y/2 - upper_hand_y/2) , -(conn_z/2));	
	      glTranslatef(0.0,lhand_y,0.0);
        glRotatef(rotate_ul_hand_x,1.0,0.0,0.0);
        glRotatef(rotate_ul_hand,0.0,0.0,1.0);
	      glCallList(connectors);
		    glPushMatrix();			// origin shifted to BOTTOM LEFT corner of the upper hand
			    glTranslatef(-(conn_x/2+ upper_hand_x),-(upper_hand_y/2),(conn_z/2));
			    glScalef(2,0.6,0.6);	
			    glCallList(ru_hand);
			  glPopMatrix();				
		    /*================Left Lower Hand=================*/
        glPushMatrix();
		      glTranslatef(-(conn_x/2 + upper_hand_x + conn_x/2) ,0.0, 0.0);
          glRotatef(rotate_ll_hand,0.0,0.0,1.0);
	        glCallList(connectors);
          glPushMatrix();					   
            glTranslatef(-(conn_x/2+ lower_hand_x) ,-(lower_hand_y/2), (conn_z/2));
		        glScalef(2.0,0.6,0.6);
            //ll_hand part-1
            glPushMatrix();
              glScalef(1.0,0.33,1.0);
              glTranslatef(0.0,gun_rotate,0.0);
		          glCallList(rl_hand);
            glPopMatrix();
            //ll_hand part-2
            glPushMatrix();
              glScalef(1.0,0.33,1.0);
		          glTranslatef(0.0,0.1,0.0);
              glCallList(rl_hand);
            glPopMatrix();
            //ll_hand part-3
            glPushMatrix();
              glScalef(1.0,0.33,1.0);
              glTranslatef(0.0,0.2,0.0);
              glTranslatef(0.0,-gun_rotate,0.0);
		          glCallList(rl_hand);
            glPopMatrix();
	        glPopMatrix();	
	  	  glPopMatrix();		
	    glPopMatrix();			// coordinate back to the origin
    glPopMatrix();			// final matrix of torso popped
  glPopMatrix();
}



