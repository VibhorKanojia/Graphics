#ifndef RECORD_FRAMES_H
#define RECORD_FRAMES_H
#include <stdio.h>
#include <fstream>
#include <vector>

extern int rotate_angle,rotate_x,rotate_head;
extern int rotate_ul_angle,rotate_ur_angle, rotate_ur_angle_y;
extern int rotate_ll_angle,rotate_lr_angle, rotate_ul_angle_y;
extern int rotate_lr_hand, rotate_ur_hand; 
extern int rotate_ul_hand, rotate_ll_hand;
extern int rotate_blades,rotate_split, rotate_sides;
extern int rotate_tyre,orient_tyre,rotate_ul_x,rotate_ur_x;
extern float ur_x, ul_x,rhand_y,lhand_y;
extern float translate_blades,t_head_y,gun_rotate,t_head_z;
extern float tilt_left, tilt_down;
extern int movement_flag;
extern int rotate_ball;
extern float pre_move_x, pre_move_y, pre_move_z;
extern int camera_number;


class record {
  public:
    std::vector<float> param_values;
    std::fstream frames_file;
    void update_params();
    void record_frame_params();
};

#endif
