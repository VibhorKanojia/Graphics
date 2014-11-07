#ifndef _BACKGROUND_HPP_
#define _BACKGROUND_HPP_
#include <vector>
using namespace std;
#define grnd 1000
#define blding1 1001
#define blding2 1002
#define rd 1003
#define mtrte 1004
#define before 1005
#define after 1006

extern int expl_flag;
extern float expl_scl;

class background {
public:
	GLuint texture[20];
	vector<float> heights;
	vector<int> building;
	background();
	void load_textures();
	void draw_road();
	void draw_front();
	void draw_front_after();
	/*
	void draw_meteorite(float r, int tesselation);
	void draw_segment(float R, float z1, float z2, int myprecision);
	void struct_meteorite();
	*/
	void struct_front();
	void struct_front_after();
	void struct_road();
	void draw_building(int text_num);
	void draw_ground();
	void createScene();
	void struct_ground();
	void struct_building(int text_num);
	void createRoom();
	void setCamera(int cam_pos);
};
#endif
