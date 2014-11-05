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

float record::interpolate_linear(float t, int t1, float val1, float val2) {
  //t2 is not required as (t2 - t1) is known
  float val_t;
  val_t = val1 + ((val2 - val1)/(float)TIME_INTERVAL)*(t - t1);
  return val_t;
}

std::vector<float> record::tokenize_line(std::string line) {
  std::vector<float> params;
  std::istringstream ss(line);
  std::string token;
  while(std::getline(ss, token, ',')) {
    //float val = std::atof(token.c_str());
    float val;
    sscanf(token.c_str(), "%f", &val);
    params.push_back(val);
  }
  return params; 
}

std::vector<float> record::parse_file_and_interpolate(float intermediate_time) {
  int base_time = intermediate_time/TIME_INTERVAL;
  //Now read (base_time + 1)th and (base_time + 2)th line from frames_file
  int cur_line_num = 1;
  frames_file.open("keyframes.txt",std::fstream::in);
  std::string line1, line2;
  int lines_read = 0;
  if(frames_file.is_open()) {
    while(cur_line_num != (int)(base_time + 1)) {
      getline(frames_file, line1);
      cur_line_num++;
    }
    getline(frames_file, line1);
    getline(frames_file, line2);
  }
  frames_file.close();
  std::vector<float> params_t1 = tokenize_line(line1);
  std::vector<float> params_t2 = tokenize_line(line2);
  std::vector<float> intermediate_params;
  for(int i=0; i < params_t2.size(); i++) {
    if(i >= 20 && i <= 23) {
      printf("%f, %f, %f, %f\n", params_t1[i], params_t2[i], intermediate_time, base_time);
    }
    float i_val = interpolate_linear(intermediate_time, base_time, params_t1[i], params_t2[i]);
    
    if(i >= 20 && i <= 23) {
      printf("%f\n", i_val);
    }
    intermediate_params.push_back(i_val);
  }
  return intermediate_params;  
}

void record::set_intermediate_params(std::vector<float> params, float i_time) {
  std::vector<float> i_params = parse_file_and_interpolate(i_time);
  int i = 0; 
  rotate_angle = (int)i_params[i];
  i++;    
  rotate_x = (int)i_params[i];     
  i++;    
  rotate_head = (int)i_params[i];     
  i++;    
  rotate_ul_angle = (int)i_params[i];    
  i++;    
  rotate_ur_angle = (int)i_params[i];     
  i++;    
  rotate_ur_angle_y = (int)i_params[i];     
  i++;    
  rotate_ll_angle = (int)i_params[i];     
  i++;    
  rotate_lr_angle = (int)i_params[i];     
  i++;    
  rotate_ul_angle_y = (int)i_params[i];     
  i++;    
  rotate_lr_hand = (int)i_params[i];     
  i++;    
  rotate_ur_hand = (int)i_params[i];     
  i++;    
  rotate_ul_hand = (int)i_params[i];     
  i++;    
  rotate_ll_hand = (int)i_params[i];     
  i++;    
  rotate_blades = (int)i_params[i];     
  i++;    
  rotate_split = (int)i_params[i];     
  i++;    
  rotate_sides = (int)i_params[i];     
  i++;    
  rotate_tyre = (int)i_params[i];     
  i++;    
  orient_tyre = (int)i_params[i];     
  i++;    
  rotate_ul_x = (int)i_params[i];     
  i++;    
  rotate_ur_x = (int)i_params[i];     
  i++;    
  movement_flag = (int)i_params[i];     
  i++;    
  rotate_ball = (int)i_params[i];     
  i++;    
  camera_number = (int)i_params[i];     
  i++;    
  ur_x = i_params[i];     
  i++;    
  ul_x = i_params[i];     
  i++;    
  rhand_y = i_params[i];     
  i++;    
  lhand_y = i_params[i];     
  i++;    
  translate_blades = i_params[i];     
  i++;    
  t_head_y = i_params[i];     
  i++;    
  gun_rotate = i_params[i];     
  i++;    
  t_head_z = i_params[i];     
  i++;    
  tilt_left = i_params[i];     
  i++;    
  tilt_down = i_params[i];         
  i++;    
  pre_move_x = i_params[i];        
  i++;    
  pre_move_y = i_params[i];         
  i++;    
  pre_move_z = i_params[i];          
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
 pre_move_x= 5, pre_move_y= t5, pre_move_z= 5;
 camera_number= 5;
 r.update_params();
 r.record_frame_params();
 
 rotate_angle = 6,rotate_x,rohtate_head= 6;
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
