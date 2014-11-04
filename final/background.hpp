#ifndef _BACKGROUND_HPP_
#define _BACKGROUND_HPP_

#define grnd 1000
#define blding 1001

class background {
public:
	GLuint texture[20];
	void load_textures();
	void draw_building();
	void draw_ground();
	void createScene();
	void struct_ground();
	void struct_building();
	void createRoom();
	void setCamera(int cam_pos);
};
#endif
