#include "record_frames.hpp"


void record::update_params() {
  param_values.push_back(rotate_angle);    
  param_values.push_back(rotate_x);    
  param_values.push_back(rotate_head);    
  param_values.push_back(rotate_ul_angle);    
  param_values.push_back(rotate_ur_angle);    
  param_values.push_back(rotate_ur_angle_y);    
  param_values.push_back(rotate_ll_angle);    
  param_values.push_back(rotate_lr_angle);    
  param_values.push_back(rotate_ul_angle_y);    
  param_values.push_back(rotate_lr_hand);    
  param_values.push_back(rotate_ur_hand);    
  param_values.push_back(rotate_ul_hand);    
  param_values.push_back(rotate_ll_hand);    
  param_values.push_back(rotate_blades);    
  param_values.push_back(rotate_split);    
  param_values.push_back(rotate_sides);    
  param_values.push_back(rotate_tyre);    
  param_values.push_back(orient_tyre);    
  param_values.push_back(rotate_ul_x);    
  param_values.push_back(rotate_ur_x);    
  param_values.push_back(movement_flag);    
  param_values.push_back(rotate_ball);    
  param_values.push_back(camera_number);    
  param_values.push_back(ur_x);    
  param_values.push_back(ul_x);    
  param_values.push_back(rhand_y);    
  param_values.push_back(lhand_y);    
  param_values.push_back(translate_blades);    
  param_values.push_back(t_head_y);    
  param_values.push_back(gun_rotate);    
  param_values.push_back(t_head_z);    
  param_values.push_back(tilt_left);    
  param_values.push_back(tilt_down);        
  param_values.push_back(pre_move_x);        
  param_values.push_back(pre_move_y);        
  param_values.push_back(pre_move_z);        
}

void record::record_frame_params() {
  frames_file.open("keyframes.txt",std::fstream::in | std::fstream::out | std::fstream::app);
  for(int i=0; i < param_values.size(); i++) {
    frames_file << param_values[i];
    frames_file << ",";
  }
  frames_file << "\n";
  frames_file.close();
  param_values.clear();
}

/*int main() {
 record r; 
 rotate_angle = 5,rotate_x,rotate_head= 5;
 rotate_ul_angle= 5,rotate_ur_angle= 5, rotate_ur_angle_y= 5;
 rotate_ll_angle= 5,rotate_lr_angle= 5, rotate_ul_angle_y= 5;
 rotate_lr_hand= 5, rotate_ur_hand= 5; 
 rotate_ul_hand= 5, rotate_ll_hand= 5;
 rotate_blades= 5,rotate_split= 5, rotate_sides= 5;
 rotate_tyre= 5,orient_tyre= 5,rotate_ul_x= 5,rotate_ur_x= 5;
 ur_x= 5, ul_x= 5,rhand_y= 5,lhand_y= 5;
 translate_blades= 5,t_head_y= 5,gun_rotate= 5,t_head_z= 5;
 tilt_left= 5, tilt_down= 5;
 movement_flag= 5;
 rotate_ball= 5;
 pre_move_x= 5, pre_move_y= 5, pre_move_z= 5;
 camera_number= 5;
 r.update_params();
 r.record_frame_params();
 
 rotate_angle = 6,rotate_x,rotate_head= 6;
 rotate_ul_angle= 5,rotate_ur_angle= 5, rotate_ur_angle_y= 5;
 rotate_ll_angle= 5,rotate_lr_angle= 5, rotate_ul_angle_y= 5;
 rotate_lr_hand= 5, rotate_ur_hand= 5; 
 rotate_ul_hand= 5, rotate_ll_hand= 6;
 rotate_blades= 6,rotate_split= 5, rotate_sides= 5;
 rotate_tyre= 5,orient_tyre= 5,rotate_ul_x= 5,rotate_ur_x= 5;
 ur_x= 5, ul_x= 6,rhand_y= 5,lhand_y= 5;
 translate_blades= 6,t_head_y= 5,gun_rotate= 5,t_head_z= 5;
 tilt_left= 5, tilt_down= 6;
 movement_flag= 6;
 rotate_ball= 6;
 pre_move_x= 6, pre_move_y= 6, pre_move_z= 6;
 camera_number= 6;
 r.update_params();
 r.record_frame_params();
 return 0;
}*/
