#include "gl_framework.hpp"
#include "image.hpp"
#include "transformer.hpp"
#include "background.hpp"


int main(int argc, char** argv)
{
  //! The pointer to the GLFW window
  GLFWwindow* window;

  //! Setting up the GLFW Error callback
  glfwSetErrorCallback(csX75::error_callback);

  //! Initialize GLFW
  if (!glfwInit())
    return -1;

  //! Create a windowed mode window and its OpenGL context
  window = glfwCreateWindow(800, 800, "CS475/CS675 OpenGL Framework", NULL, NULL);
  if (!window)
    {
      glfwTerminate();
      return -1;
    }
  
  //! Make the window's context current 
  glfwMakeContextCurrent(window);

  //Initialize GLEW
  GLenum err = glewInit();
  if (GLEW_OK != err)
    {
      //Problem: glewInit failed, something is seriously wrong.
      std::cerr<<"GLEW Init Failed : %s"<<std::endl;
    }

  //Print and see what context got enabled
  std::cout<<"Vendor: "<<glGetString (GL_VENDOR)<<std::endl;
  std::cout<<"Renderer: "<<glGetString (GL_RENDERER)<<std::endl;
  std::cout<<"Version: "<<glGetString (GL_VERSION)<<std::endl;
  std::cout<<"GLSL Version: "<<glGetString (GL_SHADING_LANGUAGE_VERSION)<<std::endl;

  //Keyboard Callback
  glfwSetKeyCallback(window, csX75::key_callback);
  //Framebuffer resize callback
  glfwSetFramebufferSizeCallback(window, csX75::framebuffer_size_callback);

  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  //Initialize GL state
  csX75::initGL();
  glEnable(GL_TEXTURE_2D);			// Enable Texture Mapping
  glClearDepth(1.0);				// Enables Clearing Of The Depth Buffer
  glDepthFunc(GL_LESS);			// The Type Of Depth Test To Do
  glEnable(GL_DEPTH_TEST);			// Enables Depth Testing
  glShadeModel(GL_FLAT);			// Enables Smooth Color Shading
  glEnable(GL_NORMALIZE);
  //glEnable(GL_COLOR_MATERIAL);
  glMatrixMode(GL_PROJECTION);
  glMatrixMode(GL_MODELVIEW); 
  //LoadGLTextures();				// Load The Texture(s)
  transformer T;
  background b;
  b.load_textures();
  T.load_textures();
  T.struct_head();
  T.struct_torso();
  T.struct_right_upper_leg();
  T.struct_right_lower_leg();
  T.struct_right_upper_hand();
  T.struct_right_lower_hand();
  T.struct_joint();
  T.struct_connectors();
  T.struct_blade();	
  T.struct_tail_fan();
  T.struct_tyre();
  b.struct_ground();
  b.struct_building();
  
  
  
  GLfloat diffuse1[] = {0.0,0.5,0.8,1.0};
  GLfloat light1_pos[] = {-0.5,-0.4,-0.4,1.0};
  GLfloat specular2[] = {1.0,1.0,1.0,1.0};
  GLfloat ambient2[] = {0.1,0.1,0.1,1.0};
  GLfloat diffuse2[] = {0.0,1.0,0.3,0.0};
  GLfloat light2_pos[] = {0.2,-0.5,0.0,1.0};
  GLfloat diffuse3[] = {0.0,0.5,0.8,1.0};
  GLfloat light3_pos[] = {-0.5,-0.8,0.4,0.0};
  GLfloat specular4[] = {1.0,1.0,1.0,1.0};
  GLfloat diffuse4[] = {0.5,0.0,0.0,1.0};
  GLfloat light4_pos[] = {0.05,0.9,0.0,1.0};
  glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);
  glLightfv(GL_LIGHT2, GL_POSITION, light2_pos);
  glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse2);
  glLightfv(GL_LIGHT2, GL_SPECULAR, specular2);
  glLightfv(GL_LIGHT2, GL_AMBIENT, ambient2);
  glLightfv(GL_LIGHT3, GL_POSITION, light3_pos);
  glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuse3);
  glLightfv(GL_LIGHT4, GL_POSITION, light4_pos);
  glLightfv(GL_LIGHT4, GL_DIFFUSE, diffuse4);
  glLightfv(GL_LIGHT4, GL_SPECULAR, specular4);
  glEnable(GL_LIGHTING);
  //glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  //glEnable(GL_LIGHT2);
  //glEnable(GL_LIGHT3);
  glEnable(GL_LIGHT4);
  //glShadeModel(GL_SMOOTH);
  
  glClearColor(.043,0.62,0.75,1);
  // Loop until the user closes the window
  while (glfwWindowShouldClose(window) == 0)
    {
       
      // Render here
       
      T.renderGL();

      // Swap front and back buffers
      glfwSwapBuffers(window);
      
      // Poll for and process events
      glfwPollEvents();
    }
  
  glfwTerminate();
  return 0;
}

