#include "gl_framework.hpp"

int rotate_angle = 0;
int rotate_head = 0;
int rotate_ul_angle = 0;
int rotate_ul_angle_y = 0;
int rotate_ur_angle = 0;
int rotate_ur_angle_y = 0;
float ur_x = 0.0;
float ul_x = 0.0;
int rotate_ll_angle = 0;
int rotate_lr_angle = 0;
int rotate_x = 0;
int rotate_ur_hand = 0;
int rotate_lr_hand = 0;
int rotate_ul_hand = 0;
int rotate_ll_hand = 0;
int rotate_stand_bottom = 0;
int rotate_blades = 0;
int rotate_split = 0;
int rotate_sides = 0;
int rotate_tyre = 0;
int orient_tyre = 0;
float translate_stand_bottom = 0;
float lhand_y = 0;
float rhand_y = 0;
float t_head_y = 0;
float t_head_z = 0;
float translate_blades = 0;
float gun_rotate = 0;
int rotate_ur_x = 0;
int rotate_ul_x = 0;
float tilt_left = 0;
float tilt_down = 0;
int movement_flag = 0;
float pre_move_x = 0;
float pre_move_y = 0;
float pre_move_z = 0;
int camera_number = 0;
int rotate_ball = 0;


namespace csX75
{
  //! Initialize GL State
  void initGL(void)
  {
    //Set framebuffer clear color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    //Set depth buffer furthest depth
    glClearDepth(1.0);
    //Set depth test to less-than
    glDepthFunc(GL_LESS);
    //Enable depth testing
    glEnable(GL_DEPTH_TEST); 
    //Enable Gourard shading
    glShadeModel(GL_SMOOTH);
  }
  
  //!GLFW Error Callback
  void error_callback(int error, const char* description)
  {
    std::cerr<<description<<std::endl;
  }
  
  //!GLFW framebuffer resize callback
  void framebuffer_size_callback(GLFWwindow* window, int width, int height)
  {
	if (height == 0) height =1;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    //!Resize the viewport to fit the window size - draw to entire window
    glViewport(0, 0, width, height);
    double aspect;
    gluPerspective(120,(double)width/(double)height, 0.1 , 20.0);
   
  }
  
  //!GLFW keyboard callback
  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
  {
    //!Close the window if the ESC key was pressed
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
      glfwSetWindowShouldClose(window, GL_TRUE);
    }
    if (key == GLFW_KEY_1 && action == GLFW_PRESS){
      rotate_angle = rotate_angle + 5;
    }
    if (key == GLFW_KEY_2 && action == GLFW_PRESS){
      rotate_angle = rotate_angle - 5;
    }
    if (key == GLFW_KEY_3 && action == GLFW_PRESS){
      rotate_x = rotate_x + 5;
    }
    if (key == GLFW_KEY_4 && action == GLFW_PRESS){
      rotate_x = rotate_x - 5;
    }
    
