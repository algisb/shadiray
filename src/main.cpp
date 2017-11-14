#include <stdio.h>
#include <stdlib.h>
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Config.h"
#include "Input.h"
#include "Core.h"
#include "Time.h"


static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) 
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    
    kelp::Input::update(key, scancode, action, mods);
        
}
static void error_callback(int error, const char *description)
{
    fputs(description, stderr);
}




int main(void)
{
    GLFWwindow *window;
        
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit(EXIT_FAILURE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    window = glfwCreateWindow(
        kelp::Config::s_windowWidth, 
        kelp::Config::s_windowHeight,
        "kelp-engine", 
        NULL, 
        NULL);
    if (!window) 
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    
    glewExperimental = GL_TRUE;
    glewInit();
    printf( "VENDOR = %s\n", glGetString( GL_VENDOR ) ) ;
    printf( "RENDERER = %s\n", glGetString( GL_RENDERER ) ) ;
    printf( "VERSION = %s\n", glGetString( GL_VERSION ) ) ;
    //////////////////////////////////////////////////////////////
    kelp::Core * core = new kelp::Core();
    while (!glfwWindowShouldClose(window))
    {
        kelp::Time::calc();//start timer
        glfwPollEvents();

        core->update();
        
        glfwSwapBuffers(window);
        kelp::Input::clear();
        
        
        //NOT SO FAST
        //              .--._
        //               `.  `-.
        //               .-'    `.
        //             .'      _..:._
        //            `.  .--.'      `.
        //            _.'  \.      .--.\
        //          .'      |     |    |
        //         `--.     |  .--|    D
        //             `;  /'\/   ,`---'@
        //           .'  .'   '._ `-.__.'
        //         .'  .'      _.`---'
        //       .'--''   .   `-..__.--.
        //    ~-=  =-~_-   `-..___(  ===;
        //    ~-=  - -    .'       `---'
        kelp::Time::calcEnd();//end timer
    }

    
    delete core;
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
