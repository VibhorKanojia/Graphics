#ifndef _TRANSFORMER_HPP_
#define _TRANSFORMER_HPP_

#define precision 36
#define precision2 20
#define torso 1
#define head 2
#define ru_leg 3
#define rl_leg 4
#define joint 5
#define connectors 6
#define rl_hand 7
#define ru_hand 8
#define blade 9
#define tail 10
#define stand 11
#define tyre 12
#define bomb 13
#define legs 14

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
extern float pre_move_x, pre_move_y, pre_move_z, start_time;
extern int camera_number;
extern bool playback;
extern float torso_move_z;
extern float rotate_ur_hand_x, rotate_ul_hand_x;

struct vertex_vec {
  GLdouble x;
  GLdouble y;
  GLdouble z;
};

typedef struct vertex_vec vertex_vec;  

class transformer {
  public:
    GLuint texture[20];
    float torso_x;
    float torso_y;
    float torso_z;
    float conn_x;
    float conn_y;
    float conn_z;
    float head_x;
    float head_y;
    float head_z;
    float upper_leg_x;
    float upper_leg_y;
    float upper_leg_z;
    float upper_leg_w1;
    float upper_leg_w2;
    float lower_leg_x;
    float lower_leg_y;
    float lower_leg_z; 
    float upper_hand_x;
    float upper_hand_y;
    float upper_hand_z;
    float lower_hand_x;
    float lower_hand_y;
    float lower_hand_z;

    int cam_pos;
    
    transformer();
    void load_textures();
    vertex_vec CalcNormal(vertex_vec v1, vertex_vec v2);
    void DrawCircle(float r,float Z);  
    void DrawTransformer();
    void shearMatrix(int shearX, int shearY);
    void DrawTyre(float r,float width,float z);
    void DrawSphere(float r,int flag);
    void DrawJoint(float r,float z);
    void DrawLayer(float R, float z1, float z2,int flag,int texture_flag);
    void DrawTail(float s1, float s2, float s3, float delta);
    void DrawCube(float s);
    void DrawTrapezoid(float l1, float l2, float h);
    void struct_tyre(void);
    void struct_torso(void);
    void struct_connectors(void);
    void struct_head(void);
    void struct_blade(void);
    void struct_legs(void);
    void struct_right_upper_leg(void);
    void struct_tail_fan(void);
    void struct_right_lower_leg(void);
    void struct_right_upper_hand(void);
    void struct_right_lower_hand(void);
    void struct_joint(void);
    void renderGL(void);
    void DrawHead(float s);
    void resetCamera(void);
    void DrawBackground(void);
    void DrawBomb(void);
    void struct_bomb(void);
};
#endif














