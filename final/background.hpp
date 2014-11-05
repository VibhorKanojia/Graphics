#ifndef _BACKGROUND_HPP_
#define _BACKGROUND_HPP_
#include <vector>
using namespace std;
#define grnd 1000
#define blding1 1001
#define blding2 1002
#define rd 1003

class background {
public:
	GLuint texture[20];
	vector<float> heights;
	vector<int> building;
	background();
	void load_textures();
	void draw_road();
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