    if (key == GLFW_KEY_5 && action == GLFW_PRESS){
      if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL)) {
        glDisable(GL_LIGHT0);
      }
      else glEnable(GL_LIGHT0);
    }
    
    if (key == GLFW_KEY_UP && action == GLFW_PRESS){
      movement_flag=1;
    }
    
    if (key == GLFW_KEY_DOWN && action == GLFW_PRESS){
      movement_flag =2;
    }
    
    if (key == GLFW_KEY_LEFT && action == GLFW_PRESS){
      tilt_left = tilt_left - 5;
      std::cout<<"tilt_left "<<tilt_left<<std::endl;
    }
    
    if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS){
      tilt_left = tilt_left + 5;
      std::cout<<"tilt_left "<<tilt_left<<std::endl;
    }
    
    if (key == GLFW_KEY_6 && action == GLFW_PRESS){
      tilt_down = tilt_down - 5;
    }
    
    if (key == GLFW_KEY_7 && action == GLFW_PRESS){
      tilt_down = tilt_down + 5;
    }
    
     if (key == GLFW_KEY_9 && action == GLFW_PRESS){
      camera_number = camera_number + 1;
    }
    
    if (key == GLFW_KEY_A && action == GLFW_PRESS){
      if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL)) {
        rotate_ul_angle = rotate_ul_angle - 5;
      }
      else rotate_ul_angle = rotate_ul_angle + 5;
    }
    
    if (key == GLFW_KEY_S && action == GLFW_PRESS){
      if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL)) {
        rotate_ur_angle = rotate_ur_angle - 5;
      }
      else rotate_ur_angle = rotate_ur_angle + 5;
    }
    
    if (key == GLFW_KEY_V && action == GLFW_PRESS){
      if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL)) {
        rotate_tyre = rotate_tyre - 5;
      }
      else rotate_tyre= rotate_tyre + 5;
    }
    
    if (key == GLFW_KEY_C && action == GLFW_PRESS){
      if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL)) {
        orient_tyre = orient_tyre - 5;
      }
      else orient_tyre= orient_tyre + 5;
    }
    
    if (key == GLFW_KEY_D && action == GLFW_PRESS){
      if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL)) {
        ur_x = ur_x - 0.01;
      }
      else ur_x = ur_x + 0.01;
    }
    
    if (key == GLFW_KEY_F && action == GLFW_PRESS){
      if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL)) {
        ul_x = ul_x - 0.01;
      }
      else ul_x = ul_x + 0.01;
    }
      
    if (key == GLFW_KEY_P && action == GLFW_PRESS){
      if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL)) {
        rotate_ur_x = rotate_ur_x - 5;
      }
      else rotate_ur_x = rotate_ur_x + 5;
    }
      
    if (key == GLFW_KEY_O && action == GLFW_PRESS){
      if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL)) {
        rotate_ul_x = rotate_ul_x - 5;
      }
      else rotate_ul_x = rotate_ul_x + 5;
    }
    
    if (key == GLFW_KEY_Q && action == GLFW_PRESS){
      if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL)) {
        rhand_y = rhand_y - 0.01;
      }
      else rhand_y = rhand_y + 0.01;
    }
    
    if (key == GLFW_KEY_W && action == GLFW_PRESS){
      if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL)) {
        lhand_y = lhand_y - 0.01;
      }
      else lhand_y = lhand_y + 0.01;
    }
    
    if (key == GLFW_KEY_I && action == GLFW_PRESS){
      if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL)) {
        t_head_y = t_head_y - 0.01;
      }
      else t_head_y = t_head_y + 0.01;
    }
    
    if (key == GLFW_KEY_J && action == GLFW_PRESS){
      if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL)) {
        rotate_split = rotate_split - 5;
      }
      else rotate_split = rotate_split + 5;
    }

    if (key == GLFW_KEY_K && action == GLFW_PRESS){
      if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL)) {
        translate_blades = translate_blades - 0.01;
      }
      else translate_blades = translate_blades + 0.01;
    }
    
    if (key == GLFW_KEY_Z && action == GLFW_PRESS){
      if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL)) {
        gun_rotate = gun_rotate - 0.01;
      }
      else gun_rotate = gun_rotate + 0.01;
    }
    
    if (key == GLFW_KEY_L && action == GLFW_PRESS){
      if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL)) {
        rotate_blades = rotate_blades - 5;
      }
      else rotate_blades = rotate_blades + 5;
    }
        
    if (key == GLFW_KEY_G && action == GLFW_PRESS){
      if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL)) {
        rotate_lr_angle = rotate_lr_angle - 5;
      }
      else rotate_lr_angle = rotate_lr_angle + 5;
    }
    
    if (key == GLFW_KEY_H && action == GLFW_PRESS){
      if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL)) {
        rotate_ll_angle = rotate_ll_angle - 5;
      }
      else rotate_ll_angle = rotate_ll_angle + 5;
    }
    
    
    if (key == GLFW_KEY_M && action == GLFW_PRESS){
      if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL)) {
        t_head_z = t_head_z - 0.01;
      }
      else  t_head_z = t_head_z + 0.01;
    }
    
    if (key == GLFW_KEY_B && action == GLFW_PRESS){
      if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL)) {
        rotate_sides = rotate_sides - 5;
      }
      else  rotate_sides = rotate_sides + 5;
    }
        
    if (key == GLFW_KEY_E && action == GLFW_PRESS){
      if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL)) {
        rotate_ur_hand = rotate_ur_hand - 5;
      }
      else rotate_ur_hand = rotate_ur_hand + 5;
    }
    
    if (key == GLFW_KEY_R && action == GLFW_PRESS){
      if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL)) {
        rotate_lr_hand = rotate_lr_hand - 5;
      }
      else rotate_lr_hand = rotate_lr_hand + 5;
    }
    
    if (key == GLFW_KEY_Y && action == GLFW_PRESS){
      if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL)) {
        rotate_ul_hand = rotate_ul_hand - 5;
      }
      else rotate_ul_hand = rotate_ul_hand + 5;
    }
    
    if (key == GLFW_KEY_U && action == GLFW_PRESS){
      if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL)) {
        rotate_ll_hand = rotate_ll_hand - 5;
      }
      else rotate_ll_hand = rotate_ll_hand + 5;
    }
    
    if (key == GLFW_KEY_T && action == GLFW_PRESS){
      if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL)) {
        rotate_ul_angle = 0;
        rotate_ur_angle = 0;
        ur_x = 0;
        ul_x = 0;
        rotate_lr_angle = 0;
        rotate_ll_angle = 0;
        rhand_y = 0;
        lhand_y = 0;
        rotate_ur_hand = 0;
        rotate_lr_hand = 0;
        rotate_ul_hand = 0;
        rotate_ll_hand = 0;
        rotate_split = 0;
        translate_blades = 0;
        rotate_blades = 0;
        gun_rotate = 0;
        rotate_stand_bottom = 0;
        translate_stand_bottom = 0;
        t_head_y = 0;
        t_head_z = 0;
        rotate_x = 0;
        rotate_angle = 0;
        rotate_sides = 0;
        rotate_tyre = 0;
        orient_tyre = 0;
      }
      else {
        rotate_ul_angle = 2*5;
        rotate_ur_angle = -2*5;
        ur_x = 0.01;
        ul_x = -0.01;
        rotate_lr_angle = 90;
        rotate_ll_angle = -90;
        rhand_y = - 26*0.01;
        lhand_y = - 26*0.01;
        rotate_ur_hand =  - 9*5;
        rotate_lr_hand = 26*5;
        rotate_ul_hand = 9*5;
        rotate_ll_hand =  - 26*5;
        rotate_split =  8*5;
        translate_blades = 20*0.01;
        rotate_blades = 18*5;
        gun_rotate = 26*0.01;
        rotate_stand_bottom = 15*5;
        translate_stand_bottom =8*0.01;
        t_head_y =  - 23*0.01;
        t_head_z = 3*0.01;
        rotate_x = - 16*5;
        rotate_angle =  - 12*5;
        rotate_sides = 9*5;
        rotate_tyre = 10*5;
        orient_tyre = 18*5;
      }
    }
    
  }
  
};  
  


